#include <stm32f4xx_spi.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>

#define spi_select() (PAout(15) = 0)
#define spi_unselect()  (PAout(15) = 1)

static void w5500_init_spi(void) {
    RCC->AHB1ENR.bits.gpioa = 1;
    RCC->AHB1ENR.bits.gpiob = 1;
    RCC->APB2ENR.bits.spi1 = 1;
    // 功能选择
    GPIOA->AFR.bits.pin7 = GPIO_AF_SPI1;
    GPIOB->AFR.bits.pin3 = GPIO_AF_SPI1;
    GPIOB->AFR.bits.pin4 = GPIO_AF_SPI1;
    // 片选引脚PA15
    struct gpio_pin_conf pincof;
    pincof.mode = GPIO_Mode_Out;
    pincof.otype = GPIO_OType_PP;
    pincof.pull = GPIO_Pull_Up;
    pincof.speed = GPIO_OSpeed_High;
    gpio_init(GPIOA, GPIO_Pin_15, &pincof);
    // PA7->MOSI, PB3->SCK, PB4->MISO
    pincof.mode = GPIO_Mode_Af;
    gpio_init(GPIOA, GPIO_Pin_7, &pincof);
    gpio_init(GPIOB, GPIO_Pin_3 | GPIO_Pin_4, &pincof);
    // SPI1配置
    SPI1->CR1.bits.SPE = 0;
    SPI1->CR1.bits.MSTR = 1;
    SPI1->CR1.bits.DFF = SPI_Data_Size_8b; // 8位
    SPI1->CR1.bits.CPHA = 0;
    SPI1->CR1.bits.CPOL = 0;
    SPI1->CR1.bits.BR = SPI_Prescaler_2;
    SPI1->CR1.bits.LSBFIRST = 0;
    SPI1->CR1.bits.SSM = 1;
    SPI1->CR1.bits.SSI = 1;
    SPI1->CR1.bits.SPE = 1;
    // 片选
    spi_unselect();
}

uint8 data;
void w5500_init(void) {
    w5500_init_spi();

    spi_select();

    data = spi_exchange(SPI1, 0x00);
    data = spi_exchange(SPI1, 0x2E);
    data = spi_exchange(SPI1, 0x00);
    data = spi_exchange(SPI1, 0x00);

    spi_unselect();
}
