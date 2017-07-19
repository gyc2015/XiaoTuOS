#include <stm32f407.h>
#include <xtos.h>
#include <led.h>
#include <uart4.h>
#include <w5500.h>

/***************************************************/
#define TASKA_STK_SIZE 1024
#define TASKB_STK_SIZE 1024
static uint32 taskA_Stk[TASKA_STK_SIZE];
static uint32 taskB_Stk[TASKB_STK_SIZE];

static struct xtos_task_struct taskA;
static struct xtos_task_struct taskB;

void task_switch() {
    if (gp_xtos_cur_task == &taskA)
        gp_xtos_next_task = &taskB;
    else
        gp_xtos_next_task = &taskA;

    xtos_context_switch();
}

void taska() {
    while (1) {
        LED_R = LED_ON;
        LED_G = LED_OFF;
        LED_B = LED_OFF;
    }
}

void taskb() {
    while (1) {
        LED_R = LED_OFF;
        LED_G = LED_ON;
        LED_B = LED_OFF;

        iwdg_feed();
        //wwdg_feed();
    }
}

#define SysTicks_Irq_n 15

void systick_init(uint32 ticks) {
    SYSTICK->LOAD.bits.cnt = ticks;         // 重装载数据
    SYSTICK->VAL.bits.cnt = 0;              // 清除当前计数

    SCB->SHP[SysTicks_Irq_n - 4] = 0x00;    // 暂时赋予最高优先级

    SYSTICK->CTRL.bits.clksource = 1;       // 使用CPU时钟168MHz
    SYSTICK->CTRL.bits.tickint = 1;         // 开启计数溢出中断
    SYSTICK->CTRL.bits.en = 0;              // 暂不开启计时器
}

void SysTick_Handler(void) {
    static int counter = 0;

    if ((counter++ % 1000) == 0) {
        task_switch();
    }
}
/***************************************************/

void config_interruts(void);

int main(void) {
    led_init();
    systick_init(168000);

    LED_R = LED_OFF;
    LED_G = LED_OFF;
    LED_B = LED_ON;

    for (int i = 0; i < 5000; i++)
        for (int j = 0; j < 1000; j++)
            ;

    w5500_init();
    //iwdg_init(IWDG_PR_DIV_16, 0xfff);
    //wwdg_init(WWDG_DIV8, 0x7F, 0x7E);

    xtos_create_task(&taskA, taska, &taskA_Stk[TASKA_STK_SIZE - 1]);
    xtos_create_task(&taskB, taskb, &taskB_Stk[TASKB_STK_SIZE - 1]);

    gp_xtos_next_task = &taskA;

    SYSTICK->CTRL.bits.en = 1;
    xtos_start();

    while (1) {
        
    }
}
