/*

    Written by : Bebo
    DATE : 7/2/2019
    AUTOSAR Version : 4.3.1
    DOC Name : AUTOSAR_SWS_OS.pdf
    Target : ARM TIVA_C TM4C123GH6PM

*/



#include "../AutosarOS/Os_Headers/OsInterface_Headers/Os.h"

/* set pending bit of PendSv exception and set stack pointer to MSP */

#define DISPATCHER_CALL   __asm ( " MRS R9, CONTROL " ) ;\
                          __asm ( " BIC R9, R9, #0x02 " ) ;\
                          __asm ( " MSR CONTROL, R9 " );\
                          *( ( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000ED04 ) |= ( 0x01u << 28 );\
                          __asm ( " MRS R9, CONTROL " ) ;\
                          __asm ( " ORR R9, R9, #0x02 " ) ;\
                          __asm ( " MSR CONTROL, R9 " )

/* set priority of dispatcher to be lowest */
#define PEND_SV_PRIORITY   *( ( volatile P2VAR( uint32, AUTOMATIC, REGSPACE ) ) 0xE000ED20 ) |= ( 0x07u << 21  )


/* set BASEPRI priority to be 7 to disable dispatcher*/
#define DISPATCHER_OFF  __asm ( " MRS R9, BASEPRI " ) ;\
                        __asm ( " MOV R10, #0x0E0u " ) ;\
                        __asm ( " MSR BASEPRI_MAX, R10 " )


/* befor convert to dipatcher make stack pointer for MSP*/
#define DISPATCHER_ON    __asm ( " MRS R8, CONTROL " ) ;\
                         __asm ( " BIC R8, R8, #0x02 " ) ;\
                         __asm ( " MSR CONTROL, R8 " );\
                         __asm ( " MSR BASEPRI_MAX, R9  " ) ;\
                         __asm ( " MRS R8, CONTROL " ) ;\
                         __asm ( " ORR R8, R8, #0x02 " ) ;\
                         __asm ( " MSR CONTROL, R8 " )



#define DELAY 2000000
#define delay   i= DELAY ;\
                while(i--)

#define SW_1    * ( ( volatile unsigned long * ) (0x4005D000 + (1<<6) ))
#define SW_2    * ( ( volatile unsigned long * ) (0x4005D000 + (1<<2) ))

#define LED_R   * ( ( volatile unsigned long * ) (0x4005D000 + (1<<3) ))
#define LED_B   * ( ( volatile unsigned long * ) (0x4005D000 + (1<<4) ))
#define LED_G   * ( ( volatile unsigned long * ) (0x4005D000 + (1<<5) ))

#define CS_ON       __asm ( " CPSID i " )
#define CS_OFF      __asm ( " CPSIE i " )


unsigned long i = 0 ;


void TaskRedOn (void) ;
void TaskGreenOn (void) ;
void TaskBlueOn (void) ;
void TaskYellowOn (void) ;
void TaskBurbuleOn (void) ;
void TaskAquaOn (void) ;
void TaskWhiteOn (void) ;
void TaskRedOff (void) ;
void TaskGreenOff (void) ;
void TaskBlueOff (void) ;
void TaskYellowOff (void) ;
void TaskBurbuleOff (void) ;
void TaskAquaOff (void) ;
void TaskWhiteOff (void) ;

CONSTP2FUNC( void, OS_CONFIG_DATA, OsTasksNames_Array [TASKS_NUMBER] ) (void) =
{

  TaskRedOn
 ,TaskGreenOn
 ,TaskBlueOn
 ,TaskYellowOn
 ,TaskBurbuleOn
 ,TaskAquaOn
 ,TaskWhiteOn
 ,TaskRedOff
 ,TaskGreenOff
 ,TaskBlueOff
 ,TaskYellowOff
 ,TaskBurbuleOff
 ,TaskAquaOff
 ,TaskWhiteOff

};



int main(void)
{

    PEND_SV_PRIORITY ;

    /* set MSP to address 0x20008000 */
    __asm ( " MOV R10, #0x8000 " ) ;
    __asm ( " MOVT R10, #0x2000 " ) ;
    __asm ( " MSR MSP, R10 " ) ;

    /* assign stack pointer to PSP */
    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;

    __asm ( " MOV R10, #0x7000 " ) ;
    __asm ( " MOVT R10, #0x2000 " ) ;
    __asm ( " MSR PSP, R10 " ) ;



    /* initialize portf */
    * ( ( volatile unsigned long * ) ( 0x400FE000 + 0x608 ) ) |= 0X3F ;         /* enable clock */
    * ( ( volatile unsigned long * ) ( 0x400FE000 + 0x06C ) ) |= (1<<5) ;       /* enble AHB for port F */
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x520 ) ) |= 0x4C4F434B ;   /* unlock GPIOCR  */
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x524 ) ) |= 0b01 ;         /* unlock PF0  */
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x400 ) ) &= ~(0b10001) ;   /* define input in port f */
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x400 ) ) |= (0b01110) ;    /* define output in port f */
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x420 ) ) &= ~(0b11111) ;   /* configure port f as gpio pin */
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x508 ) ) |= (0b11111) ;    /* drive port f with 8-ma  */
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x510 ) ) |= (0b10001) ;    /* put pull up resistor for port f 0,4  */
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x51C ) ) |= (0b11111) ;    /* enable port f as dio  */
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x404 ) ) &= ~(0b11111) ;
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x408 ) ) &= ~(0b11111) ;
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x40C ) ) &= ~(0b11111) ;
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x41C ) ) |= (0b11111) ;
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x410 ) ) &= ~(0b11111) ;
    * ( ( volatile unsigned long * ) ( 0x4005D000 + 0x410 ) ) |= (0b00001) ;


    ActivateTask( TASK_RED_ON ) ;



    while (1)
    {

    LED_R ^= 2 ;

    delay ;

    LED_R ^= 2 ;

    delay ;

    }

}




void TaskRedOn (void)
{


    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;

    LED_R = 2 ;
    delay ;

    GetResource(RESORCE_4) ;

    GetResource(RESORCE_3) ;

    GetResource(RESORCE_2) ;

    /*
    GetResource(RESORCE_1) ;

    DISPATCHER_CALL ;

    ReleaseResource (RESORCE_1) ;
    */

    ActivateTask( TASK_GREEN_ON ) ;
    ActivateTask( TASK_GREEN_ON ) ;
    ActivateTask( TASK_BLUE_ON ) ;
    ActivateTask( TASK_YELLOW_ON ) ;
    ActivateTask( TASK_BURBULE_ON ) ;
    ActivateTask( TASK_AQUA_ON ) ;
    ActivateTask( TASK_WHITE_ON ) ;
    ActivateTask( TASK_RED_OFF ) ;
    ActivateTask( TASK_GREEN_OFF ) ;
    ActivateTask( TASK_BLUE_OFF ) ;
    ActivateTask( TASK_YELLOW_OFF ) ;
    ActivateTask( TASK_BURBULE_OFF ) ;
    ActivateTask( TASK_AQUA_OFF ) ;
    ActivateTask( TASK_WHITE_OFF ) ;

    SetEvent (TASK_RED_OFF, OS_EVENT_MASK_1 ) ;

    ReleaseResource (RESORCE_3) ;

    ReleaseResource (RESORCE_2) ;

    ReleaseResource (RESORCE_3) ;

    ReleaseResource (RESORCE_4) ;

    Schedule () ;

    ChainTask(TASK_RED_ON) ;

    return ;
}

void TaskGreenOn (void)
{

    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;

    LED_G = 8 ;
    delay ;

    TerminateTask() ;

    return ;
}

void TaskBlueOn (void)
{
    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;
    LED_B = 4 ;
    delay ;

    TerminateTask() ;

    return ;
}

void TaskYellowOn (void)
{

    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;
    LED_G = 8 ;
    LED_R = 2 ;

    delay ;

    TerminateTask() ;

    return ;
}

void TaskBurbuleOn (void)
{

    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;
    LED_B = 4 ;
    LED_R = 2 ;

    delay ;

    TerminateTask() ;

    return ;
}

void TaskAquaOn (void)
{

    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;

    LED_G = 8 ;
    LED_B = 4 ;

    delay ;

    TerminateTask() ;

    return ;
}

void TaskWhiteOn (void)
{

    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;

    LED_G = 8 ;
    LED_B = 4 ;
    LED_R = 2 ;

    delay ;

    ChainTask(TASK_RED_OFF) ;

    return ;
}

void TaskRedOff (void)
{

    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;

    EventMaskType mask = 0 ;
    EventMaskRefType mask_ptr = &mask ;

    WaitEvent( OS_EVENT_MASK_1 | OS_EVENT_MASK_2 | OS_EVENT_MASK_3 ) ;

    GetEvent( TASK_RED_OFF, mask_ptr ) ;
    ClearEvent ( *mask_ptr ) ;
    WaitEvent( OS_EVENT_MASK_1 | OS_EVENT_MASK_2 | OS_EVENT_MASK_3 ) ;


    LED_R = 0 ;

    delay ;

    TerminateTask() ;

    return ;
}

void TaskGreenOff (void)
{

    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;

    SetEvent (TASK_RED_OFF, OS_EVENT_MASK_4 ) ;
    SetEvent (TASK_RED_OFF, OS_EVENT_MASK_1 ) ;

    LED_G = 0 ;

    delay ;

    TerminateTask() ;

    return ;
}

void TaskBlueOff (void)
{

    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;
    LED_B = 0 ;

    delay ;

    TerminateTask() ;

    return ;
}

void TaskYellowOff (void)
{

    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;
    LED_G = 0 ;
    LED_R = 0 ;

    delay ;

    TerminateTask() ;

    return ;
}

void TaskBurbuleOff (void)
{

    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;
    LED_R = 0 ;
    LED_B = 0 ;

    delay ;

    TerminateTask() ;

    return ;
}

void TaskAquaOff (void)
{
    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;

    LED_B = 0 ;
    LED_G = 0 ;
    delay ;

    TerminateTask() ;

    return ;
}

void TaskWhiteOff (void)
{

    __asm ( " MRS R9, CONTROL " ) ;
    __asm ( " ORR R9, R9, #0x02 " ) ;
    __asm ( " MSR CONTROL, R9 " ) ;
    LED_G = 0 ;
    LED_R = 0 ;
    LED_B = 0 ;

    delay ;


    TerminateTask() ;

    return ;
}




/*

    DISPATCHER_OFF ;


    ActivateTask( TASK_RED_ON ) ;
    ActivateTask( TASK_GREEN_ON ) ;
    ActivateTask( TASK_BLUE_ON ) ;
    ActivateTask( TASK_YELLOW_ON ) ;
    ActivateTask( TASK_BURBULE_ON ) ;
    ActivateTask( TASK_AQUA_ON ) ;
    ActivateTask( TASK_WHITE_ON ) ;
    ActivateTask( TASK_RED_OFF ) ;
    ActivateTask( TASK_GREEN_OFF ) ;
    ActivateTask( TASK_BLUE_OFF ) ;
    ActivateTask( TASK_YELLOW_OFF ) ;
    ActivateTask( TASK_BURBULE_OFF ) ;
    ActivateTask( TASK_AQUA_OFF ) ;
    ActivateTask( TASK_WHITE_OFF ) ;

    DISPATCHER_ON ;
*/
