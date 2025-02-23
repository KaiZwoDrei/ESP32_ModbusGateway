#include "SerialMonitor.h"

//----------------------------- INIT -------------------------------------------
void initSerialMonitor(void) {
  Serial.begin(baudrateSerialMonitor);

  clearSerialMonitor();
  infoSerialCommands();
}
//----------------------------- MAIN -------------------------------------------
void loopSerialMonitor(void) {
  serialCMDread();

}

//------------------------------- CLS -----------------------------------------
void clearSerialMonitor(void) {
  // Autoscroll ausnutzen!
  int i = 0;
  for (i = 0; i < 20; i++) {
    Serial.println("");
  }
}
//------------------------------- Ausgabe Messwert -----------------------------------------
void ausgabeMesswert(String wert, bool cls = true) {
  if (cls)
    clearSerialMonitor();
  Serial.println(wert);
}
void ausgabeMesswert(String wert) {
  Serial.println(wert);
}
//------------------------------- INFO -----------------------------------------
void ausgabeCommand(void) {
  if (mbRTUdata.doRead) {
    if (mbRTUdata.doPoll) {
      Serial.print("Polling: ");
    }
    else {
      Serial.print("Read: ");
    }
    Serial.print(String(mbRTUdata.serialBAUD));  Serial.print(", ");
    mbRTUdata.serialMOD.replace("SERIAL_", "");
    Serial.print(mbRTUdata.serialMOD);  Serial.print(", ");

    Serial.print("Slave: ");  Serial.print("2");  Serial.print(", ");
    Serial.print(mbRTUdata.fc); Serial.print(", ");
    Serial.print("Reg: "); Serial.print(mbRTUdata.regAdr, DEC);   Serial.print(", ");
    Serial.print("Anz.: "); Serial.print(mbRTUdata.regAnz, DEC);   Serial.print(", ");
    Serial.print("scale: ");  Serial.print(mbRTUdata.scale);  Serial.print(", ");
    Serial.print("byteOrder: ");  Serial.print(mbRTUdata.byteOrder);  //Serial.print(", ");

    if (mbRTUdata.doPoll) {
      Serial.print(", Polling Anz.: "); Serial.print(mbRTUdata.anzPoll, DEC);   Serial.print(", ");
      Serial.print("Polling Interv.: "); Serial.print(mbRTUdata.pollTime, DEC);   Serial.print("sek.");
    }

    Serial.println("");
  }
}
//------------------------------- ERROR MSG -----------------------------------------
void ausgabeFehler(String wert) {
  clearSerialMonitor();
  infoSerialCommands();
  Serial.println("!!! FEHLER !!!");
  Serial.println(wert);
}
//-------------------------------- CMD INFO ----------------------------------------
void infoSerialCommands(void) {
  Serial.println("-------- Eingabemöglichkeiten --------");
  Serial.println("Einstellungen speichern:........'saveSettings';");
  Serial.println("Einstellungen laden:............'loadSettings';");
  Serial.println("Controller Neustart:............'restart';");
  Serial.println("");
  Serial.println("Datenabfragen stoppen:..........'stop'");
  Serial.println("Set Baud 9600:..................'9600;'");
  Serial.println("Set Modus 8N1:..................'8N1;'");
  Serial.println("Set Slave ID 2:.................'SLAVE2;'");
  Serial.println("Set Anz. Register 2:............'ANZ2;'");
  Serial.println("Set skallierung 100:............'SCALE100;'");
  Serial.println("Set Poll Time 1s:...............'time1;'");
  Serial.println("Set Poll Anzahl 10:.............'poll10;'");
  Serial.println("Byte-Order 4321.................'4321;'");
  Serial.println("");
  Serial.println("Read Coil 0:....................'COIL0;'");
  Serial.println("Read DiscreteInput 0:...........'DINP0;'");
  Serial.println("Read InputRegister 0:...........'IREG0;'");
  Serial.println("Read HoldingRegister 0:.........'HREG0;'");
  Serial.println("");
  Serial.println("Write Coil 0 to 1:..............'COIL0=1;'");
  Serial.println("Write HoldingRegister 0 to 1:...'COIL0=1;'");
  Serial.println("");
  Serial.println("Daten pollen:...................'start;'");
}
//--------------------------- Read Serial-CMD ---------------------------------------------
void serialCMDread(void) {
  String help = "";

  // String lesen
  while (Serial.available() > 0)
  {
    String eingabe = Serial.readStringUntil('\n');// solange lesen, bis return \n eingegeben wurde
    clearSerialMonitor();
    infoSerialCommands();

    // return Eingabe:
    Serial.println("");  Serial.print("eingabe: "); Serial.println(eingabe);

    // ----------------------------------------------------------------------
    if (eingabe.indexOf(";") || true) { // Eingabe abschlossen/Gültig
      eingabe.toLowerCase();

      //********* Commands *********
      // ### SetUp: Anzahl Register ###
      if (eingabe.indexOf("anz") >= 0) {
        help = eingabe;
        help.replace("anz", "");
        help.replace(";", "");

        if (isNumeric(help)) {
          // hässliche globale Variablen setzen
          if (help.toInt() > 2 || help.toInt() < 1) {
            ausgabeFehler("Falsche Anzahl: (1 oder 2)");
          }
          else {
            mbRTUdata.regAnz = help.toInt();
          }
        }
      }
      
      // ### SetUp: Skallierung ###
      else if (eingabe.indexOf("scale") >= 0) {
        help = eingabe;
        help.replace("scale", "");
        help.replace(";", "");

        if (isNumeric(help)) {
          mbRTUdata.scale = help.toInt(); // hässliche globale Variablen setzen
        }
      }
      // ### SetUp: polling time ###
      else if (eingabe.indexOf("time") >= 0) { // ### polling time ###
        help = eingabe;
        help.replace("time", "");
        help.replace(";", "");

        if (isNumeric(help)) {
          mbRTUdata.pollTime = help.toInt(); // hässliche globale Variablen setze
        }
      }
      // ### SetUp: polling anzahl ###
      else if (eingabe.indexOf("poll") >= 0) { // ### polling anzahl ###
        help = eingabe;
        help.replace("poll", "");
        help.replace(";", "");

        if (isNumeric(help)) {
          mbRTUdata.anzPoll = help.toInt(); // hässliche globale Variablen setze
        }
      }
      // ### setUp: byteOrder ###
      else if (eingabe.indexOf("4321") >= 0) { // ### 4321 ###
        mbRTUdata.byteOrder = "4321";
        ausgabeCommand();
      }
      else if (eingabe.indexOf("1234") >= 0) { // ### 1234 ###
        mbRTUdata.byteOrder = "2143";
        ausgabeCommand();
      }
      else if (eingabe.indexOf("2143") >= 0) { // ### 2143 ###
        mbRTUdata.byteOrder = "4321";
        ausgabeCommand();
      }
      // ### start: polling ###
      else if (eingabe.indexOf("start") >= 0 && eingabe.indexOf("restart") < 0) { // ### polling ###
        mbRTUdata.doPoll = true;
        mbRTUdata.doRead = true;
        ausgabeCommand();
      }
      // ### start: SlaveID ###
      else if (eingabe.indexOf("slaveid") >= 0) { // ### slave Adresse ###
        help = eingabe;
        help.replace("poll", "");
        help.replace(";", "");

        if (isNumeric(help)) {
          mbRTUdata.remSlaveAdr = help.toInt(); // hässliche globale Variablen setzen
        }

        ausgabeCommand();
      }
      // ### SetUp: baudRate ###
      else if (eingabe.indexOf("4800") >= 0 || eingabe.indexOf("9600") >= 0 || eingabe.indexOf("115200") >= 0) { // ### Baudrate ###
        help = eingabe;
        help.replace(";", "");
        if (isNumeric(help)) {
          mbRTUdata.serialBAUD = help.toInt(); // hässliche globale Variablen setze
          ausgabeCommand();
          initModbus(); // Modbus mit neuen Einstellungen initialisieren
        }
      }
      // ### SetUp: Modus/Parität ###
      else if (eingabe.indexOf("8n1") >= 0 || eingabe.indexOf("8e1") >= 0 || eingabe.indexOf("8e2") >= 0) { // ### Modus/Parität ###
        help = eingabe;
        help.replace(";", "");
        help.toUpperCase();
        mbRTUdata.serialMOD = help; // hässliche globale Variablen setze
        ausgabeCommand();
        initModbus(); // Modbus mit neuen Einstellungen initialisieren
      }
      // ### Daten/Parameter/Einstellungen speichern ###
      else if (eingabe.indexOf("savesettings") >= 0 ) { // ### daten speichern ###
        datenSpeichern();
      }
      // ### Daten/Parameter/Einstellungen aus Speicher laden ###
      else if (eingabe.indexOf("loadsettings") >= 0 ) { // ### daten laden ###
        datenLaden();
      }
      // ### Controller neustarten ###
      else if (eingabe.indexOf("restart") >= 0 ) { // ### restart ###
        Serial.println("Neustart in 2s !");
        delay(2000);
        ESP.restart();
      }
      //------------------- Register Schreiben/Lesen -----------------------
      // ### check CMD ###
      String regTyp = ""; // coil, ireg, hreg, dinp
      String wert = ""; // 1, 2, ...
      byte writeCMD = cmdSplit(eingabe, regTyp, mbRTUdata.regAdr, wert); // 0=fehler, 1=read, 2=write
      if (writeCMD == 1) {
        mbRTUdata.fc = regTyp;
        mbRTUdata.doRead = true;
        ausgabeCommand();
      }
      else if (writeCMD == 2) {
        mbRTUdata.fc = regTyp;
        mbRTUdata.doWrite = true;
        mbRTUdata.writeValue = wert;
        ausgabeCommand();
      }

      else { // else von: //********* Commands *********
        // stopping
        mbRTUdata.doPoll = false;
      }
    }
    else { // else von: // Eingabe abschlossen/Gültig
      // stopping
      mbRTUdata.doPoll = false;
    } 
  } // Ende Eingabe


}

//-------------------------------- Serial CMD split ----------------------------------------
byte cmdSplit(String cmd, String& regType, unsigned int& reg, String& wert) { // return 0=nothing/error, 1=read, 2=write
  String help=cmd;
  help.replace(";", "");
  bool schreiben = false;

  if (help.indexOf("coil")>=0 || help.indexOf("dinp")>=0 || help.indexOf("ireg")>=0 || help.indexOf("hreg")>=0) {
    // valid
  }
  else {
    return 0;
  }
  // modus
  if (help.indexOf("=") < 2) { // Read only
    schreiben = false;
  }
  else if (help.indexOf("=") > 2) { // Write only
    schreiben = true;
  }
  //--- Register typen & validierung ---
  //** Inhalt von help: "ireg0", "hreg0=2" **
  // Register: IREG
  if (help.indexOf("ireg") >= 0) {
    if (schreiben) {
      return 0; // read only!, if '=' then return error
    }
    regType = "ireg";
  }
  // Register: DiscreteInput (DINP)
  else if (help.indexOf("dinp") >= 0) {
    if (schreiben) {
      return 0;// read only!, if '=' then return error
    }
    regType = "dinp";
  }
  // Register: HREG
  else if (help.indexOf("hreg") >= 0) {
    regType = "hreg";
  }
  // Register: COIL
  else if (help.indexOf("coil") >= 0) {
    regType = "coil";
  }

  //--- Aufgabe (Read/Write) ---
  help.replace(regType, ""); //help: "ireg0" ->> "0", "hreg0=2" ->> "0=2"
  //*** Read ***
  if (!schreiben) {
    if (isNumeric(help)) {
      reg = help.toInt();
            return 1;
    }
    return 0;
  }
  //*** Write ***
  else {
    // RegsiterAdresse
    String help2 = help;
    help = help.substring(0, help.indexOf("=")); // "hreg0=2" ->> "0=2" ->> "0" // Registeradresse extrahieren
    if (isNumeric(help)) {
      reg = help.toInt();
    }
    else {
      return 0;
    }
    // Regsiter schreib-Wert
    help2.replace(help+"=", ""); // "hreg0=2" ->> "0=2" ->> "2" // Soll Register Wert axtrahieren
    if (isNumeric(help2)) {
      wert = help2;
      return 2;
    }
    else {
      return 0;
    }
  }
}
