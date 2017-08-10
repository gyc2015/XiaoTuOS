#include <stm32f4xx_spi.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <w5500.h>

#define spi_select() (PAout(15) = 0)
#define spi_unselect()  (PAout(15) = 1)
#define W5500_SPI   SPI1

struct w5500 gW5500 = {
    .mac = { 0x00,0x98,0xdc,0x42,0x61,0x11 },
    .ip = { 192,168,1,10 },
    .sub = { 255,255,255,0 },
    .gw = { 192,168,1,1 },
    .txbuf_size = { 2,2,2,2, 2,2,2,2 },
    .rxbuf_size = { 2,2,2,2, 2,2,2,2 },
    .timeout = 2000,
    .rcount = 8
};

/*
 * delay_ms - 延时函数
 */
static void delay_ms(int ct) {
    int i, j;

    for (i = 0; i < ct; i++) {
        for (j = 0; j < 10000; j++);
    }
}
/*
 * w5500_init_spi - 初始化W5500的SPI端口
 */
static void w5500_init_spi(void) {
    RCC->AHB1ENR.bits.gpioa = 1;
    RCC->AHB1ENR.bits.gpiob = 1;
    RCC->APB2ENR.bits.spi1 = 1;
    // 功能选择
    GPIOA->AFR.bits.pin7 = GPIO_AF_SPI1;
    GPIOB->AFR.bits.pin3 = GPIO_AF_SPI1;
    GPIOB->AFR.bits.pin4 = GPIO_AF_SPI1;
    // 片选引脚PA15
    struct gpio_pin_conf pincof;
    pincof.mode = GPIO_Mode_Out;
    pincof.otype = GPIO_OType_PP;
    pincof.pull = GPIO_Pull_Up;
    pincof.speed = GPIO_OSpeed_High;
    gpio_init(GPIOA, GPIO_Pin_15, &pincof);
    // PA7->MOSI, PB3->SCK, PB4->MISO
    pincof.mode = GPIO_Mode_Af;
    gpio_init(GPIOA, GPIO_Pin_7, &pincof);
    gpio_init(GPIOB, GPIO_Pin_3 | GPIO_Pin_4, &pincof);
    // W5500_SPI配置
    W5500_SPI->CR1.bits.SPE = 0;
    W5500_SPI->CR1.bits.MSTR = 1;
    W5500_SPI->CR1.bits.DFF = SPI_Data_Size_8b; // 8位
    W5500_SPI->CR1.bits.CPHA = 0;
    W5500_SPI->CR1.bits.CPOL = 0;
    W5500_SPI->CR1.bits.BR = SPI_Prescaler_2;
    W5500_SPI->CR1.bits.LSBFIRST = 0;
    W5500_SPI->CR1.bits.SSM = 1;
    W5500_SPI->CR1.bits.SSI = 1;
    W5500_SPI->CR1.bits.SPE = 1;
    // 片选
    spi_unselect();
}

/************************************************/

/*
 * w5500_sw_reset - 软件复位
 */
w5500_error_t w5500_sw_reset(void) {
    w5500_write_byte(W5500_MR, W5500_MR_RST);
    uint32 timeout = 10;
    while (0 != (W5500_MR_RST & w5500_read_byte(W5500_MR))) {
        delay_ms(100);
        if (0 == timeout--)
            return Err_W5500_Timeout;
    }
    return Err_W5500_No_Error;
}

/*
 * w5500_init - 初始化W5500
 */
w5500_error_t w5500_init(struct w5500 *dev) {
    w5500_init_spi();
    delay_ms(2000);

    // 检查链接是否建立
    uint8 retry = 100;
    while (0 == (W5500_PHY_LinkUp & w5500_read_byte(W5500_PHYCFGR))) {
        delay_ms(100);
        if (0 == retry--)
            return Err_W5500_Phy_No_Link;
        retry--;
    }

    w5500_sw_reset();
    // 配置本地mac, 子网掩码, 网关, ip
    w5500_write_bytes(W5500_SHAR, dev->mac, 6);
    w5500_write_bytes(W5500_SUBR, dev->sub, 4);
    w5500_write_bytes(W5500_GAR, dev->gw, 4);
    w5500_write_bytes(W5500_SIPR, dev->ip, 4);
    // 配置Socket收发缓存大小
    for (int i = 0; i < W5500_Max_Socket_Num; i++) {
        w5500_write_byte(W5500_Sn_RXBUF_SIZE(i), dev->rxbuf_size[i]);
        w5500_write_byte(W5500_Sn_TXBUF_SIZE(i), dev->txbuf_size[i]);
    }
    // 超时时间和重复次数
    w5500_write_bytes_inv(W5500_RTR, (uint8*)&(dev->timeout), 2);
    w5500_write_byte(W5500_RCR, dev->rcount);
    // 配置中断
    w5500_write_byte(W5500_IMR, (W5500_INT_CONFLICT | W5500_INT_UNREACH));
    w5500_write_byte(W5500_SIMR, U8Bit(0));
    w5500_write_byte(W5500_Sn_IMR(0), W5500_SnIR_All);

    return Err_W5500_No_Error;
}

uint8 w5500_read_byte(uint32 addrbsb) {
    spi_select();

    spi_exchange(W5500_SPI, (addrbsb & 0x00FF0000) >> 16);
    spi_exchange(W5500_SPI, (addrbsb & 0x0000FF00) >> 8);
    spi_exchange(W5500_SPI, (addrbsb & 0x000000F8));
    uint8 data = spi_exchange(W5500_SPI, 0x00);

    spi_unselect();
    return data;
}

void w5500_write_byte(uint32 addrbsb, uint8 data) {
    spi_select();

    spi_exchange(W5500_SPI, (addrbsb & 0x00FF0000) >> 16);
    spi_exchange(W5500_SPI, (addrbsb & 0x0000FF00) >> 8);
    spi_exchange(W5500_SPI, (addrbsb & 0x000000F8) + 4);
    spi_exchange(W5500_SPI, data);

    spi_unselect();
}

void w5500_read_bytes(uint32 addrbsb, uint8 *buf, int len) {
    spi_select();

    spi_exchange(W5500_SPI, (addrbsb & 0x00FF0000) >> 16);
    spi_exchange(W5500_SPI, (addrbsb & 0x0000FF00) >> 8);
    spi_exchange(W5500_SPI, (addrbsb & 0x000000F8));

    for (int i = 0; i < len; i++)
        buf[i] = spi_exchange(W5500_SPI, 0x00);

    spi_unselect();
}
/*
 * w5500_write_bytes_inv - 逆序接收数据到@buf中
 */
void w5500_read_bytes_inv(uint32 addrbsb, uint8 *buf, int len) {
    spi_select();

    spi_exchange(W5500_SPI, (addrbsb & 0x00FF0000) >> 16);
    spi_exchange(W5500_SPI, (addrbsb & 0x0000FF00) >> 8);
    spi_exchange(W5500_SPI, (addrbsb & 0x000000F8));

    for (int i = 0; i < len; i++)
        buf[len - i - 1] = spi_exchange(W5500_SPI, 0x00);

    spi_unselect();
}

void w5500_write_bytes(uint32 addrbsb, const uint8 *buf, int len) {
    spi_select();

    spi_exchange(W5500_SPI, (addrbsb & 0x00FF0000) >> 16);
    spi_exchange(W5500_SPI, (addrbsb & 0x0000FF00) >> 8);
    spi_exchange(W5500_SPI, (addrbsb & 0x000000F8) + 4);

    for (int i = 0; i < len; i++)
        spi_exchange(W5500_SPI, buf[i]);

    spi_unselect();
}
/*
 * w5500_write_bytes_inv - 逆序发送@buf中的数据
 */
void w5500_write_bytes_inv(uint32 addrbsb, const uint8 *buf, int len) {
    spi_select();

    spi_exchange(W5500_SPI, (addrbsb & 0x00FF0000) >> 16);
    spi_exchange(W5500_SPI, (addrbsb & 0x0000FF00) >> 8);
    spi_exchange(W5500_SPI, (addrbsb & 0x000000F8) + 4);

    for (int i = 0; i < len; i++)
        spi_exchange(W5500_SPI, buf[len - i - 1]);

    spi_unselect();
}

/************************************************/
static bool w5500_send_sncmd(uint8 n, uint8 cmd) {
    w5500_write_byte(W5500_Sn_CR(n), cmd);
    uint8 retry = 100;
    while (w5500_read_byte(W5500_Sn_CR(n))) {
        delay_ms(100);
        if (0 == retry--)
            return FALSE;
        retry--;
    }
    return TRUE;
}
/*
 * w5500_init_socket - 初始化套接字
 *
 * @socket: 套接字对象
 */
w5500_error_t w5500_init_socket(const struct w5500_socket *socket) {
    w5500_error_t err = w5500_close_socket(socket);
    if (Err_W5500_No_Error != err)
        return err;
    // 配置mode和port
    w5500_write_byte(W5500_Sn_MR(socket->n), socket->mode);
    w5500_write_bytes_inv(W5500_Sn_PORT(socket->n), (uint8 *)&(socket->local_port), 2);
    // 打开套接字
    if (!w5500_send_sncmd(socket->n, W5500_SnCR_OPEN))
        return Err_W5500_Socket_CmdErr;

    return Err_W5500_No_Error;
}
/*
 * w5500_close_sn - 关闭套接字
 *
 * @socket: 套接字对象
 */
w5500_error_t w5500_close_socket(const struct w5500_socket *socket) {
    if (!w5500_send_sncmd(socket->n, W5500_SnCR_CLOSE))
        return Err_W5500_Socket_CmdErr;
    // 清除中断
    w5500_write_byte(W5500_Sn_IR(socket->n), W5500_SnIR_All);
    return Err_W5500_No_Error;
}
/*
 * w5500_connect_socket - 连接套接字@n,TCP客户端模式
 *
 * @socket: 套接字对象
 */
w5500_error_t w5500_connect_socket(const struct w5500_socket *socket) {
    w5500_write_bytes(W5500_Sn_DIPR(socket->n), socket->remote_ip, 4);
    w5500_write_bytes_inv(W5500_Sn_DPORT(socket->n), (uint8 *)&(socket->remote_port), 2);
    // 建立连接
    if (!w5500_send_sncmd(socket->n, W5500_SnCR_CONNECT))
        return Err_W5500_Socket_CmdErr;
    //
    uint8 tmp = w5500_read_byte(W5500_Sn_IR(socket->n));
    while (W5500_SnSR_ESTABLISHED != w5500_read_byte(W5500_Sn_SR(socket->n))) {
        tmp = w5500_read_byte(W5500_Sn_IR(socket->n));
        if (W5500_SnIR_TIMEOUT & tmp) {
            w5500_write_byte(W5500_Sn_IR(socket->n), W5500_SnIR_TIMEOUT);
            return Err_W5500_Timeout;
        }
        if (W5500_SnIR_DISCON & tmp) {
            w5500_write_byte(W5500_Sn_IR(socket->n), W5500_SnIR_DISCON);
            return Err_W5500_Connect_Failed;
        }
    }
    // 清除连接中断
    w5500_write_byte(W5500_Sn_IR(socket->n), W5500_SnIR_CON);
    return Err_W5500_No_Error;
}
/*
 * w5500_listen_socket - 监听套接字@n, TCP服务器模式
 *
 * @socket: 套接字对象
 */
w5500_error_t w5500_listen_socket(const struct w5500_socket *socket) {
    // 监听连接
    if (!w5500_send_sncmd(socket->n, W5500_SnCR_LISTEN))
        return Err_W5500_Socket_CmdErr;
    return Err_W5500_No_Error;
}
/*
 * w5500_get_sn_received_len - 获取套接字接收到的数据长度
 *
 * @socket: 套接字对象
 */
uint16 w5500_get_socket_received_len(const struct w5500_socket *socket) {
    uint16 len = 0;
    w5500_read_bytes_inv(W5500_Sn_RX_RSR(socket->n), (uint8*)&len, 2);
    return len;
}
/*
 * w5500_receive - 接收数据,成功运行则返回接收到的数据长度,否则返回-1
 *
 * @socket: 套接字对象
 * @buf: 数据缓存
 * @len: 数据长度
 */
int w5500_receive(struct w5500_socket *socket, uint8 *buf, uint16 len) {
    uint16 ptr = 0;
    w5500_read_bytes_inv(W5500_Sn_RX_RD(socket->n), (uint8*)&ptr, 2);

    uint32 addrbsb = ((uint32)ptr << 8) + (socket->n << 5) + 0x18;
    w5500_read_bytes(addrbsb, buf, len);

    ptr += len;
    w5500_write_bytes_inv(W5500_Sn_RX_RD(socket->n), (uint8*)&ptr, 2);

    if (!w5500_send_sncmd(socket->n, W5500_SnCR_RECV))
        return -1;

    return len;
}
/*
 * w5500_receive_from - 接收数据,成功运行则返回接收到的数据长度,否则返回-1
 *
 * @socket: 套接字对象
 * @buf: 数据缓存
 * @len: 数据长度
 */
int w5500_receive_from(struct w5500_socket *socket, uint8 *buf, uint16 len) {
    uint16 ptr = 0;
    w5500_read_bytes_inv(W5500_Sn_RX_RD(socket->n), (uint8*)&ptr, 2);

    uint8 head[8];
    uint32 addrbsb = ((uint32)ptr << 8) + (socket->n << 5) + 0x18;
    w5500_read_bytes(addrbsb, head, 8);
    ptr += 8;

    socket->remote_ip[0] = head[0];
    socket->remote_ip[1] = head[1];
    socket->remote_ip[2] = head[2];
    socket->remote_ip[3] = head[3];
    ((uint8 *)&(socket->remote_port))[1] = head[4];
    ((uint8 *)&(socket->remote_port))[0] = head[5];
    ((uint8 *)&len)[1] = head[6];
    ((uint8 *)&len)[0] = head[7];

    addrbsb = ((uint32)ptr << 8) + (socket->n << 5) + 0x18;
    w5500_read_bytes(addrbsb, buf, len);

    ptr += len;
    w5500_write_bytes_inv(W5500_Sn_RX_RD(socket->n), (uint8*)&ptr, 2);

    if (!w5500_send_sncmd(socket->n, W5500_SnCR_RECV))
        return -1;

    return len;
}
/*
 * w5500_send - 发送数据
 *
 * @socket: 套接字对象
 * @buf: 数据缓存
 * @len: 数据长度
 */
w5500_error_t w5500_send(struct w5500_socket *socket, const uint8 *buf, uint16 len) {
    uint16 freesize = 0;
    w5500_read_bytes_inv(W5500_Sn_TX_FSR(socket->n), (uint8*)&freesize, 2);
    if (freesize < len)
        return Err_W5500_TxBuf_Overflow;

    uint16 ptr = 0;
    w5500_read_bytes_inv(W5500_Sn_TX_WR(socket->n), (uint8*)&ptr, 2);

    uint32 addrbsb = ((uint32)ptr << 8) + (socket->n << 5) + 0x10;
    w5500_write_bytes(addrbsb, buf, len);

    ptr += len;
    w5500_write_bytes_inv(W5500_Sn_TX_WR(socket->n), (uint8*)&ptr, 2);

    if (!w5500_send_sncmd(socket->n, W5500_SnCR_SEND))
        return Err_W5500_Socket_CmdErr;

    while (!(W5500_SnIR_SEND_OK & w5500_read_byte(W5500_Sn_IR(socket->n)))) {
        if (W5500_SnIR_TIMEOUT & w5500_read_byte(W5500_Sn_IR(socket->n))) {
            w5500_write_byte(W5500_Sn_IR(socket->n), W5500_SnIR_TIMEOUT | W5500_SnIR_SEND_OK);
            w5500_close_socket(socket);
            return Err_W5500_Timeout;
        }
    }

    w5500_write_byte(W5500_Sn_IR(socket->n), W5500_SnIR_SEND_OK);
    return Err_W5500_No_Error;
}
/*
 * w5500_send - 发送数据
 *
 * @socket: 套接字对象
 * @buf: 数据缓存
 * @len: 数据长度
 */
w5500_error_t w5500_send_to(struct w5500_socket *socket, const uint8 *buf, uint16 len) {
    w5500_write_bytes(W5500_Sn_DIPR(socket->n), socket->remote_ip, 4);
    w5500_write_bytes_inv(W5500_Sn_DPORT(socket->n), (uint8 *)&socket->remote_port, 2);

    return w5500_send(socket, buf, len);
}


