/*
 * UART.c
 *
 *  Created on: 24-Apr-2018
 *      Author: root
 */
#include <include/UART.h>
#include "include/tm4c123gh6pm.h"

void  UART_Init(void)
{                                        //  should  be  called  only    once
        SYSCTL_RCGCUART_R   |=  1U << 1U; //  activate    UART1
        SYSCTL_RCGCGPIO_R   |=  1U << 1U; //  activate    port    B
        UART1_CTL_R &=  ~0x0001;                    //  disable UART
        UART1_IBRD_R    =  8; // 43; //  IBRD=int(80000000/(16*115,200)) =   int(43.40278) // 8.68055
        UART1_FBRD_R    =   43; //  FBRD    =   round(0.40278   *   64) =   26
        UART1_LCRH_R    =   0x0070;                 //  8-bit   word    length, enable  FIFO

        UART1_IFLS_R &= 0U << 3U;
        UART1_IM_R |= 1U << 4U;
        NVIC_EN0_R  =   1U << 6U;

        UART1_CTL_R =   0x0301;                     //  enable  RXE,    TXE and UART
        GPIO_PORTB_PCTL_R   =   (GPIO_PORTB_PCTL_R&0xFFFFFF00)+0x00000011;//  UART
        GPIO_PORTB_AFSEL_R  |=  0x03;  //  TM4C,   disable analog  on  PA1-0       GPIO_PORTA_AFSEL_R  |=  0x03;       //  enable  alt funct   on  PA1-0
        GPIO_PORTB_DEN_R    |=  0x03;               //  enable  digital I/O on  PA1-0
}

//  Wait    for new input,  then    return  ASCII   code
char UART_InChar(void)
{
        while((UART1_FR_R&0x0010)   !=  0); //  wait    until   RXFE    is  0
        return((char)(UART1_DR_R&0xFF));
}
//  Wait    for buffer  to  be  not full,   then    output
void  UART_OutChar(char data)
{
        while((UART1_FR_R&0x0020)   !=  0);     //  wait    until   TXFF    is  0
        UART1_DR_R  =   data;
}

void UART_Handler(void)
{
    //Ack interrupt
    UART1_ICR_R |= 1U << 4U;
    robot1.direction = UART1_DR_R&0xFF;
    robot1.speed = UART1_DR_R&0xFF;

}

