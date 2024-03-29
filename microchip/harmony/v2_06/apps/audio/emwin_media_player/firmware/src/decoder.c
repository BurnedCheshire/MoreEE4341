/*******************************************************************************
  Universal Audio Decoders Demo

  Company:
    Microchip Technology Inc.

  File Name:
    decoder.c

  Summary:
   Contains the functional implementation of decoder functions.

  Description:
   This file contains the functional implementation of decoder functions.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2016-2017 released Microchip Technology Inc.  All rights reserved.

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

#define DECODER_C
#include "decoder.h"
#include "app.h"



static DECODER_TYPE decoderType;
uint32_t decoderBitrate;
uint32_t decoderSamplerate;
int sampling_frequency;

////////////////////////////////////////////////////////////////////////////////


void DECODER_Initialize ( uint8_t type )
{
    uint8_t frameHeader[WAV_HEADER_SIZE]; // 44 bytes
   
    decoderType = DECODER_TYPE_UNKNOWN;
    APP_SDCARD_AUDIO_PLAYER *AppDataAudioPlayerPtr = (APP_SDCARD_AUDIO_PLAYER *)APP_SDCARD_AUDIO_Player_GetInstance();
    
    switch ( type )
    {            
        case APP_SDCARD_AUDIO_DECODER_WAV:
            AppDataAudioPlayerPtr->currentStreamType = APP_SDCARD_AUDIO_STREAM_WAV;
            decoderType = DECODER_TYPE_WAV;
            APP_SDCARD_AUDIO_Card_ReadCurrentFile(frameHeader, WAV_HEADER_SIZE);            
            AppDataAudioPlayerPtr->readBytes = WAV_INPUT_BUFFER_SIZE;             
            AppDataAudioPlayerPtr->readbyte_flag = true;
            WAV_Initialize (frameHeader);            
            DECODER_EventHandler ( DECODER_EVENT_STREAM_START, 0 );            
            DECODER_EventHandler ( DECODER_EVENT_SAMPLERATE, WAV_GetSampleRate() );
            DECODER_EventHandler ( DECODER_EVENT_BITRATE, WAV_GetBitRate() );
            DECODER_EventHandler ( DECODER_EVENT_TRACK_TIME, WAV_GetDuration());
            
            break;            
            
        case APP_SDCARD_AUDIO_DECODER_UNKNOWN:
            break;
    }
}

bool DECODER_Decode ( uint8_t *input, uint16_t inSize, uint16_t *read, int16_t *output, uint16_t *written )
{
    *read = 0;
    *written = 0;
    switch ( decoderType )
    {
        case DECODER_TYPE_WAV:
            if( WAV_Decoder (input,inSize,read,output,written)==true)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;            

        case DECODER_TYPE_UNKNOWN:
            break;
        default:
            break;
    }

    return ( true );
}

uint32_t DECODER_GetCurrentValidAudioSize()
{
    uint32_t ret = 0;
    switch(decoderType)
    {
        case DECODER_TYPE_WAV:
            ret = WAV_GetAudioSize();
            break;
        case DECODER_TYPE_MP3:
            
            break;
        default:
            ret = 0;
            break;
    }
    return ret;
}

/////////////////////////////////////////////////////////////
uint32_t GetDecodeBitRate(void)
{
    return ( (uint32_t) decoderBitrate );
}

/////////////////////////////////////////////////////////////
uint32_t GetDecodeSamplingRate ( void )
{
    return ( (uint32_t) decoderSamplerate );
}