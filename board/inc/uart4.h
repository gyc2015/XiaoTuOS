#pragma once

void uart4_init(uint32 baudrate);
void uart4_send_byte(uint8 value);
void uart4_send_bytes(const uint8 *buf, uint32 len);
void uart4_send_str(const uint8 *str);


