

#include "Alarm.h"



void vidHitAlarm(void)
{
    HAL_GPIO_WritePin(GPIOB, ALARM_Pin, GPIO_PIN_SET);
}

void vidClearAlarm(void)
{
    HAL_GPIO_WritePin(GPIOB, ALARM_Pin, GPIO_PIN_RESET);
}





