#include <stm32f407.h>
#include <uart4.h>

/*
 * uart4_init_gpio - 初始化端口配置
 */
static void uart4_init_gpio(void) {
    RCC->AHB1ENR.bits.gpioa = 1;
    struct gpio_pin_conf pincof, pincof1;
    // 功能选择
    // remark: 对于引脚的功能选择应当放在具体的配置之前
    // 否则初始化后，会通过串口发送一个0xFF的数到上位机
    GPIOA->AFR.bits.pin0 = 0x08;
    GPIOA->AFR.bits.pin1 = 0x08;
    // PA0 : tx
    pincof.mode = GPIO_Mode_Af;
    pincof.otype = GPIO_OType_PP;
    pincof.pull = GPIO_Pull_Up;
    pincof.speed = GPIO_OSpeed_High;
    gpio_init(GPIOA, GPIO_Pin_0, &pincof);

    // PA1 : rx
    pincof1.mode = GPIO_Mode_Af;
    pincof1.pull = GPIO_Pull_No;
    pincof1.otype = GPIO_OType_OD;
    gpio_init(GPIOA, GPIO_Pin_1, &pincof1);
}
/*
 * uart4_init - 初始化串口
 */
void uart4_init(uint32 baudrate) {
    uint32 tmp, mantissa, fraction;

    uart4_init_gpio();

    RCC->APB1ENR.bits.uart4 = 1;// 串口时钟使能
    
    UART4->CR1.bits.M = 0;      // 8数据位
    UART4->CR1.bits.PCE = 0;    // 无奇偶校验
    UART4->CR1.bits.RE = 1;     // 收
    UART4->CR1.bits.TE = 1;     // 发
    UART4->CR2.bits.STOP = USART_STOP_1bit; // 1位停止位

    UART4->CR3.bits.CTSE = 0;   // 关闭硬件控制流
    UART4->CR3.bits.RTSE = 0;

    UART4->CR1.bits.OVER8 = 0;  // 起始位16次重采样，并依此计算波特率
    tmp = (25 * 42000000) / (4 * baudrate);
    mantissa = tmp / 100;
    fraction = (16 * (tmp - 100 * mantissa) + 50) / 100;
    UART4->BRR.bits.mantissa = mantissa;
    UART4->BRR.bits.fraction = fraction;

    UART4->CR1.bits.RXNEIE = 1; // 开启接收中断
    UART4->CR1.bits.UE = 1;     // 开启串口
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

