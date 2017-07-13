/***********************************************************
 *
 * stm32f407_rcc - 复位和时钟控制,Reset and Clock Control
 *
 ************************************** 高乙超.2016.1224 ***/
#ifndef STM32F407_RCC_H
#define STM32F407_RCC_H

#include <types.h>

/*
 * AHB1外设时钟使能寄存器 RCC_AHB1ENR
 * 偏移地址: 0x30
 * 复位值: 0x0010 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
struct rcc_ahb1enr_bits {
    uint32 gpioa : 1;
    uint32 gpiob : 1;
    uint32 gpioc : 1;
    uint32 gpiod : 1;
    uint32 gpioe : 1;
    uint32 gpiof : 1;
    uint32 gpiog : 1;
    uint32 gpioh : 1;
    uint32 gpioi : 1;
    uint32 r1 : 3;
    uint32 crc : 1;
    uint32 r2 : 5;
    uint32 bkpsram : 1;
    uint32 r3 : 1;
    uint32 ccmdataram : 1;
    uint32 dma1 : 1;
    uint32 dma2 : 1;
    uint32 r4 : 2;
    uint32 ethmac : 1;
    uint32 ethmac_tx : 1;
    uint32 ethmac_rx : 1;
    uint32 ethmac_ptp : 1;
    uint32 otg_hs : 1;
    uint32 otg_hs_ulpi : 1;
    uint32 r5 : 1;
};
union rcc_ahb1enr {
    struct rcc_ahb1enr_bits bits;
    uint32 all;
};

typedef struct rcc_regs {
    volatile  uint32 CR;            /* 时钟控制寄存器, offset: 0x00 */
    volatile  uint32 PLLCFGR;       /* 锁相环配置寄存器, offset: 0x04 */
    volatile  uint32 CFGR;          /* 时钟配置寄存器, offset: 0x08 */
    volatile  uint32 CIR;           /* 时钟中断寄存器, offset: 0x0C */
    volatile  uint32 AHB1RSTR;      /* AHB1外设复位寄存器, offset: 0x10 */
    volatile  uint32 AHB2RSTR;      /* AHB2外设复位寄存器, offset: 0x14 */
    volatile  uint32 AHB3RSTR;      /* AHB3外设复位寄存器, offset: 0x18 */
    uint32 RESERVED0;               /* 保留, 0x1C */
    volatile  uint32 APB1RSTR;      /* APB1外设复位寄存器, offset: 0x20 */
    volatile  uint32 APB2RSTR;      /* APB2外设复位寄存器, offset: 0x24 */
    uint32  RESERVED1[2];           /* 保留, 0x28-0x2C */
    volatile  union rcc_ahb1enr AHB1ENR;       /* AHB1外设时钟使能寄存器, offset: 0x30 */
    volatile  uint32 AHB2ENR;       /* AHB2外设时钟使能寄存器, offset: 0x34 */
    volatile  uint32 AHB3ENR;       /* AHB3外设时钟使能寄存器, offset: 0x38 */
    uint32 RESERVED2;               /* 保留, 0x3C */
    volatile  uint32 APB1ENR;       /* APB1外设时钟使能寄存器, offset: 0x40 */
    volatile  uint32 APB2ENR;       /* APB2外设时钟使能寄存器, offset: 0x44 */
    uint32 RESERVED3[2];            /* 保留, 0x48-0x4C */
    volatile  uint32 AHB1LPENR;     /* AHB1低电压模式下外设时钟使能寄存器, offset: 0x50 */
    volatile  uint32 AHB2LPENR;     /* AHB2低电压模式下外设时钟使能寄存器, offset: 0x54 */
    volatile  uint32 AHB3LPENR;     /* AHB3低电压模式下外设时钟使能寄存器, offset: 0x58 */
    uint32 RESERVED4;               /* 保留, 0x5C */
    volatile  uint32 APB1LPENR;     /* APB1低电压模式下外设时钟使能寄存器, offset: 0x60 */
    volatile  uint32 APB2LPENR;     /* APB2低电压模式下外设时钟使能寄存器, offset: 0x64 */
    uint32 RESERVED5[2];            /* 保留, 0x68-0x6C */
    volatile  uint32 BDCR;          /* Backup domain控制寄存器, offset: 0x70 */
    volatile  uint32 CSR;           /* 时钟控制和状态寄存器, offset: 0x74 */
    uint32 RESERVED6[2];            /* 保留, 0x78-0x7C */
    volatile  uint32 SSCGR;         /* 扩频时钟发生器寄存器(听起来很高大上，有什么用暂时不知道，以后会详细解析) offset: 0x80 */
    volatile  uint32 PLLI2SCFGR;    /* 锁相环PLLI2S配置寄存器, offset: 0x84 */
} rcc_regs_t;

/* RCC寄存器地址映射 */
#define RCC_BASE 0x40023800
/* RCC寄存器指针访问 */
#define RCC ((rcc_regs_t *) RCC_BASE)

/*
 * 时钟控制寄存器 RCC_CR
 * 偏移地址: 0x00
 * 复位值: 0x0000 XX83
 * 访问: 无等待状态, word/half-word/byte访问
 */
#define RCC_CR_RESET_VALUE  ((uint32)0x00000083)        /* 复位值           */
#define RCC_CR_HSION        ((uint32)0x00000001)        /* 内部高速时钟 使能 */
#define RCC_CR_HSIRDY       ((uint32)0x00000002)        /* 内部高速时钟 就绪 */
#define RCC_CR_HSITRIM      ((uint32)0x000000F8)        /* 内部高速时钟 调整 */
#define RCC_CR_HSICAL       ((uint32)0x0000FF00)        /* 内部高速时钟 校准 */
#define RCC_CR_HSEON        ((uint32)0x00010000)        /* 外部高速时钟 使能 */
#define RCC_CR_HSERDY       ((uint32)0x00020000)        /* 外部高速时钟 就绪 */
#define RCC_CR_HSEBYP       ((uint32)0x00040000)        /* 外部高速时钟 旁路 */
#define RCC_CR_CSSON        ((uint32)0x00080000)        /* 时钟安全系统 使能 */
#define RCC_CR_PLLON        ((uint32)0x01000000)        /* PLL         使能 */
#define RCC_CR_PLLRDY       ((uint32)0x02000000)        /* PLL         就绪 */
#define RCC_CR_PLLI2SON     ((uint32)0x04000000)        /* PLLI2S      就绪 */
#define RCC_CR_PLLI2SRDY    ((uint32)0x08000000)        /* PLLI2S      就绪 */

/*
 * 锁相环配置寄存器 RCC_PLLCFGR
 * 偏移地址: 0x04
 * 复位值: 0x2400 3010
 * 访问: 无等待状态, word/half-word/byte访问
 *
 * 系统时钟计算方法：
 * f(VCO clock) = f(PLL clock input) * PLLN / PLLM
 * f(PLL general clock output) = f(VCO clock) / PLLP
 * f(USB OTG FS, SDIO, RNG clock output) = f(VCO clock) / PLLQ
 */
#define RCC_PLLCFGR_RESET_VALUE ((uint32)0x24003010)        /* 复位值           */
#define RCC_PLLCFGR_PLLM        ((uint32)0x0000003F)        /* PLLM */
#define RCC_PLLCFGR_PLLN        ((uint32)0x00007FC0)        /* PLLN */
#define RCC_PLLCFGR_PLLP        ((uint32)0x00030000)        /* PLLP */
#define RCC_PLLCFGR_PLLSRC      ((uint32)0x00400000)        /* PLL时钟源 */
#define RCC_PLLCFGR_PLLSRC_HSI  ((uint32)0x00000000)
#define RCC_PLLCFGR_PLLSRC_HSE  ((uint32)0x00400000)
#define RCC_PLLCFGR_PLLQ        ((uint32)0x0F000000)        /* PLLQ */

 /*
 * 时钟配置寄存器 RCC_CFGR
 * 偏移地址: 0x08
 * 复位值: 0x0000 0000
 * 访问: 当访问发生在时钟切换时会有1或者两个等待周期, word/half-word/byte访问
 */
#define RCC_CFGR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_CFGR_SW             ((uint32)0x00000003)    /* 系统时钟源选择位 SW[1:0]*/
#define RCC_CFGR_SW_HSI         ((uint32)0x00000000)    /* 内部高速时钟 */
#define RCC_CFGR_SW_HSE         ((uint32)0x00000001)    /* 外部高速时钟 */
#define RCC_CFGR_SW_PLL         ((uint32)0x00000002)    /* PLL */

#define RCC_CFGR_SWS            ((uint32)0x0000000C)    /* 当前系统时钟 SWS[1:0] */
#define RCC_CFGR_SWS_HSI        ((uint32)0x00000000)    /* 内部高速时钟 */
#define RCC_CFGR_SWS_HSE        ((uint32)0x00000004)    /* 外部高速时钟 */
#define RCC_CFGR_SWS_PLL        ((uint32)0x00000008)    /* PLL */

#define RCC_CFGR_HPRE           ((uint32)0x000000F0)    /* AHB分频 HPRE[3:0],对SYSCLK,HCLK */
#define RCC_CFGR_HPRE_DIV1      ((uint32)0x00000000)    /* 1分频 */
#define RCC_CFGR_HPRE_DIV2      ((uint32)0x00000080)    /* 2分频 */
#define RCC_CFGR_HPRE_DIV4      ((uint32)0x00000090)    /* 4分频 */
#define RCC_CFGR_HPRE_DIV8      ((uint32)0x000000A0)    /* 8分频 */
#define RCC_CFGR_HPRE_DIV16     ((uint32)0x000000B0)    /* 16分频 */
#define RCC_CFGR_HPRE_DIV64     ((uint32)0x000000C0)    /* 64分频 */
#define RCC_CFGR_HPRE_DIV128    ((uint32)0x000000D0)    /* 128分频 */
#define RCC_CFGR_HPRE_DIV256    ((uint32)0x000000E0)    /* 256分频 */
#define RCC_CFGR_HPRE_DIV512    ((uint32)0x000000F0)    /* 512分频 */

#define RCC_CFGR_PPRE1          ((uint32)0x00001C00)    /* 低速外设(APB1)分频 PRE1[2:0],对HCLK,最大为84MHz,PCLK1 */
#define RCC_CFGR_PPRE1_DIV1     ((uint32)0x00000000)    /* 1分频 */
#define RCC_CFGR_PPRE1_DIV2     ((uint32)0x00001000)    /* 2分频 */
#define RCC_CFGR_PPRE1_DIV4     ((uint32)0x00001400)    /* 4分频 */
#define RCC_CFGR_PPRE1_DIV8     ((uint32)0x00001800)    /* 8分频 */
#define RCC_CFGR_PPRE1_DIV16    ((uint32)0x00001C00)    /* 16分频 */

#define RCC_CFGR_PPRE2          ((uint32)0x0000E000)    /* 高速外设(APB2)分频 PRE2[2:0],对HCLK,最大为42MHz,PCLK2 */
#define RCC_CFGR_PPRE2_DIV1     ((uint32)0x00000000)    /* 1分频 */
#define RCC_CFGR_PPRE2_DIV2     ((uint32)0x00008000)    /* 2分频 */
#define RCC_CFGR_PPRE2_DIV4     ((uint32)0x0000A000)    /* 4分频 */
#define RCC_CFGR_PPRE2_DIV8     ((uint32)0x0000C000)    /* 8分频 */
#define RCC_CFGR_PPRE2_DIV16    ((uint32)0x0000E000)    /* 16分频 */

#define RCC_CFGR_RTCPRE         ((uint32)0x001F0000)    /* 实时时钟(RTC)分频 RTCPRE[4:0],对HSE */
#define RCC_CFGR_RTCPRE_1       ((uint32)0x00000000)    /* HSE / 1 */
#define RCC_CFGR_RTCPRE_2       ((uint32)0x00020000)    /* HSE / 2 */
#define RCC_CFGR_RTCPRE_3       ((uint32)0x00030000)    /* HSE / 3 */
#define RCC_CFGR_RTCPRE_4       ((uint32)0x00040000)    /* HSE / 4 */
#define RCC_CFGR_RTCPRE_5       ((uint32)0x00050000)
#define RCC_CFGR_RTCPRE_6       ((uint32)0x00060000)
#define RCC_CFGR_RTCPRE_7       ((uint32)0x00070000)
#define RCC_CFGR_RTCPRE_8       ((uint32)0x00080000)
#define RCC_CFGR_RTCPRE_9       ((uint32)0x00090000)
#define RCC_CFGR_RTCPRE_10      ((uint32)0x000a0000)
#define RCC_CFGR_RTCPRE_11      ((uint32)0x000b0000)
#define RCC_CFGR_RTCPRE_12      ((uint32)0x000c0000)
#define RCC_CFGR_RTCPRE_13      ((uint32)0x000d0000)
#define RCC_CFGR_RTCPRE_14      ((uint32)0x000e0000)
#define RCC_CFGR_RTCPRE_15      ((uint32)0x000f0000)
#define RCC_CFGR_RTCPRE_16      ((uint32)0x00100000)
#define RCC_CFGR_RTCPRE_17      ((uint32)0x00110000)
#define RCC_CFGR_RTCPRE_18      ((uint32)0x00120000)
#define RCC_CFGR_RTCPRE_19      ((uint32)0x00130000)
#define RCC_CFGR_RTCPRE_20      ((uint32)0x00140000)
#define RCC_CFGR_RTCPRE_21      ((uint32)0x00150000)
#define RCC_CFGR_RTCPRE_22      ((uint32)0x00160000)
#define RCC_CFGR_RTCPRE_23      ((uint32)0x00170000)
#define RCC_CFGR_RTCPRE_24      ((uint32)0x00180000)
#define RCC_CFGR_RTCPRE_25      ((uint32)0x00190000)
#define RCC_CFGR_RTCPRE_26      ((uint32)0x001a0000)
#define RCC_CFGR_RTCPRE_27      ((uint32)0x001b0000)
#define RCC_CFGR_RTCPRE_28      ((uint32)0x001c0000)
#define RCC_CFGR_RTCPRE_29      ((uint32)0x001d0000)
#define RCC_CFGR_RTCPRE_30      ((uint32)0x001e0000)    /* HSE / 30 */
#define RCC_CFGR_RTCPRE_31      ((uint32)0x001f0000)    /* HSE / 31 */

// 建议在开启外部时钟和PLL之前配置
#define RCC_CFGR_MCO1         ((uint32)0x00600000)    /* MCO1引脚的时钟输出源 */
#define RCC_CFGR_MCO1_HSI     ((uint32)0x00000000)
#define RCC_CFGR_MCO1_LSE     ((uint32)0x00200000)
#define RCC_CFGR_MCO1_HSE     ((uint32)0x00400000)
#define RCC_CFGR_MCO1_PLL     ((uint32)0x00600000)

#define RCC_CFGR_I2SSRC         ((uint32)0x00800000)    /* I2S时钟源 */
#define RCC_CFGR_I2SSRC_PLLI2S  ((uint32)0x00000000)    /* PLLI2S */
#define RCC_CFGR_I2SSRC_Ext     ((uint32)0x00800000)    /* 连接到I2S_CKIN引脚的外部时钟 */

// 建议在开启外部时钟和PLL之前配置
#define RCC_CFGR_MCO1_PRE       ((uint32)0x07000000)    /* MCO1引脚的时钟输出分频 */
#define RCC_CFGR_MCO1_DIV1      ((uint32)0x00000000)
#define RCC_CFGR_MCO1_DIV2      ((uint32)0x04000000)
#define RCC_CFGR_MCO1_DIV3      ((uint32)0x05000000)
#define RCC_CFGR_MCO1_DIV4      ((uint32)0x06000000)
#define RCC_CFGR_MCO1_DIV5      ((uint32)0x07000000)

// 建议在开启外部时钟和PLL之前配置
#define RCC_CFGR_MCO2_PRE       ((uint32)0x31000000)    /* MCO2引脚的时钟输出分频 */
#define RCC_CFGR_MCO2_DIV1      ((uint32)0x00000000)
#define RCC_CFGR_MCO2_DIV2      ((uint32)0x20000000)
#define RCC_CFGR_MCO2_DIV3      ((uint32)0x21000000)
#define RCC_CFGR_MCO2_DIV4      ((uint32)0x30000000)
#define RCC_CFGR_MCO2_DIV5      ((uint32)0x31000000)

// 建议在开启外部时钟和PLL之前配置
#define RCC_CFGR_MCO2           ((uint32)0xC0000000)    /* MCO2引脚的时钟输出源 */
#define RCC_CFGR_MCO2_SYSCLK    ((uint32)0x00000000)
#define RCC_CFGR_MCO2_PLLI2S    ((uint32)0x40000000)
#define RCC_CFGR_MCO2_HSE       ((uint32)0x80000000)
#define RCC_CFGR_MCO2_PLL       ((uint32)0xC0000000)

/*
 * 时钟中断寄存器 RCC_CIR
 * 偏移地址: 0x0C
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_CIR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_CIR_LSIRDYF         ((uint32)0x00000001)        /* LSI时钟就绪中断,LSIRDYIE=1时由硬件置1,软件写1到LSIRDYC位清除 */
#define RCC_CIR_LSERDYF         ((uint32)0x00000002)        /* LSE时钟就绪中断,LSERDYIE=1时由硬件置1,软件写1到LSERDYC位清除 */
#define RCC_CIR_HSIRDYF         ((uint32)0x00000004)        /* HSI时钟就绪中断,HSIRDYIE=1时由硬件置1,软件写1到HSIRDYC位清除 */
#define RCC_CIR_HSERDYF         ((uint32)0x00000008)        /* HSE时钟就绪中断,HSERDYIE=1时由硬件置1,软件写1到HSERDYC位清除 */
#define RCC_CIR_PLLRDYF         ((uint32)0x00000010)        /* PLL时钟就绪中断,PLLRDYIE=1时由硬件置1,软件写1到PLLRDYC位清除 */
#define RCC_CIR_PLLI2SRDYF      ((uint32)0x00000020)        /* PLLI2S时钟就绪中断,PLLRDYIE=1时由硬件置1,软件写1到PLLRDYC位清除 */
#define RCC_CIR_CSSF            ((uint32)0x00000080)        /* 时钟安全系统中断标志,HSE失效时硬件置1,软件写1到CSSC位清除 */
#define RCC_CIR_LSIRDYIE        ((uint32)0x00000100)        /* LSI就绪中断使能 */
#define RCC_CIR_LSERDYIE        ((uint32)0x00000200)        /* LSE就绪中断使能 */
#define RCC_CIR_HSIRDYIE        ((uint32)0x00000400)        /* HSI就绪中断使能 */
#define RCC_CIR_HSERDYIE        ((uint32)0x00000800)        /* HSE就绪中断使能 */
#define RCC_CIR_PLLRDYIE        ((uint32)0x00001000)        /* PLL就绪中断使能 */
#define RCC_CIR_PLLI2SRDYIE     ((uint32)0x00002000)        /* PLL就绪中断使能 */
#define RCC_CIR_LSIRDYC         ((uint32)0x00010000)        /* 清除LSI就绪中断 */
#define RCC_CIR_LSERDYC         ((uint32)0x00020000)        /* 清除LSE就绪中断 */
#define RCC_CIR_HSIRDYC         ((uint32)0x00040000)        /* 清除HSI就绪中断 */
#define RCC_CIR_HSERDYC         ((uint32)0x00080000)        /* 清除HSE就绪中断 */
#define RCC_CIR_PLLRDYC         ((uint32)0x00100000)        /* 清除PLL就绪中断 */
#define RCC_CIR_PLLI2SRDYC      ((uint32)0x00200000)        /* 清除PLL就绪中断 */
#define RCC_CIR_CSSC            ((uint32)0x00800000)        /* 清除时钟安全系统中断 */

#define RCC_CIE_ALLE            ((uint32)0x00003F00)        /* 打开所有中断 */
#define RCC_CIR_ALLC            ((uint32)0x00BF0000)        /* 清除所有中断标志 */
/*
 * AHB1外设复位寄存器 RCC_AHB1RSTR
 * 偏移地址: 0x10
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB1RSTR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_AHB1RSTR_GPIOA    ((uint32)0x00000001)
#define RCC_AHB1RSTR_GPIOB    ((uint32)0x00000002)
#define RCC_AHB1RSTR_GPIOC    ((uint32)0x00000004)
#define RCC_AHB1RSTR_GPIOD    ((uint32)0x00000008)
#define RCC_AHB1RSTR_GPIOE    ((uint32)0x00000010)
#define RCC_AHB1RSTR_GPIOF    ((uint32)0x00000020)
#define RCC_AHB1RSTR_GPIOG    ((uint32)0x00000040)
#define RCC_AHB1RSTR_GPIOH    ((uint32)0x00000080)
#define RCC_AHB1RSTR_GPIOI    ((uint32)0x00000100)
#define RCC_AHB1RSTR_CRC      ((uint32)0x00001000)
#define RCC_AHB1RSTR_DMA1     ((uint32)0x00200000)
#define RCC_AHB1RSTR_DMA2     ((uint32)0x00400000)
#define RCC_AHB1RSTR_ETHMAC   ((uint32)0x02000000)
#define RCC_AHB1RSTR_OTGHS    ((uint32)0x20000000)
/*
 * AHB2外设复位寄存器 RCC_AHB2RSTR
 * 偏移地址: 0x14
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB2RSTR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_AHB2RSTR_DCMI    ((uint32)0x00000001)
#define RCC_AHB2RSTR_CRYP    ((uint32)0x00000010)
#define RCC_AHB2RSTR_HASH    ((uint32)0x00000020)
#define RCC_AHB2RSTR_RNG     ((uint32)0x00000040)
#define RCC_AHB2RSTR_OTGFS   ((uint32)0x00000080)
/*
 * AHB3外设复位寄存器 RCC_AHB3RSTR
 * 偏移地址: 0x18
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB3RSTR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_AHB3RSTR_FSMC    ((uint32)0x00000001)
/*
 * APB1外设复位寄存器 RCC_APB1RSTR
 * 偏移地址: 0x20
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_APB1RSTR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_APB1RSTR_TIM2    ((uint32)0x00000001)
#define RCC_APB1RSTR_TIM3    ((uint32)0x00000002)
#define RCC_APB1RSTR_TIM4    ((uint32)0x00000004)
#define RCC_APB1RSTR_TIM5    ((uint32)0x00000008)
#define RCC_APB1RSTR_TIM6    ((uint32)0x00000010)
#define RCC_APB1RSTR_TIM7    ((uint32)0x00000020)
#define RCC_APB1RSTR_TIM12   ((uint32)0x00000040)
#define RCC_APB1RSTR_TIM13   ((uint32)0x00000080)
#define RCC_APB1RSTR_TIM14   ((uint32)0x00000100)
#define RCC_APB1RSTR_WWDG    ((uint32)0x00000800)
#define RCC_APB1RSTR_SPI2    ((uint32)0x00004000)
#define RCC_APB1RSTR_SPI3    ((uint32)0x00008000)
#define RCC_APB1RSTR_UART2   ((uint32)0x00020000)
#define RCC_APB1RSTR_UART3   ((uint32)0x00040000)
#define RCC_APB1RSTR_UART4   ((uint32)0x00080000)
#define RCC_APB1RSTR_UART5   ((uint32)0x00100000)
#define RCC_APB1RSTR_I2C1    ((uint32)0x00200000)
#define RCC_APB1RSTR_I2C2    ((uint32)0x00400000)
#define RCC_APB1RSTR_I2C3    ((uint32)0x00800000)
#define RCC_APB1RSTR_CAN1    ((uint32)0x02000000)
#define RCC_APB1RSTR_CAN2    ((uint32)0x04000000)
#define RCC_APB1RSTR_PWR     ((uint32)0x10000000)   /* Power Interface */
#define RCC_APB1RSTR_DAC     ((uint32)0x20000000)
/*
 * APB2外设复位寄存器 RCC_APB2RSTR
 * 偏移地址: 0x24
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_APB2RSTR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_APB2RSTR_TIM1    ((uint32)0x00000001)
#define RCC_APB2RSTR_TIM8    ((uint32)0x00000002)
#define RCC_APB2RSTR_USART1  ((uint32)0x00000010)
#define RCC_APB2RSTR_USART6  ((uint32)0x00000020)
#define RCC_APB2RSTR_ADC     ((uint32)0x00000100)
#define RCC_APB2RSTR_SDIO    ((uint32)0x00000800)
#define RCC_APB2RSTR_SPI1    ((uint32)0x00001000)
#define RCC_APB2RSTR_SYSCFG  ((uint32)0x00004000)
#define RCC_APB2RSTR_TIM9    ((uint32)0x00010000)
#define RCC_APB2RSTR_TIM10   ((uint32)0x00020000)
#define RCC_APB2RSTR_TIM11   ((uint32)0x00040000)

/*
 * AHB2外设时钟使能寄存器 RCC_AHB2ENR
 * 偏移地址: 0x34
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB2ENR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_AHB2ENR_DCMI       ((uint32)0x00000001)
#define RCC_AHB2ENR_CRYP       ((uint32)0x00000010)
#define RCC_AHB2ENR_HASH       ((uint32)0x00000020)
#define RCC_AHB2ENR_RNG        ((uint32)0x00000040)
#define RCC_AHB2ENR_OTGFS      ((uint32)0x00000080)
/*
 * AHB3外设时钟使能寄存器 RCC_AHB3ENR
 * 偏移地址: 0x38
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB3ENR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_AHB3ENR_FSMC       ((uint32)0x00000001)
/*
 * APB1外设时钟使能寄存器 RCC_APB1ENR
 * 偏移地址: 0x40
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_APB1ENR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_APB1ENR_TIM2       ((uint32)0x00000001)
#define RCC_APB1ENR_TIM3       ((uint32)0x00000002)
#define RCC_APB1ENR_TIM4       ((uint32)0x00000004)
#define RCC_APB1ENR_TIM5       ((uint32)0x00000008)
#define RCC_APB1ENR_TIM6       ((uint32)0x00000010)
#define RCC_APB1ENR_TIM7       ((uint32)0x00000020)
#define RCC_APB1ENR_TIM12      ((uint32)0x00000040)
#define RCC_APB1ENR_TIM13      ((uint32)0x00000080)
#define RCC_APB1ENR_TIM14      ((uint32)0x00000100)
#define RCC_APB1ENR_WWDG       ((uint32)0x00000800)
#define RCC_APB1ENR_SPI2       ((uint32)0x00004000)
#define RCC_APB1ENR_SPI3       ((uint32)0x00008000)
#define RCC_APB1ENR_USART2     ((uint32)0x00020000)
#define RCC_APB1ENR_USART3     ((uint32)0x00040000)
#define RCC_APB1ENR_UART4      ((uint32)0x00080000)
#define RCC_APB1ENR_UART5      ((uint32)0x00100000)
#define RCC_APB1ENR_I2C1       ((uint32)0x00200000)
#define RCC_APB1ENR_I2C2       ((uint32)0x00400000)
#define RCC_APB1ENR_I2C3       ((uint32)0x00800000)
#define RCC_APB1ENR_CAN1       ((uint32)0x02000000)
#define RCC_APB1ENR_CAN2       ((uint32)0x04000000)
#define RCC_APB1ENR_PWR        ((uint32)0x10000000)
#define RCC_APB1ENR_DAC        ((uint32)0x20000000)
/*
 * APB2外设时钟使能寄存器 RCC_APB2ENR
 * 偏移地址: 0x44
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_APB2ENR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_APB2ENR_TIM1       ((uint32)0x00000001)
#define RCC_APB2ENR_TIM8       ((uint32)0x00000002)
#define RCC_APB2ENR_UART1      ((uint32)0x00000010)
#define RCC_APB2ENR_UART6      ((uint32)0x00000020)
#define RCC_APB2ENR_ADC1       ((uint32)0x00000100)
#define RCC_APB2ENR_ADC2       ((uint32)0x00000200)
#define RCC_APB2ENR_ADC3       ((uint32)0x00000400)
#define RCC_APB2ENR_SDIO       ((uint32)0x00000800)
#define RCC_APB2ENR_SPI1       ((uint32)0x00001000)
#define RCC_APB2ENR_SYSCFG     ((uint32)0x00004000)
#define RCC_APB2ENR_TIM9       ((uint32)0x00010000)
#define RCC_APB2ENR_TIM10      ((uint32)0x00020000)
#define RCC_APB2ENR_TIM11      ((uint32)0x00040000)
/*
 * 低电压模式下AHB1外设时钟使能寄存器 RCC_AHB1LPENR
 * 偏移地址: 0x50
 * 复位值: 0x7E67 91FF
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB1LPENR_RESET_VALUE    ((uint32)0x7E6791FF)    /* 复位值 */

#define RCC_AHB1LPENR_GPIOA       ((uint32)0x00000001)
#define RCC_AHB1LPENR_GPIOB       ((uint32)0x00000002)
#define RCC_AHB1LPENR_GPIOC       ((uint32)0x00000004)
#define RCC_AHB1LPENR_GPIOD       ((uint32)0x00000008)
#define RCC_AHB1LPENR_GPIOE       ((uint32)0x00000010)
#define RCC_AHB1LPENR_GPIOF       ((uint32)0x00000020)
#define RCC_AHB1LPENR_GPIOG       ((uint32)0x00000040)
#define RCC_AHB1LPENR_GPIOH       ((uint32)0x00000080)
#define RCC_AHB1LPENR_GPIOI       ((uint32)0x00000100)
#define RCC_AHB1LPENR_CRC         ((uint32)0x00001000)
#define RCC_AHB1LPENR_FLITFLP     ((uint32)0x00008000)
#define RCC_AHB1LPENR_SRAM1       ((uint32)0x00010000)
#define RCC_AHB1LPENR_SRAM2       ((uint32)0x00020000)
#define RCC_AHB1LPENR_BKPSRAM     ((uint32)0x00040000)
#define RCC_AHB1LPENR_DMA1        ((uint32)0x00200000)
#define RCC_AHB1LPENR_DMA2        ((uint32)0x00400000)
#define RCC_AHB1LPENR_ETHMAC      ((uint32)0x02000000)
#define RCC_AHB1LPENR_ETHMACTX    ((uint32)0x04000000)
#define RCC_AHB1LPENR_ETHMACRX    ((uint32)0x08000000)
#define RCC_AHB1LPENR_ETHMACPTP   ((uint32)0x10000000)
#define RCC_AHB1LPENR_OTGHS       ((uint32)0x20000000)
#define RCC_AHB1LPENR_OTGHSULPI   ((uint32)0x40000000)
/*
 * 低电压模式下AHB2外设时钟使能寄存器 RCC_AHB2LPENR
 * 偏移地址: 0x54
 * 复位值: 0x0000 00F1
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB2LPENR_RESET_VALUE    ((uint32)0x000000F1)    /* 复位值 */

#define RCC_AHB2LPENR_DCMI       ((uint32)0x00000001)
#define RCC_AHB2LPENR_CRYP       ((uint32)0x00000010)
#define RCC_AHB2LPENR_HASH       ((uint32)0x00000020)
#define RCC_AHB2LPENR_RNG        ((uint32)0x00000040)
#define RCC_AHB2LPENR_OTGFS      ((uint32)0x00000080)
/*
 * 低电压模式下AHB3外设时钟使能寄存器 RCC_AHB3LPENR
 * 偏移地址: 0x58
 * 复位值: 0x0000 0001
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_AHB3LPENR_RESET_VALUE    ((uint32)0x00000001)    /* 复位值 */

#define RCC_AHB3LPENR_FSMC       ((uint32)0x00000001)
/*
 * 低电压模式下APB1外设时钟使能寄存器 RCC_APB1LPENR
 * 偏移地址: 0x60
 * 复位值: 0x36FE C9FF
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_APB1LPENR_RESET_VALUE    ((uint32)0x36FEC9FF)    /* 复位值 */

#define RCC_APB1LPENR_TIM2       ((uint32)0x00000001)
#define RCC_APB1LPENR_TIM3       ((uint32)0x00000002)
#define RCC_APB1LPENR_TIM4       ((uint32)0x00000004)
#define RCC_APB1LPENR_TIM5       ((uint32)0x00000008)
#define RCC_APB1LPENR_TIM6       ((uint32)0x00000010)
#define RCC_APB1LPENR_TIM7       ((uint32)0x00000020)
#define RCC_APB1LPENR_TIM12      ((uint32)0x00000040)
#define RCC_APB1LPENR_TIM13      ((uint32)0x00000080)
#define RCC_APB1LPENR_TIM14      ((uint32)0x00000100)
#define RCC_APB1LPENR_WWDG       ((uint32)0x00000800)
#define RCC_APB1LPENR_SPI2       ((uint32)0x00004000)
#define RCC_APB1LPENR_SPI3       ((uint32)0x00008000)
#define RCC_APB1LPENR_USART2     ((uint32)0x00020000)
#define RCC_APB1LPENR_USART3     ((uint32)0x00040000)
#define RCC_APB1LPENR_UART4      ((uint32)0x00080000)
#define RCC_APB1LPENR_UART5      ((uint32)0x00100000)
#define RCC_APB1LPENR_I2C1       ((uint32)0x00200000)
#define RCC_APB1LPENR_I2C2       ((uint32)0x00400000)
#define RCC_APB1LPENR_I2C3       ((uint32)0x00800000)
#define RCC_APB1LPENR_CAN1       ((uint32)0x02000000)
#define RCC_APB1LPENR_CAN2       ((uint32)0x04000000)
#define RCC_APB1LPENR_PWR        ((uint32)0x10000000)
#define RCC_APB1LPENR_DAC        ((uint32)0x20000000)
/*
 * 低电压模式下APB2外设时钟使能寄存器 RCC_APB2LPENR
 * 偏移地址: 0x64
 * 复位值: 0x0407 5F33
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_APB2LPENR_RESET_VALUE    ((uint32)0x04075F33)    /* 复位值 */

#define RCC_APB2LPENR_TIM1       ((uint32)0x00000001)
#define RCC_APB2LPENR_TIM8       ((uint32)0x00000002)
#define RCC_APB2LPENR_UART1      ((uint32)0x00000010)
#define RCC_APB2LPENR_UART6      ((uint32)0x00000020)
#define RCC_APB2LPENR_ADC1       ((uint32)0x00000100)
#define RCC_APB2LPENR_ADC2       ((uint32)0x00000200)
#define RCC_APB2LPENR_ADC3       ((uint32)0x00000400)
#define RCC_APB2LPENR_SDIO       ((uint32)0x00000800)
#define RCC_APB2LPENR_SPI1       ((uint32)0x00001000)
#define RCC_APB2LPENR_SYSCFG     ((uint32)0x00004000)
#define RCC_APB2LPENR_TIM9       ((uint32)0x00010000)
#define RCC_APB2LPENR_TIM10      ((uint32)0x00020000)
#define RCC_APB2LPENR_TIM11      ((uint32)0x00040000)
/*
 * backup domain controller register RCC_BDCR
 * 偏移地址: 0x70
 * 复位值: 0x0000 0000, reset by reset domain reset
 * 访问: 有0到3个时钟的等待状态, word/half-word/byte访问
 *       添加等待状态以防止连续的访问该寄存器
 */
#define RCC_BDCR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_BDCR_LSEON       ((uint32)0x00000001)
#define RCC_BDCR_LSERDY      ((uint32)0x00000002)
#define RCC_BDCR_LSEBYP      ((uint32)0x00000004)
#define RCC_BDCR_RTCSEL      ((uint32)0x00000300)
#define RCC_BDCR_RTCEN       ((uint32)0x00008000)
#define RCC_BDCR_BDRST       ((uint32)0x00010000)
/*
 * 时钟控制和状态寄存器 RCC_CSR
 * 偏移地址: 0x74
 * 复位值: 0x0E00 0000, reset by system reset except reset  flags by power reset only
 * 访问: 有0到3个时钟的等待状态, word/half-word/byte访问
 *       添加等待状态以防止连续的访问该寄存器
 */
#define RCC_CSR_RESET_VALUE    ((uint32)0x0E000000)    /* 复位值 */

#define RCC_CSR_LSION       ((uint32)0x00000001)
#define RCC_CSR_LSIRDY      ((uint32)0x00000002)
#define RCC_CSR_RMVF        ((uint32)0x01000000)
#define RCC_CSR_BORRSTF     ((uint32)0x02000000)
#define RCC_CSR_PINRSTF     ((uint32)0x04000000)
#define RCC_CSR_PORRSTF     ((uint32)0x08000000)
#define RCC_CSR_SFTRSTF     ((uint32)0x10000000)
#define RCC_CSR_IWDGRSTF    ((uint32)0x20000000)
#define RCC_CSR_WWDGRSTF    ((uint32)0x40000000)
#define RCC_CSR_LPWRRSTF    ((uint32)0x80000000)
/*
 * 扩频时钟寄存器 RCC_SSCGR
 * 偏移地址: 0x80
 * 复位值: 0x0000 0000
 * 访问: 没有等待状态, word/half-word/byte访问
 */
#define RCC_SSCGR_RESET_VALUE    ((uint32)0x00000000)    /* 复位值 */

#define RCC_SSCGR_MODPER       ((uint32)0x00001FFF)
#define RCC_SSCGR_INCSTEP      ((uint32)0x0FFFE000)
#define RCC_SSCGR_SPREADSEL    ((uint32)0x40000000)
#define RCC_SSCGR_SSCGEN       ((uint32)0x80000000)
/*
 * PLLI2S寄存器 RCC_PLLI2SCFGR
 * 偏移地址: 0x84
 * 复位值: 0x2000 3000
 * 访问: 没有等待状态, word/half-word/byte访问
 * PLLI2S时钟计算方法：
 * f(VCO clock) = f(PLLI2S clock input) * PLLI2SN / PLLM
 * f(PLLI2S clock output) = f(VCO clock) / PLLI2SR
 */
#define RCC_PLLI2SCFGR_RESET_VALUE    ((uint32)0x20003000)    /* 复位值 */

#define RCC_PLLI2SCFGR_PLLI2SN       ((uint32)0x00007FC0)
#define RCC_PLLI2SCFGR_PLLI2SR       ((uint32)0x70000000)















#endif
