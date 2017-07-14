/********************************************************************
 *
 *  Nested Vectored Interrupt Controller, NVIC
 *
 *  关于NVIC的详细内容参见ST公司的Cortex-M4 programming manual(PM0214)文档
 *  http://gaoyichao.com/Xiaotu/?book=mcu_stm32f407&title=cortex_m4_nvic
 *
 *	高乙超
 *  gaoyichao_2016@126.com
 *
 *******************************************************************/
#ifndef CORTEX_M4_NVIC_H
#define CORTEX_M4_NVIC_H

#include <types.h>

/*
 * vector_table_1bit - 向量表的位定义,3个32bit
 */
struct vector_table_1bit {
    uint32 WWDG : 1;            /* 0 */
    uint32 PVD : 1;             /* 1 */
    uint32 TAMP_STAMP : 1;      /* 2 */
    uint32 RTC_WKUP : 1;        /* 3 */
    uint32 FLASH : 1;           /* 4 */
    uint32 RCC : 1;             /* 5 */
    uint32 EXTI0 : 1;           /* 6 */
    uint32 EXTI1 : 1;           /* 7 */
    
    uint32 EXTI2 : 1;           /* 8 */
    uint32 EXTI3 : 1;           /* 9 */
    uint32 EXTI4 : 1;           /* 10 */
    uint32 DMA1_Stream0 : 1;    /* 11 */
    uint32 DMA1_Stream1 : 1;    /* 12 */
    uint32 DMA1_Stream2 : 1;    /* 13 */
    uint32 DMA1_Stream3 : 1;    /* 14 */
    uint32 DMA1_Stream4 : 1;    /* 15 */
    
    uint32 DMA1_Stream5 : 1;    /* 16 */
    uint32 DMA1_Stream6 : 1;    /* 17 */
    uint32 ADC : 1;             /* 18 */
    uint32 CAN1_TX : 1;         /* 19 */
    uint32 CAN1_RX0 : 1;        /* 20 */
    uint32 CAN1_RX1 : 1;        /* 21 */
    uint32 CAN1_SCE : 1;        /* 22 */
    uint32 EXTI9_5 : 1;         /* 23 */
    
    uint32 TIM1_BRK_TIM9 : 1;   /* 24 */
    uint32 TIM1_UP_TIM10 : 1;   /* 25 */
    uint32 TIM1_TRG_COM_TIM11 : 1; /* 26 */
    uint32 TIM1_CC : 1;         /* 27 */
    uint32 TIM2 : 1;            /* 28 */
    uint32 TIM3 : 1;            /* 29 */
    uint32 TIM4 : 1;            /* 30 */
    uint32 I2C1_EV : 1;         /* 31 */
    // 1
    uint32 I2C1_ER : 1;         /* 32 */
    uint32 I2C2_EV : 1;         /* 33 */
    uint32 I2C2_ER : 1;         /* 34 */
    uint32 SPI1 : 1;            /* 35 */
    uint32 SPI2 : 1;            /* 36 */
    uint32 USART1 : 1;          /* 37 */
    uint32 USART2 : 1;          /* 38 */
    uint32 USART3 : 1;          /* 39 */
    
    uint32 EXTI15_10 : 1;       /* 40 */
    uint32 RTC_Alarm : 1;       /* 41 */
    uint32 OTG_FS_WKUP : 1;     /* 42 */
    uint32 TIM8_BRK_TIM12 : 1;  /* 43 */
    uint32 TIM8_UP_TIM13 : 1;   /* 44 */
    uint32 TIM8_TRG_COM_TIM14 : 1; /* 45 */
    uint32 TIM8_CC : 1;         /* 46 */
    uint32 DMA1_Stream7 : 1;    /* 47 */
    
    uint32 FSMC : 1;            /* 48 */
    uint32 SDIO : 1;            /* 49 */
    uint32 TIM5 : 1;            /* 50 */
    uint32 SPI3 : 1;            /* 51 */
    uint32 UART4 : 1;           /* 52 */
    uint32 UART5 : 1;           /* 53 */
    uint32 TIM6_DAC : 1;        /* 54 */
    uint32 TIM7 : 1;            /* 55 */
    
    uint32 DMA2_Stream0 : 1;    /* 56 */
    uint32 DMA2_Stream1 : 1;    /* 57 */
    uint32 DMA2_Stream2 : 1;    /* 58 */
    uint32 DMA2_Stream3 : 1;    /* 59 */
    uint32 DMA2_Stream4 : 1;    /* 60 */
    uint32 ETH : 1;             /* 61 */
    uint32 ETH_WKUP : 1;        /* 62 */
    uint32 CAN2_TX : 1;         /* 63 */
    // 2
    uint32 CAN2_RX0 : 1;        /* 64 */
    uint32 CAN2_RX1 : 1;        /* 65 */
    uint32 CAN2_SCE : 1;        /* 66 */
    uint32 OTG_FS : 1;          /* 67 */
    uint32 DMA2_Stream5 : 1;    /* 68 */
    uint32 DMA2_Stream6 : 1;    /* 69 */
    uint32 DMA2_Stream7 : 1;    /* 70 */
    uint32 USART6 : 1;          /* 71 */
    
    uint32 I2C3_EV : 1;         /* 72 */
    uint32 I2C3_ER : 1;         /* 73 */
    uint32 OTG_HS_EP1_OUT : 1;  /* 74 */
    uint32 OTG_HS_EP1_IN : 1;   /* 75 */
    uint32 OTG_HS_WKUP : 1;     /* 76 */
    uint32 OTG_HS : 1;          /* 77 */
    uint32 DCMI : 1;            /* 78 */
    uint32 CRYP : 1;            /* 79 */
    
    uint32 HASH_RNG : 1;        /* 80 */
    uint32 FPU : 1;             /* 81 */
    uint32 reserved : 14;
    // 3
};

union nvic_1bit_register {
    struct vector_table_1bit bits;
    uint32 words[3];
};


/*
 * vector_table_1bit - 向量表的位定义,3个32bit
 */
struct vector_table_8bit {
    uint8 WWDG;            /* 0 */
    uint8 PVD;             /* 1 */
    uint8 TAMP_STAMP;      /* 2 */
    uint8 RTC_WKUP;        /* 3 */
    // 1
    uint8 FLASH;           /* 4 */
    uint8 RCC;             /* 5 */
    uint8 EXTI0;           /* 6 */
    uint8 EXTI1;           /* 7 */
    // 2
    uint8 EXTI2;           /* 8 */
    uint8 EXTI3;           /* 9 */
    uint8 EXTI4;           /* 10 */
    uint8 DMA1_Stream0;    /* 11 */
    // 3
    uint8 DMA1_Stream1;    /* 12 */
    uint8 DMA1_Stream2;    /* 13 */
    uint8 DMA1_Stream3;    /* 14 */
    uint8 DMA1_Stream4;    /* 15 */
    // 4
    uint8 DMA1_Stream5;    /* 16 */
    uint8 DMA1_Stream6;    /* 17 */
    uint8 ADC;             /* 18 */
    uint8 CAN1_TX;         /* 19 */
    // 5
    uint8 CAN1_RX0;        /* 20 */
    uint8 CAN1_RX1;        /* 21 */
    uint8 CAN1_SCE;        /* 22 */
    uint8 EXTI9_5;         /* 23 */
    // 6
    uint8 TIM1_BRK_TIM9;   /* 24 */
    uint8 TIM1_UP_TIM10;   /* 25 */
    uint8 TIM1_TRG_COM_TIM11; /* 26 */
    uint8 TIM1_CC;         /* 27 */
    // 7
    uint8 TIM2;            /* 28 */
    uint8 TIM3;            /* 29 */
    uint8 TIM4;            /* 30 */
    uint8 I2C1_EV;         /* 31 */
    // 8
    uint8 I2C1_ER;         /* 32 */
    uint8 I2C2_EV;         /* 33 */
    uint8 I2C2_ER;         /* 34 */
    uint8 SPI1;            /* 35 */
    // 9
    uint8 SPI2;            /* 36 */
    uint8 USART1;          /* 37 */
    uint8 USART2;          /* 38 */
    uint8 USART3;          /* 39 */
    // 10
    uint8 EXTI15_10;       /* 40 */
    uint8 RTC_Alarm;       /* 41 */
    uint8 OTG_FS_WKUP;     /* 42 */
    uint8 TIM8_BRK_TIM12;  /* 43 */
    // 11
    uint8 TIM8_UP_TIM13;   /* 44 */
    uint8 TIM8_TRG_COM_TIM14; /* 45 */
    uint8 TIM8_CC;         /* 46 */
    uint8 DMA1_Stream7;    /* 47 */
    // 12
    uint8 FSMC;            /* 48 */
    uint8 SDIO;            /* 49 */
    uint8 TIM5;            /* 50 */
    uint8 SPI3;            /* 51 */
    // 13
    uint8 UART4;           /* 52 */
    uint8 UART5;           /* 53 */
    uint8 TIM6_DAC;        /* 54 */
    uint8 TIM7;            /* 55 */
    // 14
    uint8 DMA2_Stream0;    /* 56 */
    uint8 DMA2_Stream1;    /* 57 */
    uint8 DMA2_Stream2;    /* 58 */
    uint8 DMA2_Stream3;    /* 59 */
    // 15
    uint8 DMA2_Stream4;    /* 60 */
    uint8 ETH;             /* 61 */
    uint8 ETH_WKUP;        /* 62 */
    uint8 CAN2_TX;         /* 63 */
    // 16
    uint8 CAN2_RX0;        /* 64 */
    uint8 CAN2_RX1;        /* 65 */
    uint8 CAN2_SCE;        /* 66 */
    uint8 OTG_FS;          /* 67 */
    // 17
    uint8 DMA2_Stream5;    /* 68 */
    uint8 DMA2_Stream6;    /* 69 */
    uint8 DMA2_Stream7;    /* 70 */
    uint8 USART6;          /* 71 */
    // 18
    uint8 I2C3_EV;         /* 72 */
    uint8 I2C3_ER;         /* 73 */
    uint8 OTG_HS_EP1_OUT;  /* 74 */
    uint8 OTG_HS_EP1_IN;   /* 75 */
    // 19
    uint8 OTG_HS_WKUP;     /* 76 */
    uint8 OTG_HS;          /* 77 */
    uint8 DCMI;            /* 78 */
    uint8 CRYP;            /* 79 */
    // 20
    uint8 HASH_RNG;        /* 80 */
    uint8 FPU;             /* 81 */
};

union nvic_8bit_register {
    struct vector_table_8bit bits;
    uint8 bytes[82];
};

struct nvic_stir_bits {
    uint32 intid : 8;
    uint32 r0 : 24;
};

union nvic_stir {
    struct nvic_stir_bits bits;
    uint32 all;
};

typedef struct nvic_regs {
    /* 中断使能寄存器 */
    volatile union nvic_1bit_register ISER;
    uint32 r0[29];
    /* 清除中断使能寄存器 */
    volatile union nvic_1bit_register ICER;
    uint32 r1[29];
    /* 中断Pending置位寄存器 */
    volatile union nvic_1bit_register ISPR;
    uint32 r2[29];
    /* 中断Pending清除寄存器 */
    volatile union nvic_1bit_register ICPR;
    uint32 r3[29];
    /* 中断Active状态寄存器, 只读 */
    volatile union nvic_1bit_register IABR;
    uint32 r4[61];
    /* 中断优先级寄存器 */
    volatile union nvic_8bit_register IPR;
    uint8 r5[2];
    uint32 r6[683];
    /* 软件触发中断寄存器(Software Trigger Interrupt Register) */
    volatile union nvic_stir STIR;
} nvic_regs_t;
/* SCB寄存器地址映射 */
#define NVIC_BASE  0xE000E100
/* SCB寄存器指针访问 */
#define NVIC ((nvic_regs_t *) NVIC_BASE)







#endif
