/*******************************************************************************
  MPLAB Harmony Graphics Composer Generated Implementation File

  File Name:
    libaria_harmony.c

  Summary:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

  Description:
    Build-time generated implementation from the MPLAB Harmony
    Graphics Composer.

    Created with MPLAB Harmony Version 2.06
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
// DOM-IGNORE-END

#include "gfx/libaria/libaria_harmony.h"
#include "gfx/libaria/libaria_init.h"

#include "gfx/libaria/libaria.h"


/*** libaria Object Global ***/
libaria_objects libariaObj;
static LIBARIA_STATES libariaState;

int32_t LibAria_Initialize(void) 
{
	if(laInitialize() == LA_FAILURE)
		return -1;
		
	libariaObj.context = laContext_Create(0, 0, 0, GFX_COLOR_MODE_RGB_565, NULL);
	
	if(libariaObj.context == NULL)
		return -1;
	
	laContext_SetActive(libariaObj.context);
	
	libaria_initialize(); // use auto-generated initialization functions


	libariaState = LIBARIA_STATE_INIT;
	
	return 0;
}

void LibAria_Tasks(void)
{
    switch(libariaState)
    {
		case LIBARIA_STATE_INIT:
        {
                libariaState = LIBARIA_STATE_RUNNING;
            break;
        }
        case LIBARIA_STATE_RUNNING:
		{
			laContext_SetActive(libariaObj.context);
            
			
			
			laUpdate(0);
            
			break;
		}
             
		default:
		{
            break;
		}
    }
}

	

