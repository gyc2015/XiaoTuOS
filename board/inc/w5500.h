#ifndef W5500_H
#define W5500_H

#include <types.h>

#define W5500_Max_Socket_Num    8
#define W5500_Max_Frame_Len     512

struct w5500 {
    uint8 mac[6];
    uint8 ip[4];
    uint8 sub[4];
    uint8 gw[4];
};

void w5500_init(void);

uint8 w5500_read_byte(uint32 addrbsb);
void w5500_write_byte(uint32 addrbsb, uint8 data);
void w5500_read_bytes(uint32 addrbsb, uint8 *buf, int len);
void w5500_write_bytes(uint32 addrbsb, const uint8 *buf, int len);

#endif
