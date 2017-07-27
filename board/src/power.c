/***********************************************************
 *
 * power - ������
 *
 ************************************** ���ҳ�.2017.0618 ***/
#include <power.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>

#define ADC_REF 2.483
/*
 * power_init - ��ʼ����Դ���
 */
void power_init(void) {
    // ʱ��
    RCC->APB2ENR.bits.adc1 = 1;
    RCC->APB2ENR.bits.adc3 = 1;
    RCC->AHB1ENR.bits.gpioc = 1;
    RCC->AHB1ENR.bits.gpiof = 1;

    // PC4 -> VSENSE, PC5 -> ISENSE
    GPIOC->MODER.bits.pin4 = GPIO_Mode_Analog;
    GPIOC->PUPDR.bits.pin4 = GPIO_Pull_No;
    GPIOC->MODER.bits.pin5 = GPIO_Mode_Analog;
    GPIOC->PUPDR.bits.pin5 = GPIO_Pull_No;
    // PF5 -> 1V2SENSE, PF6 -> 3V3SENSE, PF7 -> 2V5SENSE
    GPIOF->MODER.bits.pin5 = GPIO_Mode_Analog;
    GPIOF->PUPDR.bits.pin5 = GPIO_Pull_No;
    GPIOF->MODER.bits.pin6 = GPIO_Mode_Analog;
    GPIOF->PUPDR.bits.pin6 = GPIO_Pull_No;
    GPIOF->MODER.bits.pin7 = GPIO_Mode_Analog;
    GPIOF->PUPDR.bits.pin7 = GPIO_Pull_No;

    ADC_COM->CCR.bits.MULTI = ADC_Mode_Independent;         // ADC��������
    ADC_COM->CCR.bits.DELAY = ADC_SamplingDelay_5Cycles;    // ������������֮���ʱ����
    ADC_COM->CCR.bits.DMA = 0;                              // �ر�DMA
    ADC_COM->CCR.bits.ADCPRE = ADC_Prescaler_Div6;          // ��Ƶϵ��

    ADC1->CR1.bits.RES = ADC_RES_12Bits;                    // �ֱ���
    ADC1->CR1.bits.SCAN = 0;                                // �ر�SCANģʽ
    ADC1->CR2.bits.CONT = 0;                                // �ر�����ת��ģʽ
    ADC1->CR2.bits.EXTEN = ADC_ExtTrigger_Dis;              // ��ֹ�������
    ADC1->CR2.bits.ALIGN = ADC_Align_Right;                 // �Ҷ���
    ADC1->SQR1.bits.L = 1 - ADC_SQR_LOffset;                // 1��ת���ڹ���������

    ADC3->CR1.bits.RES = ADC_RES_12Bits;                    // �ֱ���
    ADC3->CR1.bits.SCAN = 0;                                // �ر�SCANģʽ
    ADC3->CR2.bits.CONT = 0;                                // �ر�����ת��ģʽ
    ADC3->CR2.bits.EXTEN = ADC_ExtTrigger_Dis;              // ��ֹ�������
    ADC3->CR2.bits.ALIGN = ADC_Align_Right;                 // �Ҷ���
    ADC3->SQR1.bits.L = 1 - ADC_SQR_LOffset;                // 1��ת���ڹ���������

    ADC1->CR2.bits.ADON = 1;
    ADC3->CR2.bits.ADON = 1;
}

float power_get_vcc(void) {
    // PC4, ADC1_IN14
    ADC1->SMPR1.bits.SMP4 = ADC_Sample_Time_480Cycles;
    ADC1->SQR3.bits.SQ1 = 14;
    ADC1->CR2.bits.SWSTART = 1;
    while (!ADC1->SR.bits.EOC);
    uint16 data = ADC1->DR;
    return 6.0 * data * ADC_REF / 4096.0;
}

float power_get_current(void) {
    // PC5, ADC1_IN15
    ADC1->SMPR1.bits.SMP4 = ADC_Sample_Time_480Cycles;
    ADC1->SQR3.bits.SQ1 = 15;
    ADC1->CR2.bits.SWSTART = 1;
    while (!ADC1->SR.bits.EOC);
    uint16 data = ADC1->DR;
    return 0.5 * data * ADC_REF / 4096.0;
}

float power_get_D1V2(void) {
    // PF5, ADC3_IN15
    ADC3->SMPR1.bits.SMP4 = ADC_Sample_Time_480Cycles;
    ADC3->SQR3.bits.SQ1 = 15;
    ADC3->CR2.bits.SWSTART = 1;
    while (!ADC3->SR.bits.EOC);
    uint16 data = ADC3->DR;
    return data * ADC_REF / 4096.0;
}

float power_get_D3V3(void) {
    // PF6, ADC3_IN4
    ADC3->SMPR2.bits.SMP4 = ADC_Sample_Time_480Cycles;
    ADC3->SQR3.bits.SQ1 = 4;
    ADC3->CR2.bits.SWSTART = 1;
    while (!ADC3->SR.bits.EOC);
    uint16 data = ADC3->DR;
    return 2.0 * data * ADC_REF / 4096.0;
}

float power_get_A2V5(void) {
    // PF7, ADC3_IN5
    ADC3->SMPR2.bits.SMP4 = ADC_Sample_Time_480Cycles;
    ADC3->SQR3.bits.SQ1 =5;
    ADC3->CR2.bits.SWSTART = 1;
    while (!ADC3->SR.bits.EOC);
    uint16 data = ADC3->DR;
    return 2.0 * data * ADC_REF / 4096.0;
}


