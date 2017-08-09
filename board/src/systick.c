#include <systick.h>
#include <xtos.h>

void systick_init(uint32 ticks) {
    SYSTICK->LOAD.bits.cnt = ticks;         // 重装载数据
    SYSTICK->VAL.bits.cnt = 0;              // 清除当前计数

    SCB->SHP[SysTicks_Irq_n - 4] = 0x00;    // 暂时赋予最高优先级

    SYSTICK->CTRL.bits.clksource = 1;       // 使用CPU时钟168MHz
    SYSTICK->CTRL.bits.tickint = 1;         // 开启计数溢出中断
    SYSTICK->CTRL.bits.en = 1;              // 暂不开启计时器
}


void SysTick_Handler(void) {
    xtos_tick();
}

