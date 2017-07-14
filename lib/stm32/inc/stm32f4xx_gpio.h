/***********************************************************
 *
 * stm32f407_gpio - 通用IO
 *
 ************************************** 高乙超.2016.1224 ***/
#pragma once

#include <types.h>

/*
 * 端口模式寄存器 GPIO_MODER
 * 偏移地址: 0x00
 * 复位值: 0xA800 0000(GPIOA), 0x0000 0280(GPIOB), 0x0000 0000(其它)
 * 访问: word/half-word/byte访问
 */
#define GPIO_Mode_In 0x00
#define GPIO_Mode_Out 0x01
#define GPIO_Mode_Af 0x02
#define GPIO_Mode_Analog 0x03
#define Gen_Gpio_Pin_Mode(pin, mode) ((mode) << 2 * (pin))
struct gpio_moder_bits {
    uint32 pin0 : 2;
    uint32 pin1 : 2;
    uint32 pin2 : 2;
    uint32 pin3 : 2;

    uint32 pin4 : 2;
    uint32 pin5 : 2;
    uint32 pin6 : 2;
    uint32 pin7 : 2;

    uint32 pin8 : 2;
    uint32 pin9 : 2;
    uint32 pin10 : 2;
    uint32 pin11 : 2;

    uint32 pin12 : 2;
    uint32 pin13 : 2;
    uint32 pin14 : 2;
    uint32 pin15 : 2;
};
union gpio_moder {
    struct gpio_moder_bits bits;
    uint32 all;
};
/*
 * 端口输出类型寄存器 GPIO_OTYPER
 * 偏移地址: 0x04
 * 复位值: 0x0000 0000
 * 访问: word/half-word/byte访问
 */
#define GPIO_OType_PP 0
#define GPIO_OType_OD 1
struct gpio_otyper_bits {
    uint32 pin0 : 1;
    uint32 pin1 : 1;
    uint32 pin2 : 1;
    uint32 pin3 : 1;

    uint32 pin4 : 1;
    uint32 pin5 : 1;
    uint32 pin6 : 1;
    uint32 pin7 : 1;

    uint32 pin8 : 1;
    uint32 pin9 : 1;
    uint32 pin10 : 1;
    uint32 pin11 : 1;

    uint32 pin12 : 1;
    uint32 pin13 : 1;
    uint32 pin14 : 1;
    uint32 pin15 : 1;

    uint32 reserved : 16;
};
union gpio_otyper {
    struct gpio_otyper_bits bits;
    uint32 all;
};
/*
 * 端口输出速度寄存器 GPIO_OSPEEDR
 * 偏移地址: 0x08
 * 复位值: 0x0C00 0000(GPIOA), 0x0000 00C0(GPIOB), 0x0000 0000(其它)
 * 访问: word/half-word/byte访问
 */
#define GPIO_OSpeed_Low 0x00
#define GPIO_OSpeed_Medium 0x01
#define GPIO_OSpeed_High 0x02
#define GPIO_OSpeed_Very_High 0x03
#define Gen_Gpio_Pin_OSpeed(pin, speed) ((speed) << 2 * (pin))
struct gpio_ospeedr_bits {
    uint32 pin0 : 2;
    uint32 pin1 : 2;
    uint32 pin2 : 2;
    uint32 pin3 : 2;

    uint32 pin4 : 2;
    uint32 pin5 : 2;
    uint32 pin6 : 2;
    uint32 pin7 : 2;

    uint32 pin8 : 2;
    uint32 pin9 : 2;
    uint32 pin10 : 2;
    uint32 pin11 : 2;

    uint32 pin12 : 2;
    uint32 pin13 : 2;
    uint32 pin14 : 2;
    uint32 pin15 : 2;
};
union gpio_ospeedr {
    struct gpio_ospeedr_bits bits;
    uint32 all;
};
/*
 * 端口上拉下拉电阻寄存器 GPIO_PUPDR
 * 偏移地址: 0x0C
 * 复位值: 0x6400 0000(GPIOA), 0x0000 0100(GPIOB), 0x0000 0000(其它)
 * 访问: word/half-word/byte访问
 */
#define GPIO_Pull_Up 0x00
#define GPIO_Pull_Down 0x01
#define Gen_Gpio_Pin_PuPd(pin, pupd) ((pupd) << 2 * (pin))
struct gpio_pupdr_bits {
    uint32 pin0 : 2;
    uint32 pin1 : 2;
    uint32 pin2 : 2;
    uint32 pin3 : 2;

    uint32 pin4 : 2;
    uint32 pin5 : 2;
    uint32 pin6 : 2;
    uint32 pin7 : 2;

    uint32 pin8 : 2;
    uint32 pin9 : 2;
    uint32 pin10 : 2;
    uint32 pin11 : 2;

    uint32 pin12 : 2;
    uint32 pin13 : 2;
    uint32 pin14 : 2;
    uint32 pin15 : 2;
};
union gpio_pupdr {
    struct gpio_pupdr_bits bits;
    uint32 all;
};
/*
 * 端口输入数据寄存器 GPIO_IDR
 * 偏移地址: 0x10
 * 复位值: 0x0000 XXXX
 * 访问: word/half-word/byte访问
 */
struct gpio_idr_bits {
    uint32 pin0 : 1;
    uint32 pin1 : 1;
    uint32 pin2 : 1;
    uint32 pin3 : 1;

    uint32 pin4 : 1;
    uint32 pin5 : 1;
    uint32 pin6 : 1;
    uint32 pin7 : 1;

    uint32 pin8 : 1;
    uint32 pin9 : 1;
    uint32 pin10 : 1;
    uint32 pin11 : 1;

    uint32 pin12 : 1;
    uint32 pin13 : 1;
    uint32 pin14 : 1;
    uint32 pin15 : 1;

    uint32 reserved : 16;
};
union gpio_idr {
    struct gpio_idr_bits bits;
    uint32 all;
};
/*
 * 端口输入数据寄存器 GPIO_ODR
 * 偏移地址: 0x14
 * 复位值: 0x0000 0000
 * 访问: word/half-word/byte访问
 */
struct gpio_odr_bits {
    uint32 pin0 : 1;
    uint32 pin1 : 1;
    uint32 pin2 : 1;
    uint32 pin3 : 1;

    uint32 pin4 : 1;
    uint32 pin5 : 1;
    uint32 pin6 : 1;
    uint32 pin7 : 1;

    uint32 pin8 : 1;
    uint32 pin9 : 1;
    uint32 pin10 : 1;
    uint32 pin11 : 1;

    uint32 pin12 : 1;
    uint32 pin13 : 1;
    uint32 pin14 : 1;
    uint32 pin15 : 1;

    uint32 reserved : 16;
};
union gpio_odr {
    struct gpio_odr_bits bits;
    uint32 all;
};
/*
 * 端口Set/Reset寄存器 GPIO_BSRR
 * 偏移地址: 0x18
 * 复位值: 0x0000 0000
 * 访问: word/half-word/byte访问
 */
struct gpio_bsrrl_bits {
    uint16 pin0 : 1;
    uint16 pin1 : 1;
    uint16 pin2 : 1;
    uint16 pin3 : 1;

    uint16 pin4 : 1;
    uint16 pin5 : 1;
    uint16 pin6 : 1;
    uint16 pin7 : 1;

    uint16 pin8 : 1;
    uint16 pin9 : 1;
    uint16 pin10 : 1;
    uint16 pin11 : 1;

    uint16 pin12 : 1;
    uint16 pin13 : 1;
    uint16 pin14 : 1;
    uint16 pin15 : 1;
};
union gpio_bsrrl {
    struct gpio_bsrrl_bits bits;
    uint16 all;
};
struct gpio_bsrrh_bits {
    uint16 pin0 : 1;
    uint16 pin1 : 1;
    uint16 pin2 : 1;
    uint16 pin3 : 1;

    uint16 pin4 : 1;
    uint16 pin5 : 1;
    uint16 pin6 : 1;
    uint16 pin7 : 1;

    uint16 pin8 : 1;
    uint16 pin9 : 1;
    uint16 pin10 : 1;
    uint16 pin11 : 1;

    uint16 pin12 : 1;
    uint16 pin13 : 1;
    uint16 pin14 : 1;
    uint16 pin15 : 1;
};
union gpio_bsrrh {
    struct gpio_bsrrh_bits bits;
    uint16 all;
};
struct gpio_bsrr_hws {
    union gpio_bsrrl set;
    union gpio_bsrrh reset;
};
union gpio_bsrr {
    struct gpio_bsrr_hws hwords;
    uint32 all;
};
/*
 * 端口配置锁定寄存器 GPIO_LCKR
 * 偏移地址: 0x1C
 * 复位值: 0x0000 0000
 * 访问: word访问
 *
 * 当按照101的序列写key后，端口的配置将被锁定，直到下一次MCU或者外设重置时解锁
 * 每个pin用于锁定端口的一个引脚的配置
 * 在写key时，pin的值不应当变动，该寄存器只能32位访问
 */
struct gpio_lckr_bits {
    uint32 pin0 : 1;
    uint32 pin1 : 1;
    uint32 pin2 : 1;
    uint32 pin3 : 1;

    uint32 pin4 : 1;
    uint32 pin5 : 1;
    uint32 pin6 : 1;
    uint32 pin7 : 1;

    uint32 pin8 : 1;
    uint32 pin9 : 1;
    uint32 pin10 : 1;
    uint32 pin11 : 1;

    uint32 pin12 : 1;
    uint32 pin13 : 1;
    uint32 pin14 : 1;
    uint32 pin15 : 1;

    uint32 key : 1;
    uint32 reserved : 15;
};
union gpio_lckr {
    struct gpio_lckr_bits bits;
    uint32 all;
};

/*
 * 端口复选功能寄存器 GPIO_AFR
 * 偏移地址: 0x20
 * 复位值: 0x0000 0000
 * 访问: word/half-word/byte访问
 */
#include <stm32f4xx_ioafmap.h>
struct gpio_afr_bits {
    uint32 pin0 : 4;
    uint32 pin1 : 4;
    uint32 pin2 : 4;
    uint32 pin3 : 4;

    uint32 pin4 : 4;
    uint32 pin5 : 4;
    uint32 pin6 : 4;
    uint32 pin7 : 4;

    uint32 pin8 : 4;
    uint32 pin9 : 4;
    uint32 pin10 : 4;
    uint32 pin11 : 4;

    uint32 pin12 : 4;
    uint32 pin13 : 4;
    uint32 pin14 : 4;
    uint32 pin15 : 4;
};
union gpio_afr {
    struct gpio_afr_bits bits;
    uint32 afr[2];
};

typedef struct gpio_regs {
    volatile union gpio_moder MODER;        /* 端口模式寄存器, offset: 0x00 */
    volatile union gpio_otyper OTYPER;      /* 端口输出类型寄存器, offset: 0x04 */
    volatile union gpio_ospeedr OSPEEDR;    /* 端口输出速度寄存器, offset: 0x08 */
    volatile union gpio_pupdr PUPDR;        /* 端口上拉下拉电阻寄存器, offset: 0x0C */
    volatile union gpio_idr IDR;            /* 端口输入数据寄存器, offset: 0x10 */
    volatile union gpio_odr ODR;            /* 端口输出数据寄存器, offset: 0x14 */
    volatile union gpio_bsrr BSRR;          /* 端口Set/Reset寄存器, offset: 0x18 */
    volatile union gpio_lckr LCKR;          /* 端口配置锁定寄存器, offset: 0x1C */
    volatile union gpio_afr AFR;            /* 端口复选功能寄存器, offset: 0x20-0x24 */
} gpio_regs_t;

/* GPIO寄存器地址映射 */
#define GPIOA_BASE 0x40020000
#define GPIOB_BASE 0x40020400
#define GPIOC_BASE 0x40020800
#define GPIOD_BASE 0x40020C00
#define GPIOE_BASE 0x40021000
#define GPIOF_BASE 0x40021400
#define GPIOG_BASE 0x40021800
#define GPIOH_BASE 0x40021C00
#define GPIOI_BASE 0x40022000
/* GPIO寄存器指针访问 */
#define GPIOA ((gpio_regs_t *) GPIOA_BASE)
#define GPIOB ((gpio_regs_t *) GPIOB_BASE)
#define GPIOC ((gpio_regs_t *) GPIOC_BASE)
#define GPIOD ((gpio_regs_t *) GPIOD_BASE)
#define GPIOE ((gpio_regs_t *) GPIOE_BASE)
#define GPIOF ((gpio_regs_t *) GPIOF_BASE)
#define GPIOG ((gpio_regs_t *) GPIOG_BASE)
#define GPIOH ((gpio_regs_t *) GPIOH_BASE)
#define GPIOI ((gpio_regs_t *) GPIOI_BASE)


