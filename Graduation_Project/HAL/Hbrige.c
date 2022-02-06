#include "main.h"
#include "Hbridge.h"
 
void Hbrige_voidRotForward (const HBRIGE_pinConfig * copy_ptrHbrigecongfig){
    HAL_GPIO_WritePin(copy_ptrHbrigecongfig->Port1 ,copy_ptrHbrigecongfig->Pin1 , GPIO_PIN_SET);
    HAL_GPIO_WritePin(copy_ptrHbrigecongfig->Port2 ,copy_ptrHbrigecongfig->Pin2 , GPIO_PIN_RESET);

}

void Hbrige_voidRotReverse (const HBRIGE_pinConfig * copy_ptrHbrigecongfig){
    HAL_GPIO_WritePin(copy_ptrHbrigecongfig->Port1 ,copy_ptrHbrigecongfig->Pin1 , GPIO_PIN_RESET);
    HAL_GPIO_WritePin(copy_ptrHbrigecongfig->Port2 ,copy_ptrHbrigecongfig->Pin2 , GPIO_PIN_SET);

}
void Hbrige_voidStop (const HBRIGE_pinConfig * copy_ptrHbrigecongfig){
    HAL_GPIO_WritePin(copy_ptrHbrigecongfig->Port1 ,copy_ptrHbrigecongfig->Pin1 , GPIO_PIN_RESET);
    HAL_GPIO_WritePin(copy_ptrHbrigecongfig->Port2 ,copy_ptrHbrigecongfig->Pin2 , GPIO_PIN_RESET);

}

void Hbrige_voidRotForwardcontrled (const HBRIGE_pinConfig * copy_ptrHbrigecongfig ,u8 copy_u8DutyCycle){
    u8 dutyCycle = (65536 * copy_u8DutyCycle)/100 ;
    HAL_GPIO_WritePin(copy_ptrHbrigecongfig->Port1 ,copy_ptrHbrigecongfig->Pin1 , GPIO_PIN_SET);
    HAL_GPIO_WritePin(copy_ptrHbrigecongfig->Port2 ,copy_ptrHbrigecongfig->Pin2 , GPIO_PIN_RESET);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, dutyCycle);
}