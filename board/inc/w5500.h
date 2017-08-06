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
 * MR - ģʽ�Ĵ���
 */
#define W5500_MR        0x000000
#define W5500_MR_RST    ((uint8)0x80)
/*
 * SHAR - ����MAC��ַ,��������,ip,����
 */
#define W5500_SHAR      0x000900
#define W5500_SUBR      0x000500
#define W5500_GAR       0x000100
#define W5500_SIPR      0x000F00
/*
 * IR - �жϼĴ���
 * IMR - �ж�����Ĵ���
 */
#define W5500_IR        0x001500
#define W5500_IMR       0x001600
#define W5500_INT_CONFLICT  ((uint8)0x80)   /* IP��ַ��ͻ */
#define W5500_INT_UNREACH   ((uint8)0x40)   /* Ŀ���ַ�޷����� */
#define W5500_INT_PPPoE     ((uint8)0x20)   /* PPPoE���ӹر� */
#define W5500_INT_MP        ((uint8)0x10)   /* Magic Packet */
/*
 * SIR - �׽����жϼĴ���
 * SIMR - �׽����ж�����Ĵ���
 */
#define W5500_SIR       0x001700
#define W5500_SIMR      0x001800
/*
 * PHYCFGR - ����PHY����ģʽ�Լ���λPHY
 */
#define W5500_PHYCFGR   0x002E00
#define W5500_PHY_nRST          ((uint8)0x80)   /* 0������λ */
#define W5500_PHY_FullDuplex    ((uint8)0x04)   /* 1:ȫ˫��, 0:��˫�� */
#define W5500_PHY_100Mpbs       ((uint8)0x02)   /* 1:100M, 0: 10M */
#define W5500_PHY_LinkUp        ((uint8)0x01)   /* 1:��������, 0:δ���� */
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
    uint16 timeout;     // ��ʱ
    uint8 rcount;      // �ظ�����
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
 * Sn_MR - �׽���n��ģʽ�Ĵ���
 */
#define W5500_Sn_MR(n)      (0x000008 + (n<<5))
#define W5500_SnMR_CLOSED   0x00
#define W5500_SnMR_TCP      0x01
#define W5500_SnMR_UDP      0x02
#define W5500_SnMR_MACRAW   0x04
#define W5500_SnMR_UNICAST  0x10    /* ʹ��Unicast blocking(UDP flag) */
#define W5500_SnMR_MIP6B    0x10    /* ʹ��IPv6 blocking(MACRAW flag) */
#define W5500_SnMR_ND       0x20    /* ʹ�����ӳ���Ӧ(No Delay ACK)(TCP flag) */
#define W5500_SnMR_MC       0x20    /* Using IGMP version 1(UDP flag) */
#define W5500_SnMR_MMB      0x20    /* ʹ�ܶಥblocking(MACRAW flag) */
#define W5500_SnMR_BCASTB   0x40    /* ʹ�ܹ㲥blocking(UDP, MACRAW flag) */
#define W5500_SnMR_MULTI    0x80    /* ʹ�ܶಥblocking(UDP flag) */
#define W5500_SnMR_MFEN     0x80    /* Enable MAC Filtering(MACRAW flag) */
/*
 * Sn_CR - �׽���n��ָ��Ĵ���
 */
#define W5500_Sn_CR(n)          (0x000108 + (n<<5))
#define W5500_SnCR_OPEN         0x01     /* ��ʼ��Socket */
#define W5500_SnCR_LISTEN       0x02     /* Socket������TCP������ģʽ��,�ȴ��ͻ������� */
#define W5500_SnCR_CONNECT      0x04     /* Socket������TCP�ͻ���ģʽ��,��Sn_DIPR��Sn_DPORTָ����IP�Ͷ˿ڷ����������� */
#define W5500_SnCR_DISCON       0x08     /* TCPģʽ�µ�Socket���ͶϿ��������� */
#define W5500_SnCR_CLOSE        0x10     /* �ر�socket */
#define W5500_SnCR_SEND         0x20     /* ����TX�����е����� */
#define W5500_SnCR_SEND_MAC     0x21     /* UDPģʽ�µ�Socket�������ݸ���Sn_DHAR�е�MAC��ַ,��ͨ��ARP���̻�ȡMAC��ַ */
#define W5500_SnCR_SEND_KEEP    0x22     /* TCPģʽ�µ�Socket����һ���ֽڵ�keep alive�� */
#define W5500_SnCR_RECV         0x40     /* ����RX�����е����� */
/*
 * Sn_IR - �׽���n���жϼĴ���
 * Sn_IMR - �׽���n���ж�����Ĵ���
 */
#define W5500_Sn_IR(n)          (0x000208 + (n << 5))
#define W5500_Sn_IMR(n)         (0x002C08 + (n << 5))
#define W5500_SnIR_SEND_OK      0x10    /* ������� */
#define W5500_SnIR_TIMEOUT      0x08    /* ��ʱ */
#define W5500_SnIR_RECV         0x04    /* �������� */
#define W5500_SnIR_DISCON       0x02    /* ���յ�FIN����FIN/ACK */
#define W5500_SnIR_CON          0x01    /* �������� */
#define W5500_SnIR_All          0x1F    /* ���������ж� */

/*
 * Sn_SR - �׽���n��״̬�Ĵ���
 */
#define W5500_Sn_SR(n)          (0x000308 + (n<<5))
#define W5500_SnSR_CLOSED       0x00    /* Socket���ͷ� */
#define W5500_SnSR_INIT         0x13    /* Socket��TCP����ʽ���� */
#define W5500_SnSR_LISTEN       0x14    /* Socket������TCP������ģʽ��,�ȴ����Կͻ��˵��������� */
#define W5500_SnSR_ESTABLISHED  0x17    /* Socket���������� */
#define W5500_SnSR_CLOSE_WAIT   0x1C    /* Socket���յ��˶Է��Ͽ����ӵ����� */
#define W5500_SnSR_UDP          0x22    /* Socket��UDP����ʽ���� */
#define W5500_SnSR_MACRAW       0x42    /* Socket��MACRAW����ʽ���� */
#define W5500_SnSR_SYNSENT      0x15    /* Socket������һ����������SYN */

#define W5500_Sn_PORT(n)        (0x000408 + (n<<5))
#define W5500_Sn_DIPR(n)        (0x000C08 + (n<<5))
#define W5500_Sn_DPORT(n)       (0x001008 + (n<<5))
/*
* Sn_RXBUF_SIZE - �׽���n�Ľ��ջ����С�Ĵ���
* Sn_TXBUF_SIZE - �׽���n�ķ��ͻ����С�Ĵ���
*/
#define W5500_Sn_RXBUF_SIZE(n)  (0x001E08 + (n<<5))
#define W5500_Sn_TXBUF_SIZE(n)  (0x001F08 + (n<<5))

#define W5500_Sn_TX_FSR(n)      (0x002008 + (n<<5))
#define W5500_Sn_TX_WR(n)       (0x002408 + (n<<5))
/*
 * Sn_RX_RSR - �׽���n�������ݳ��ȼĴ���
 */
#define W5500_Sn_RX_RSR(n)      (0x002608 + (n<<5))
#define W5500_Sn_RX_RD(n)       (0x002808 + (n<<5))
/*
 * w5500_init_sn - ��ʼ���׽���@n
 */
w5500_error_t w5500_init_socket(uint8 n, uint8 mode, uint16 port);
/*
 * w5500_close_sn - �ر��׽���@n
 */
w5500_error_t w5500_close_socket(uint8 n);
/*
 * w5500_connect_socket - �����׽���@n,TCP�ͻ���ģʽ
 */
w5500_error_t w5500_connect_socket(uint8 n, uint8 *ip, uint16 port);
/*
 * w5500_get_sn_received_len - ��ȡ�׽���@n���յ������ݳ���
 */
uint16 w5500_get_socket_received_len(uint8 n);
/*
 * w5500_receive_socket - �����׽���@n
 */
w5500_error_t w5500_receive_socket(uint8 n, uint8 *buf, uint16 len);
/*
 * w5500_send_socket - �����׽���@n
 */
w5500_error_t w5500_send_socket(uint8 n, uint8 *buf, uint16 len);


#endif
