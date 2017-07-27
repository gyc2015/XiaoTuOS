#include <stm32f407.h>
#include <xtos.h>
#include <power.h>
#include <led.h>

void config_interruts(void);

float vcc;
float current;
float d1v2;
float d3v3;
float a2v5;

int main(void) {
    led_pwm_init();
    power_init();

    for (int i = 0; i < 5000; i++)
        for (int j = 0; j < 1000; j++)
            ;

    config_interruts();

    led_set_color(0, 0, 5);

    vcc = power_get_vcc();
    current = power_get_current();
    d1v2 = power_get_D1V2();
    d3v3 = power_get_D3V3();
    a2v5 = power_get_A2V5();

    while (1) {
        
    }
}
