//******************************************************************************************************//
// IDE: 1.8.18
// Board-URL: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
// Board-Package: esp32 by Espressif Systems, Version 3.1.3
// Board: ESP32 Arduino -> ESP32 Fev Module
//******************************************************************************************************//

String datumAenderung="-";
String versionNr="0.1";

//*** Verdrahtung ***
//  MAX485...ESP32
//      R0...18
//      DI...19
//   RE+DE...4

/* Allgemein */
#define baudrateSerialMonitor 115200 
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <Arduino.h>

//--- Webserver ---
#include <AsyncTCP.h> // Async TCP by ESP32Async, Version 3.3.5
#include <DNSServer.h> // included
#include "ESPAsyncWebServer.h" // ESP Async WebServer by ESP32Async, Version 3.7.0

#include "webserver_welcome.h"
#include "webserver_ModbusRTU.h"
#include "webserver_ModbusTCP.h"
#include "webserver_ModbusBridge.h"
#include "webserver_ModbusRepeater.h"
#include "webserver_settings.h"

//WiFiServer server(80);
AsyncWebServer server(80);
DNSServer dnsServer; 

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

ModbusMaster MB_RTU;

//### hässliche globale Variablen ###
struct mbTCPdataSTRUCT {
  byte IP1=192;
  byte IP2=168;
  byte IP3=0;
  byte IP4=199;
  byte SUB1=255;
  byte SUB2=255;
  byte SUB3=255;
  byte SUB4=0;
  byte GW1=192;
  byte GW2=168;
  byte GW3=0;
  byte GW4=1;
  
  byte remIP1=192;
  byte remIP2=168;
  byte remIP3=0;
  byte remIP4=10;

  byte slaveAdr=1;  
  byte remSlaveAdr=2;
  
  unsigned int regAdr=0;
  unsigned int regAnz=1;
  unsigned int scale=1;
  unsigned int pollTime=1; // sek.
  unsigned int anzPoll=10; // ende bei 0
  String byteOrder="4321"; // 4321, 1234, 2143
  String fc="ireg";
  String writeValue="";
  bool doRead=false;
  bool doWrite=false;
  bool doPoll=false;
  String rcv="";
  String error="";
};
mbTCPdataSTRUCT mbTCPdata;

struct netzwerkConfigSTRUCT {
  bool on=false;
  bool dhcp=false;
  byte IP1=192;
  byte IP2=168;
  byte IP3=0;
  byte IP4=199;
  byte SUB1=255;
  byte SUB2=255;
  byte SUB3=255;
  byte SUB4=0;
  byte GW1=192;
  byte GW2=168;
  byte GW3=0;
  byte GW4=1;  
};
netzwerkConfigSTRUCT ethernetConfig;
netzwerkConfigSTRUCT wlanConfig;
struct wlanLoginSTRUCT {
  String ssid="";  
  String pw="";  
};
wlanLoginSTRUCT wlanLogin; // für den login in ein bestehendes wlan

struct mbRTUdataSTRUCT {
  unsigned long serialBAUD=9600; // Baud rate for esp32 and max485 communication
  String serialMOD="8N1"; //"SERIAL_8N1"; // 8 Datenbits, Keine Parität, 1 Stoppbit
  byte remSlaveAdr=2;
  unsigned int regAdr=0;
  unsigned int regAnz=1;
  unsigned int scale=1;
  unsigned int pollTime=1; // sek.
  unsigned int anzPoll=10; // ende bei 0
  String byteOrder="4321"; // 4321, 1234, 2143
  String fc="ireg";
  String writeValue="";
  bool doRead=false;
  bool doWrite=false;
  bool doPoll=false;
  String rcv="";
  String error="";
};
mbRTUdataSTRUCT mbRTUdata;
/*
01: Coils (FC=01)
02: Discrete Inputs (FC=02)
03: Multiple Holding Registers (FC=03) // not supportet yet!!
04: Input Registers (FC=04)
05: Single Coil (FC=05)
06: Single Holding Register (FC=06)
0F: Multiple Coils (FC=15) // not supportet yet!!
10: Multiple Holding Registers (FC=16) // not supportet yet!!
 */
//------------------------------------------------------------------------
//**** Deklarationsteil ****
// Modbus
void modbusRTUreadInputRegister(unsigned int regAdr, unsigned int regLen, float scale);
void modbusRTUreadHoldingRegister(unsigned int regAdr, unsigned int regLen, float scale);
void modbusRTUreadCoil(unsigned int regAdr);
void modbusRTUreadDiscreteInput(unsigned int regAdr);
// SerialMonitor
byte cmdSplit(String cmd, String& regType, unsigned int& reg, String& wert);
// Webserver
void setupServer(void);
void loopWebserver(void);
// speicher
void initSpeicher(void);
void datenSpeichern(void);
void datenLaden(void);
// hilfsfunktionen
bool isNumeric(String str);

//------------------------------------------------------------------------
void task01(void *arg)
{                         //*** OTA, SerialCommands, ...
    while(1){             
      loopOTA(); 
      loopSerialMonitor();
      loopWebserver();
      vTaskDelay(tik_100ms/ portTICK_RATE_MS);
    }
}
//------------------------------------------------------------------------
void task02(void *arg)
{                         //*** ModbusRTU, ...
    while(1){   
      loopModbus();
      
      vTaskDelay(tik_100ms/ portTICK_RATE_MS); // 500ms
    }
}

void setup()
{ 
  initSpeicher(); // Datenspeicher init und Daten laden
  initSerialMonitor();
  initAccespointWebserver();
  setupWebserver();  
  initOTA(); 
  
  initModbus();

    //*** Task´s ***    
  xTaskCreatePinnedToCore(task01, "task01, Serial", 4096, NULL, 10, NULL, 0); // Core 0
  xTaskCreatePinnedToCore(task02, "task02, Modbus", 4096, NULL, 10, NULL, 1); // Core 1
} 

void loop()
{

  }

//-----------------------------------------------
void initAccespointWebserver(void){
  IPAddress Ip_AP(192, 168, 11, 1);
  IPAddress Gw_AP(192, 168, 11, 1);
  IPAddress NMask_AP(255, 255, 255, 0);

  WiFi.mode(WIFI_AP); //WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(Ip_AP, Gw_AP, NMask_AP);
  WiFi.softAP("ModbusGateway", "123456789"); // ssid, pw

  dnsServer.start(53, "*", Ip_AP); //dnsServer.start(53, "*", WiFi.softAPIP());
  
  // Webserver
  //webServer.begin();
}

//------------------------------------------------
void initOTA(void){
  // ArduinoOTA.setPort(8266);
   ArduinoOTA.setHostname(otaHostName);
   ArduinoOTA.setPassword(otaHostPw);

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
      }
  });
  ArduinoOTA.onEnd([]() {});
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {  
  });
  ArduinoOTA.onError([](ota_error_t error) {});
  ArduinoOTA.begin();
}

//------------------------------------------------
void loopOTA(void) {
  ArduinoOTA.handle();                    
}
