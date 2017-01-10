//
// This file is part of the GNU ARM Eclipse Plug-ins project.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef PACKET_H_
#define PACKET_H_

#include <stddef.h>
#include <stdio.h>

// ----------------------------------------------------------------------------
//char *dataString[2] = {"Weight","Temp"};
typedef struct {
   char *name;
   uint32_t preamble;
   uint8_t ID;
   uint8_t type;
   uint16_t data;
   uint8_t ECC;
   uint32_t formattedPacketLW;//<preamble, ID, Data Type, Data, ECC>
   uint32_t formattedPacketHW;//<preamble, ID, Data Type, Data, ECC>
} Packet;


void printPacket(Packet *packet);
void generatePreamble(Packet *packet);
void writeID(Packet *packet, uint8_t);
void setDataType(Packet *packet, uint8_t type, char *name);
void writeData(Packet *packet, uint16_t data);
void generateECC(Packet *packet);
void formatPacket(Packet *packet);
void sendPacket(Packet *packet);
void createPacket(Packet *packet, uint8_t ID, uint8_t type, uint16_t data, char *name);
// ----------------------------------------------------------------------------

#endif // PACKET_H_
