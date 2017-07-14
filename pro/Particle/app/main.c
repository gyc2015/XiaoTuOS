#include <stm32f407.h>

#define KEY (GPIOH->IDR.bits.pin15)

#define LED_R (GPIOI->ODR.bits.pin5)
#define LED_G (GPIOI->ODR.bits.pin6)
#define LED_B (GPIOI->ODR.bits.pin7)
#define ON 0
#define OFF 1

int times = 0;
bool state = FALSE;

void init_led() {
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
}

void init_key() {
    RCC->AHB1ENR.bits.gpioh = 1;

    GPIOH->MODER.bits.pin15 = GPIO_Mode_In;
    GPIOH->OSPEEDR.bits.pin15 = GPIO_OSpeed_Very_High;
    GPIOH->PUPDR.bits.pin15 = GPIO_Pull_No;
}

void init_exti() {
    // 配置GPIOH为EXTI15的信号源
    RCC->APB2ENR.bits.syscfg = 1;
    SYSCFG->EXTICR.bits.exti15 = Exti_PortSource_H;
    // 开启外部中断关闭事件
    EXTI->IMR.bits.tr15 = 1;
    EXTI->EMR.bits.tr15 = 0;
    // 下降沿触发
    EXTI->RTSR.bits.tr15 = 0;
    EXTI->FTSR.bits.tr15 = 1;
    // 外部中断的优先级和使能
    NVIC->IPR.bits.EXTI15_10 = 0x00;
    NVIC->ISER.bits.EXTI15_10 = 1;
}

void delay(int c) {
    for (int i = 0; i < c; i++);
}

void EXTI15_10_IRQHandler(void) {
    if (EXTI->PR.bits.tr15) {
        delay(1000);
        if (!KEY) {
            times++;
            if (times > 2)
                times = 0;
            switch (times) {
            case 0:
                LED_R = ON;
                LED_G = OFF;
                LED_B = OFF;
                break;
            case 1:
                LED_R = OFF;
                LED_G = ON;
                LED_B = OFF;
                break;
            case 2:
                LED_R = OFF;
                LED_G = OFF;
                LED_B = ON;
                break;
            default:
                break;
            }
        }
        EXTI->PR.bits.tr15 = 1;
    }
}

int main(void) {
    init_led();
    init_key();
    init_exti();

    GPIOI->ODR.bits.pin5 = 1;
    GPIOI->ODR.bits.pin6 = 1;
    GPIOI->ODR.bits.pin7 = 1;

    while (1) {
        delay(100);
    }
}
