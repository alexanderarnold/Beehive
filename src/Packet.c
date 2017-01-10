/**
******************************************************************************
*   @file
*   @brief    Source file for communication part.
*   @version  V0.1
*   @author   ADI
*   @date     August 2015
*
*******************************************************************************

*
*******************************************************************************
**/


/***************************** Include Files **********************************/
#include "Packet.h"
#include "Communication.h"


/************************** Variable Definitions ******************************/

void printPacket(Packet *packet){
   char str[16];
   //Print Premable
   UART_WriteString("\r\nPreamble:\t0x");
   itoa(packet->preamble,&str,16);
   UART_WriteString(str);
   UART_WriteString("\r\n");

   //Print Beehive ID
   UART_WriteString("Beehive ID:\t0x");
   itoa(packet->ID,&str,16);
   UART_WriteString(str);
   UART_WriteString("\r\n");

   //Print Data
   UART_WriteString(packet->name);
   UART_WriteString(":\t\t0x");
   itoa(packet->data,&str,16);
   UART_WriteString(str);
   UART_WriteString("\r\n");

   //Print ECC
   UART_WriteString("ECC:\t\t0x");
   itoa(packet->ECC,&str,16);
   UART_WriteString(str);
   UART_WriteString("\r\n");

   //Print Packet
   UART_WriteString("Packet:\t\t0x");
   itoa(packet->formattedPacketHW,&str,16);
   UART_WriteString(str);
   itoa(packet->formattedPacketLW,&str,16);
   UART_WriteString(str);
   UART_WriteString("\r\n");


}


void generatePreamble(Packet *packet){
   packet->preamble = 0x0B77;
}

void writeID(Packet *packet, uint8_t ID){
   packet->ID = ID;
}

void setDataType(Packet *packet, uint8_t type, char *name){
   packet->type = type;
   packet->name = name;
}

void writeData(Packet *packet, uint16_t data){
   packet->data = data;
}

void generateECC(Packet *packet){
   packet->ECC = 0x3F;
}

void formatPacket(Packet *packet){
   uint32_t temp = 0;
   char str[16];
   temp = ((packet->ID && 0x3) << 30) |(packet->type << 22) | (packet->data << 6) | (packet->ECC);
   packet->formattedPacketLW = temp;
   temp = 0;
   temp |= (packet->preamble << 6) | (packet->ID >> 2);
   packet->formattedPacketHW = temp;
}

//void sendPacket(Packet *packet);

void createPacket(Packet *packet, uint8_t ID, uint8_t type, uint16_t data, char *name){
   generatePreamble(packet);
   writeID(packet, ID);
   setDataType(packet, type, name);
   writeData(packet, data);
   generateECC(packet);
   formatPacket(packet);
}

void sendPacket(Packet *packet){
   char temp[4] = {0};
   temp[0] = (char) (packet->formattedPacketLW & 0xFF);
   //UART_WriteString(packet->formattedPacketHW);
   UART_WriteString(&temp);
}
/************************* Functions Definitions ******************************/


