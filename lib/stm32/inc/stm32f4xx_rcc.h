/***********************************************************
 *
 * stm32f407_rcc - ��λ��ʱ�ӿ���,Reset and Clock Control
 *
 ************************************** ���ҳ�.2016.1224 ***/
#ifndef STM32F407_RCC_H
#define STM32F407_RCC_H

#include <types.h>

/*
 * AHB1����ʱ��ʹ�ܼĴ��� RCC_AHB1ENR
 * ƫ�Ƶ�ַ: 0x30
 * ��λֵ: 0x0010 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
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
    volatile  uint32 CR;            /* ʱ�ӿ��ƼĴ���, offset: 0x00 */
    volatile  uint32 PLLCFGR;       /* ���໷���üĴ���, offset: 0x04 */
    volatile  uint32 CFGR;          /* ʱ�����üĴ���, offset: 0x08 */
    volatile  uint32 CIR;           /* ʱ���жϼĴ���, offset: 0x0C */
    volatile  uint32 AHB1RSTR;      /* AHB1���踴λ�Ĵ���, offset: 0x10 */
    volatile  uint32 AHB2RSTR;      /* AHB2���踴λ�Ĵ���, offset: 0x14 */
    volatile  uint32 AHB3RSTR;      /* AHB3���踴λ�Ĵ���, offset: 0x18 */
    uint32 RESERVED0;               /* ����, 0x1C */
    volatile  uint32 APB1RSTR;      /* APB1���踴λ�Ĵ���, offset: 0x20 */
    volatile  uint32 APB2RSTR;      /* APB2���踴λ�Ĵ���, offset: 0x24 */
    uint32  RESERVED1[2];           /* ����, 0x28-0x2C */
    volatile  union rcc_ahb1enr AHB1ENR;       /* AHB1����ʱ��ʹ�ܼĴ���, offset: 0x30 */
    volatile  uint32 AHB2ENR;       /* AHB2����ʱ��ʹ�ܼĴ���, offset: 0x34 */
    volatile  uint32 AHB3ENR;       /* AHB3����ʱ��ʹ�ܼĴ���, offset: 0x38 */
    uint32 RESERVED2;               /* ����, 0x3C */
    volatile  uint32 APB1ENR;       /* APB1����ʱ��ʹ�ܼĴ���, offset: 0x40 */
    volatile  uint32 APB2ENR;       /* APB2����ʱ��ʹ�ܼĴ���, offset: 0x44 */
    uint32 RESERVED3[2];            /* ����, 0x48-0x4C */
    volatile  uint32 AHB1LPENR;     /* AHB1�͵�ѹģʽ������ʱ��ʹ�ܼĴ���, offset: 0x50 */
    volatile  uint32 AHB2LPENR;     /* AHB2�͵�ѹģʽ������ʱ��ʹ�ܼĴ���, offset: 0x54 */
    volatile  uint32 AHB3LPENR;     /* AHB3�͵�ѹģʽ������ʱ��ʹ�ܼĴ���, offset: 0x58 */
    uint32 RESERVED4;               /* ����, 0x5C */
    volatile  uint32 APB1LPENR;     /* APB1�͵�ѹģʽ������ʱ��ʹ�ܼĴ���, offset: 0x60 */
    volatile  uint32 APB2LPENR;     /* APB2�͵�ѹģʽ������ʱ��ʹ�ܼĴ���, offset: 0x64 */
    uint32 RESERVED5[2];            /* ����, 0x68-0x6C */
    volatile  uint32 BDCR;          /* Backup domain���ƼĴ���, offset: 0x70 */
    volatile  uint32 CSR;           /* ʱ�ӿ��ƺ�״̬�Ĵ���, offset: 0x74 */
    uint32 RESERVED6[2];            /* ����, 0x78-0x7C */
    volatile  uint32 SSCGR;         /* ��Ƶʱ�ӷ������Ĵ���(�������ܸߴ��ϣ���ʲô����ʱ��֪�����Ժ����ϸ����) offset: 0x80 */
    volatile  uint32 PLLI2SCFGR;    /* ���໷PLLI2S���üĴ���, offset: 0x84 */
} rcc_regs_t;

/* RCC�Ĵ�����ַӳ�� */
#define RCC_BASE 0x40023800
/* RCC�Ĵ���ָ����� */
#define RCC ((rcc_regs_t *) RCC_BASE)

/*
 * ʱ�ӿ��ƼĴ��� RCC_CR
 * ƫ�Ƶ�ַ: 0x00
 * ��λֵ: 0x0000 XX83
 * ����: �޵ȴ�״̬, word/half-word/byte����
 */
#define RCC_CR_RESET_VALUE  ((uint32)0x00000083)        /* ��λֵ           */
#define RCC_CR_HSION        ((uint32)0x00000001)        /* �ڲ�����ʱ�� ʹ�� */
#define RCC_CR_HSIRDY       ((uint32)0x00000002)        /* �ڲ�����ʱ�� ���� */
#define RCC_CR_HSITRIM      ((uint32)0x000000F8)        /* �ڲ�����ʱ�� ���� */
#define RCC_CR_HSICAL       ((uint32)0x0000FF00)        /* �ڲ�����ʱ�� У׼ */
#define RCC_CR_HSEON        ((uint32)0x00010000)        /* �ⲿ����ʱ�� ʹ�� */
#define RCC_CR_HSERDY       ((uint32)0x00020000)        /* �ⲿ����ʱ�� ���� */
#define RCC_CR_HSEBYP       ((uint32)0x00040000)        /* �ⲿ����ʱ�� ��· */
#define RCC_CR_CSSON        ((uint32)0x00080000)        /* ʱ�Ӱ�ȫϵͳ ʹ�� */
#define RCC_CR_PLLON        ((uint32)0x01000000)        /* PLL         ʹ�� */
#define RCC_CR_PLLRDY       ((uint32)0x02000000)        /* PLL         ���� */
#define RCC_CR_PLLI2SON     ((uint32)0x04000000)        /* PLLI2S      ���� */
#define RCC_CR_PLLI2SRDY    ((uint32)0x08000000)        /* PLLI2S      ���� */

/*
 * ���໷���üĴ��� RCC_PLLCFGR
 * ƫ�Ƶ�ַ: 0x04
 * ��λֵ: 0x2400 3010
 * ����: �޵ȴ�״̬, word/half-word/byte����
 *
 * ϵͳʱ�Ӽ��㷽����
 * f(VCO clock) = f(PLL clock input) * PLLN / PLLM
 * f(PLL general clock output) = f(VCO clock) / PLLP
 * f(USB OTG FS, SDIO, RNG clock output) = f(VCO clock) / PLLQ
 */
#define RCC_PLLCFGR_RESET_VALUE ((uint32)0x24003010)        /* ��λֵ           */
#define RCC_PLLCFGR_PLLM        ((uint32)0x0000003F)        /* PLLM */
#define RCC_PLLCFGR_PLLN        ((uint32)0x00007FC0)        /* PLLN */
#define RCC_PLLCFGR_PLLP        ((uint32)0x00030000)        /* PLLP */
#define RCC_PLLCFGR_PLLSRC      ((uint32)0x00400000)        /* PLLʱ��Դ */
#define RCC_PLLCFGR_PLLSRC_HSI  ((uint32)0x00000000)
#define RCC_PLLCFGR_PLLSRC_HSE  ((uint32)0x00400000)
#define RCC_PLLCFGR_PLLQ        ((uint32)0x0F000000)        /* PLLQ */

 /*
 * ʱ�����üĴ��� RCC_CFGR
 * ƫ�Ƶ�ַ: 0x08
 * ��λֵ: 0x0000 0000
 * ����: �����ʷ�����ʱ���л�ʱ����1���������ȴ�����, word/half-word/byte����
 */
#define RCC_CFGR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_CFGR_SW             ((uint32)0x00000003)    /* ϵͳʱ��Դѡ��λ SW[1:0]*/
#define RCC_CFGR_SW_HSI         ((uint32)0x00000000)    /* �ڲ�����ʱ�� */
#define RCC_CFGR_SW_HSE         ((uint32)0x00000001)    /* �ⲿ����ʱ�� */
#define RCC_CFGR_SW_PLL         ((uint32)0x00000002)    /* PLL */

#define RCC_CFGR_SWS            ((uint32)0x0000000C)    /* ��ǰϵͳʱ�� SWS[1:0] */
#define RCC_CFGR_SWS_HSI        ((uint32)0x00000000)    /* �ڲ�����ʱ�� */
#define RCC_CFGR_SWS_HSE        ((uint32)0x00000004)    /* �ⲿ����ʱ�� */
#define RCC_CFGR_SWS_PLL        ((uint32)0x00000008)    /* PLL */

#define RCC_CFGR_HPRE           ((uint32)0x000000F0)    /* AHB��Ƶ HPRE[3:0],��SYSCLK,HCLK */
#define RCC_CFGR_HPRE_DIV1      ((uint32)0x00000000)    /* 1��Ƶ */
#define RCC_CFGR_HPRE_DIV2      ((uint32)0x00000080)    /* 2��Ƶ */
#define RCC_CFGR_HPRE_DIV4      ((uint32)0x00000090)    /* 4��Ƶ */
#define RCC_CFGR_HPRE_DIV8      ((uint32)0x000000A0)    /* 8��Ƶ */
#define RCC_CFGR_HPRE_DIV16     ((uint32)0x000000B0)    /* 16��Ƶ */
#define RCC_CFGR_HPRE_DIV64     ((uint32)0x000000C0)    /* 64��Ƶ */
#define RCC_CFGR_HPRE_DIV128    ((uint32)0x000000D0)    /* 128��Ƶ */
#define RCC_CFGR_HPRE_DIV256    ((uint32)0x000000E0)    /* 256��Ƶ */
#define RCC_CFGR_HPRE_DIV512    ((uint32)0x000000F0)    /* 512��Ƶ */

#define RCC_CFGR_PPRE1          ((uint32)0x00001C00)    /* ��������(APB1)��Ƶ PRE1[2:0],��HCLK,���Ϊ84MHz,PCLK1 */
#define RCC_CFGR_PPRE1_DIV1     ((uint32)0x00000000)    /* 1��Ƶ */
#define RCC_CFGR_PPRE1_DIV2     ((uint32)0x00001000)    /* 2��Ƶ */
#define RCC_CFGR_PPRE1_DIV4     ((uint32)0x00001400)    /* 4��Ƶ */
#define RCC_CFGR_PPRE1_DIV8     ((uint32)0x00001800)    /* 8��Ƶ */
#define RCC_CFGR_PPRE1_DIV16    ((uint32)0x00001C00)    /* 16��Ƶ */

#define RCC_CFGR_PPRE2          ((uint32)0x0000E000)    /* ��������(APB2)��Ƶ PRE2[2:0],��HCLK,���Ϊ42MHz,PCLK2 */
#define RCC_CFGR_PPRE2_DIV1     ((uint32)0x00000000)    /* 1��Ƶ */
#define RCC_CFGR_PPRE2_DIV2     ((uint32)0x00008000)    /* 2��Ƶ */
#define RCC_CFGR_PPRE2_DIV4     ((uint32)0x0000A000)    /* 4��Ƶ */
#define RCC_CFGR_PPRE2_DIV8     ((uint32)0x0000C000)    /* 8��Ƶ */
#define RCC_CFGR_PPRE2_DIV16    ((uint32)0x0000E000)    /* 16��Ƶ */

#define RCC_CFGR_RTCPRE         ((uint32)0x001F0000)    /* ʵʱʱ��(RTC)��Ƶ RTCPRE[4:0],��HSE */
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

// �����ڿ����ⲿʱ�Ӻ�PLL֮ǰ����
#define RCC_CFGR_MCO1         ((uint32)0x00600000)    /* MCO1���ŵ�ʱ�����Դ */
#define RCC_CFGR_MCO1_HSI     ((uint32)0x00000000)
#define RCC_CFGR_MCO1_LSE     ((uint32)0x00200000)
#define RCC_CFGR_MCO1_HSE     ((uint32)0x00400000)
#define RCC_CFGR_MCO1_PLL     ((uint32)0x00600000)

#define RCC_CFGR_I2SSRC         ((uint32)0x00800000)    /* I2Sʱ��Դ */
#define RCC_CFGR_I2SSRC_PLLI2S  ((uint32)0x00000000)    /* PLLI2S */
#define RCC_CFGR_I2SSRC_Ext     ((uint32)0x00800000)    /* ���ӵ�I2S_CKIN���ŵ��ⲿʱ�� */

// �����ڿ����ⲿʱ�Ӻ�PLL֮ǰ����
#define RCC_CFGR_MCO1_PRE       ((uint32)0x07000000)    /* MCO1���ŵ�ʱ�������Ƶ */
#define RCC_CFGR_MCO1_DIV1      ((uint32)0x00000000)
#define RCC_CFGR_MCO1_DIV2      ((uint32)0x04000000)
#define RCC_CFGR_MCO1_DIV3      ((uint32)0x05000000)
#define RCC_CFGR_MCO1_DIV4      ((uint32)0x06000000)
#define RCC_CFGR_MCO1_DIV5      ((uint32)0x07000000)

// �����ڿ����ⲿʱ�Ӻ�PLL֮ǰ����
#define RCC_CFGR_MCO2_PRE       ((uint32)0x31000000)    /* MCO2���ŵ�ʱ�������Ƶ */
#define RCC_CFGR_MCO2_DIV1      ((uint32)0x00000000)
#define RCC_CFGR_MCO2_DIV2      ((uint32)0x20000000)
#define RCC_CFGR_MCO2_DIV3      ((uint32)0x21000000)
#define RCC_CFGR_MCO2_DIV4      ((uint32)0x30000000)
#define RCC_CFGR_MCO2_DIV5      ((uint32)0x31000000)

// �����ڿ����ⲿʱ�Ӻ�PLL֮ǰ����
#define RCC_CFGR_MCO2           ((uint32)0xC0000000)    /* MCO2���ŵ�ʱ�����Դ */
#define RCC_CFGR_MCO2_SYSCLK    ((uint32)0x00000000)
#define RCC_CFGR_MCO2_PLLI2S    ((uint32)0x40000000)
#define RCC_CFGR_MCO2_HSE       ((uint32)0x80000000)
#define RCC_CFGR_MCO2_PLL       ((uint32)0xC0000000)

/*
 * ʱ���жϼĴ��� RCC_CIR
 * ƫ�Ƶ�ַ: 0x0C
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_CIR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_CIR_LSIRDYF         ((uint32)0x00000001)        /* LSIʱ�Ӿ����ж�,LSIRDYIE=1ʱ��Ӳ����1,���д1��LSIRDYCλ��� */
#define RCC_CIR_LSERDYF         ((uint32)0x00000002)        /* LSEʱ�Ӿ����ж�,LSERDYIE=1ʱ��Ӳ����1,���д1��LSERDYCλ��� */
#define RCC_CIR_HSIRDYF         ((uint32)0x00000004)        /* HSIʱ�Ӿ����ж�,HSIRDYIE=1ʱ��Ӳ����1,���д1��HSIRDYCλ��� */
#define RCC_CIR_HSERDYF         ((uint32)0x00000008)        /* HSEʱ�Ӿ����ж�,HSERDYIE=1ʱ��Ӳ����1,���д1��HSERDYCλ��� */
#define RCC_CIR_PLLRDYF         ((uint32)0x00000010)        /* PLLʱ�Ӿ����ж�,PLLRDYIE=1ʱ��Ӳ����1,���д1��PLLRDYCλ��� */
#define RCC_CIR_PLLI2SRDYF      ((uint32)0x00000020)        /* PLLI2Sʱ�Ӿ����ж�,PLLRDYIE=1ʱ��Ӳ����1,���д1��PLLRDYCλ��� */
#define RCC_CIR_CSSF            ((uint32)0x00000080)        /* ʱ�Ӱ�ȫϵͳ�жϱ�־,HSEʧЧʱӲ����1,���д1��CSSCλ��� */
#define RCC_CIR_LSIRDYIE        ((uint32)0x00000100)        /* LSI�����ж�ʹ�� */
#define RCC_CIR_LSERDYIE        ((uint32)0x00000200)        /* LSE�����ж�ʹ�� */
#define RCC_CIR_HSIRDYIE        ((uint32)0x00000400)        /* HSI�����ж�ʹ�� */
#define RCC_CIR_HSERDYIE        ((uint32)0x00000800)        /* HSE�����ж�ʹ�� */
#define RCC_CIR_PLLRDYIE        ((uint32)0x00001000)        /* PLL�����ж�ʹ�� */
#define RCC_CIR_PLLI2SRDYIE     ((uint32)0x00002000)        /* PLL�����ж�ʹ�� */
#define RCC_CIR_LSIRDYC         ((uint32)0x00010000)        /* ���LSI�����ж� */
#define RCC_CIR_LSERDYC         ((uint32)0x00020000)        /* ���LSE�����ж� */
#define RCC_CIR_HSIRDYC         ((uint32)0x00040000)        /* ���HSI�����ж� */
#define RCC_CIR_HSERDYC         ((uint32)0x00080000)        /* ���HSE�����ж� */
#define RCC_CIR_PLLRDYC         ((uint32)0x00100000)        /* ���PLL�����ж� */
#define RCC_CIR_PLLI2SRDYC      ((uint32)0x00200000)        /* ���PLL�����ж� */
#define RCC_CIR_CSSC            ((uint32)0x00800000)        /* ���ʱ�Ӱ�ȫϵͳ�ж� */

#define RCC_CIE_ALLE            ((uint32)0x00003F00)        /* �������ж� */
#define RCC_CIR_ALLC            ((uint32)0x00BF0000)        /* ��������жϱ�־ */
/*
 * AHB1���踴λ�Ĵ��� RCC_AHB1RSTR
 * ƫ�Ƶ�ַ: 0x10
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB1RSTR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

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
 * AHB2���踴λ�Ĵ��� RCC_AHB2RSTR
 * ƫ�Ƶ�ַ: 0x14
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB2RSTR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_AHB2RSTR_DCMI    ((uint32)0x00000001)
#define RCC_AHB2RSTR_CRYP    ((uint32)0x00000010)
#define RCC_AHB2RSTR_HASH    ((uint32)0x00000020)
#define RCC_AHB2RSTR_RNG     ((uint32)0x00000040)
#define RCC_AHB2RSTR_OTGFS   ((uint32)0x00000080)
/*
 * AHB3���踴λ�Ĵ��� RCC_AHB3RSTR
 * ƫ�Ƶ�ַ: 0x18
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB3RSTR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_AHB3RSTR_FSMC    ((uint32)0x00000001)
/*
 * APB1���踴λ�Ĵ��� RCC_APB1RSTR
 * ƫ�Ƶ�ַ: 0x20
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_APB1RSTR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

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
 * APB2���踴λ�Ĵ��� RCC_APB2RSTR
 * ƫ�Ƶ�ַ: 0x24
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_APB2RSTR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

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
 * AHB2����ʱ��ʹ�ܼĴ��� RCC_AHB2ENR
 * ƫ�Ƶ�ַ: 0x34
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB2ENR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_AHB2ENR_DCMI       ((uint32)0x00000001)
#define RCC_AHB2ENR_CRYP       ((uint32)0x00000010)
#define RCC_AHB2ENR_HASH       ((uint32)0x00000020)
#define RCC_AHB2ENR_RNG        ((uint32)0x00000040)
#define RCC_AHB2ENR_OTGFS      ((uint32)0x00000080)
/*
 * AHB3����ʱ��ʹ�ܼĴ��� RCC_AHB3ENR
 * ƫ�Ƶ�ַ: 0x38
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB3ENR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_AHB3ENR_FSMC       ((uint32)0x00000001)
/*
 * APB1����ʱ��ʹ�ܼĴ��� RCC_APB1ENR
 * ƫ�Ƶ�ַ: 0x40
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_APB1ENR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

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
 * APB2����ʱ��ʹ�ܼĴ��� RCC_APB2ENR
 * ƫ�Ƶ�ַ: 0x44
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_APB2ENR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

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
 * �͵�ѹģʽ��AHB1����ʱ��ʹ�ܼĴ��� RCC_AHB1LPENR
 * ƫ�Ƶ�ַ: 0x50
 * ��λֵ: 0x7E67 91FF
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB1LPENR_RESET_VALUE    ((uint32)0x7E6791FF)    /* ��λֵ */

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
 * �͵�ѹģʽ��AHB2����ʱ��ʹ�ܼĴ��� RCC_AHB2LPENR
 * ƫ�Ƶ�ַ: 0x54
 * ��λֵ: 0x0000 00F1
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB2LPENR_RESET_VALUE    ((uint32)0x000000F1)    /* ��λֵ */

#define RCC_AHB2LPENR_DCMI       ((uint32)0x00000001)
#define RCC_AHB2LPENR_CRYP       ((uint32)0x00000010)
#define RCC_AHB2LPENR_HASH       ((uint32)0x00000020)
#define RCC_AHB2LPENR_RNG        ((uint32)0x00000040)
#define RCC_AHB2LPENR_OTGFS      ((uint32)0x00000080)
/*
 * �͵�ѹģʽ��AHB3����ʱ��ʹ�ܼĴ��� RCC_AHB3LPENR
 * ƫ�Ƶ�ַ: 0x58
 * ��λֵ: 0x0000 0001
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_AHB3LPENR_RESET_VALUE    ((uint32)0x00000001)    /* ��λֵ */

#define RCC_AHB3LPENR_FSMC       ((uint32)0x00000001)
/*
 * �͵�ѹģʽ��APB1����ʱ��ʹ�ܼĴ��� RCC_APB1LPENR
 * ƫ�Ƶ�ַ: 0x60
 * ��λֵ: 0x36FE C9FF
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_APB1LPENR_RESET_VALUE    ((uint32)0x36FEC9FF)    /* ��λֵ */

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
 * �͵�ѹģʽ��APB2����ʱ��ʹ�ܼĴ��� RCC_APB2LPENR
 * ƫ�Ƶ�ַ: 0x64
 * ��λֵ: 0x0407 5F33
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_APB2LPENR_RESET_VALUE    ((uint32)0x04075F33)    /* ��λֵ */

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
 * ƫ�Ƶ�ַ: 0x70
 * ��λֵ: 0x0000 0000, reset by reset domain reset
 * ����: ��0��3��ʱ�ӵĵȴ�״̬, word/half-word/byte����
 *       ��ӵȴ�״̬�Է�ֹ�����ķ��ʸüĴ���
 */
#define RCC_BDCR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_BDCR_LSEON       ((uint32)0x00000001)
#define RCC_BDCR_LSERDY      ((uint32)0x00000002)
#define RCC_BDCR_LSEBYP      ((uint32)0x00000004)
#define RCC_BDCR_RTCSEL      ((uint32)0x00000300)
#define RCC_BDCR_RTCEN       ((uint32)0x00008000)
#define RCC_BDCR_BDRST       ((uint32)0x00010000)
/*
 * ʱ�ӿ��ƺ�״̬�Ĵ��� RCC_CSR
 * ƫ�Ƶ�ַ: 0x74
 * ��λֵ: 0x0E00 0000, reset by system reset except reset  flags by power reset only
 * ����: ��0��3��ʱ�ӵĵȴ�״̬, word/half-word/byte����
 *       ��ӵȴ�״̬�Է�ֹ�����ķ��ʸüĴ���
 */
#define RCC_CSR_RESET_VALUE    ((uint32)0x0E000000)    /* ��λֵ */

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
 * ��Ƶʱ�ӼĴ��� RCC_SSCGR
 * ƫ�Ƶ�ַ: 0x80
 * ��λֵ: 0x0000 0000
 * ����: û�еȴ�״̬, word/half-word/byte����
 */
#define RCC_SSCGR_RESET_VALUE    ((uint32)0x00000000)    /* ��λֵ */

#define RCC_SSCGR_MODPER       ((uint32)0x00001FFF)
#define RCC_SSCGR_INCSTEP      ((uint32)0x0FFFE000)
#define RCC_SSCGR_SPREADSEL    ((uint32)0x40000000)
#define RCC_SSCGR_SSCGEN       ((uint32)0x80000000)
/*
 * PLLI2S�Ĵ��� RCC_PLLI2SCFGR
 * ƫ�Ƶ�ַ: 0x84
 * ��λֵ: 0x2000 3000
 * ����: û�еȴ�״̬, word/half-word/byte����
 * PLLI2Sʱ�Ӽ��㷽����
 * f(VCO clock) = f(PLLI2S clock input) * PLLI2SN / PLLM
 * f(PLLI2S clock output) = f(VCO clock) / PLLI2SR
 */
#define RCC_PLLI2SCFGR_RESET_VALUE    ((uint32)0x20003000)    /* ��λֵ */

#define RCC_PLLI2SCFGR_PLLI2SN       ((uint32)0x00007FC0)
#define RCC_PLLI2SCFGR_PLLI2SR       ((uint32)0x70000000)















#endif
