#include <stm32f407.h>
#include <xtos.h>
#include <led.h>


/*
* tim3_init - ��ʼ��TIM3, ������������APB1��,����Ƶ�����Ϊ42MHz
*
* @pres: Ԥ��Ƶϵ��
* @period: ��������
*/
void tim3_init(uint16 pres, uint16 period) {
    RCC->APB1ENR.bits.tim3 = 1;
    TIM3->CR1.bits.DIR = TIM_COUNT_DIR_UP;
    TIM3->PSC = pres;
    TIM3->ARR = period;
    TIM3->EGR.bits.UG = 1;

    TIM3->DIER.bits.UIE = 1;
    TIM3->CR1.bits.CEN = 1;
}

static int counter = 0;
void TIM3_IRQHandler(void) {
    if (1 == TIM3->SR.bits.UIF) {
        if (0 == counter % 3) {
            LED_R = LED_ON;
            LED_G = LED_OFF;
            LED_B = LED_OFF;
        } else if (1 == counter % 3) {
            LED_R = LED_OFF;
            LED_G = LED_ON;
            LED_B = LED_OFF;
        } else if (2 == counter % 3) {
            LED_R = LED_OFF;
            LED_G = LED_OFF;
            LED_B = LED_ON;
        }
        counter++;
    }
    TIM3->SR.bits.UIF = 0;
}

void config_interruts(void);

int main(void) {
    led_init();
    tim3_init(42000, 1000);

    LED_R = LED_OFF;
    LED_G = LED_OFF;
    LED_B = LED_OFF;

    config_interruts();

    while (1) {
        
    }
}
