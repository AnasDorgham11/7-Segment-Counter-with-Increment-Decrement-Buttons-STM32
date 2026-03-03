#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "MCAL/RCC/RCC_prv.h"
#include "MCAL/RCC/RCC_int.h"
#include "MCAL/GPIO/GPIO_prv.h"
#include "MCAL/GPIO/GPIO_int.h"
#include "MCAL/NVIC/NVIC_int.h"
#include "MCAL/EXTI/EXTI_int.h"
#include "HAL/7_SEGMENT/7_SEGMENT_int.h"
#include "MCAL/SYSTICK/SYSTICK_int.h"

u8 count = 0;

void Button_vIncrement(void){
	MEXTI_vDisableINT(7);
	count++;
	if (count == 10){
		count = 0;
	}
	H7SEGMENT_vPrintNumber(count);
	MSYSTICK_vSetDelay_ms(20);
	while(MGPIO_u8GetPinValue(GPIO_PORTB, GPIO_PIN7) == 0);
	MSYSTICK_vSetDelay_ms(20);
	MEXTI_vEnableINT(7, EXTI_PORTB, EXTI_FALLING_EDGE);
}

void Button_vDecrement(void){
	MEXTI_vDisableINT(8);
	count--;
	if (count == 255){
		count = 9;
	}
	H7SEGMENT_vPrintNumber(count);
	MSYSTICK_vSetDelay_ms(20);
	while(MGPIO_u8GetPinValue(GPIO_PORTB, GPIO_PIN8) == 0);
	MSYSTICK_vSetDelay_ms(20);
	MEXTI_vEnableINT(8, EXTI_PORTB, EXTI_FALLING_EDGE);
}

int main(void)
{
	MRCC_vInit();
	MRCC_vEnableClk(RCC_AHB1, GPIOBEN);
	MRCC_vEnableClk(RCC_APB2, SYSCFGEN);
	MNVIC_vEnable_Peripheral_INT(23);

	GPIOx_PinConfig_t Button_Increase =
	{
			.Port = GPIO_PORTB,
			.Pin = GPIO_PIN7,
			.Mode = GPIO_MODE_INPUT,
			.Speed = GPIO_SPEED_HIGH,
			.PullType = GPIO_PULL_UP
	};

	GPIOx_PinConfig_t Button_Decrease =
	{
			.Port = GPIO_PORTB,
			.Pin = GPIO_PIN8,
			.Mode = GPIO_MODE_INPUT,
			.Speed = GPIO_SPEED_HIGH,
			.PullType = GPIO_PULL_UP
	};

	MGPIO_vPinInit(&Button_Increase);
	MGPIO_vPinInit(&Button_Decrease);

	MEXTI_vEnableINT(7, EXTI_PORTB, EXTI_FALLING_EDGE);
	MEXTI_vEnableINT(8, EXTI_PORTB, EXTI_FALLING_EDGE);

	MEXTI_vSetCallBack(Button_vIncrement, 7);
	MEXTI_vSetCallBack(Button_vDecrement, 8);
	H7SEGMENT_vInit();
	H7SEGMENT_vPrintNumber(0);


	while(1);

	return 0;
}


