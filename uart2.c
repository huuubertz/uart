#include "uart2.h"

void uart2_init(){
	
	// sygnal taktujacy do UART2 i PORTE
	SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	// ustawienie odpowiedniej f-cji do koncowek portu
	// TX
	PORTE->PCR[16] |= PORT_PCR_MUX(3);
	// RX
	PORTE->PCR[17] |= PORT_PCR_MUX(3);
	
	// zablokowac transmiter [TE] i reciver [RE]
	UART2->C2 &= ~(UART_C2_TE_MASK, UART_C2_RE_MASK);
	
	// set baudrate to 9600
	uint32_t SBR;
	SBR = BusClock/(16* baud_rate);
	UART2->BDH |= (SBR<<5);
	UART2->BDL |= SBR;

	// 1-bit stop
	UART2->BDH &= ~UART0_BDH_SBNS_MASK;
	
	// 8-bit ramka, brak sprzetowego sprawdzania parzystosci
	UART2->C1 &= ~(UART_C1_M_MASK, UART_C1_PE_MASK);
	
	// interupt transmitter or/and reciver ENABLE HERE
	
	// ENABLE transmitter and reciver
	UART2->C2 |= (UART_C2_TE_MASK, UART_C2_RE_MASK);
}

// we could recive data by UART2->D and also we are able to transmitt this date by UART2->D

void transmitter_UART2_data(uint8_t data){
	while(!(UART2->S1 & UART_S1_TDRE_MASK));
	UART2->D = data;
}

uint8_t reciver_UART2_data(void){
	while(!(UART2->S1 & UART_S1_RDRF_MASK));
	return UART2->D;
}