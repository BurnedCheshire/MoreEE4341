/*******************************************************************************
  MPLAB Harmony Application Source File

  Company:
    Microchip Technology Inc.

  File Name:
    btad_buttons.c

  Summary:
    This file contains the button handlers for bluetooth audio development kit configurations.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It
    implements the logic of the application's state machine and it may call
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
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
#include <stdio.h>
#include <stdlib.h>
#include "buttons.h"
#include "app.h"


#define APP_BUTTON1_PIN (1<<PORTS_BIT_POS_0)
#define APP_BUTTON2_PIN (1<<PORTS_BIT_POS_1)
#define APP_BUTTON3_PIN (1<<PORTS_BIT_POS_10)
#define APP_BUTTON4_PIN (1<<PORTS_BIT_POS_12)
#define APP_BUTTON5_PIN (1<<PORTS_BIT_POS_13)

 



static bool state;
static unsigned int mNewButtonState;
static unsigned int mButtonState;
static uint8_t  mButtonEvent = 0;
int8_t  mRepeatButton;
int32_t mRepeatCount;
/*
 * 
 * Local Macro Definitions 
 * 
 */
#define READ_BUTTON_PORTS()                         SYS_PORTS_Read(PORTS_ID_0,PORT_CHANNEL_A) |\
                                                        SYS_PORTS_Read(PORTS_ID_0,PORT_CHANNEL_B)

#define LONG_PRESS_DELAY                10 // 1s

static void APP_OnButtonEvent(uint8_t button, bool bButtonClosed, int32_t repeatCount);

void APP_ButtonInit(void)
{
    mButtonState = READ_BUTTON_PORTS();

    mRepeatButton = INVALID_BUTTON;
    mRepeatCount = 0;
    mButtonEvent = 0;
}

void APP_ButtonTask(void)
{
    unsigned int newState = mNewButtonState;
    unsigned int changed;
    bool intStatus;

    if (mButtonEvent == 1)
    {
        intStatus = SYS_INT_Disable();
        {
            mButtonEvent = 0;
            newState = mNewButtonState;
            changed = mButtonState ^ newState;
        }
        if(intStatus) SYS_INT_Enable();

        if (changed & APP_BUTTON1_PIN)
        {
            state = (BSP_SwitchStateGet(BSP_SWITCH_1));
            if ( !state && ((newState & APP_BUTTON1_PIN) == 0))
            {
                
                //DOWN
                APP_OnButtonEvent(APP_BUTTON1,true,0);
                if (mRepeatButton == INVALID_BUTTON)
                {
                    mRepeatButton = APP_BUTTON1;
                    mRepeatCount = 0;
                }
                
            }else if(state && (newState & APP_BUTTON1_PIN))
            {
//                if(BSP_SwitchStateGet(BSP_SWITCH_1)){
                //UP
                if (mRepeatButton == APP_BUTTON1)
                {
                    APP_OnButtonEvent(APP_BUTTON1,false,mRepeatCount);
                    mRepeatButton = INVALID_BUTTON;
                    
                }

            }
        }
        if (changed & APP_BUTTON2_PIN)
        {
            if ((newState & APP_BUTTON2_PIN) == 0)
            {
                APP_OnButtonEvent(APP_BUTTON2,true,0);
                if (mRepeatButton == INVALID_BUTTON)
                {
                    mRepeatButton = APP_BUTTON2;
                    mRepeatCount = 0;
                }
            }else
            {
                //UP
                if (mRepeatButton == APP_BUTTON2)
                {
                    APP_OnButtonEvent(APP_BUTTON2,false,mRepeatCount);
                    mRepeatButton = INVALID_BUTTON;
                    
                }
//                else
//                {
//                    APP_OnButtonEvent(APP_BUTTON2,false,0);
//                }
                
            }
        }
        if (changed & APP_BUTTON3_PIN)
        {
            if ((newState & APP_BUTTON3_PIN) == 0)
            {
                APP_OnButtonEvent(APP_BUTTON3,true,0);
                if (mRepeatButton == INVALID_BUTTON)
                {
                    mRepeatButton = APP_BUTTON3;
                    mRepeatCount = 0;
                }
            }else
            {
                //UP
                if (mRepeatButton == APP_BUTTON3)
                {
                    APP_OnButtonEvent(APP_BUTTON3,false,mRepeatCount);
                    mRepeatButton = INVALID_BUTTON;
                    
                }
//                else
//                {
//                    APP_OnButtonEvent(APP_BUTTON3,false,0);
//                }
            }
        }
        if (changed & APP_BUTTON4_PIN)
        {
            state = (BSP_SwitchStateGet(BSP_SWITCH_4));
            if ( !state && ((newState & APP_BUTTON4_PIN) == 0))
            {
                APP_OnButtonEvent(APP_BUTTON4,true,0);
                if (mRepeatButton == INVALID_BUTTON)
                {
                    mRepeatButton = APP_BUTTON4;
                    mRepeatCount = 0;
                }
                
            }else if(state && (newState & APP_BUTTON4_PIN))
            {
                //UP
                if (mRepeatButton == APP_BUTTON4)
                {
                    APP_OnButtonEvent(APP_BUTTON4,false,mRepeatCount);
                    mRepeatButton = INVALID_BUTTON;
                    
                }
            }
        }
        if (changed & APP_BUTTON5_PIN)
        {
            if ((newState & APP_BUTTON5_PIN) == 0)
            {
               APP_OnButtonEvent(APP_BUTTON5,true,0);
                if (mRepeatButton == INVALID_BUTTON)
                {
                    mRepeatButton = APP_BUTTON5;
                    mRepeatCount = 0;
                }
            }else
            {
                //UP
                if (mRepeatButton == APP_BUTTON5)
                {
                    APP_OnButtonEvent(APP_BUTTON5,false,mRepeatCount);
                    mRepeatButton = INVALID_BUTTON;
                    
                }
            }
        }
        mButtonState = newState;
    }
}

// pass the mRepeatButton to this function
int8_t APP_ButtonGetState(int8_t  button){
    if(button == INVALID_BUTTON)
        return -1;
    int8_t ret = -1;
    switch(button){
        case APP_BUTTON1:
            ret = BSP_SwitchStateGet(BSP_SWITCH_1);
            break;
        case APP_BUTTON2:
            ret = BSP_SwitchStateGet(BSP_SWITCH_2);
            break;
        case APP_BUTTON3:
            ret = BSP_SwitchStateGet(BSP_SWITCH_3);
            break;
        case APP_BUTTON4:
            ret = BSP_SwitchStateGet(BSP_SWITCH_4);
            break;
        case APP_BUTTON5:
            ret = BSP_SwitchStateGet(BSP_SWITCH_5);
            break;
        default:
            break;
    }
    return ret;
}

static void APP_OnButtonEvent(uint8_t button, bool bButtonClosed, int32_t repeatCount)
{
    switch (button)
    {
        // *****************************************************************************
        // Button S1: UP
        // *****************************************************************************
        case APP_BUTTON1:
        
            
            if (bButtonClosed) { // Button Closed
                if (repeatCount==LONG_PRESS_DELAY) {

                }
            } else { // Button Open
                // Short press
                if (repeatCount < LONG_PRESS_DELAY) {
                    APP_DecrementEncoderSelectionIndex();
                }
            }
            break;
            
        case APP_BUTTON2:
            // Disable Button2 function
            // Using unfolding index
            if(bButtonClosed)
            {
                if(repeatCount == LONG_PRESS_DELAY)
                {
                }
            }else
            {
                if(repeatCount < LONG_PRESS_DELAY)
                {
                    APP_IncrementEncoderSelectionIndex();
                }
                    
            }
            break;
            
        case APP_BUTTON3:
            if(bButtonClosed)
            {
                if(repeatCount >= LONG_PRESS_DELAY)
                {

                }
                
            }else
            {
                // Short press on SW3
                if(repeatCount < LONG_PRESS_DELAY)
                {
                    
                    APP_StopRecord();
                }
                else
                {
                    
                }
            }
            break;
            
        case APP_BUTTON4:
            if(bButtonClosed)
            {
//                if(repeatCount < LONG_PRESS_DELAY)
//                {
//                    
//                }
            }else
            {
                
            }
            break;
            
        case APP_BUTTON5:
            if(bButtonClosed)
            {
                if(repeatCount >= LONG_PRESS_DELAY)
                {
                    // every 100ms
                    
                } 
                
            }else
            {
                // Short press on SW3
                if(repeatCount < LONG_PRESS_DELAY)
                {
                    APP_StartRecord();
                }
                else
                {
                   
                }
            }
            break;
            
        default:
            break;
    }
}

void APP_ButtonsHandleInterrupt(unsigned int newButtonState)
{
    // Remember new buttons state
    mNewButtonState = newButtonState;
    mButtonEvent = 1;
}