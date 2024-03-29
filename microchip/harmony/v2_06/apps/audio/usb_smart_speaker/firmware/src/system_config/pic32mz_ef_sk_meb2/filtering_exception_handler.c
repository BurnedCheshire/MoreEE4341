//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2017 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Exception handling
// *****************************************************************************
// *****************************************************************************
/*
    The standard exception handling provided by the compiler's installation is
    insufficient to handle overflow exception that can happen inside of assembly
    IIR routines.

    Exceptions are handled by the default code by simply throwing the application
    into a while (1) loop, which simply ends all processing of the application.
    This new code attempts to return control back to the application.

    If an overflow exception is trapped a fallback return value is written to
    the $v0 register for use by the IIR primitive that generated the overflow.
    The application can use +1 (0x7FFF) or Zero, or random noise as the fallback
    return value.  See below.
 */
#include "system_config.h"
#include "system_definitions.h"
#include "system/console/sys_console.h"
#include "system/debug/sys_debug.h"

typedef struct _XCPT_FRAME  // access to all major registers from the instruction that caused the exception
{
    uint32_t at;
    uint32_t v0;
    uint32_t v1;
    uint32_t a0;
    uint32_t a1;
    uint32_t a2;
    uint32_t a3;
    uint32_t t0;
    uint32_t t1;
    uint32_t t2;
    uint32_t t3;
    uint32_t t4;
    uint32_t t5;
    uint32_t t6;
    uint32_t t7;
    uint32_t t8;
    uint32_t t9;
    uint32_t ra;
    uint32_t lo;
    uint32_t hi;
    uint32_t cause;
    uint32_t status;
    uint32_t epc;

} XCPT_FRAME;

static enum {
    EXCEP_IRQ      =  0, // interrupt
    EXCEP_AdEL     =  4, // address error exception (load or ifetch)
    EXCEP_AdES     =  5, // address error exception (store)
    EXCEP_IBE      =  6, // bus error (ifetch)
    EXCEP_DBE      =  7, // bus error (load/store)
    EXCEP_Sys      =  8, // syscall
    EXCEP_Bp       =  9, // breakpoint
    EXCEP_RI       = 10, // reserved instruction
    EXCEP_CpU      = 11, // coprocessor unusable
    EXCEP_Overflow = 12, // arithmetic overflow
    EXCEP_Trap     = 13, // trap (possible divide by zero)
    EXCEP_IS1      = 16, // implementation specfic 1
    EXCEP_CEU      = 17, // CorExtend Unuseable
    EXCEP_C2E      = 18, // coprocessor 2
} _excep_code;

// Use static variables, with fixed addresses, since S/W stack can be unstable
static unsigned int _excep_code;
static unsigned int _excep_addr;
static uint32_t  _CP0_StatusValue;   // Status value from CP0 Register 12
static uintptr_t _StackPointerValue; // Stack pointer value
static uintptr_t _BadVirtualAddress; // Bad address for address exceptions
static uintptr_t _ReturnAddress;     // Return Address (ra)

#define MSG_BUFFER_LENGTH 256
char msgBuffer[MSG_BUFFER_LENGTH];

void __attribute__((nomips16)) _general_exception_handler (XCPT_FRAME* const pXFrame)
{
    register uint32_t _localStackPointerValue asm("sp");

    _excep_addr = pXFrame->epc;
    _excep_code = pXFrame->cause;   // capture exception type
    _excep_code = (_excep_code & 0x0000007C) >> 2;

    _CP0_StatusValue   = _CP0_GET_STATUS();
    _StackPointerValue = _localStackPointerValue;
    _BadVirtualAddress = _CP0_GET_BADVADDR();
    _ReturnAddress     = pXFrame->ra;

    if (_excep_code == EXCEP_Overflow)
    {// Provide fallback return value for filtering primitive throwing an overflow exception.
        pXFrame->v0 = 0x7FFF;  // set function output to maximum (saturation)
        pXFrame->v1 = 0x7FFF;  // set intermediate results to maximum (saturation)
        pXFrame->epc = pXFrame->epc + 4; // set return from exception to next instruction (skip)
        return;
    }

    sprintf(msgBuffer,"**EXCEPTION:*\r\n"
                      " ECode: %d, EAddr: 0x%08X, CPO Status: 0x%08X\r\n"
                      " Stack Ptr: 0x%08X, Bad Addr: 0x%08X, Return Addr: 0x%08X\r\n"
                      "**EXCEPTION:*\r\n",
                      _excep_code,_excep_addr,_CP0_StatusValue,
                      _StackPointerValue,_BadVirtualAddress,_ReturnAddress);
    SYS_CONSOLE_Write( SYS_CONSOLE_INDEX_0, STDOUT_FILENO, msgBuffer, strlen(msgBuffer) );

    while (1) {
        SYS_DEBUG_BreakPoint();  // Stop here is in debugger.
    }
}

/*******************************************************************************
 End of File
*/
