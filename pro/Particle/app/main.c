#include <stm32f407.h>

int data;

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

int main(void) {
    init_led();

    data = 31;

    GPIOI->BSRR.hwords.reset.bits.pin5 = 1;
    GPIOI->BSRR.hwords.reset.bits.pin7 = 1;
    GPIOI->BSRR.hwords.set.bits.pin6 = 1;

    GPIOI->ODR.bits.pin5 = 0;
    GPIOI->ODR.bits.pin6 = 0;
    GPIOI->ODR.bits.pin7 = 0;

    GPIOI->ODR.bits.pin5 = 0;
    GPIOI->ODR.bits.pin6 = 0;
    GPIOI->ODR.bits.pin7 = 1;

    GPIOI->ODR.bits.pin5 = 0;
    GPIOI->ODR.bits.pin6 = 1;
    GPIOI->ODR.bits.pin7 = 0;

    GPIOI->ODR.bits.pin5 = 0;
    GPIOI->ODR.bits.pin6 = 1;
    GPIOI->ODR.bits.pin7 = 1;

    GPIOI->ODR.bits.pin5 = 1;
    GPIOI->ODR.bits.pin6 = 0;
    GPIOI->ODR.bits.pin7 = 0;

    GPIOI->ODR.bits.pin5 = 1;
    GPIOI->ODR.bits.pin6 = 0;
    GPIOI->ODR.bits.pin7 = 1;

    GPIOI->ODR.bits.pin5 = 1;
    GPIOI->ODR.bits.pin6 = 1;
    GPIOI->ODR.bits.pin7 = 0;

    GPIOI->ODR.bits.pin5 = 1;
    GPIOI->ODR.bits.pin6 = 1;
    GPIOI->ODR.bits.pin7 = 1;

    while (1) {

    }
}
