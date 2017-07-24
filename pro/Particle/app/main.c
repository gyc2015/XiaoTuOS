#include <stm32f407.h>
#include <xtos.h>
#include <led.h>

void config_interruts(void);

int main(void) {
    led_pwm_init();

    LED_R = LED_OFF;
    LED_G = LED_OFF;
    LED_B = LED_OFF;

    config_interruts();

    led_set_color(0, 0, 50);

    led_set_color(0, 50, 50);

    while (1) {
        
    }
}
