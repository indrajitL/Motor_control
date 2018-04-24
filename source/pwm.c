/*
 * pwm.c
 *
 *  Created on: 06-Apr-2018
 *      Author: root
 */

#include <include/pwm.h>

void pwm_init(uint16_t freq)
{
    SYSCTL_RCGC0_R |= 1U << 20U; /* Turn on pwm module clock */

    SYSCTL_RCGC2_R |= 1U << 1U; /* gpio port B clock */
    SYSCTL_RCGC2_R |= 1U << 2U; /* gpio port C clock */

   // GPIO_PORTB_DR8R_R |= 3U << 6U; // 8mA drive pin
   // GPIO_PORTC_DR8R_R |= 3U << 4U; // 8mA drive pin

    GPIO_PORTB_AFSEL_R |= 3U << 6U ;//| 3U << 4U; /* select alternative  function for pins  PB6, PB7*/
    GPIO_PORTC_AFSEL_R |= 3U << 4U;

    GPIO_PORTB_PCTL_R |= 4U << 24U | 4U << 28U ;//| 4U << 16U | 4U << 20U;  /* select port control function as a pwm */
    GPIO_PORTC_PCTL_R |= 4U << 16U | 4U << 20U ;

    GPIO_PORTB_DEN_R |= 3U << 6U;// | 3U << 4U; /* enable digital pins */
    GPIO_PORTC_DEN_R |= 0x30;
    SYSCTL_RCC_R |= 0U << 17U; // clock source

    PWM0_INVERT_R |= 1U << 1U | 1U << 0U | 1U << 6U | 1U << 7U; // active low output on pins ....

    // pwm0 module 0
    PWM0_0_CTL_R |= 00U;  // configure pwm0 module to generate pwm0,1 .. mode count down mode
    PWM0_0_GENA_R |= 2U << 6U | 3U << 0U;
    PWM0_0_GENB_R |= 2U << 10U | 3U << 0U;

    PWM0_3_CTL_R |= 00U;  // configure pwm0 module to generate pwm0,1 .. mode count down mode
    PWM0_3_GENA_R |= 2U << 6U | 3U << 0U;
    PWM0_3_GENB_R |= 2U << 10U | 3U << 0U;

    PWM0_0_LOAD_R |= 0x0000063FU; // 10KHz --> pwm
    PWM0_3_LOAD_R |= 0x0000063FU;
    PWM0_0_CMPA_R = 800;
    PWM0_0_CMPB_R = 000;
    PWM0_3_CMPA_R = 800;
    PWM0_3_CMPB_R = 000;

    PWM0_0_CTL_R |= 1U << 0U;  /* start pwm*/
    PWM0_3_CTL_R |= 1U << 0U;

    PWM0_ENABLE_R |= 3U << 0U;// | 3U << 2U;
    PWM0_ENABLE_R |= 3U << 6U;

}

void set_pwm0_duty(float duty)
{
    PWM0_0_CMPA_R = 1600*duty;
}
void set_pwm1_duty(float duty)
{
    PWM0_0_CMPB_R = 1600*duty;
}
void set_pwm2_duty(float duty)
{
    PWM0_3_CMPA_R = 1600*duty;
}
void set_pwm3_duty(float duty)
{
    PWM0_3_CMPB_R = 1600*duty;
}
