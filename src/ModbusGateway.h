#ifndef MODBUS_GATEWAY_H
#define MODBUS_GATEWAY_H


//*** Verdrahtung ***
//  MAX485...ESP32
//      R0...18
//      DI...19
//   RE+DE...4

/* Allgemein */
#define baudrateSerialMonitor 115200 
#include <Arduino.h>

#include <WiFi.h>
#include <ArduinoOTA.h>
#include <Preferences.h>
#include <ModbusMaster.h>
//--- Webserver ---
#include <AsyncTCP.h> // Async TCP by ESP32Async, Version 3.3.5
#include <DNSServer.h> // included
#include "ESPAsyncWebServer.h" // ESP Async WebServer by ESP32Async, Version 3.7.0
#include "SerialMonitor.h"
#include "webserver_welcome.h"
#include "webserver_ModbusRTU.h"
#include "webserver_ModbusTCP.h"
#include "webserver_ModbusBridge.h"
#include "webserver_ModbusRepeater.h"
#include "webserver_settings.h"
#include "webserver_welcome.h"

// Constants
#define MODBUS_DIR_PIN 4
#define MODBUS_RX_PIN 18
#define MODBUS_TX_PIN 19
#define OTA_HOST_NAME "Modbus_Gateway"
#define OTA_HOST_PW "admin"





//--- OTA ---
#include <ArduinoOTA.h> // ArduinoOTA by Juraj Andrassy, Version 1.1.0
#define otaHostName "Modbus_Gateway"
#define otaHostPw "admin"

/* Speichersystem */
#include <Preferences.h> // Preferences by Volodymyr Shymanskyy, Version 2.1.0
Preferences parameterSpeicher;

/* Task stuff*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#define tik_100ms 100
#define tik_500ms 500

/* Modbus stuff */
#include <ModbusMaster.h> // ModbusMaster by Doc Walker 4-20ma@wvfans.net, Version 2.0.1
#define MODBUS_DIR_PIN  4 // connect DR, RE pin of MAX485 to gpio 4
#define MODBUS_RX_PIN 18 // Rx pin  
#define MODBUS_TX_PIN 19 // Tx pin 



// Global variables
extern String datumAenderung;
extern String versionNr;
extern AsyncWebServer server;
extern DNSServer dnsServer;
extern Preferences parameterSpeicher;
extern ModbusMaster MB_RTU;
extern mbTCPdataSTRUCT mbTCPdata;
extern netzwerkConfigSTRUCT ethernetConfig;
extern netzwerkConfigSTRUCT wlanConfig;
extern wlanLoginSTRUCT wlanLogin;
extern mbRTUdataSTRUCT mbRTUdata;

// Function declarations
void modbusRTUreadInputRegister(unsigned int regAdr, unsigned int regLen, float scale);
void modbusRTUreadHoldingRegister(unsigned int regAdr, unsigned int regLen, float scale);
void modbusRTUreadCoil(unsigned int regAdr);
void modbusRTUreadDiscreteInput(unsigned int regAdr);
byte cmdSplit(String cmd, String& regType, unsigned int& reg, String& wert);
void setupServer(void);
void loopWebserver(void);
void initSpeicher(void);
void datenSpeichern(void);
void datenLaden(void);
bool isNumeric(String str);
void loopOTA(void);
void loopSerialMonitor(void);
void loopModbus(void);
void initSerialMonitor(void);
void initAccespointWebserver(void);
void setupWebserver(void);
void initOTA(void);
void initModbus(void);

#endif // MODBUS_GATEWAY_H
