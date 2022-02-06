
#include "Switch.h"
#include "main.h"

u8 Switch_u8Read(copy_u8SwitchPort , copy_u8SwitchPin){
    u8 Val ;
    HAL_GPIO_ReadPin(copy_u8SwitchPort, copy_u8SwitchPin);

    return Val ;
}

