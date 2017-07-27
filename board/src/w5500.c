#include <stm32f4xx_spi.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <w5500.h>

#define spi_select() (PAout(15) = 0)
#define spi_unselect()  (PAout(15) = 1)
#define W5500_SPI   SPI1

struct w5500 gW5500 = {
    .mac = { 0x00,0x98,0xdc,0x42,0x61,0x11 },
    .ip = { 192,168,0,10 },
    .sub = { 255,255,255,0 },
    .gw = { 192,168,0,1 }
};
/*
 * w5500_init_spi - 初始化W5500的SPI端口
 */
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
    // W5500_SPI配置
    W5500_SPI->CR1.bits.SPE = 0;
    W5500_SPI->CR1.bits.MSTR = 1;
    W5500_SPI->CR1.bits.DFF = SPI_Data_Size_8b; // 8位
    W5500_SPI->CR1.bits.CPHA = 0;
    W5500_SPI->CR1.bits.CPOL = 0;
    W5500_SPI->CR1.bits.BR = SPI_Prescaler_2;
    W5500_SPI->CR1.bits.LSBFIRST = 0;
    W5500_SPI->CR1.bits.SSM = 1;
    W5500_SPI->CR1.bits.SSI = 1;
    W5500_SPI->CR1.bits.SPE = 1;
    // 片选
    spi_unselect();
}

/************************************************/

void w5500_init(void) {
    w5500_init_spi();

    int data = w5500_read_byte(0x002E00);

}

uint8 w5500_read_byte(uint32 addrbsb) {
    spi_select();

    spi_exchange(W5500_SPI, (addrbsb & 0x00FF0000) >> 16);
    spi_exchange(W5500_SPI, (addrbsb & 0x0000FF00) >> 8);
    spi_exchange(W5500_SPI, (addrbsb & 0x000000F8));
    uint8 data = spi_exchange(W5500_SPI, 0x00);

    spi_unselect();
    return data;
}

void w5500_write_byte(uint32 addrbsb, uint8 data) {
    spi_select();

    spi_exchange(W5500_SPI, (addrbsb & 0x00FF0000) >> 16);
    spi_exchange(W5500_SPI, (addrbsb & 0x0000FF00) >> 8);
    spi_exchange(W5500_SPI, (addrbsb & 0x000000F8) + 4);
    spi_exchange(W5500_SPI, data);

    spi_unselect();
}

void w5500_read_bytes(uint32 addrbsb, uint8 *buf, int len) {
    spi_select();

    spi_exchange(W5500_SPI, (addrbsb & 0x00FF0000) >> 16);
    spi_exchange(W5500_SPI, (addrbsb & 0x0000FF00) >> 8);
    spi_exchange(W5500_SPI, (addrbsb & 0x000000F8));

    for (int i = 0; i < len; i++)
        buf[i] = spi_exchange(W5500_SPI, 0x00);

    spi_unselect();
}

void w5500_write_bytes(uint32 addrbsb, const uint8 *buf, int len) {
    spi_select();

    spi_exchange(W5500_SPI, (addrbsb & 0x00FF0000) >> 16);
    spi_exchange(W5500_SPI, (addrbsb & 0x0000FF00) >> 8);
    spi_exchange(W5500_SPI, (addrbsb & 0x000000F8) + 4);

    for (int i = 0; i < len; i++)
        spi_exchange(W5500_SPI, buf[i]);

    spi_unselect();
}

