#include "main.h"
#include "Ultrasonic.h"

#define usTIM TIM4

void usDelay(uint32_t uSec);

uint8_t icFlag = 0;
uint8_t captureIdx=0;
uint32_t edge1Time=0, edge2Time=0;

const float speedOfSound = 0.0343/2;
float distance;



u8 USONIC_u8CalcDistance(copy_u8TrigPort , copy_u8TrigPin ){
	//Set Trigger Pin to Low
	HAL_GPIO_WritePin(copy_u8TrigPort , copy_u8TrigPin , GPIO_PIN_RESET);
	usDelay(3);

	//UltraSonic measuring routine
	HAL_GPIO_WritePin(copy_u8TrigPort , copy_u8TrigPin , GPIO_PIN_SET);
	usDelay(10);
	HAL_GPIO_WritePin(copy_u8TrigPort , copy_u8TrigPin , GPIO_PIN_RESET);

	//START ICU Timer

	HAL_TIM_IC_Start_IT(&htim3 , TIM_CHANNEL_1);
	uint32_t startTick = HAL_GetTick();

	do
	{
		if (icFlag) break;
	}while((HAL_GetTick()- startTick)<500);

	icFlag = 0;
	HAL_TIM_Stop_IT(&htim3 , TIM_CHANNEL_1);

	if(edge2Time > edge2Time){
		distance = ((edge2Time - edge1Time)+ 0.0f)*SoundSpeed ;
	}
	else{
		distance = 0.0f;

	}
	return distance ;
}

void usDelay(uint32_t uSec)
{
	if(uSec < 2) uSec = 2;
	usTIM->ARR = uSec - 1; 	/*sets the value in the auto-reload register*/
	usTIM->EGR = 1; 			/*Re-initialises the timer*/
	usTIM->SR &= ~1; 		//Resets the flag
	usTIM->CR1 |= 1; 		//Enables the counter
	while((usTIM->SR&0x0001) != 1);
	usTIM->SR &= ~(0x0001);
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{

	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);

		if(captureIdx == 0) //Fisrt edge
		{
			edge1Time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); //__HAL_TIM_GetCounter(&htim3);//

			captureIdx = 1;
		}
		else if(captureIdx == 1) //Second edge
		{
			edge2Time = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			captureIdx = 0;
			icFlag = 1;
		}
}



