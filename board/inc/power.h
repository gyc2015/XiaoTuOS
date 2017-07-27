/***********************************************************
 *
 * power - ������
 *
 ************************************** ���ҳ�.2017.0618 ***/
#pragma once

#include <stm32f4xx_adc.h>

/*
 * power_init - ��ʼ����Դ���
 */
void power_init(void);

float power_get_vcc(void);
float power_get_current(void);
float power_get_D1V2(void);
float power_get_D3V3(void);
float power_get_A2V5(void);
