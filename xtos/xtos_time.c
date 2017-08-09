#include <xtos.h>
#include <xtos_time.h>

uint32 gXtosTicks = 0;

void xtos_tick(void) {
    gXtosTicks++;
}

void xtos_delay_ticks(uint32 ticks) {
    uint32 origin = gXtosTicks;
    uint32 delta = gXtosTicks - origin;

    while (delta < ticks) {
        xtos_schedule();
        delta = gXtosTicks - origin;
    }
}
