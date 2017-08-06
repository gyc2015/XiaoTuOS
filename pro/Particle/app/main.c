#include <stm32f407.h>
#include <xtos.h>
#include <power.h>
#include <led.h>
#include <w5500.h>

void config_interruts(void);

extern struct w5500 gW5500;
uint8 remote_ip[4] = { 192,168,1,101 };
uint8 gTmpByte = 0;
uint16 gReceivedLen = 0;
uint8 gRxBuf[1024];
w5500_error_t gW5500Err = Err_W5500_No_Error;

int main(void) {
    led_pwm_init();

    for (int i = 0; i < 5000; i++)
        for (int j = 0; j < 1000; j++)
            ;

    config_interruts();

    led_set_color(0, 0, 5);

    w5500_init(&gW5500);

    while (1) {
        switch (w5500_read_byte(W5500_Sn_SR(0))) {
        case W5500_SnSR_CLOSED:
            gW5500Err = w5500_init_socket(0, W5500_SnMR_TCP | W5500_SnMR_ND, 0);
            break;
        case W5500_SnSR_INIT:
            gW5500Err = w5500_connect_socket(0, remote_ip, 60001);
            break;
        case W5500_SnSR_ESTABLISHED:
            gReceivedLen = w5500_get_socket_received_len(0);
            if (gReceivedLen > 0) {
                gW5500Err = w5500_receive_socket(0, gRxBuf, gReceivedLen);
                gW5500Err = w5500_send_socket(0, gRxBuf, gReceivedLen);
            }
            break;
        default:
            gTmpByte = w5500_read_byte(W5500_Sn_SR(0));
            break;
        }
    }
}
