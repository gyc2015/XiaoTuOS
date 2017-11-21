#include <stm32f407.h>
#include <xtos.h>
#include <power.h>
#include <led.h>
#include <uart4.h>

void config_interruts(void);

void tim8_ch1_pc6_gpio_init(void) {
    RCC->AHB1ENR.bits.gpioc = 1;

    GPIOC->AFR.bits.pin6 = GPIO_AF_TIM8;
    GPIOC->MODER.bits.pin6 = GPIO_Mode_Af;
    GPIOC->OTYPER.bits.pin6 = GPIO_OType_PP;
    GPIOC->PUPDR.bits.pin6 = GPIO_Pull_Up;
    GPIOC->OSPEEDR.bits.pin6 = GPIO_OSpeed_Very_High;
}

void tim1_init(void) {
    RCC->APB2ENR.bits.tim1 = 1;
    // 时机单元
    TIM1->CR1.bits.DIR = TIM_COUNT_DIR_UP;
    TIM1->PSC = 167;
    TIM1->ARR = 65535;
    TIM1->EGR.all |= 0x02;
    TIM1->CR1.bits.ARPE = 1;
    // PA8 : TIM1CH1
    RCC->AHB1ENR.bits.gpioa = 1;
    GPIOA->AFR.bits.pin8 = GPIO_AF_TIM1;
    GPIOA->MODER.bits.pin8 = GPIO_Mode_Af;
    GPIOA->OTYPER.bits.pin8 = GPIO_Pull_No;
    GPIOA->OSPEEDR.bits.pin8 = GPIO_OType_OD;
    // 输入通道
    union timer_chanel_mode cfg;
    cfg.ic.CCxS = TIM_Channel_Mode_Input1;
    cfg.ic.ICxPSC = TIM_ICMode_PSC_0;
    cfg.ic.ICxF = 0xF;
    union timer_chanel_en cen;
    cen.bits.CCxE = 1;
    cen.bits.CCxP = 0;
    cen.bits.CCxNP = 0;
    timer_set_ccmr(TIM1, 1, cfg);
    timer_set_ccer(TIM1, 1, cen);
    // 使能中断
    TIM1->DIER.bits.CC1IE = 1;
    TIM1->CR1.bits.CEN = 1;
}

uint32 gDuring = 0;
void TIM1_CC_IRQHandler(void) {
    if (1 == TIM1->SR.bits.CC1IF) {
        gDuring = TIM1->CCR1;
        TIM1->CNT = 0;
    }
    TIM1->SR.bits.CC1IF = 0;
}

void config_interruts(void);

uint8 gUartByte = 0;

int main(void) {
    tim8_ch1_pc6_gpio_init();
    led_pwm_init();
    tim1_init();
    uart4_init(115200);

    TIM8->CCR1 = 100;

    config_interruts();

    uart4_send_str("wuhahahahaha\r\n");

    while (1) {
        switch (gUartByte) {
        case 'a':
            uart4_send_bytes((uint8*)&gDuring, 4);
            gUartByte = 0;
            break;
        }
    }
}

