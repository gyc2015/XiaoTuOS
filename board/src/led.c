/***********************************************************
 *
 * led.c - 三色灯驱动
 *
 ************************************** 高乙超.2017.0201 ***/
#include <stm32f407.h>
#include <led.h>
/*
 * led_init - 初始化三色灯
 */
void led_init(void) {
    RCC->AHB1ENR.bits.gpioi = 1;

    GPIOI->MODER.bits.pin5 = GPIO_Mode_Out;
    GPIOI->MODER.bits.pin6 = GPIO_Mode_Out;
    GPIOI->MODER.bits.pin7 = GPIO_Mode_Out;

    GPIOI->OTYPER.bits.pin5 = GPIO_OType_PP;
    GPIOI->OTYPER.bits.pin6 = GPIO_OType_PP;
    GPIOI->OTYPER.bits.pin7 = GPIO_OType_PP;

    GPIOI->PUPDR.bits.pin5 = GPIO_Pull_Up;
    GPIOI->PUPDR.bits.pin6 = GPIO_Pull_Up;
    GPIOI->PUPDR.bits.pin7 = GPIO_Pull_Up;

    GPIOI->OSPEEDR.bits.pin5 = GPIO_OSpeed_Very_High;
    GPIOI->OSPEEDR.bits.pin6 = GPIO_OSpeed_Very_High;
    GPIOI->OSPEEDR.bits.pin7 = GPIO_OSpeed_Very_High;

    LED_R = LED_OFF;
    LED_G = LED_OFF;
    LED_B = LED_OFF;
}
