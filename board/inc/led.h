/***********************************************************
 *
 * led.h - 三色灯驱动
 *
 ************************************** 高乙超.2017.0201 ***/
#pragma once

#include <stm32f4xx_gpio.h>

#define LED_R PIout(5)
#define LED_G PIout(6)
#define LED_B PIout(7)

#define LED_ON 0
#define LED_OFF 1

/*
 * led_init - 初始化三色灯
 */
void led_init(void);
/*
* led_pwm_init - 初始化PWM控制的三色灯
*/
void led_pwm_init(void);

/*
* led_set_color - 设置灯光颜色
*/
void led_set_color(uint8 r, uint8 g, uint8 b);


