#include "Types.h"

#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_spi.h"
#include "SpiFun.h"



void SPI_voidStartSPI (){
    HAL_GPIO_WritePin(CsPort, CsPIN, GPIO_PIN_RESET);
}

void  SPI_voidEndSPI(){
    HAL_GPIO_WritePin(CSPORT, CsPIN  , GPIO_PIN_SET);
}

u8 SPI_voidSendRecieve (u8 copy_u8TxByte){
    u8 RxByte ;
    HAL_SPI_TransmitReceive(SPI_CAN, &copy_u8TxByte, &RxByte, 1, SPI_TIMEOUT);
	return RxByte;
}
