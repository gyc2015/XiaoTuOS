#include <stm32f407.h>
#include <uart4.h>

/*
 * uart4_init - 初始化串口
 */
void uart4_init(uint32 baudrate) {
    RCC->AHB1ENR.bits.gpioa = 1;
    RCC->APB1ENR.bits.uart4 = 1;// 串口时钟使能
    // 功能选择
    // remark: 对于引脚的功能选择应当放在具体的配置之前
    // 否则初始化后，会通过串口发送一个0xFF的数到上位机
    GPIOA->AFR.bits.pin0 = GPIO_AF_UART4;
    GPIOA->AFR.bits.pin1 = GPIO_AF_UART4;
    // PA0 : tx
    GPIOA->MODER.bits.pin0 = GPIO_Mode_Af;
    GPIOA->OTYPER.bits.pin0 = GPIO_OType_PP;
    GPIOA->PUPDR.bits.pin0 = GPIO_Pull_Up;
    GPIOA->OSPEEDR.bits.pin0 = GPIO_OSpeed_High;
    // PA1 : rx
    GPIOA->MODER.bits.pin1 = GPIO_Mode_Af;
    GPIOA->PUPDR.bits.pin1 = GPIO_Pull_No;
    GPIOA->OTYPER.bits.pin1 = GPIO_OType_OD;

    uart_init(UART4, baudrate);
}

void uart4_send_byte(uint8 value) {
    UART4->DR.bits.byte = value;
    while (!UART4->SR.bits.TXE);
}

void uart4_send_bytes(const uint8 *buf, uint32 len) {
    for (uint32 i = 0; i < len; i++) {
        UART4->DR.bits.byte = buf[i];
        while (!UART4->SR.bits.TXE);
    }
}

void uart4_send_str(const uint8 *str) {
    while ('\0' != str[0]) {
        UART4->DR.bits.byte = str[0];
        while (!UART4->SR.bits.TXE);
        str++;
    }
}

void UART4_IRQHandler(void) {
    if (0 != UART4->SR.bits.RXNE) {
        uint8 data = UART4->DR.bits.byte;
        uart4_send_byte(data);
    }
}

