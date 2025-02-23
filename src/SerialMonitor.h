#ifndef SERIAL_MONITOR_H
#define SERIAL_MONITOR_H

#include "ModbusGateway.h"

void initSerialMonitor();
void loopSerialMonitor();
void clearSerialMonitor();
void ausgabeMesswert(String wert, bool cls = true);
void ausgabeCommand();
void ausgabeFehler(String wert);
void infoSerialCommands();
void serialCMDread();

#endif // SERIAL_MONITOR_H
