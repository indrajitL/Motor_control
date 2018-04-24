/*
 * UART.h
 *
 *  Created on: 24-Apr-2018
 *      Author: root
 */

#ifndef INCLUDE_UART_H_
#define INCLUDE_UART_H_

#include "stdlib.h"
#include "stdio.h"
#include <stdint.h>

typedef struct UART_data{
    char direction;
    char speed;
}CONTROL_DATA;

extern CONTROL_DATA robot1;

void  UART_Init(void);
char UART_InChar(void);
void  UART_OutChar(char data);


#endif /* INCLUDE_UART_H_ */
