#ifndef __WIFI_H_
#define __WIFI_H_

extern uint8 wifi_spi_test_buffer[] = "this is wifi spi test buffer";
extern uint8 wifi_spi_recv_buffer[] = "recv buffer : ";
extern uint8 wifi_spi_get_data_buffer[256];
extern uint16 data_length;

void Wifi_Init(void);

#endif