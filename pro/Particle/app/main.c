#include <stm32f407.h>
#include <led.h>
#include <uart4.h>

void config_interruts(void);

int main(void) {
    led_init();
    uart4_init(115200);

    config_interruts();

    LED_R = LED_ON;
    LED_G = LED_OFF;
    LED_B = LED_OFF;

    uart4_send_str("wuhaha\r\n");

    while (1) {
        
    }
}
