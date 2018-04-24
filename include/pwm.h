/*
 * pwm.h
 *
 *  Created on: 06-Apr-2018
 *      Author: root
 */

#ifndef INCLUDE_PWM_H_
#define INCLUDE_PWM_H_

#include <stdlib.h>
#include <stdint.h>
#include "include/tm4c123gh6pm.h"

void pwm_init(uint16_t freq);
void set_pwm0_duty(float duty);
void set_pwm1_duty(float duty);
void set_pwm2_duty(float duty);
void set_pwm3_duty(float duty);


#endif /* INCLUDE_PWM_H_ */
