#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H


#if defined(__ICCARM__) || defined(__CC_ARM) || defined(__GNUC__)
  #include <stdint.h>
  extern uint32_t SystemCoreClock;
  void xPortSysTickHandler(void);
  void vAssertCalled(const char *file, int line);
#endif


#ifndef CMSIS_device_header
  #define CMSIS_device_header "stm32f4xx.h"
#endif


/* Hardware and Core Settings */
#define configCPU_CLOCK_HZ                       ( SystemCoreClock )
#define configTICK_RATE_HZ                       ((TickType_t)1000)


/* Task and Scheduler Settings */
#define configUSE_PREEMPTION                     1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION  1      /* CLZ based, requires configMAX_PRIORITIES <= 32 */
#define configMAX_PRIORITIES                     ( 8 )
#define configMINIMAL_STACK_SIZE                 ((uint16_t)128)
#define configMAX_TASK_NAME_LEN                  ( 16 )
#define configUSE_16_BIT_TICKS                   0
#define configIDLE_SHOULD_YIELD                  1
#define configUSE_IDLE_HOOK                      1
#define configUSE_TICK_HOOK                      0


/* Memory Management (heap_4.c) */
#define configSUPPORT_STATIC_ALLOCATION          0
#define configSUPPORT_DYNAMIC_ALLOCATION         1
#define configTOTAL_HEAP_SIZE                    ((size_t)(20 * 1024))
#define configUSE_NEWLIB_REENTRANT               1      /* per-task newlib _reent; needs newlib/newlib-nano */


/* Error detection hooks (defined in freertos_hooks.c) */
#define configCHECK_FOR_STACK_OVERFLOW           2
#define configUSE_MALLOC_FAILED_HOOK             1


/* Synchronization and Software Timers */
#define configUSE_MUTEXES                        1
#define configUSE_RECURSIVE_MUTEXES              1
#define configUSE_COUNTING_SEMAPHORES            1
#define configQUEUE_REGISTRY_SIZE                8
#define configUSE_TRACE_FACILITY                 1
#define configUSE_CO_ROUTINES                    0
#define configMAX_CO_ROUTINE_PRIORITIES          ( 2 )
#define configUSE_TIMERS                         1
#define configTIMER_TASK_PRIORITY                ( 2 )
#define configTIMER_QUEUE_LENGTH                 10
#define configTIMER_TASK_STACK_DEPTH             256
#define configMESSAGE_BUFFER_LENGTH_TYPE         size_t


/* Included API Functions */
#define INCLUDE_vTaskPrioritySet                 1
#define INCLUDE_uxTaskPriorityGet                1
#define INCLUDE_vTaskDelete                      1
#define INCLUDE_vTaskCleanUpResources            0
#define INCLUDE_vTaskSuspend                     1
#define INCLUDE_vTaskDelayUntil                  1
#define INCLUDE_vTaskDelay                       1
#define INCLUDE_xTaskGetSchedulerState           1
#define INCLUDE_xTimerPendFunctionCall           1
#define INCLUDE_xQueueGetMutexHolder             1
#define INCLUDE_uxTaskGetStackHighWaterMark      1
#define INCLUDE_xTaskGetCurrentTaskHandle        1
#define INCLUDE_eTaskGetState                    1


/* Cortex-M Interrupt Priorities
 * STM32F4 has 4 priority bits. Use NVIC_SetPriorityGrouping(3) (all preempt bits).
 * ISRs calling FreeRTOS "FromISR" APIs must use priority 5..15 (numerically).
 * Priorities 0..4 are never masked by FreeRTOS; do not call FreeRTOS APIs from them. */
#ifdef __NVIC_PRIO_BITS
  #define configPRIO_BITS                        __NVIC_PRIO_BITS
#else
  #define configPRIO_BITS                        4
#endif


#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5
#define configKERNEL_INTERRUPT_PRIORITY          ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY     ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )


/* Assertion: vAssertCalled() is in freertos_hooks.c (put a breakpoint there) */
#define configASSERT( x )                        do { if( ( x ) == 0 ) { vAssertCalled( __FILE__, __LINE__ ); } } while( 0 )


/* Interrupt Vector Mappings */
#define vPortSVCHandler                          SVC_Handler
#define xPortPendSVHandler                       PendSV_Handler
#define xPortSysTickHandler                      SysTick_Handler

#endif /* FREERTOS_CONFIG_H */
