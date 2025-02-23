// Paramter/Einstellungen speichern und laden
// Daten im nicht flüchtigen Speicher verwalten
// deklarationen
#include "ModbusGateway.h"
#include "speicher.h"
//-----------------------------------
void initSpeicher(void) {
  //parameterSpeicher.begin("parameter", false);  // false= read & write Mode
  //parameterSpeicher.clear(); // alle daten löschen
  //parameterSpeicher.remove(key); // einzelne Daten löschen
  //parameterSpeicher.end();

  datenLaden();
}
/*** Allgemeine Daten speichern ***/
void datenSpeichern(void) {
  parameterSpeicher.begin("parameter", false);  // false= read & write Mode

  //****** Modbus RTU Parameter ******
  parameterSpeicher.putULong("mbRTU_baudrate", mbRTUdata.serialBAUD);
  parameterSpeicher.putString("mbRTU_modusParitaet", mbRTUdata.serialMOD);
  parameterSpeicher.putUChar("mbRTU_remSlaveAdr", mbRTUdata.remSlaveAdr);
  parameterSpeicher.putUInt("mbRTU_regAdr", mbRTUdata.regAdr);
  parameterSpeicher.putUInt("mbRTU_regAnz", mbRTUdata.regAnz);
  parameterSpeicher.putUInt("mbRTU_scale", mbRTUdata.scale);
  parameterSpeicher.putUInt("mbRTU_pollTime", mbRTUdata.pollTime);
  parameterSpeicher.putString("mbRTU_byteOrder", mbRTUdata.byteOrder);
  parameterSpeicher.putString("mbRTU_fc", mbRTUdata.fc);

  //****** Modbus RTU Parameter ******
  parameterSpeicher.putUChar("mbTCP_IP1", mbTCPdata.IP1);
  parameterSpeicher.putUChar("mbTCP_IP2", mbTCPdata.IP2);
  parameterSpeicher.putUChar("mbTCP_IP3", mbTCPdata.IP3);
  parameterSpeicher.putUChar("mbTCP_IP4", mbTCPdata.IP4);
  parameterSpeicher.putUChar("mbTCP_SUB1", mbTCPdata.SUB1);
  parameterSpeicher.putUChar("mbTCP_SUB2", mbTCPdata.SUB2);
  parameterSpeicher.putUChar("mbTCP_SUB3", mbTCPdata.SUB3);
  parameterSpeicher.putUChar("mbTCP_SUB4", mbTCPdata.SUB4);
  parameterSpeicher.putUChar("mbTCP_GW1", mbTCPdata.GW1);
  parameterSpeicher.putUChar("mbTCP_GW2", mbTCPdata.GW2);
  parameterSpeicher.putUChar("mbTCP_GW3", mbTCPdata.GW3);
  parameterSpeicher.putUChar("mbTCP_GW4", mbTCPdata.GW4);
  parameterSpeicher.putUChar("mbTCP_remIP1", mbTCPdata.remIP1);
  parameterSpeicher.putUChar("mbTCP_remIP2", mbTCPdata.remIP2);
  parameterSpeicher.putUChar("mbTCP_remIP3", mbTCPdata.remIP3);
  parameterSpeicher.putUChar("mbTCP_remIP4", mbTCPdata.remIP4);

  parameterSpeicher.putUChar("mbTCP_slaveAdr", mbTCPdata.slaveAdr);
  parameterSpeicher.putUChar("mbTCP_remSlaveAdr", mbTCPdata.remSlaveAdr);

  parameterSpeicher.putUInt("mbTCP_regAdr", mbTCPdata.regAdr);
  parameterSpeicher.putUInt("mbTCP_regAnz", mbTCPdata.regAnz);
  parameterSpeicher.putUInt("mbTCP_scale", mbTCPdata.scale);
  parameterSpeicher.putUInt("mbTCP_pollTime", mbTCPdata.pollTime);
  parameterSpeicher.putString("mbTCP_byteOrder", mbTCPdata.byteOrder);
  parameterSpeicher.putString("mbTCP_fc", mbTCPdata.fc);

  /****** Netzwerkparameter Ethernet ******/
  parameterSpeicher.putBool("ethernetConfig_on", ethernetConfig.on);
  parameterSpeicher.putBool("ethernetConfig_dhcp", ethernetConfig.dhcp);
  parameterSpeicher.putUChar("ethernetConfig_IP1", ethernetConfig.IP1);
  parameterSpeicher.putUChar("ethernetConfig_IP2", ethernetConfig.IP2);
  parameterSpeicher.putUChar("ethernetConfig_IP3", ethernetConfig.IP3);
  parameterSpeicher.putUChar("ethernetConfig_IP4", ethernetConfig.IP4);
  parameterSpeicher.putUChar("ethernetConfig_SUB1", ethernetConfig.SUB1);
  parameterSpeicher.putUChar("ethernetConfig_SUB2", ethernetConfig.SUB2);
  parameterSpeicher.putUChar("ethernetConfig_SUB3", ethernetConfig.SUB3);
  parameterSpeicher.putUChar("ethernetConfig_SUB4", ethernetConfig.SUB4);
  parameterSpeicher.putUChar("ethernetConfig_GW1", ethernetConfig.GW1);
  parameterSpeicher.putUChar("ethernetConfig_GW2", ethernetConfig.GW2);
  parameterSpeicher.putUChar("ethernetConfig_GW3", ethernetConfig.GW3);
  parameterSpeicher.putUChar("ethernetConfig_GW4", ethernetConfig.GW4);

  /****** Netzwerkparameter WLan ******/
  parameterSpeicher.putBool("wlanConfig_on", wlanConfig.on);
  parameterSpeicher.putBool("wlanConfig_dhcp", wlanConfig.dhcp);
  parameterSpeicher.putUChar("wlanConfig_IP1", wlanConfig.IP1);
  parameterSpeicher.putUChar("wlanConfig_IP2", wlanConfig.IP2);
  parameterSpeicher.putUChar("wlanConfig_IP3", wlanConfig.IP3);
  parameterSpeicher.putUChar("wlanConfig_IP4", wlanConfig.IP4);
  parameterSpeicher.putUChar("wlanConfig_SUB1", wlanConfig.SUB1);
  parameterSpeicher.putUChar("wlanConfig_SUB2", wlanConfig.SUB2);
  parameterSpeicher.putUChar("wlanConfig_SUB3", wlanConfig.SUB3);
  parameterSpeicher.putUChar("wlanConfig_SUB4", wlanConfig.SUB4);
  parameterSpeicher.putUChar("wlanConfig_GW1", wlanConfig.GW1);
  parameterSpeicher.putUChar("wlanConfig_GW2", wlanConfig.GW2);
  parameterSpeicher.putUChar("wlanConfig_GW3", wlanConfig.GW3);
  parameterSpeicher.putUChar("wlanConfig_GW4", wlanConfig.GW4);


  Serial.println("--- daten gespeichert ---");
  parameterSpeicher.end();
}
/*** Allgemeine Daten laden ***/
void datenLaden(void) {
  parameterSpeicher.begin("parameter", false);  // false= read & write Mode

  //****** Modbus RTU Parameter ******
  mbRTUdata.serialBAUD=parameterSpeicher.getULong("mbRTU_baudrate", mbRTUdata.serialBAUD);
  mbRTUdata.serialMOD=parameterSpeicher.getString("mbRTU_modusParitaet", mbRTUdata.serialMOD);
  mbRTUdata.remSlaveAdr=parameterSpeicher.getUChar("mbRTU_remSlaveAdr", mbRTUdata.remSlaveAdr);
  mbRTUdata.regAdr=parameterSpeicher.getUInt("mbRTU_regAdr", mbRTUdata.regAdr);
  mbRTUdata.regAnz=parameterSpeicher.getUInt("mbRTU_regAnz", mbRTUdata.regAnz);
  mbRTUdata.scale=parameterSpeicher.getUInt("mbRTU_scale", mbRTUdata.scale);
  mbRTUdata.pollTime=parameterSpeicher.getUInt("mbRTU_pollTime", mbRTUdata.pollTime);
  mbRTUdata.anzPoll=parameterSpeicher.getUInt("mbRTU_anzPoll", mbRTUdata.anzPoll);
  mbRTUdata.byteOrder=parameterSpeicher.getString("mbRTU_byteOrder", mbRTUdata.byteOrder);
  mbRTUdata.fc=parameterSpeicher.getString("mbRTU_fc", mbRTUdata.fc);

  //****** Modbus RTU Parameter ******
   mbTCPdata.IP1=parameterSpeicher.getUChar("mbTCP_IP1", mbTCPdata.IP1);
   mbTCPdata.IP2=parameterSpeicher.getUChar("mbTCP_IP2", mbTCPdata.IP2);
   mbTCPdata.IP3=parameterSpeicher.getUChar("mbTCP_IP3", mbTCPdata.IP3);
   mbTCPdata.IP4=parameterSpeicher.getUChar("mbTCP_IP4", mbTCPdata.IP4);
   mbTCPdata.SUB1=parameterSpeicher.getUChar("mbTCP_SUB1", mbTCPdata.SUB1);
   mbTCPdata.SUB2=parameterSpeicher.getUChar("mbTCP_SUB2", mbTCPdata.SUB2);
   mbTCPdata.SUB3=parameterSpeicher.getUChar("mbTCP_SUB3", mbTCPdata.SUB3);
   mbTCPdata.SUB4=parameterSpeicher.getUChar("mbTCP_SUB4", mbTCPdata.SUB4);
   mbTCPdata.GW1=parameterSpeicher.getUChar("mbTCP_GW1", mbTCPdata.GW1);
   mbTCPdata.GW2=parameterSpeicher.getUChar("mbTCP_GW2", mbTCPdata.GW2);
   mbTCPdata.GW3=parameterSpeicher.getUChar("mbTCP_GW3", mbTCPdata.GW3);
   mbTCPdata.GW4=parameterSpeicher.getUChar("mbTCP_GW4", mbTCPdata.GW4);
   mbTCPdata.remIP1=parameterSpeicher.getUChar("mbTCP_remIP1", mbTCPdata.remIP1);
   mbTCPdata.remIP2=parameterSpeicher.getUChar("mbTCP_remIP2", mbTCPdata.remIP2);
   mbTCPdata.remIP3=parameterSpeicher.getUChar("mbTCP_remIP3", mbTCPdata.remIP3);
   mbTCPdata.remIP4=parameterSpeicher.getUChar("mbTCP_remIP4", mbTCPdata.remIP4);

   mbTCPdata.slaveAdr=parameterSpeicher.getUChar("mbTCP_slaveAdr", mbTCPdata.slaveAdr);
   mbTCPdata.remSlaveAdr=parameterSpeicher.getUChar("mbTCP_remSlaveAdr", mbTCPdata.remSlaveAdr);

   mbTCPdata.regAdr=parameterSpeicher.getUInt("mbTCP_regAdr", mbTCPdata.regAdr);
   mbTCPdata.regAnz=parameterSpeicher.getUInt("mbTCP_regAnz", mbTCPdata.regAnz);
   mbTCPdata.scale=parameterSpeicher.getUInt("mbTCP_scale", mbTCPdata.scale);
   mbTCPdata.pollTime=parameterSpeicher.getUInt("mbTCP_pollTime", mbTCPdata.pollTime);
  mbTCPdata.anzPoll=parameterSpeicher.getUInt("mbTCPdata_anzPoll", mbTCPdata.anzPoll);
   mbTCPdata.byteOrder=parameterSpeicher.getString("mbTCP_byteOrder", mbTCPdata.byteOrder);
   mbTCPdata.fc=parameterSpeicher.getString("mbTCP_fc", mbTCPdata.fc);


  Serial.println("--- daten geladen ---"); //Serial.end();
  parameterSpeicher.end();
}

/*** Standard Eisntellungen herstellen ***/
void datenZuruecksetzen(void) {
  
  mbTCPdataSTRUCT mbTCPdata_DEFAULT;
  mbTCPdata=mbTCPdata_DEFAULT;
  
  mbRTUdataSTRUCT mbRTUdata_DEFAULT;
  mbRTUdata=mbRTUdata_DEFAULT;
/*
  //****** Modbus RTU Parameter ******
  mbRTUdata.serialBAUD = 9600;
  mbRTUdata.serialMOD = "SERIAL_8N1";

  mbRTUdata.remSlaveAdr = 2;

  mbRTUdata.regAdr = 0;
  mbRTUdata.regAnz = 1;
  mbRTUdata.scale = 1;
  mbRTUdata.pollTime = 1; // sek.
  mbRTUdata.anzPoll = 10; // ende bei 0
  mbRTUdata.byteOrder = "4321"; // 4321, 1234, 2143

  //****** Modbus RTU Parameter ******
  mbTCPdata.IP1 = 192;
  mbTCPdata.IP2 = 168;
  mbTCPdata.IP3 = 0;
  mbTCPdata.IP4 = 199;
  mbTCPdata.SUB1 = 255;
  mbTCPdata.SUB2 = 255;
  mbTCPdata.SUB3 = 255;
  mbTCPdata.SUB4 = 0;
  mbTCPdata.GW1 = 192;
  mbTCPdata.GW2 = 168;
  mbTCPdata.GW3 = 0;
  mbTCPdata.GW4 = 1;

  mbTCPdata.remIP1 = 192;
  mbTCPdata.remIP2 = 168;
  mbTCPdata.remIP3 = 0;
  mbTCPdata.remIP4 = 10;

  mbTCPdata.slaveAdr = 1;
  mbTCPdata.remSlaveAdr = 2;

  mbTCPdata.regAdr = 0;
  mbTCPdata.regAnz = 1;
  mbTCPdata.scale = 1;
  mbTCPdata.pollTime = 1; // sek.
  mbTCPdata.anzPoll = 10; // ende bei 0
  mbTCPdata.byteOrder = "4321"; // 4321, 1234, 2143
*/
  Serial.println("--- daten geladen ---"); //Serial.end();
}
