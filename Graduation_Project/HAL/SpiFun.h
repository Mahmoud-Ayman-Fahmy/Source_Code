#ifndef SPIFUN_H
#define SPIFUN_H

#define SPI_CAN                 &hspi2
#define SPI_TIMEOUT             10



void SPI_voidStartSPI ();
void  SPI_voidEndSPI();
u8 SPI_voidSendRecieve (u8 copy_u8TxByte);

#endif