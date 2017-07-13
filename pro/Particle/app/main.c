#include <stm32f407.h>

int data = 0;

int main(void) {
    data = 31;

    while(1) {
        data++;
    }
}
