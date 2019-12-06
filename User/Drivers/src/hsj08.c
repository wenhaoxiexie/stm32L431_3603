#include "hsj08.h"
#include "delay.h"
#include "global.h"

uint8_t reValue;
void LOCK(void)
{
	 //__disable_irq();
	 HAL_GPIO_WritePin(pwm1_GPIO_Port, pwm1_Pin, GPIO_PIN_SET);
	 HAL_GPIO_WritePin(pwm2_GPIO_Port, pwm2_Pin, GPIO_PIN_RESET);
	 sys_delay_us(150000);
	
	 HAL_GPIO_WritePin(pwm1_GPIO_Port, pwm1_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(pwm2_GPIO_Port, pwm2_Pin, GPIO_PIN_RESET);
	 //__enable_irq();
}

void UNLOCK(void)
{
	 //__disable_irq();
	 HAL_GPIO_WritePin(pwm1_GPIO_Port, pwm1_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(pwm2_GPIO_Port, pwm2_Pin, GPIO_PIN_SET);
	 sys_delay_us(150000);
	 HAL_GPIO_WritePin(pwm1_GPIO_Port, pwm1_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(pwm2_GPIO_Port, pwm2_Pin, GPIO_PIN_RESET);
	//__enable_irq();
}

void hsj08_exit(void)
{
	 HAL_GPIO_WritePin(pwm1_GPIO_Port, pwm1_Pin, GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(pwm2_GPIO_Port, pwm2_Pin, GPIO_PIN_RESET);
}
