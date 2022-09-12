/*******************************************************************************
  MPLAB Harmony Application Header File

  Company:
    Microchip Technology Inc.

  File Name:
    app_error.h

  Summary:
    This header file provides prototypes and definitions for the error handing
    within the application.

  Description:

*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

#ifndef _APP_ERROR_H
#define _APP_ERROR_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#if   defined( BT_AUDIO_DK )
  //assert to display
  #include "error.h"
#elif defined (AK7755_BT_AUDIO_DK)
  //assert to display
  #include "error.h"
#elif defined( PIC32MZ_EC_SK_MEB2 )
  #if defined( __DEBUG )
    #undef assert
    #undef __assert
    #define assert(expression)  \
        if (!(expression))\
            SYS_DEBUG_BreakPoint();
  #endif
#elif defined( PIC32MZ_EF_SK_MEB2 )
  #if defined( __DEBUG )
    #undef assert
    #undef __assert
    #define assert(expression)  \
        if (!(expression))\
            SYS_DEBUG_BreakPoint();
  #endif
#else
//  #error "Unknown build configuration!"
#endif

#endif//_APP_ERROR_H

