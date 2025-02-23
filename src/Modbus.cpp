
#include "Modbus.h"
#include "ModbusGateway.h"

//------------------------------------------------------------------------

void modbusPreTransmission()
{
  delay(500);
  digitalWrite(MODBUS_DIR_PIN, HIGH);
}
void modbusPostTransmission()
{
  digitalWrite(MODBUS_DIR_PIN, LOW);
  delay(500);
}
//------------------------------------------------------------------------
void initModbus(void){ 
static bool iAmInit;
// stoppen
if(iAmInit){
	//MB_RTU.end()
	Serial2.end();	
}
// initialisieren
  pinMode(MODBUS_DIR_PIN, OUTPUT);
  digitalWrite(MODBUS_DIR_PIN, LOW);
  uint32_t paritaet=SERIAL_8N1;
  
  if (mbRTUdata.serialMOD=="8N1"){paritaet=SERIAL_8N1;}
  if (mbRTUdata.serialMOD=="8E1"){paritaet=SERIAL_8E1;}
  if (mbRTUdata.serialMOD=="8E2"){paritaet=SERIAL_8E2;}
  
  Serial2.begin(mbRTUdata.serialBAUD, paritaet, MODBUS_RX_PIN, MODBUS_TX_PIN);
  Serial2.setTimeout(200);
  
  MB_RTU.begin(int(mbRTUdata.remSlaveAdr), Serial2);

//  callbacks allow us to configure the RS485 transceiver correctly
   MB_RTU.preTransmission(modbusPreTransmission);
   MB_RTU.postTransmission(modbusPostTransmission);  

iAmInit=true;
}
//------------------------------------------------------------------------
void loopModbus(void){ //100ms
/*
01: Read Coil (FC=01)
02: Read Discrete Inputs (FC=02)
03: Read Input Registers (FC=03)
04: Read Holding Registers (FC=04)
05: Write Coil (FC=05)
06: Write Holding Register (FC=06) / (FC=16)
 */
//### hässliche globale Variablen ###
/*
unsigned int regAdr=0;
unsigned int regAnz=1;
unsigned int scale=1;
unsigned int pollTime=1; // sek.
unsigned int anzPoll=10; // ende bei 0
byte fc=0x04;
bool doRead=false;
bool doPoll=false;
*/
static bool pipStart;
static unsigned int pollCount;
static unsigned long int myMillis;

// Flankenauswertung - Start
if (pipStart==false && mbRTUdata.doPoll==true){
  pipStart=true;
  pollCount=mbRTUdata.anzPoll-1;
  myMillis=millis();
  }
// Flankenauswertung - Ende
if (pipStart==true && mbRTUdata.doPoll==false){
  pipStart=false;
  }

// Polling interval
  if(mbRTUdata.doRead==false && mbRTUdata.doPoll==true && (millis()>myMillis+(mbRTUdata.pollTime*1000))){ 
    myMillis=millis();  
    mbRTUdata.doRead=true; 
    if(pollCount>1){
      pollCount--;      
    }
    else{
      mbRTUdata.doPoll=false;
    }
  }

  //--- Modbus RTU lesen ---
  if(mbRTUdata.doRead){
    mbRTUdata.doRead=false;
	// Read: InputRegister
    if(mbRTUdata.fc=="ireg"){
      modbusRTUreadInputRegister(mbRTUdata.regAdr, mbRTUdata.regAnz, float(mbRTUdata.scale));
    }
	// Read: HoldingRegister
    else if(mbRTUdata.fc=="hreg"){
      modbusRTUreadHoldingRegister(mbRTUdata.regAdr, mbRTUdata.regAnz, float(mbRTUdata.scale));
    }
	// Read: DiscreteInput
    else if(mbRTUdata.fc=="dinp"){
      modbusRTUreadDiscreteInput(mbRTUdata.regAdr);
    }
	// Read: Coil
    else if(mbRTUdata.fc=="dinp"){
      modbusRTUreadCoil(mbRTUdata.regAdr);
    }    
    
  }
  //--- Modbus RTU schreiben ---
  else if(mbRTUdata.doWrite){
    mbRTUdata.doWrite=false;
	// Write: HoldingRegister
    if(mbRTUdata.fc=="hreg"){
      //modbusRTUreadInputRegister(mbRTUdata.regAdr, mbRTUdata.regAnz, float(mbRTUdata.scale));
    }
    
	mbRTUdata.writeValue="";    
  }
  
}
//------------------------------------------------------------------------
void modbusRTUreadInputRegister(unsigned int regAdr=0, unsigned int regLen=1, float scale=1.0){  
    uint8_t result;
    uint16_t data[2];
    float reading;

      result = MB_RTU.readInputRegisters(regAdr, regLen); // adr, laenge
        if (result == MB_RTU.ku8MBSuccess) { // result=0 = kein Fehler
          
           data[0]=MB_RTU.getResponseBuffer(0x00); // Word/Register 1 (int)
           data[1]=MB_RTU.getResponseBuffer(0x01); // Word/Register 2 (int)
           MB_RTU.clearResponseBuffer();
           
		   // ToDo 
		   // gloabl: byteOrder
            if (regLen==2){
              reading=(data[1] << 16) | data[0];
            }
            else{
              reading= data[0];
            }
            reading=reading/scale;			
            ausgabeMesswert("Value: " + String(reading));
            
            mbRTUdata.rcv=String(reading); // GLOBAL!
           
        } else {
          ausgabeFehler("Failed, Response Code: " + String(result));
          
          mbRTUdata.error="! Fehler !"; // GLOBAL!
        }
}
void modbusRTUreadHoldingRegister(unsigned int regAdr=0, unsigned int regLen=1, float scale=1.0){  
    uint8_t result;
    uint16_t data[2];
    float reading;

      result = MB_RTU.readHoldingRegisters(regAdr, regLen); // adr, laenge
        if (result == MB_RTU.ku8MBSuccess) { // result=0 = kein Fehler
          
           data[0]=MB_RTU.getResponseBuffer(0x00); // Word/Register 1 (int)
           data[1]=MB_RTU.getResponseBuffer(0x01); // Word/Register 2 (int)
           MB_RTU.clearResponseBuffer();
           
		   // ToDo 
		   // gloabl: byteOrder
           
            if (regLen==2){
              reading=(data[1] << 16) | data[0];
            }
            else{
              reading= data[0];
            }
            reading=reading/scale;			
            ausgabeMesswert("Value: " + String(reading));
            
            mbRTUdata.rcv=String(reading); // GLOBAL!
           
        } else {
          ausgabeFehler("Failed, Response Code: " + String(result));
          
          mbRTUdata.error="! Fehler !"; // GLOABL!
        }
}
void modbusRTUreadCoil(unsigned int regAdr=0){  
    uint8_t result;
    uint16_t data[2];
    bool reading;

      result = MB_RTU.readCoils(regAdr, 1); // adr, laenge
        if (result == MB_RTU.ku8MBSuccess) { // result=0 = kein Fehler
          
           data[0]=MB_RTU.getResponseBuffer(0x00); // Word/Register 1 (int)
           MB_RTU.clearResponseBuffer();
           
            reading=(data[0]>0); // true/false
						
            ausgabeMesswert("Value: " + String(reading));
            
            mbRTUdata.rcv=String(reading); // GLOBAL!
           
        } else {
          ausgabeFehler("Failed, Response Code: " + String(result));
          
          mbRTUdata.error="! Fehler !"; // GLOBAL!
        }
}
void modbusRTUreadDiscreteInput(unsigned int regAdr=0){  
    uint8_t result;
    uint16_t data[2];
    bool reading;

      result = MB_RTU.readDiscreteInputs(regAdr, 1); // adr, laenge
        if (result == MB_RTU.ku8MBSuccess) { // result=0 = kein Fehler
          
           data[0]=MB_RTU.getResponseBuffer(0x00); // Word/Register 1 (int)
           MB_RTU.clearResponseBuffer();
           
            reading=(data[0]>0); // true/false
						
            ausgabeMesswert("Value: " + String(reading));
            
            mbRTUdata.rcv=String(reading); // GLOBAL!
           
        } else {
          ausgabeFehler("Failed, Response Code: " + String(result));
          
          mbRTUdata.error="! Fehler !"; // GLOBAL!
        }
}
