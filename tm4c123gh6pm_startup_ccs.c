//*****************************************************************************
//
// Startup code for use with TI's Code Composer Studio.
//
// Copyright (c) 2011-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#include <stdint.h>
#include "..\OS\Os_Headers\OsInterface_Headers\Os.h"
#include "..\OS\Os_Headers\OsInternal_Headers\Os_Internal.h"
#include "..\OS\Os_Headers\OsInternal_Headers\Os_ExternalVariables.h"


//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void ResetISR(void);
static void NmiSR(void);
static void FaultISR(void);
static void IntDefaultHandler(void);
void PendSV (void) ;
void SVCall (void) ;

//*****************************************************************************
//
// External declaration for the reset handler that is to be called when the
// processor is started
//
//*****************************************************************************
extern void _c_int00(void);
extern void SysTick_Handler(void);

//*****************************************************************************
//
// Linker variable that marks the top of the stack.
//
//*****************************************************************************
 uint32_t * stack_ptr = ( uint32_t *) 0x20008000;

//*****************************************************************************
//
// External declarations for the interrupt handlers used by the application.
//
//*****************************************************************************
// To be added by user

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000 or at the start of
// the program if located at a start address other than 0.
//
//*****************************************************************************
#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))  0x20008000  ,
                                            // The initial stack pointer
    ResetISR,                               // The reset handler
    NmiSR,                                  // The NMI handler
    FaultISR,                               // The hard fault handler
    IntDefaultHandler,                      // The MPU fault handler
    IntDefaultHandler,                      // The bus fault handler
    IntDefaultHandler,                      // The usage fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    SVCall,                                 // SVCall handler
    IntDefaultHandler,                      // Debug monitor handler
    0,                                      // Reserved
    PendSV,                                 // The PendSV handler
    SysTick_Handler,                      // The SysTick handler
    IntDefaultHandler,                      // GPIO Port A
    IntDefaultHandler,                      // GPIO Port B
    IntDefaultHandler,                      // GPIO Port C
    IntDefaultHandler,                      // GPIO Port D
    IntDefaultHandler,                      // GPIO Port E
    IntDefaultHandler,                      // UART0 Rx and Tx
    IntDefaultHandler,                      // UART1 Rx and Tx
    IntDefaultHandler,                      // SSI0 Rx and Tx
    IntDefaultHandler,                      // I2C0 Master and Slave
    IntDefaultHandler,                      // PWM Fault
    IntDefaultHandler,                      // PWM Generator 0
    IntDefaultHandler,                      // PWM Generator 1
    IntDefaultHandler,                      // PWM Generator 2
    IntDefaultHandler,                      // Quadrature Encoder 0
    IntDefaultHandler,                      // ADC Sequence 0
    IntDefaultHandler,                      // ADC Sequence 1
    IntDefaultHandler,                      // ADC Sequence 2
    IntDefaultHandler,                      // ADC Sequence 3
    IntDefaultHandler,                      // Watchdog timer
    IntDefaultHandler,                      // Timer 0 subtimer A
    IntDefaultHandler,                      // Timer 0 subtimer B
    IntDefaultHandler,                      // Timer 1 subtimer A
    IntDefaultHandler,                      // Timer 1 subtimer B
    IntDefaultHandler,                      // Timer 2 subtimer A
    IntDefaultHandler,                      // Timer 2 subtimer B
    IntDefaultHandler,                      // Analog Comparator 0
    IntDefaultHandler,                      // Analog Comparator 1
    IntDefaultHandler,                      // Analog Comparator 2
    IntDefaultHandler,                      // System Control (PLL, OSC, BO)
    IntDefaultHandler,                      // FLASH Control
    IntDefaultHandler,                      // GPIO Port F
    IntDefaultHandler,                      // GPIO Port G
    IntDefaultHandler,                      // GPIO Port H
    IntDefaultHandler,                      // UART2 Rx and Tx
    IntDefaultHandler,                      // SSI1 Rx and Tx
    IntDefaultHandler,                      // Timer 3 subtimer A
    IntDefaultHandler,                      // Timer 3 subtimer B
    IntDefaultHandler,                      // I2C1 Master and Slave
    IntDefaultHandler,                      // Quadrature Encoder 1
    IntDefaultHandler,                      // CAN0
    IntDefaultHandler,                      // CAN1
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // Hibernate
    IntDefaultHandler,                      // USB0
    IntDefaultHandler,                      // PWM Generator 3
    IntDefaultHandler,                      // uDMA Software Transfer
    IntDefaultHandler,                      // uDMA Error
    IntDefaultHandler,                      // ADC1 Sequence 0
    IntDefaultHandler,                      // ADC1 Sequence 1
    IntDefaultHandler,                      // ADC1 Sequence 2
    IntDefaultHandler,                      // ADC1 Sequence 3
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // GPIO Port J
    IntDefaultHandler,                      // GPIO Port K
    IntDefaultHandler,                      // GPIO Port L
    IntDefaultHandler,                      // SSI2 Rx and Tx
    IntDefaultHandler,                      // SSI3 Rx and Tx
    IntDefaultHandler,                      // UART3 Rx and Tx
    IntDefaultHandler,                      // UART4 Rx and Tx
    IntDefaultHandler,                      // UART5 Rx and Tx
    IntDefaultHandler,                      // UART6 Rx and Tx
    IntDefaultHandler,                      // UART7 Rx and Tx
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // I2C2 Master and Slave
    IntDefaultHandler,                      // I2C3 Master and Slave
    IntDefaultHandler,                      // Timer 4 subtimer A
    IntDefaultHandler,                      // Timer 4 subtimer B
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // Timer 5 subtimer A
    IntDefaultHandler,                      // Timer 5 subtimer B
    IntDefaultHandler,                      // Wide Timer 0 subtimer A
    IntDefaultHandler,                      // Wide Timer 0 subtimer B
    IntDefaultHandler,                      // Wide Timer 1 subtimer A
    IntDefaultHandler,                      // Wide Timer 1 subtimer B
    IntDefaultHandler,                      // Wide Timer 2 subtimer A
    IntDefaultHandler,                      // Wide Timer 2 subtimer B
    IntDefaultHandler,                      // Wide Timer 3 subtimer A
    IntDefaultHandler,                      // Wide Timer 3 subtimer B
    IntDefaultHandler,                      // Wide Timer 4 subtimer A
    IntDefaultHandler,                      // Wide Timer 4 subtimer B
    IntDefaultHandler,                      // Wide Timer 5 subtimer A
    IntDefaultHandler,                      // Wide Timer 5 subtimer B
    IntDefaultHandler,                      // FPU
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // I2C4 Master and Slave
    IntDefaultHandler,                      // I2C5 Master and Slave
    IntDefaultHandler,                      // GPIO Port M
    IntDefaultHandler,                      // GPIO Port N
    IntDefaultHandler,                      // Quadrature Encoder 2
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // GPIO Port P (Summary or P0)
    IntDefaultHandler,                      // GPIO Port P1
    IntDefaultHandler,                      // GPIO Port P2
    IntDefaultHandler,                      // GPIO Port P3
    IntDefaultHandler,                      // GPIO Port P4
    IntDefaultHandler,                      // GPIO Port P5
    IntDefaultHandler,                      // GPIO Port P6
    IntDefaultHandler,                      // GPIO Port P7
    IntDefaultHandler,                      // GPIO Port Q (Summary or Q0)
    IntDefaultHandler,                      // GPIO Port Q1
    IntDefaultHandler,                      // GPIO Port Q2
    IntDefaultHandler,                      // GPIO Port Q3
    IntDefaultHandler,                      // GPIO Port Q4
    IntDefaultHandler,                      // GPIO Port Q5
    IntDefaultHandler,                      // GPIO Port Q6
    IntDefaultHandler,                      // GPIO Port Q7
    IntDefaultHandler,                      // GPIO Port R
    IntDefaultHandler,                      // GPIO Port S
    IntDefaultHandler,                      // PWM 1 Generator 0
    IntDefaultHandler,                      // PWM 1 Generator 1
    IntDefaultHandler,                      // PWM 1 Generator 2
    IntDefaultHandler,                      // PWM 1 Generator 3
    IntDefaultHandler                       // PWM 1 Fault
};

//*****************************************************************************/
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************/
void
ResetISR(void)
{
    //
    // Jump to the CCS C initialization routine.  This will enable the
    // floating-point unit as well, so that does not need to be done here.
    //
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}

//*****************************************************************************/
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************/
static void
NmiSR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************/
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************/
static void
FaultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************/
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************/
static void
IntDefaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}

/*****************************************************************************/

void SVCall (void)
{
    /* enable privilege level in thread mode */
    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " BIC R9, R9, #0x01 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;

    return ;

}

/*****************************************************************************/

void PendSV (void)
{
    __asm ( " POP { R8 } " ) ;
    __asm ( " POP { R9 } " ) ;


    __asm ( " MOV R9, #0xFFF9 " ) ;
    __asm ( " MOVT R9, #0xFFFF " ) ;



    __asm ( " MRS R10, PSP " ) ;
    __asm ( " LDMIA R10, {R0-R7} " ) ;
    __asm ( " ADD R10, R10, #0x20 " ) ;
    __asm ( " MSR PSP, R10 " ) ;


    __asm ( " MRS R10, MSP " ) ;
    __asm ( " STMDB R10, {R0-R7} " ) ;
    __asm ( " SUB R10, R10, #0x20 " ) ;
    __asm ( " MSR MSP, R10 " ) ;

    __asm ( " PUSH { R9 } " ) ;
    __asm ( " PUSH { R8 } " ) ;



    __asm ( " MOV LR, #0xFFF9 " ) ;
    __asm ( " MOVT LR, #0xFFFF " ) ;






    if ( INVALID_TASK != RunningTaskPCB_Index )/* case there's preemption to running task */
    {


        /* push value of preempted task's special registers which not pushed automatically into main stack while preemption */
        __asm ( " MRS R12, PSP " ) ;
        __asm ( " PUSH {R12} " ) ;
        __asm ( " PUSH {R4} " ) ;
        __asm ( " PUSH {R5} " ) ;
        __asm ( " PUSH {R6} " ) ;
        __asm ( " PUSH {R7} " ) ;
        __asm ( " PUSH {R8} " ) ;
        __asm ( " PUSH {R9} " ) ;
        __asm ( " PUSH {R10} " ) ;
        __asm ( " PUSH {R11} " ) ;



        /* save context of preempted task */

        /* change old task state */
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_State = READY ;

        /* save processor states of preempted task in its pcb, this states are pushed in main stack when exception of task context switching (PendSV) is triggered */
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_PSR = OsMSP_StackFrame_ptr->PSR ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_PC = OsMSP_StackFrame_ptr->PC ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_LR = OsMSP_StackFrame_ptr->LR ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R12 = OsMSP_StackFrame_ptr->R12 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R3 = OsMSP_StackFrame_ptr->R3 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R2 = OsMSP_StackFrame_ptr->R2 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R1 = OsMSP_StackFrame_ptr->R1 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R0 = OsMSP_StackFrame_ptr->R0 ;

        /* this registers are pushed manually */
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_SP = OsMSP_StackFrame_ptr->PSP ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R4 = OsMSP_StackFrame_ptr->R4 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R5 = OsMSP_StackFrame_ptr->R5 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R6 = OsMSP_StackFrame_ptr->R6 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R7 = OsMSP_StackFrame_ptr->R7 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R8 = OsMSP_StackFrame_ptr->R8 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R9 = OsMSP_StackFrame_ptr->R9 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R10 = OsMSP_StackFrame_ptr->R10 ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_R11 = OsMSP_StackFrame_ptr->R11 ;


        OsTaskResourceAllocation[ ( OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_Priority ) ] = PreemptionPriority ;

    }
    else    /* case running task is terminated */
    {

    }

    if ( INVALID_TASK != ReadyHighestPriority ) /* case there's tasks could enter running state */
    {
        __asm ( " MOV R12, #0x7FB4 " ) ;
        __asm( " MOVT R12, #0x2000 " ) ;
        __asm ( " MSR MSP, R12 " ) ;

        /* take copy for ReadyTaskPCB_Index, CS for read modify write sequence from ReadyTaskPCB_Index to ReadyHighestPriority*/
        __asm ( " CPSID i " ) ;

        DispatcherLocal_Variable = ReadyTaskPCB_Index ;
        PreemptionPriority = OsTasks_Array[ ( OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_ID ) ].OsTaskCeillingPriority_Internal ;
        __asm ( " CPSIE i " ) ;

        /* write values of next running task into stack to be popped into registers */

        /* popped manually by code */
        OsMSP_StackFrame_ptr->R11 =  ( VAR( uint32, AUTOMATIC ) )OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_PC ;
        OsMSP_StackFrame_ptr->R10 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R10 ;
        OsMSP_StackFrame_ptr->R9 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R9 ;
        OsMSP_StackFrame_ptr->R8 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R8 ;
        OsMSP_StackFrame_ptr->R7 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R7 ;
        OsMSP_StackFrame_ptr->R6 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R6 ;
        OsMSP_StackFrame_ptr->R5 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R5 ;
        OsMSP_StackFrame_ptr->R4 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R4 ;
        OsMSP_StackFrame_ptr->PSP = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_SP ;

        /* will be popped automatically in exception return */
        OsMSP_StackFrame_ptr->R0 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R0 ;
        OsMSP_StackFrame_ptr->R1 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R1 ;
        OsMSP_StackFrame_ptr->R2 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R2 ;
        OsMSP_StackFrame_ptr->R3 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R3 ;
        OsMSP_StackFrame_ptr->R12 = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_R12 ;
        OsMSP_StackFrame_ptr->LR = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_LR ;
        OsMSP_StackFrame_ptr->PC = OsTaskFrame ;
        OsMSP_StackFrame_ptr->PSR = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_PSR ;

        OsTaskCode_Ptr = OsTasksPCB_Array[ DispatcherLocal_Variable ].Task_PC ;


        /* manual pop for special register ready task */

        /* pop program counter in r11 to use int TaskFrame functino */
        __asm ( " POP {R11} " ) ;
        __asm ( " POP {R10} " ) ;
        __asm ( " POP {R9} " ) ;
        __asm ( " POP {R8} " ) ;
        __asm ( " POP {R7} " ) ;
        __asm ( " POP {R6} " ) ;
        __asm ( " POP {R5} " ) ;
        __asm ( " POP {R4} " ) ;

        __asm ( " POP {R12} " ) ;
        __asm ( " MSR PSP, R12 " ) ;





        /* change index of running task pcb and change state for running task */
        RunningTaskPCB_Index = DispatcherLocal_Variable ;
        OsTasksPCB_Array[ RunningTaskPCB_Index ].Task_State = RUNNING ;
    }
    else /* no ready tasks, go to idle mechanism */
    {
        while ( INVALID_TASK == ReadyHighestPriority) ;
    }

    return ;

}
