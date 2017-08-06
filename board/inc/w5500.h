#ifndef W5500_H
#define W5500_H

#include <types.h>

#define W5500_Max_Socket_Num    8
#define W5500_Max_Frame_Len     512

typedef enum w5500_error {
    Err_W5500_No_Error = 0,
    Err_W5500_Phy_No_Link = 1,
    Err_W5500_Timeout = 2,
    Err_W5500_Socket_CmdErr = 3,
    Err_W5500_Connect_Failed = 4,
    Err_W5500_TxBuf_Overflow = 5,
    Err_W5500_SendData_Err = 6
} w5500_error_t;

/*
 * MR - 模式寄存器
 */
#define W5500_MR        0x000000
#define W5500_MR_RST    ((uint8)0x80)
/*
 * SHAR - 本地MAC地址,子网掩码,ip,网关
 */
#define W5500_SHAR      0x000900
#define W5500_SUBR      0x000500
#define W5500_GAR       0x000100
#define W5500_SIPR      0x000F00
/*
 * IR - 中断寄存器
 * IMR - 中断掩码寄存器
 */
#define W5500_IR        0x001500
#define W5500_IMR       0x001600
#define W5500_INT_CONFLICT  ((uint8)0x80)   /* IP地址冲突 */
#define W5500_INT_UNREACH   ((uint8)0x40)   /* 目标地址无法访问 */
#define W5500_INT_PPPoE     ((uint8)0x20)   /* PPPoE连接关闭 */
#define W5500_INT_MP        ((uint8)0x10)   /* Magic Packet */
/*
 * SIR - 套接字中断寄存器
 * SIMR - 套接字中断掩码寄存器
 */
#define W5500_SIR       0x001700
#define W5500_SIMR      0x001800
/*
 * PHYCFGR - 配置PHY工作模式以及复位PHY
 */
#define W5500_PHYCFGR   0x002E00
#define W5500_PHY_nRST          ((uint8)0x80)   /* 0触发复位 */
#define W5500_PHY_FullDuplex    ((uint8)0x04)   /* 1:全双工, 0:半双工 */
#define W5500_PHY_100Mpbs       ((uint8)0x02)   /* 1:100M, 0: 10M */
#define W5500_PHY_LinkUp        ((uint8)0x01)   /* 1:建立连接, 0:未建立 */
/*
 * RTR - retry time value register
 * RCR - retry count register
 */
#define W5500_RTR       0x001900
#define W5500_RCR       0x001B00

struct w5500 {
    uint8 mac[6];
    uint8 ip[4];
    uint8 sub[4];
    uint8 gw[4];
    uint8 txbuf_size[W5500_Max_Socket_Num];
    uint8 rxbuf_size[W5500_Max_Socket_Num];
    uint16 timeout;     // 超时
    uint8 rcount;      // 重复次数
};


w5500_error_t w5500_sw_reset(void);
w5500_error_t w5500_init(struct w5500 *dev);

uint8 w5500_read_byte(uint32 addrbsb);
void w5500_write_byte(uint32 addrbsb, uint8 data);
void w5500_read_bytes(uint32 addrbsb, uint8 *buf, int len);
void w5500_read_bytes_inv(uint32 addrbsb, uint8 *buf, int len);
void w5500_write_bytes(uint32 addrbsb, const uint8 *buf, int len);
void w5500_write_bytes_inv(uint32 addrbsb, const uint8 *buf, int len);

/******************************************************/
/*
 * Sn_MR - 套接字n的模式寄存器
 */
#define W5500_Sn_MR(n)      (0x000008 + (n<<5))
#define W5500_SnMR_CLOSED   0x00
#define W5500_SnMR_TCP      0x01
#define W5500_SnMR_UDP      0x02
#define W5500_SnMR_MACRAW   0x04
#define W5500_SnMR_UNICAST  0x10    /* 使能Unicast blocking(UDP flag) */
#define W5500_SnMR_MIP6B    0x10    /* 使能IPv6 blocking(MACRAW flag) */
#define W5500_SnMR_ND       0x20    /* 使用无延迟响应(No Delay ACK)(TCP flag) */
#define W5500_SnMR_MC       0x20    /* Using IGMP version 1(UDP flag) */
#define W5500_SnMR_MMB      0x20    /* 使能多播blocking(MACRAW flag) */
#define W5500_SnMR_BCASTB   0x40    /* 使能广播blocking(UDP, MACRAW flag) */
#define W5500_SnMR_MULTI    0x80    /* 使能多播blocking(UDP flag) */
#define W5500_SnMR_MFEN     0x80    /* Enable MAC Filtering(MACRAW flag) */
/*
 * Sn_CR - 套接字n的指令寄存器
 */
#define W5500_Sn_CR(n)          (0x000108 + (n<<5))
#define W5500_SnCR_OPEN         0x01     /* 初始化Socket */
#define W5500_SnCR_LISTEN       0x02     /* Socket工作在TCP服务器模式下,等待客户端连接 */
#define W5500_SnCR_CONNECT      0x04     /* Socket工作在TCP客户端模式下,向Sn_DIPR和Sn_DPORT指定的IP和端口发送连接请求 */
#define W5500_SnCR_DISCON       0x08     /* TCP模式下的Socket发送断开连接请求 */
#define W5500_SnCR_CLOSE        0x10     /* 关闭socket */
#define W5500_SnCR_SEND         0x20     /* 发送TX缓存中的数据 */
#define W5500_SnCR_SEND_MAC     0x21     /* UDP模式下的Socket发送数据附带Sn_DHAR中的MAC地址,不通过ARP过程获取MAC地址 */
#define W5500_SnCR_SEND_KEEP    0x22     /* TCP模式下的Socket发送一个字节的keep alive包 */
#define W5500_SnCR_RECV         0x40     /* 接收RX缓存中的数据 */
/*
 * Sn_IR - 套接字n的中断寄存器
 * Sn_IMR - 套接字n的中断掩码寄存器
 */
#define W5500_Sn_IR(n)          (0x000208 + (n << 5))
#define W5500_Sn_IMR(n)         (0x002C08 + (n << 5))
#define W5500_SnIR_SEND_OK      0x10    /* 发送完毕 */
#define W5500_SnIR_TIMEOUT      0x08    /* 超时 */
#define W5500_SnIR_RECV         0x04    /* 接收数据 */
#define W5500_SnIR_DISCON       0x02    /* 接收到FIN或者FIN/ACK */
#define W5500_SnIR_CON          0x01    /* 建立连接 */
#define W5500_SnIR_All          0x1F    /* 上述所有中断 */

/*
 * Sn_SR - 套接字n的状态寄存器
 */
#define W5500_Sn_SR(n)          (0x000308 + (n<<5))
#define W5500_SnSR_CLOSED       0x00    /* Socket被释放 */
#define W5500_SnSR_INIT         0x13    /* Socket以TCP的形式被打开 */
#define W5500_SnSR_LISTEN       0x14    /* Socket工作在TCP服务器模式下,等待来自客户端的连接请求 */
#define W5500_SnSR_ESTABLISHED  0x17    /* Socket建立了连接 */
#define W5500_SnSR_CLOSE_WAIT   0x1C    /* Socket接收到了对方断开连接的请求 */
#define W5500_SnSR_UDP          0x22    /* Socket以UDP的形式被打开 */
#define W5500_SnSR_MACRAW       0x42    /* Socket以MACRAW的形式被打开 */
#define W5500_SnSR_SYNSENT      0x15    /* Socket发送了一个连接请求SYN */

#define W5500_Sn_PORT(n)        (0x000408 + (n<<5))
#define W5500_Sn_DIPR(n)        (0x000C08 + (n<<5))
#define W5500_Sn_DPORT(n)       (0x001008 + (n<<5))
/*
* Sn_RXBUF_SIZE - 套接字n的接收缓存大小寄存器
* Sn_TXBUF_SIZE - 套接字n的发送缓存大小寄存器
*/
#define W5500_Sn_RXBUF_SIZE(n)  (0x001E08 + (n<<5))
#define W5500_Sn_TXBUF_SIZE(n)  (0x001F08 + (n<<5))

#define W5500_Sn_TX_FSR(n)      (0x002008 + (n<<5))
#define W5500_Sn_TX_WR(n)       (0x002408 + (n<<5))
/*
 * Sn_RX_RSR - 套接字n接收数据长度寄存器
 */
#define W5500_Sn_RX_RSR(n)      (0x002608 + (n<<5))
#define W5500_Sn_RX_RD(n)       (0x002808 + (n<<5))
/*
 * w5500_init_sn - 初始化套接字@n
 */
w5500_error_t w5500_init_socket(uint8 n, uint8 mode, uint16 port);
/*
 * w5500_close_sn - 关闭套接字@n
 */
w5500_error_t w5500_close_socket(uint8 n);
/*
 * w5500_connect_socket - 连接套接字@n,TCP客户端模式
 */
w5500_error_t w5500_connect_socket(uint8 n, uint8 *ip, uint16 port);
/*
 * w5500_get_sn_received_len - 获取套接字@n接收到的数据长度
 */
uint16 w5500_get_socket_received_len(uint8 n);
/*
 * w5500_receive_socket - 接收套接字@n
 */
w5500_error_t w5500_receive_socket(uint8 n, uint8 *buf, uint16 len);
/*
 * w5500_send_socket - 发送套接字@n
 */
w5500_error_t w5500_send_socket(uint8 n, uint8 *buf, uint16 len);


#endif
