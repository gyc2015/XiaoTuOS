#include <stm32f407.h>
#include <xtos.h>
#include <led.h>

void delay(int c) {
    for (int i = 0; i < c; i++);
}

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
        for (int i = 0; i < 1000; i++)
            delay(10000);
        task_switch();
    }
}

void taskb() {
    while (1) {
        led_set_color(5, 0, 100);
        for (int i = 0; i < 1000; i++)
            delay(10000);
        task_switch();
    }
}


int main(void) {
    led_pwm_init();

    xtos_create_task(&taskA, taska, &taskA_Stk[TASKA_STK_SIZE - 1]);
    xtos_create_task(&taskB, taskb, &taskB_Stk[TASKB_STK_SIZE - 1]);

    gp_xtos_next_task = &taskA;

    xtos_start();

    while (1) {

    }
}
