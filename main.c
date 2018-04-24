#include <include/pwm.h>
#include <include/timer.h>
#include <include/UART.h>

/**
 * main.c
 */

uint32_t count;
CONTROL_DATA robot1;
volatile float speed=9;
char Dir='A';


int main(void)
{

    UART_Init();
    pwm_init(2000);


    while(1)
    {
        speed = (robot1.speed - '0')/9.0;
        Dir = robot1.direction;

        switch (Dir) {
            case 'A':
                set_pwm0_duty(speed);
                set_pwm1_duty(0.0);
                set_pwm2_duty(speed);
                set_pwm3_duty(0.0);
                break;
            case 'B':
                set_pwm0_duty(0.0);
                set_pwm1_duty(0.0);
                set_pwm2_duty(speed);
                set_pwm3_duty(0.0);
                break;
            case 'C':
                set_pwm0_duty(0.0);
                set_pwm1_duty(speed);
                set_pwm2_duty(0.0);
                set_pwm3_duty(speed);
                break;
            case 'D':
                set_pwm0_duty(speed);
                set_pwm1_duty(0.0);
                set_pwm2_duty(0.0);
                set_pwm3_duty(0.0);
                break;
            case 'E':
                set_pwm0_duty(0.0);
                set_pwm1_duty(0.0);
                set_pwm2_duty(0.0);
                set_pwm3_duty(0.0);
                break;
            default:
                break;
        }
    }

}

