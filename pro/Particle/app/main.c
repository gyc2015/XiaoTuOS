#include <stm32f407.h>
#include <xtos.h>
#include <led.h>

#include <utils.h>

#define TASKA_STK_SIZE 1024
#define TASKB_STK_SIZE 1024
static uint32 taskA_Stk[TASKA_STK_SIZE];
static uint32 taskB_Stk[TASKB_STK_SIZE];

static struct xtos_task_descriptor taskA;
static struct xtos_task_descriptor taskB;

void taska() {
    while (1) {
        led_set_color(100, 0, 5);
        for (int i = 0; i < 1000; i++)
            delay(10000);
        xtos_schedule();
    }
}

void taskb() {
    while (1) {
        led_set_color(5, 0, 100);
        for (int i = 0; i < 1000; i++)
            delay(10000);
        xtos_schedule();
    }
}

int main(void) {
    led_pwm_init();

    xtos_init();
    xtos_init_task_descriptor(&taskA, taska, &taskA_Stk[TASKA_STK_SIZE - 1], 0);
    xtos_init_task_descriptor(&taskB, taskb, &taskB_Stk[TASKB_STK_SIZE - 1], 1);
    xtos_start();

    while (1) {

    }
}

