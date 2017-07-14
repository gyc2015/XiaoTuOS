#include <stm32f407.h>
#include <led.h>
#include <uart4.h>

/***************************************************/

uint32 src_buffer[32] = {
    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80 };

uint32 dst_buffer[32] = { 0 };

void dma_init() {
    RCC->AHB1ENR.bits.dma2 = 1;
    DMA_ResetStream(DMA2_Stream0);

    DMA2_Stream0->CR.bits.CHSEL = 0;            // 通道选择
    DMA2_Stream0->CR.bits.DIR = DMA_DIR_M2M;    // 传输方向
    DMA2_Stream0->CR.bits.CIRC = 0;             // 关闭循环模式
    DMA2_Stream0->CR.bits.PL = DMA_Priority_High;// 优先级
    DMA2_Stream0->CR.bits.PINC = 1;             // 外设增长
    DMA2_Stream0->CR.bits.PSIZE = DMA_PSIZE_32Bits; // 外设数据宽度
    DMA2_Stream0->CR.bits.MINC = 1;             // 内存增长
    DMA2_Stream0->CR.bits.MSIZE = DMA_PSIZE_32Bits; // 内存数据宽度
    DMA2_Stream0->CR.bits.MBURST = DMA_Burst_0; // Single Transfer
    DMA2_Stream0->CR.bits.PBURST = DMA_Burst_0; // Single Transfer

    DMA2_Stream0->FCR.bits.DMDIS = 0;           // 保持Direct Mode
    DMA2_Stream0->FCR.bits.FTH = DMA_FIFO_4;

    DMA2_Stream0->PAR = (uint32)src_buffer;
    DMA2_Stream0->M0AR = (uint32)dst_buffer;
    DMA2_Stream0->NDTR.all = 32;

    DMA2_Stream0->CR.bits.EN = 1;
}
/***************************************************/

void config_interruts(void);

int main(void) {
    led_init();
    dma_init();

    config_interruts();

    LED_R = LED_ON;
    LED_G = LED_OFF;
    LED_B = LED_OFF;

    while (!(0x01 && DMA2_Stream0->CR.all));

    for (int i = 0; i < 32; i++) {
        if (src_buffer[i] != dst_buffer[i]) {
            LED_R = LED_OFF;
            LED_G = LED_ON;
            LED_B = LED_OFF;
        }
    }

    while (1) {
        
    }
}
