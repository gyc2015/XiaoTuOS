/***********************************************************
 *
 * led.h - ��ɫ������
 *
 ************************************** ���ҳ�.2017.0201 ***/
#pragma once

#include <stm32f4xx_gpio.h>

#define LED_R PIout(5)
#define LED_G PIout(6)
#define LED_B PIout(7)

#define LED_ON 0
#define LED_OFF 1

/*
 * led_init - ��ʼ����ɫ��
 */
void led_init(void);
/*
* led_pwm_init - ��ʼ��PWM���Ƶ���ɫ��
*/
void led_pwm_init(void);

/*
* led_set_color - ���õƹ���ɫ
*/
void led_set_color(uint8 r, uint8 g, uint8 b);


