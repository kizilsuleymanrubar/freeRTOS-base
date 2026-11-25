#include "main.h"


static volatile uint32_t idle_counter = 0;


/* Called by configASSERT(). Put a breakpoint here. */
void vAssertCalled(const char *file, int line)
{
    (void)file;
    (void)line;

    //taskDISABLE_INTERRUPTS();
    __disable_irq();

    for (;;)
    	;
}


/* configCHECK_FOR_STACK_OVERFLOW != 0 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;

    //taskDISABLE_INTERRUPTS();
    __disable_irq();

    for (;;)
    	;
}


/* configUSE_MALLOC_FAILED_HOOK == 1 (pvPortMalloc could not satisfy a request) */
void vApplicationMallocFailedHook(void)
{
    //taskDISABLE_INTERRUPTS();
    __disable_irq();

    for (;;)
    	;
}


void vApplicationIdleHook( void )
{
	// Enter sleep mode...
	idle_counter++;
	__WFI();
}


void vApplicationTickHook( void )
{
	// Do nothing...
	__NOP();
	__NOP();
}
