#include <stm32f407.h>
#include <xtos.h>
#include <power.h>
#include <led.h>
#include <i2c1.h>

void config_interruts(void);
uint8 gtestdata;


uint8 txbuf[100];
uint8 rxbuf[100];


int main(void) {
    led_pwm_init();
    i2c1_init();

    config_interruts();

    led_set_color(0, 0, 5);

    for (int i = 0; i < 100; i++) {
        txbuf[i] = i;
        rxbuf[i] = 0;
    }
    Delay_fs(5);

    eeprom_write_bytes(txbuf, 100, 0);
    Delay_fs(1);
    eeprom_read_bytes(rxbuf, 100, 0);

    while (1) {

    }
}

/*




*/


