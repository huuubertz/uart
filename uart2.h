#ifndef UART2_H
#define UART2_H

#include "MKL46Z4.h"

#define baud_rate 9600
#define BusClock 24000000

void uart2_init(void);
void transmitter_UART2_data(uint8_t data);
uint8_t reciver_UART2_data(void);

#endif