#ifndef LINKPORT_H
#define LINKPORT_H

#include "stm32f10x_conf.h"

#define MACHINE_ID 0x03
#define MACHINE_ID2 0x83

#define LINK_TIMEOUT 7200000
#define LINK_BIT_DELAY 50
#define LINK_BYTE_DELAY 500

#define LINK_INIT_GPIO_CLOCK RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
#define LINK_GPIO_Speed GPIO_Speed_50MHz

//	RED = Tip
#define	LINK_RED_port		GPIOA
#define	LINK_RED_bit		GPIO_Pin_8

//	WHITE = Middle
#define	LINK_WHITE_port	        GPIOA
#define	LINK_WHITE_bit		GPIO_Pin_9

#define Breset BRR
#define Bset BSRR

#define LINK_RED_high LINK_RED_port->Bset = LINK_RED_bit;
#define LINK_RED_low LINK_RED_port->Breset = LINK_RED_bit;
#define LINK_WHITE_high LINK_WHITE_port->Bset = LINK_WHITE_bit;
#define LINK_WHITE_low LINK_WHITE_port->Breset = LINK_WHITE_bit;

#define	LINK_RED_wait_until_high		while(!GPIO_ReadInputDataBit(LINK_RED_port, LINK_RED_bit));                                                
#define	LINK_RED_wait_until_low		while(GPIO_ReadInputDataBit(LINK_RED_port, LINK_RED_bit));

#define	LINK_WHITE_wait_until_high		  while(!GPIO_ReadInputDataBit(LINK_WHITE_port, LINK_WHITE_bit));
#define	LINK_WHITE_wait_until_low   while(GPIO_ReadInputDataBit(LINK_WHITE_port, LINK_WHITE_bit));




extern uint8_t screenshot[768];
extern uint8_t framebuffer[96][64];
extern uint64_t keys;
extern int return_to_tios;
extern uint8_t password[9];


void LINK_init();
int16_t LINK_get_byte();
void LINK_transfer_framedata();
void LINK_send_command(uint8_t command_ID, uint16_t length, uint8_t data[]);
void LINK_send_byte (uint8_t byte);
void LINK_send_array(uint8_t array[], int length);
void LINK_send_key(uint16_t key);
void LINK_send_key_sequence(uint16_t key_sequence[], uint16_t length);
void LINK_send_array_with_checksum(uint8_t data[], uint16_t length);
void LINK_get_screenshot(void);
void LINK_send_os(void);
int LINK_check_password(void);

#endif