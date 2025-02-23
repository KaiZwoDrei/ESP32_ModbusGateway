#ifndef MODBUS_H
#define MODBUS_H

#include "ModbusGateway.h"

void modbusPreTransmission();
void modbusPostTransmission();
void initModbus();
void loopModbus();

#endif // MODBUS_H
