/*
 * esp.h
 *
 *  Created on: Oct 19, 2017
 *      Author: Ahmed
 */

#ifndef ESP_H_
#define ESP_H_

#include "std_types.h"
#include "uart.h"
#include <string.h>

#define CR  0x0D  //CR carriage return
#define LF  0x0A  //LF line feed(new line)

void find_get_string(uint8 *string, uint8 *from, uint8 _from, uint8 *to,
		uint8 _to, uint8 *get_text);
uint8 find_string(uint8 *string, uint8 *string_find);
void new_line();
void UART_Write_AT(uint8 *str);

#endif /* ESP_H_ */
