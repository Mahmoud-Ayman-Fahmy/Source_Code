#include "Types.h"

#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_spi.h"
#include "SpiFun.h"


void MCP_voidSetReg (u8 copy_u8Register , u8 copy_u8Value){
    SPI_voidStartSPI();
    SPI_voidSendRecieve(INSTRUCTION_WRITE);
    SPI_voidSendRecieve(copy_u8Register);
    SPI_voidSendRecieve(copy_u8Value);
    SPI_voidEndSPI();
    
}


void MCP_voidSetRegs (u8 copy_u8Register , u8 copy_u8Value[] , u8 copy_u8Length){
    u8 counter ;
    SPI_voidStartSPI();
    SPI_voidSendRecieve(INSTRUCTION_WRITE);
    SPI_voidSendRecieve(copy_u8Register);
    for(counter = 0 ; counter<copy_u8Length ; counter ++){
    SPI_voidSendRecieve(copy_u8Value[i]);
    }
    SPI_voidEndSPI();
    
}

void MCP_voidLoadTx (u8 copy_u8Register , u8 copy_u8Value[] , u8 copy_u8Length){
    u8 counter ;
    SPI_voidStartSPI();
    SPI_voidSendRecieve(copy_u8Register);
    for(counter = 0 ; counter<copy_u8Length ; counter ++){
    SPI_voidSendRecieve(copy_u8Value[i]);
    }
    SPI_voidEndSPI();
    
}

void MCP_voidModifyReg (u8 copy_u8Register , u8 copy_u8Mask , u8 copy_u8Data){
    
    SPI_voidStartSPI();
    SPI_voidSendRecieve(INSTRUCTION_BITMOD);
    SPI_voidSendRecieve(copy_u8Register);
    SPI_voidSendRecieve(copy_u8Mask);
    SPI_voidSendRecieve(copy_u8Data);
    SPI_voidEndSPI();
    
}

u8 MCP_u8ReadReg (u8 copy_u8Register ){
    u8 Val ;
    SPI_voidStartSPI();
    SPI_voidSendRecieve(INSTRUCTION_READ);
    SPI_voidSendRecieve(copy_u8Register);
    
    Val = SPI_voidSendRecieve(0x00);
    SPI_voidEndSPI();
    return Val ;
}

void MCP_voidReadRegs (u8 copy_u8Register , u8 copy_u8Value[] , u8 copy_u8Length){
    u8 counter ;
    SPI_voidStartSPI();
    SPI_voidSendRecieve(INSTRUCTION_READ);
    SPI_voidSendRecieve(copy_u8Register);
    for(counter = 0 ; counter<copy_u8Length ; counter ++){
    copy_u8Value[i]=SPI_voidSendRecieve(0x00);
    }
    SPI_voidEndSPI();
    
}
void MCP_voidReadRX (u8 copy_u8Register , u8 copy_u8Value[] , u8 copy_u8Length){
    u8 counter ;
    SPI_voidStartSPI();
    SPI_voidSendRecieve(copy_u8Register);
    for(counter = 0 ; counter<copy_u8Length ; counter ++){
    copy_u8Value[i]=SPI_voidSendRecieve(0x00);
    }
    SPI_voidEndSPI();
    
}


void MCP_voidPrepareId (u8 *copy_ptrbuffer , u8 copy_u8ext , u32 copy_u32id){

    u16 canid = (u16)(copy_u32id&0x0fff);

    if(ext){
        copy_ptrbuffer[MCP_EID0] = (u8)(canid & 0xFF);
        copy_ptrbuffer[MCP_EID8] = (u8)(canid >>8);
        canid = (u16)(copy_u32id >>16);
        copy_ptrbuffer[MCP_SIDL] = (u8) (canid & 0x03);
        copy_ptrbuffer[MCP_SIDL] += (u8) ((canid & 0x1C) << 3);
        copy_ptrbuffer[MCP_SIDL] |= TXB_EXIDE_MASK;
        copy_ptrbuffer[MCP_SIDH] = (u8) (canid >> 5);

    } else {
        copy_ptrbuffer[MCP_SIDH] = (u8) (canid >> 3);
        copy_ptrbuffer[MCP_SIDL] = (u8) ((canid & 0x07 ) << 5);
        copy_ptrbuffer[MCP_EID0] = 0;
        copy_ptrbuffer[MCP_EID8] = 0;
    }
}

u8 MCP_voidGetStatus (void){
    SPI_voidStartSPI();
    SPI_voidSendRecieve(INSTRUCTION_READ_STATUS);
    u8 state = SPI_voidSendRecieve(0x00);
    SPI_voidEndSPI();
    return state ;
}

void MCP_voidRequestToSend(u8 instruction){
    SPI_voidStartSPI();
    SPI_voidSendRecieve(instruction);
    SPI_voidEndSPI();
}

void MCP_voidSetBitTiming(u8 copy_u8cnf1Val, u8 copy_u8cnf2Val , u8 copy_u8cnf3Val){
    MCP_voidSetReg(CNF1 , copy_u8cnf1Val);
    MCP_voidSetReg(CNF2 , copy_u8cnf2Val);
    MCP_voidSetReg(CNF3 , copy_u8cnf3Val);

}

void MCP_voidInit(void){
    MCP_voidSetReg(MCP_CANCTRL , 0x84);
    while(((MCP_u8ReadReg(MCP_CANSTAT)>>5) != MCP_MODECONFG);
    MCP_voidSetBitTiming((2<<6) , (1<<7)|(6<<3)|(1) , (5));
    //INCOMPLETE
}

void MCP_voidSendMSG(u8 copy_u8bufferID , u32 copy_u32MsgId , u8 * copy_u8Data , u8 properties){
    
}