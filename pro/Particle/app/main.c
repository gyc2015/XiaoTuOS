#include <stm32f407.h>
#include <xtos.h>
#include <systick.h>
#include <led.h>
#include <uart4.h>
#include <sdio.h>
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

uint8 gUartByte = '0';
void taskb() {
	while (1) {
		uart4_send_byte(gUartByte);
		xtos_block();
	}
}

void UART4_IRQHandler(void) {
	if (0 != UART4->SR.bits.RXNE) {
		gUartByte = UART4->DR.bits.byte;
		xtos_wakeup_task(&taskB);
	}
}

void config_interruts(void);
struct sd_card gSDCard;
uint8 writebuf[512];
uint8 readbuf[512];

int main(void) {
	systick_init(168000);
	led_pwm_init();
	uart4_init(115200);
	sdio_init(&gSDCard);

	config_interruts();

	uart4_send_str("G.Y.C");
	for (int i = 0; i < 512; i++)
		writebuf[i] = 'B';
	delay(1000000);
	sdio_write_block(&gSDCard, 0, writebuf);
	delay(1000000);
	uart4_send_str("\r\nG.Y.C\r\n");

	sdio_read_block(&gSDCard, 0, readbuf);
	delay(1000000);
	uart4_send_str("\r\n====\r\n");
	for (int i = 0; i < 512; i++)
		uart4_send_byte(readbuf[i]);
	uart4_send_str("\r\n====\r\n");



	xtos_init();
	xtos_init_task_descriptor(&taskA, taska, &taskA_Stk[TASKA_STK_SIZE - 1], 0);
	xtos_init_task_descriptor(&taskB, taskb, &taskB_Stk[TASKB_STK_SIZE - 1], 1);
	xtos_start();

	while (1) {

	}
}

