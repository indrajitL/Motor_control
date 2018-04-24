/*
 * timer.c
 *
 *  Created on: 06-Apr-2018
 *      Author: root
 */

#include <include/timer.h>


void delayms(uint32_t ms)
{
    int i;
    SYSCTL_RCGCTIMER_R |= 1;     /* enable clock to Timer Block 0 */

    TIMER0_CTL_R = 0;            /* disable Timer before initialization */
    TIMER0_CFG_R = 0x04;         /* 16-bit option */
    TIMER0_TAMR_R = 0x02;        /* periodic mode and down-counter */
    TIMER0_TAILR_R = 16000 - 1;  /* Timer A interval load value register */
    TIMER0_ICR_R = 0x1;          /* clear the TimerA timeout flag*/
    TIMER0_CTL_R |= 0x01;        /* enable Timer A after initialization */

    for(i = 0; i < ms; i++) {
        while ((TIMER0_RIS_R  & 0x1) == 0) ;      /* wait for TimerA timeout flag */
        TIMER0_ICR_R = 0x1;      /* clear the TimerA timeout flag */
    }
}

void delayus(uint32_t us)
{
    int i;
    SYSCTL_RCGCTIMER_R |= 1;     /* enable clock to Timer Block 0 */

    TIMER0_CTL_R = 0;            /* disable Timer before initialization */
    TIMER0_CFG_R = 0x04;         /* 16-bit option */
    TIMER0_TAMR_R = 0x02;        /* periodic mode and down-counter */
    TIMER0_TAILR_R = 16 - 1;  /* Timer A interval load value register */
    TIMER0_ICR_R = 0x1;          /* clear the TimerA timeout flag*/
    TIMER0_CTL_R |= 0x01;        /* enable Timer A after initialization */

    for(i = 0; i < us; i++) {
        while ((TIMER0_RIS_R  & 0x1) == 0) ;      /* wait for TimerA timeout flag */
        TIMER0_ICR_R = 0x1;      /* clear the TimerA timeout flag */
    }
}
