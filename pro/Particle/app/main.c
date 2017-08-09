#include <stm32f407.h>
#include <xtos.h>
#include <systick.h>
#include <led.h>
#include <uart4.h>

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
        xtos_delay_ticks(1000);
        led_set_color(5, 0, 100);
        xtos_delay_ticks(1000);
    }
}

void taskb() {
    while (1) {
        uart4_send_byte('A');
        xtos_delay_ticks(1000);
        uart4_send_byte('B');
        xtos_delay_ticks(1000);
    }
}

int main(void) {
    systick_init(168000);
    led_pwm_init();
    uart4_init(115200);

    xtos_init();
    xtos_init_task_descriptor(&taskA, taska, &taskA_Stk[TASKA_STK_SIZE - 1], 0);
    xtos_init_task_descriptor(&taskB, taskb, &taskB_Stk[TASKB_STK_SIZE - 1], 1);
    xtos_start();

    while (1) {

    }
}

