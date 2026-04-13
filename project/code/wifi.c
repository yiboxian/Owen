#include "bsp_system.h"

#define WIFI_SSID_TEST          "PLA"
#define WIFI_PASSWORD_TEST      "woaiwuxie1" // 如果需要连接的WIFI 没有密码则需要将 这里 替换为 NULL



void Wifi_Init(void)
{   
        while(wifi_spi_init(WIFI_SSID_TEST, WIFI_PASSWORD_TEST))
    {
        printf("\r\n connect wifi failed. \r\n");
        system_delay_ms(100);                                                   // 初始化失败 等待 100ms
    }

    printf("\r\n module version:%s \r\n",wifi_spi_version);                     // 模块固件版本
    printf("\r\n module mac    :%s \r\n",wifi_spi_mac_addr);                    // 模块 MAC 信息
    printf("\r\n module ip     :%s \r\n",wifi_spi_ip_addr_port);                // 模块 IP 地址

    // zf_device_wifi_spi.h 文件内的宏定义可以更改模块连接(建立) WIFI 之后，是否自动连接 TCP 服务器、创建 UDP 连接、创建 TCP 服务器等操作
    if(0 == WIFI_SPI_AUTO_CONNECT)                                              // 如果没有开启自动连接 就需要手动连接目标 IP
    {
        while(wifi_spi_socket_connect(                                          // 向指定目标 IP 的端口建立 TCP 连接
            "TCP",                                                              // 指定使用TCP方式通讯
            WIFI_SPI_TARGET_IP,                                                 // 指定远端的IP地址，填写上位机的IP地址
            WIFI_SPI_TARGET_PORT,                                               // 指定远端的端口号，填写上位机的端口号，通常上位机默认是8080
            WIFI_SPI_LOCAL_PORT))                                               // 指定本机的端口号
        {
            // 如果一直建立失败 考虑一下是不是没有接硬件复位
            printf("\r\n Connect TCP Servers error, try again. \r\n");
            system_delay_ms(100);                                               // 建立连接失败 等待 100ms
        }
    }

    // 使用高速 WIFI SPI模块时无法使用屏幕（因为引脚有共用）
    // 使用高速 WIFI SPI模块时无法使用屏幕（因为引脚有共用）
    // 使用高速 WIFI SPI模块时无法使用屏幕（因为引脚有共用）

    // 发送测试数据至服务器

}
    // 此处编写wifi模块初始化代码
