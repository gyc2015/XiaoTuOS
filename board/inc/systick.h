#pragma once

#include <stm32f407.h>

#define SysTicks_Irq_n 15

void systick_init(uint32 ticks);
