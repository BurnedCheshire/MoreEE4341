/*******************************************************************************
  ADC Driver Initialization File

  File Name:
    drv_adc_hs_static.c

  Summary:
    This file contains source code necessary to initialize the IC driver.

  Description:
    This file contains source code necessary to initialize the system.  It
    implements the "DRV_ADC_Initialize" function, configuration bits, and allocates
    any necessary global system resources, such as the systemObjects structure
    that contains the object handles to all the MPLAB Harmony module objects in
    the system.
 *******************************************************************************/

/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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

// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************
#include "framework/driver/adc/drv_adc_static.h"
 
// *****************************************************************************
// *****************************************************************************
// Section: ADC Static Driver Functions
// *****************************************************************************
// *****************************************************************************
void DRV_ADC_Initialize(void)
{
    /* Select Power Mode */
	PLIB_ADCHS_Setup(
	DRV_ADC_ID_1,
	ADCHS_VREF_AVDD_AVSS,
	ADCHS_CHARGEPUMP_DISABLE,
	ADCHS_OUTPUT_DATA_FORMAT_INTEGER,
	false,
	ADCHS_FAST_SYNC_SYSTEM_CLOCK_DISABLE,
	ADCHS_FAST_SYNC_PERIPHERAL_CLOCK_DISABLE,
	ADCHS_INTERRUPT_BIT_SHIFT_LEFT_0_BITS,
	0x0000,
	ADCHS_CLOCK_SOURCE_PBCLK,
	0,
	ADCHS_WARMUP_CLOCK_32768
	);


	PLIB_ADCHS_ChannelSetup(
	DRV_ADC_ID_1,
	ADCHS_CHANNEL_7,
	ADCHS_DATA_RESOLUTION_12BIT,
	32,
	5,
	ADCHS_EARLY_INTERRUPT_PRIOR_CLOCK_4
	);

/* Since configuration of analog inputs (dedicated and alternate) for dedicated ADC channel */
/* is done via selection of dedicated channel only, here, the analog input for a dedicated */
/* ADC channel number is fixed */					
    if (DEVADC7 != 0xFFFFFFFF)
    PLIB_ADCHS_ChannelConfigurationSet(DRV_ADC_ID_1, ADCHS_CHANNEL_7, DEVADC7);




	/* Include Analog input to Scan list */
	PLIB_ADCHS_AnalogInputScanSelect
	(
		DRV_ADC_ID_1,
		ADCHS_AN28
	);
	
	PLIB_ADCHS_AnalogInputModeSelect(
			DRV_ADC_ID_1,
			ADCHS_AN28,
			ADCHS_INPUT_MODE_SINGLE_ENDED_TWOS_COMP
			);			

    PLIB_ADCHS_AnalogInputDataReadyInterruptEnable(DRV_ADC_ID_1, ADCHS_AN28);

	/* Configure input scan settings */
	PLIB_ADCHS_AnalogInputScanSetup
	(
		DRV_ADC_ID_1, 
		ADCHS_AN28, 
		ADCHS_SCAN_TRIGGER_SENSITIVE_LEVEL,
		ADCHS_SCAN_TRIGGER_SOURCE_GLOBAL_SOFTWARE_EDGE
	);
	PLIB_ADCHS_EarlyInterruptEnable(DRV_ADC_ID_1);


    /* Select CVD mode */
PLIB_ADCHS_CVDSetup
( 
	DRV_ADC_ID_1,
	ADCHS_CVD_CAPACITOR_5PF,
			false,
            true,
			false,
			false,
			false,
            ADCHS_AN28,
            1000,
            0
);

/* Enable comparator-1 as it is used by CVD */
PLIB_ADCHS_DigitalComparatorEnable
(
	DRV_ADC_ID_1,
	ADCHS_DIGITAL_COMPARATOR_1
);


    /* Enable ADC */
    PLIB_ADCHS_Enable(DRV_ADC_ID_1);
	
	/* Check Vref to be ready */
	while(!PLIB_ADCHS_VREFIsReady(DRV_ADC_ID_1));
	
	/* Check for Vref Fault */
	while(PLIB_ADCHS_VREFFaultHasOccurred(DRV_ADC_ID_1));	

	
	
	
	/* Enable analog feature for the specified channel */
	PLIB_ADCHS_ChannelAnalogFeatureEnable
	(
		DRV_ADC_ID_1,
		ADCHS_CHANNEL_7
	);
	
	/* Wait for the modules to be ready */
	while(!PLIB_ADCHS_ChannelIsReady
		(	
			DRV_ADC_ID_1,
			ADCHS_CHANNEL_7
		)
	);
	

    /* Initialize Digital Comparator 1 interrupt as it is used by CVD */
    PLIB_ADCHS_DigitalComparatorInterruptEnable(DRV_ADC_ID_1, ADCHS_DIGITAL_COMPARATOR_1);
    /* Initialize ADC Digital Comparator Interrupt */
    PLIB_INT_SourceFlagClear(INT_ID_0, INT_SOURCE_ADC_1_DC1);
    PLIB_INT_SourceEnable(INT_ID_0, INT_SOURCE_ADC_1_DC1);
    PLIB_INT_VectorPrioritySet(INT_ID_0, INT_VECTOR_ADC1_DC1, INT_PRIORITY_LEVEL3);
    PLIB_INT_VectorSubPrioritySet(INT_ID_0, INT_VECTOR_ADC1_DC1, INT_SUBPRIORITY_LEVEL0);
}


inline void DRV_ADC_DeInitialize(void)
{
    /* Enable ADC */
    PLIB_ADCHS_Disable(DRV_ADC_ID_1);
}


inline void DRV_ADC0_Open(void)
{
	/* Enable digital feature for the specified channel */
	PLIB_ADCHS_ChannelDigitalFeatureEnable
	(
		DRV_ADC_ID_1,
		ADCHS_CHANNEL_7
	);
}

inline void DRV_ADC0_Close(void)
{
	/* Disable digital feature for the specified channel */
	PLIB_ADCHS_ChannelDigitalFeatureDisable
	(
		DRV_ADC_ID_1,
		ADCHS_CHANNEL_7
	);
}


inline void DRV_ADC_Start(void)
{
    /* Start ADC */
    //PLIB_ADCHS_SoftwareSamplingStart(DRV_ADC_ID_1);
	PLIB_ADCHS_GlobalSoftwareTriggerEnable(DRV_ADC_ID_1);
}

inline void DRV_ADC_Stop(void)
{
    /* Stop ADC */
    PLIB_ADCHS_SoftwareSamplingStop(DRV_ADC_ID_1);	
}

uint32_t DRV_ADC_SamplesRead(uint8_t bufIndex)
{
    /* Read Result */
    return PLIB_ADCHS_AnalogInputResultGet
	( 
		DRV_ADC_ID_1, 
		(ADCHS_AN0 + bufIndex)
	);
}

bool DRV_ADC_SamplesAvailable(uint8_t bufIndex)
{
    /* Check if data is available or not */
	return PLIB_ADCHS_AnalogInputDataIsReady
	(
		DRV_ADC_ID_1, 
		(ADCHS_AN0 + bufIndex)
	);
}




inline void DRV_ADC_CVD_Start(void)
{
	/* Enable CVD mode */
	PLIB_ADCHS_CVDEnable
	(
		DRV_ADC_ID_1
	);
}

inline void DRV_ADC_CVD_Stop(void)
{
	/* Disable CVD mode */
	PLIB_ADCHS_CVDDisable
	(
		DRV_ADC_ID_1
	);
}

inline uint16_t DRV_ADC_CVD_ResultRead(void)
{
    /* Read Result */
    return PLIB_ADCHS_CVDResultGet
	( 
		DRV_ADC_ID_1
	);
}

inline bool DRV_ADC_DigitalComparator_EventHasOccurred(void)
{

	return(PLIB_ADCHS_DigitalComparatorEventHasOccurred
	(
		DRV_ADC_ID_1,
		ADCHS_DIGITAL_COMPARATOR_1
	));
}

ADCHS_AN_INPUT_ID DRV_ADC_DigitalComparator_AnalogInputGet(void)
{
	return(PLIB_ADCHS_DigitalComparatorAnalogInputGet
	( 
		DRV_ADC_ID_1,
		ADCHS_DIGITAL_COMPARATOR_1
	));
}


