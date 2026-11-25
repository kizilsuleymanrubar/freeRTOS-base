#include "main.h"
#include "led.h"


volatile uint32_t task1_counter = 0;
volatile uint32_t task2_counter = 0;
volatile float    fpu_test      = 1.0f;


void vTask1(void *pvParameters)
{
    (void)pvParameters;

    TickType_t last_wakeup_time;
    const TickType_t period = pdMS_TO_TICKS(1000);

    last_wakeup_time = xTaskGetTickCount();

    for(;;)
    {
        task1_counter++;
        LED_Toggle();
        vTaskDelayUntil(&last_wakeup_time, period);
    }
}


void vTask2(void *pvParameters)
{
    (void)pvParameters;

    for(;;)
    {
        task2_counter++;
        fpu_test *= 1.05f;

        if (fpu_test > 1000.0f)
        	fpu_test = 1.0f;

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}


int main(void)
{
    SystemCoreClockUpdate();
    NVIC_SetPriorityGrouping(3);
    LED_Init();

    BaseType_t r1 = xTaskCreate(vTask1, "Task1", 256, NULL, 1, NULL);
    BaseType_t r2 = xTaskCreate(vTask2, "Task2", 256, NULL, 1, NULL);
    configASSERT((r1 == pdPASS) && (r2 == pdPASS));

    vTaskStartScheduler();

    while (1)
    	;
}
