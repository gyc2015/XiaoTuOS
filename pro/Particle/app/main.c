#include <stm32f407.h>
#include <xtos.h>
#include <led.h>

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
        led_set_color(100, 0, 5);
    }
}

void taskb() {
    while (1) {
        led_set_color(5, 0, 100);
    }
}

#define SysTicks_Irq_n 15

void systick_init(uint32 ticks) {
    SYSTICK->LOAD.bits.cnt = ticks;         // ��װ������
    SYSTICK->VAL.bits.cnt = 0;              // �����ǰ����

    SCB->SHP[SysTicks_Irq_n - 4] = 0x00;    // ��ʱ����������ȼ�

    SYSTICK->CTRL.bits.clksource = 1;       // ʹ��CPUʱ��168MHz
    SYSTICK->CTRL.bits.tickint = 1;         // ������������ж�
    SYSTICK->CTRL.bits.en = 0;              // �ݲ�������ʱ��
}

void SysTick_Handler(void) {
    static int counter = 0;

    if ((counter++ % 1000) == 0) {
        task_switch();
    }
}

int main(void) {
    led_pwm_init();
    systick_init(168000);

    xtos_create_task(&taskA, taska, &taskA_Stk[TASKA_STK_SIZE - 1]);
    xtos_create_task(&taskB, taskb, &taskB_Stk[TASKB_STK_SIZE - 1]);

    gp_xtos_next_task = &taskA;

    SYSTICK->CTRL.bits.en = 1;
    xtos_start();

    while (1) {

    }
}
