/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
  
  File Name:
    app_freq_spectrum_task.c

  Summary:
    This file contains the functional implementation of the frequency spectrum
    application.

  Description:
    This file contains the functional implementation of the frequency spectrum
    application. In MIC mode, the frequency spectrum is calculated on the audio
    data received from the microphone. When in TONE mode, the frequency spectrum
    is calculated on the audio data generated by the tone generator application.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "app_freq_spectrum_task.h"
#include "app_microphone_task.h"
#include "app_speaker_task.h"
#include "app_tone_generator.h"
#include <math.h>


#define LOG10_65536     4.816479930

#define INV_LOG2_10_Q1DOT31 UINT64_C(0x268826a1) // Inverse log base 2 of 10
#define LOG10_2 0x00004D10 // to convert dB into dBFS add this to output of log10fix

int32_t log2fix (int32_t X32, size_t precision)
{
    size_t iBit; // index to current fractional bit
    int32_t bit = 1U << (precision - 1); // current fractional bit value
    int32_t Y32 = 0;
    uint32_t x;

    if (precision < 1 || precision > 31 || X32 < 0) {
        return INT32_MAX; // indicates an error
    }
    x = X32;

    if (x == 0) {
        return INT32_MIN; // represents negative infinity
    }

    while (x < 1U << precision) {
        x <<= 1;
        Y32 -= 1U << precision;
    }

    while (x >= 2U << precision) {
        x >>= 1;
        Y32 += 1U << precision;
    }

    uint64_t z = x;

    // iBit = 0 corresponds to MSB of LS word (fractional part)
    for (iBit = 0; iBit < precision; iBit++) {
        z = z * z >> precision;
        if (z >= 2U << precision) {
            z >>= 1;
            Y32 += bit;
        }
        bit >>= 1;
    }

    return Y32;

}//log2fix

int32_t log10fix (int32_t x, size_t precision)
{
    int64_t t;
    int32_t log2x;
    int32_t yout;

    x = x < 0 ? -x : x; // Make sure x >= 0

    log2x = log2fix(x, precision);
    if     ( log2x == INT32_MIN )
    {
        yout = INT32_MIN;
    }
    else if ( log2x == INT32_MAX )
    {
        yout = INT32_MAX;
    }
    else
    {
        t =  log2x * INV_LOG2_10_Q1DOT31;
        if ( t > 0 )
        {
            yout =  t >> 31;
        }
        else
        {
            yout =  -(-t>>31);
        }
    }

    return yout;

}//log10fix


/*--------------------------------------------------*/
static APP_FREQ_SPECTRUM_TASK_DATA appSpectrumTaskData;

static WINDOW_FUNCTION windowFunc[WINDOW_TYPE_MAX] = 
{
    [WINDOW_TYPE_RECT] =   {
                .init = NULL,
                .func = NULL, 
                .compFactor = RECT_WINDOW_COMPN,
                .isWindowComputed = false,
            },
    [WINDOW_TYPE_HANN] =   {
                .init = DSP_TransformWinInit_Hann16,
                /*
                 func calculates the window function every time it is called, 
                 and hence takes up CPU time. Instead, the init function can 
                 be called once to generate the window function. The generated
                 window function can then be multiplied with the input data, at 
                 run-time, to generate windowed output
                 */
                .func = DSP_TransformWindow_Hann16, 
                .compFactor = HANN_WINDOW_COMPN,
                .isWindowComputed = false,
            },
    [WINDOW_TYPE_BLACKMAN] =   {
                .init = DSP_TransformWinInit_Black16,
                /*
                 func calculates the window function every time it is called, 
                 and hence takes up CPU time. Instead, the init function can 
                 be called once to generate the window function. The generated
                 window function can then be multiplied with the input data, at 
                 run-time, to generate windowed output
                 */
                .func = DSP_TransformWindow_Black16, 
                .compFactor = BLACKMAN_WINDOW_COMPN,
                .isWindowComputed = false,
            },
    [WINDOW_TYPE_HAMMING] =   {
                .init = DSP_TransformWinInit_Hamm16,
                /*
                 func calculates the window function every time it is called, 
                 and hence takes up CPU time. Instead, the init function can 
                 be called once to generate the window function. The generated
                 window function can then be multiplied with the input data, at 
                 run-time, to generate windowed output
                 */
                .func = DSP_TransformWindow_Hamm16, 
                .compFactor = HAMMING_WINDOW_COMPN,
                .isWindowComputed = false,
            },        
};

static uint32_t fftMag[NUM_POINT_FFT/2];
static int16c   fftInput[NUM_POINT_FFT];
static int16c   fftOutput[NUM_POINT_FFT];
static int16c   scratch[NUM_POINT_FFT];
static int16c   fftCoefs[NUM_POINT_FFT];
static float  winFunc[NUM_POINT_FFT];

static const OCTAVE_TABLE octaveTable[SAMPLING_FREQ_MAX] =
{
    //SAMPLING_FREQ_48_KHZ
    {
        {
            {100,       8,       10},					//0
            {125,       10,      12},					//1
            {158,       12,      15},					//2
            {200,       15,      19},					//3
            {251,       19,      24},					//4
            {317,       24,      30},					//5
            {400,       30,      38},					//6
            {503,       38,      48},                   //7
            {634,       48,      61},                   //8
            {800,       61,      77},                   //9
            {1007,      77,      97},                   //10
            {1269,      97,      122},                  //11
            {1600,      122,     153},                  //12
            {2015,      153,     193},                  //13
            {2539,      193,     243},                  //14
            {3200,      243,     307},                  //15
            {4031,      307,     386},                  //16
            {5079,      386,     487},                  //17
            {6400,      487,     613},                  //18
            {8063,      613,     772},                  //19
            {10159,     772,     973},                  //20	
            {12800,     973,     1226},                 //21
            {16126,     1226,    1545},                 //22
            {20318,     1545,    1946},                 //23
        }        
    },
    //SAMPLING_FREQ_44_1_KHZ
    {
        {
            {100,       8,       10},					//0
            {125,       10,      13},					//1
            {158,       13,      17},					//2
            {200,       17,      21},					//3
            {251,       21,      26},					//4
            {317,       26,      33},					//5
            {400,       33,      42},					//6
            {503,       42,      53},                   //7
            {634,       53,      66},                   //8
            {800,       66,      83},                   //9
            {1007,      83,      105},                  //10
            {1269,      105,     132},                  //11
            {1600,      132,     167},                  //12
            {2015,      167,     210},                  //13
            {2539,      210,     265},                  //14
            {3200,      265,     334},                  //15
            {4031,      334,     420},                  //16
            {5079,      420,     530},                  //17
            {6400,      530,     667},                  //18
            {8063,      667,     841},                  //19
            {10159,     841,     1059},                 //20	
            {12800,     1059,    1334},                 //21
            {16126,     1334,    1681},                 //22
            {20318,     1681,    2048},                 //23                    
        }
    },
};

static void APP_FREQ_SPECTRUM_InitEvListners(void)
{
    uint8_t i;
    
    for (i = 0; i < FREQ_SPECTRUM_MAX_LISTNERS; i++)
    {
        appSpectrumTaskData.eventListners[i] = NULL;
    }
}

bool APP_FREQ_SPECTRUM_RegisterCallback(FFT_SPECTRUM_EVENT_CALLBACK evHandler)
{    
    bool isSuccess = false;
    uint8_t i;
    
    if (evHandler)
    {
        for (i = 0; i < FREQ_SPECTRUM_MAX_LISTNERS; i++)
        {
            if (NULL == appSpectrumTaskData.eventListners[i])
            {
                appSpectrumTaskData.eventListners[i] = evHandler;
                isSuccess = true;
                break;
            }
        }
    }           
        
    return isSuccess;
}

bool APP_FREQ_SPECTRUM_UnRegisterCallback(FFT_SPECTRUM_EVENT_CALLBACK evHandler)
{    
    bool isSuccess = false;
    uint8_t i;
    
    if (evHandler)
    {
        for (i = 0; i < FREQ_SPECTRUM_MAX_LISTNERS; i++)
        {
            if (appSpectrumTaskData.eventListners[i] == evHandler)
            {
                appSpectrumTaskData.eventListners[i] = NULL;
                isSuccess = true;
                break;
            }
        }
    }
    
    return isSuccess;
}

static void APP_FREQ_SPECTRUM_NotifyListners(
    FREQ_SPECTRUM_EVENT_TYPE event,
    const void* const pEventData
)
{
    uint8_t i;
    
    for (i = 0; i < FREQ_SPECTRUM_MAX_LISTNERS; i++)
    {
        if (appSpectrumTaskData.eventListners[i])
        {
            appSpectrumTaskData.eventListners[i](event, pEventData);
        }
    }    
}

static inline uint8_t APP_FREQ_SPECTRUM_DBFS_To_DisplayValue(float dBFSValue)
{
    uint8_t displayValue = 0;
    
    displayValue = 100.0 - (dBFSValue * 100.0)/(float)appSpectrumTaskData.lowDBFSLimit;
    
    return displayValue;
}

static void APP_FREQ_SPECTRUM_CalcSpectrumBandValues(
    const uint32_t* const pBuffer, 
    SAMPLING_FREQ sampFreq
)
{
	uint32_t i,j;
    
    const OCTAVE_TABLE* const pOctaveTable = &octaveTable[sampFreq];
    float value[MAX_FREQ_SPECTRUM_BANDS];    
    float signalFSValueIndB = 20*(log10fix(appSpectrumTaskData.signalFSValue, 16)/65536.0 + LOG10_65536);        
    
	for (i = 0; i < MAX_FREQ_SPECTRUM_BANDS; i++)
	{
		value[i] = 0;
		for (j= pOctaveTable->band[i].sampleLow; j < pOctaveTable->band[i].sampleHigh; j++)
		{			
            value[i] += pBuffer[j]*pBuffer[j];
		}		
	}

    //Calculate in dBFS
	for (i = 0; i < MAX_FREQ_SPECTRUM_BANDS; i++)
	{	
        if (value[i])
        {                                    
            //value = 10*(log10(a) + log10(b)) - singalFSValudeIndB
            value[i] = 10*(log10fix(value[i], 16)/65536.0 + LOG10_65536) - signalFSValueIndB;
        }
        else
        {
            value[i] = appSpectrumTaskData.lowDBFSLimit;
        }
        
        if (value[i] < appSpectrumTaskData.lowDBFSLimit)
		{
			value[i] = appSpectrumTaskData.lowDBFSLimit;
		}
        
        //Convert dBFS to display value
        appSpectrumTaskData.spectrumValue[i] = APP_FREQ_SPECTRUM_DBFS_To_DisplayValue(value[i]);
	}			
}

uint8_t APP_FREQ_SPECTRUM_GetSpectrumValueAtFreq(uint8_t freqBand)
{
    if (freqBand < MAX_FREQ_SPECTRUM_BANDS)
    {
        return appSpectrumTaskData.spectrumValue[freqBand];
    }
    else
    {
        return 0;
    }
}

static void APP_FREQ_SPECTRUM_CalcFFT(
    int16c* const pFFTInput, 
    int16c* const pFFTOutput, 
    int16c* const pFFTCoefs, 
    int16_t numPointFFT
)
{       
    DSP_TransformFFT16(pFFTOutput, pFFTInput, pFFTCoefs, scratch, 12);       
}

/*
 * This function accepts Mono or Stereo audio input
 * For Mono, the channel is ignored
 * For Stereo, the channel indicates whether Left or Right channel data is considered for 
 * frequency analysis.
 */
static void APP_FREQ_SPECTRUM_PrepareChannelData(
    const int16_t* const pAudioInput, 
    int16_t* const pChannelOutput, 
    uint32_t numData, 
    AUDIO_TYPE audioType,
    AUDIO_CHANNEL channel
)
{
    uint32_t i = 0;
    uint32_t j = 0;    
        
    if (AUDIO_TYPE_MONO == audioType)
    {        
        for (i = 0; i < numData; i++)
        {
            pChannelOutput[i] = pAudioInput[i];
        }        
    }
    else
    {
        for (i = 0, j = 0; i < numData; i++, j+=2)
        {
            pChannelOutput[i] = pAudioInput[channel + j];
        }
    }
    
}

static void APP_FREQ_SPECTRUM_CalcFFTMagnitude(
    const int16c* const pInBuffer, 
    uint32_t* const pOutBuffer, 
    WINDOW_TYPE winType
)
{
    uint32_t k;
    float value;
        
    for (k = 0; k < (NUM_POINT_FFT/2); k++)
    {
        value = (uint32_t)pInBuffer[k].re * (uint32_t)pInBuffer[k].re +
                (uint32_t)pInBuffer[k].im * (uint32_t)pInBuffer[k].im;
        value = powf(value, 0.5);
        
        //Ignore values below -80 dBFS
        if (value < 3)
        {
            value = 0;
        }
        
        pOutBuffer[k] = value * (2.0 * windowFunc[winType].compFactor);    
    }
}

void APP_FREQ_SPECTRUM_ConfigInputAudio(
    AUDIO_TYPE audioType, 
    SAMPLING_FREQ samplingFreq
)
{
    appSpectrumTaskData.audioInputConfig.audioType = audioType;
    appSpectrumTaskData.audioInputConfig.samplingFreq = samplingFreq;
}

static inline bool APP_FREQ_SPECTRUM_IsTaskIdle(void)
{
    bool isIdle = false;
    
    if (FREQ_SPECTRUM_STATE_WAIT_FOR_INPUT == appSpectrumTaskData.state)
    {
        isIdle = true;
    }
    
    return isIdle;
}

static void APP_FREQ_SPECTRUM_SetFFTInput(const int16_t* const pData)
{                    
    if (true == APP_FREQ_SPECTRUM_IsTaskIdle())
    {
        appSpectrumTaskData.pAudioData = pData;                                  
        appSpectrumTaskData.isAudioSamplesAvailable = true;      
    }    
}

static bool APP_FREQ_SPECTRUM_IsAudioDataAvailable(void)
{
    bool isAvailable = false;
    if (true == appSpectrumTaskData.isAudioSamplesAvailable)
    {
        appSpectrumTaskData.isAudioSamplesAvailable = false;
        isAvailable = true;
    }
    return isAvailable;
}

static void APP_FREQ_SPECTRUM_PrepareFFTData(
    const int16_t* const pInput, 
    int16c* const pOutput, 
    uint32_t numData
)
{
	uint32_t i = 0;
        
    for (i = 0; i < numData; i++)
    {
        pOutput[i].re = pInput[i];
        pOutput[i].im = 0;
    }    
}

static void APP_FREQ_SPECTRUM_FRAC_TO_FLOAT(
    int16_t* pFraction,
    float* pFloat,
    uint32_t numData
)
{
    uint32_t i;
    
    for (i = 0; i < numData; i++)
    {                        
        pFloat[i] = (float) ((float)pFraction[i] /32768);        
    }
}

static void APP_FREQ_SPECTRUM_ApplyWindowFunction(
    int16_t* const pInput, 
    int16_t* const pOutput, 
    uint32_t numData, 
    WINDOW_TYPE winType
)
{
    uint32_t i;    
    
    if (WINDOW_TYPE_RECT == winType)
    {
        return;
    }
        
    if (false == windowFunc[winType].isWindowComputed)
    {
        int16_t* pTempFrac = (int16_t*)fftOutput;
        
        if (windowFunc[winType].init)
        {
            windowFunc[winType].init(pTempFrac, NUM_POINT_FFT);    
            APP_FREQ_SPECTRUM_FRAC_TO_FLOAT(pTempFrac, winFunc, NUM_POINT_FFT);
        }                
        windowFunc[winType].isWindowComputed = true;
    }
    
    if (windowFunc[winType].func)
    {
        for (i = 0; i < numData; i++)
        {
            pOutput[i] = pInput[i] * winFunc[i];
        }
    }
}

static void APP_FREQ_SPECTRUM_MicDataEventHandler(
    APP_MICROPHONE_EVENT eventType, 
    const void* const pEventData
)
{
    switch(eventType)
    {
        case APP_MICROPHONE_EVENT_DATA_AVAIL:
            APP_FREQ_SPECTRUM_SetFFTInput((const int16_t* const)pEventData);
            break;
        default:
            break;
    }    
}

static void APP_FREQ_SPECTRUM_SpeakerDataEventHandler(
    APP_SPEAKER_EVENT eventType, 
    const void* const pEventData
)
{
    switch(eventType)
    {
        case APP_SPEAKER_EVENT_DATA_AVAIL:
            APP_FREQ_SPECTRUM_SetFFTInput((const int16_t* const)pEventData);
            break;
        default:
            break;
    }    
}

void APP_FREQ_SPECTRUM_SetWindowType(WINDOW_TYPE winType)
{
    if (WINDOW_TYPE_MAX > winType)
    {
        appSpectrumTaskData.fftConfig.selectedWinType = winType;
        windowFunc[appSpectrumTaskData.fftConfig.selectedWinType].isWindowComputed = false;
    }
}

void APP_FREQ_SPECTRUM_TaskInitialize(void)
{
    appSpectrumTaskData.state = FREQ_SPECTRUM_STATE_INIT;
    appSpectrumTaskData.isAudioSamplesAvailable = false;
    appSpectrumTaskData.pAudioData = NULL;
    appSpectrumTaskData.fftConfig.selectedWinType = WINDOW_TYPE_HANN;
    appSpectrumTaskData.fftConfig.channel = AUDIO_CHANNEL_LEFT;
    APP_FREQ_SPECTRUM_InitEvListners();
    
    APP_TONE_GetAmplitudeRagneInDBFS(
        &appSpectrumTaskData.lowDBFSLimit, 
        &appSpectrumTaskData.highDBFSLimit
    );
    
    appSpectrumTaskData.signalFSValue = APP_TONE_GetFullScaleSignalValue();
}

void APP_FREQ_SPECTRUM_Task(void)
{            
    switch(appSpectrumTaskData.state)
    {
        case FREQ_SPECTRUM_STATE_INIT:
            DSP_TransformFFT16_setup(fftCoefs, 12);   
            
            APP_MICROPHONE_RegisterCallback(APP_FREQ_SPECTRUM_MicDataEventHandler);
            APP_SPEAKER_RegisterCallback(APP_FREQ_SPECTRUM_SpeakerDataEventHandler);
            
            appSpectrumTaskData.state = FREQ_SPECTRUM_STATE_WAIT_FOR_INPUT;
            break;
            
        case FREQ_SPECTRUM_STATE_WAIT_FOR_INPUT:            
            if (true == APP_FREQ_SPECTRUM_IsAudioDataAvailable())
            {     
                APP_FREQ_SPECTRUM_PrepareChannelData(
                    (const int16_t* const)appSpectrumTaskData.pAudioData, 
                    (int16_t* const)scratch, 
                    NUM_POINT_FFT, 
                    appSpectrumTaskData.audioInputConfig.audioType, 
                    appSpectrumTaskData.fftConfig.channel
                );                          
                appSpectrumTaskData.state = FREQ_SPECTRUM_STATE_WINDOW_INPUT;                               
            }                                    
            break;        
            
        case FREQ_SPECTRUM_STATE_WINDOW_INPUT:          
                        
            APP_FREQ_SPECTRUM_ApplyWindowFunction(
                (int16_t*)scratch, 
                (int16_t*)scratch, 
                NUM_POINT_FFT, 
                appSpectrumTaskData.fftConfig.selectedWinType
            );            
            appSpectrumTaskData.state = FREQ_SPECTRUM_STATE_PREPARE_INPUT;
            break;
        
        case FREQ_SPECTRUM_STATE_PREPARE_INPUT:
            
            APP_FREQ_SPECTRUM_PrepareFFTData(
                (int16_t*)scratch, 
                fftInput, 
                NUM_POINT_FFT
            );
            
            appSpectrumTaskData.state = FREQ_SPECTRUM_STATE_CALC_FFT;
            break;
            
        case FREQ_SPECTRUM_STATE_CALC_FFT: 
            
            APP_FREQ_SPECTRUM_CalcFFT(
                fftInput, 
                fftOutput, 
                fftCoefs, 
                NUM_POINT_FFT
            );                             
            
            appSpectrumTaskData.state = FREQ_SPECTRUM_STATE_CALC_POWERS;
            break;
            
        case FREQ_SPECTRUM_STATE_CALC_POWERS:
            
            APP_FREQ_SPECTRUM_CalcFFTMagnitude(
                fftOutput, 
                fftMag, 
                appSpectrumTaskData.fftConfig.selectedWinType
            );            
            appSpectrumTaskData.state = FREQ_SPECTRUM_STATE_FFT_DONE;
            break;
            
        case FREQ_SPECTRUM_STATE_FFT_DONE:
            
            APP_FREQ_SPECTRUM_CalcSpectrumBandValues(
                fftMag, 
                appSpectrumTaskData.audioInputConfig.samplingFreq
            );             
            APP_FREQ_SPECTRUM_NotifyListners(
                FREQ_SPECTRUM_EVENT_TYPE_FFT_RESULTS_READY, 
                NULL
            );
                        
            appSpectrumTaskData.state = FREQ_SPECTRUM_STATE_WAIT_FOR_INPUT;
            break;
    }    
}