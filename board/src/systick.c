#include <systick.h>
#include <xtos.h>

void systick_init(uint32 ticks) {
    SYSTICK->LOAD.bits.cnt = ticks;         // ��װ������
    SYSTICK->VAL.bits.cnt = 0;              // �����ǰ����

    SCB->SHP[SysTicks_Irq_n - 4] = 0x00;    // ��ʱ����������ȼ�

    SYSTICK->CTRL.bits.clksource = 1;       // ʹ��CPUʱ��168MHz
    SYSTICK->CTRL.bits.tickint = 1;         // ������������ж�
    SYSTICK->CTRL.bits.en = 1;              // �ݲ�������ʱ��
}


void SysTick_Handler(void) {
    xtos_tick();
}

