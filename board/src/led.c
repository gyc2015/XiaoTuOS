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

static void led_pwmio_init(void) {
    RCC->AHB1ENR.bits.gpioi = 1;
    // 功能选择, TIM8的通道1,2,3
    GPIOI->AFR.bits.pin5 = 0x03;
    GPIOI->AFR.bits.pin6 = 0x03;
    GPIOI->AFR.bits.pin7 = 0x03;

    GPIOI->MODER.bits.pin5 = GPIO_Mode_Af;
    GPIOI->MODER.bits.pin6 = GPIO_Mode_Af;
    GPIOI->MODER.bits.pin7 = GPIO_Mode_Af;

    GPIOI->OTYPER.bits.pin5 = GPIO_OType_PP;
    GPIOI->OTYPER.bits.pin6 = GPIO_OType_PP;
    GPIOI->OTYPER.bits.pin7 = GPIO_OType_PP;

    GPIOI->PUPDR.bits.pin5 = GPIO_Pull_Up;
    GPIOI->PUPDR.bits.pin6 = GPIO_Pull_Up;
    GPIOI->PUPDR.bits.pin7 = GPIO_Pull_Up;

    GPIOI->OSPEEDR.bits.pin5 = GPIO_OSpeed_Very_High;
    GPIOI->OSPEEDR.bits.pin6 = GPIO_OSpeed_Very_High;
    GPIOI->OSPEEDR.bits.pin7 = GPIO_OSpeed_Very_High;
}

/*
* led_pwm_init - 初始化PWM控制的三色灯
*/
void led_pwm_init(void) {
    led_pwmio_init();

    RCC->APB2ENR.bits.tim8 = 1;
    TIM8->CR1.bits.DIR = TIM_COUNT_DIR_UP;
    TIM8->PSC = 4999;
    TIM8->ARR = 255;
    TIM8->EGR.bits.UG = 1;
    TIM8->DIER.bits.UIE = 1;

    TIM8->CR1.bits.ARPE = 1;

    union timer_chanel_mode cfg;
    cfg.oc.OCxM = TIM_OCMode_PWM2;
    cfg.oc.OCxPE = 1;
    union timer_chanel_en cen;
    cen.bits.CCxE = 1;
    cen.bits.CCxNE = 0;
    cen.bits.CCxP = 0;
    cen.bits.CCxNP = 0;

    timer_set_ccmr(TIM8, 1, cfg);
    timer_set_ccmr(TIM8, 2, cfg);
    timer_set_ccmr(TIM8, 3, cfg);

    timer_set_ccer(TIM8, 1, cen);
    timer_set_ccer(TIM8, 2, cen);
    timer_set_ccer(TIM8, 3, cen);

    TIM8->CR2.bits.OIS1 = 0;
    TIM8->CR2.bits.OIS2 = 0;
    TIM8->CR2.bits.OIS3 = 0;

    TIM8->CCR1 = 0;
    TIM8->CCR2 = 0;
    TIM8->CCR3 = 0;
    TIM8->CR1.bits.CEN = 1;
    TIM8->BDTR.bits.MOE = 1;
}

/*
* led_set_color - 设置灯光颜色
*/
void led_set_color(uint8 r, uint8 g, uint8 b) {
    TIM8->CCR1 = r;
    TIM8->CCR2 = g;
    TIM8->CCR3 = b;
}
