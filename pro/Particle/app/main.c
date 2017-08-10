#include <stm32f407.h>
#include <xtos.h>
#include <power.h>
#include <led.h>
#include <w5500.h>

void config_interruts(void);

extern struct w5500 gW5500;
struct w5500_socket gSocket0 = {
    .n = 0,
    .mode = W5500_SnMR_UDP,
    .remote_ip = { 192,168,1,101 },
    .remote_port = 5000,
    .local_port = 5000
};

struct w5500_socket gSocket1 = {
    .n = 1,
    .mode = W5500_SnMR_TCP | W5500_SnMR_ND,
    .remote_ip = { 192,168,1,101 },
    .remote_port = 60001,
    .local_port = 6000
};

struct w5500_socket gSocket2 = {
    .n = 2,
    .mode = W5500_SnMR_TCP | W5500_SnMR_ND,
    .remote_ip = { 192,168,1,101 },
    .remote_port = 60000,
    .local_port = 6001
};

uint8 gRxBuf0[1024];
uint8 gRxBuf1[1024];
uint8 gRxBuf2[1024];

uint8 remote_ip[4] = { 192,168,1,101 };
uint16 remote_port = 60001;
uint8 gTmpByte = 0;
uint16 gReceivedLen = 0;
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
        int tmp;
        switch (w5500_get_socket_status(&gSocket0)) {
        case W5500_SnSR_CLOSED:
            gW5500Err = w5500_init_socket(&gSocket0);
            break;
        case W5500_SnSR_UDP:
            gReceivedLen = w5500_get_socket_received_len(&gSocket0);
            if (gReceivedLen > 0) {
                tmp = w5500_receive_from(&gSocket0, gRxBuf0, gReceivedLen);
                if (-1 != tmp)
                    gW5500Err = w5500_send_to(&gSocket0, gRxBuf0, tmp);
            }
            break;
        }
        /*********************************************/
        switch (w5500_get_socket_status(&gSocket1)) {
        case W5500_SnSR_CLOSED:
            gW5500Err = w5500_init_socket(&gSocket1);
            break;
        case W5500_SnSR_INIT:
            gW5500Err = w5500_connect_socket(&gSocket1);
            break;
        case W5500_SnSR_ESTABLISHED:
            gReceivedLen = w5500_get_socket_received_len(&gSocket1);
            if (gReceivedLen > 0) {
                if (-1 != w5500_receive(&gSocket1, gRxBuf1, gReceivedLen))
                    gW5500Err = w5500_send(&gSocket1, gRxBuf1, gReceivedLen);
            }
            break;
        }
        /*********************************************/
        switch (w5500_get_socket_status(&gSocket2)) {
        case W5500_SnSR_CLOSED:
            gW5500Err = w5500_init_socket(&gSocket2);
            break;
        case W5500_SnSR_INIT:
            gW5500Err = w5500_listen_socket(&gSocket2);
            break;
        case W5500_SnSR_ESTABLISHED:
            gReceivedLen = w5500_get_socket_received_len(&gSocket2);
            if (gReceivedLen > 0) {
                if (-1 != w5500_receive(&gSocket2, gRxBuf2, gReceivedLen))
                    gW5500Err = w5500_send(&gSocket2, gRxBuf2, gReceivedLen);
            }
            break;
        }
    }
}

/*




*/


