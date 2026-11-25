#include "stm32f4xx.h"


void LED_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER &= ~(3UL << (5 * 2));
    GPIOA->MODER |=  (1UL << (5 * 2));
}


void LED_Toggle(void)
{
    GPIOA->ODR ^= (1UL << 5);
}
