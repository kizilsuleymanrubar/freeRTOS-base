# FreeRTOS-base
 
A minimal, clean FreeRTOS starting point for the **STM32F411RE** (Cortex-M4F), created as an empty STM32CubeIDE project with FreeRTOS integrated by hand. It is meant to be a base you can clone and build on: a tuned `FreeRTOSConfig.h`, error-catching hooks, and a small demo with two tasks.
 
## Features
 
- FreeRTOS **V10.3.1** (kernel files taken from ST's STM32Cube middleware) and `ARM_CM4F` port
- Hardware FPU support (lazy stacking handled by the port)
- Cortex-M interrupt priority setup done correctly (4 preempt bits, `NVIC_SetPriorityGrouping(3)`)
- Newlib re-entrancy enabled (`configUSE_NEWLIB_REENTRANT`), so `printf`, `errno` and friends are per-task
- Debug-friendly error hooks: assert, stack overflow and malloc failure all stop the system in one place
- Idle hook enters sleep with `WFI`
- Small, readable demo: one periodic LED task and one FPU test task
## Hardware
 
| Item | Value |
|---|---|
| MCU | STM32F411RE (Cortex-M4F, 128 KB RAM, 512 KB Flash) |
| LED | GPIOA pin 5 (user LED on the Nucleo-F411RE) |
| Clock | HSI, 16 MHz (`SystemCoreClock` is read at startup, so a crystal / PLL setup can be added later) |
 
## Demo behaviour
 
| Task | Period | What it does |
|---|---|---|
| `Task1` | 1000 ms (`vTaskDelayUntil`) | Toggles the LED, increments `task1_counter` |
| `Task2` | 500 ms (`vTaskDelay`) | Increments `task2_counter`, runs a float multiplication to exercise the FPU |
 
 
## Project files
 
| File | Role |
|---|---|
| `main.c` / `main.h` | Application entry, task creation; `main.h` collects the common includes |
| `led.c` / `led.h` | Minimal register-level LED driver (`LED_Init`, `LED_Toggle`) |
| `FreeRTOSConfig.h` | Kernel configuration |
| `freertos_hooks.c` | Assert, stack-overflow, malloc-failed, idle and tick hooks |
| `port.c`, `portmacro.h` | `ARM_CM4F` port (from ST middleware, unmodified) |
| `heap_4.c` | FreeRTOS heap (20 KB static array in `.bss`) |
| `sysmem.c`, `syscalls.c` | ST/CubeIDE newlib stubs (`_sbrk`, `_write`, ...) |
| `system_stm32f4xx.c` | CMSIS system initialization (`SystemInit`, `SystemCoreClockUpdate`) |
 
