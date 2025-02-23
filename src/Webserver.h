#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "ModbusGateway.h"

void ausgabeDebug(String nachricht);
String variablenBinderHTML(const String& var);
void setupWebserver();
void loopWebserver();

#endif // WEBSERVER_H
