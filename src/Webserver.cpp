#include "Webserver.h"
#include "ModbusGateway.h"
#include "webserver_welcome.h"
#include "webserver_ModbusRTU.h"
#include "webserver_ModbusTCP.h"
#include "webserver_ModbusBridge.h"
#include "webserver_ModbusRepeater.h"
#include "webserver_welcome.h"
#include "webserver_settings.h"
//--- Serielle Ausgabe ---
void ausgabeDebug(String nachricht) {
  Serial.println(nachricht);
}

//--- Variablen auf Website ---
String variablenBinderHTML(const String& var) {
  //********* Allgemein *********
  if (var == "DATUM_AENDERUNG") {
    return String(datumAenderung);
  }
  else if (var == "NR_VERSION") {
    return String(versionNr);
  }
    //********* ModbusRTU *********
  else if (var == "valueModbusRTUread") {
    return String(mbRTUdata.rcv);
  }
  else if (var == "mbRTU_BAUDRATE") {
    return String(mbRTUdata.serialBAUD);
  }
  else if (var == "mbRTU_MODUS") {
    return String(mbRTUdata.serialMOD);
  }
  else if (var == "mbRTU_REG_TYP") {
    String help = mbRTUdata.fc;
    help.toUpperCase();
    return String(help);
  }
  else if (var == "mbRTU_INPUT_SLAVE") {
    return String(mbRTUdata.remSlaveAdr);
  }
  else if (var == "mbRTU_INPUT_ADR") {
    return String(mbRTUdata.regAdr);
  }
  else if (var == "mbRTU_INPUT_VALUE") {
    return String(mbRTUdata.writeValue);
  }
  else if (var == "mbRTU_INPUT_FAKTOR") {
    return String(mbRTUdata.scale);
  }
  else if (var == "mbRTU_pollTime") {
    return String(mbRTUdata.pollTime);
  }
  else if (var == "mbRTU_pollAnzahl") {
    return String(mbRTUdata.anzPoll);
  }
    //********* ModbusTCP *********
  else if (var == "mbTCP_REG_TYP") {
    String help = mbRTUdata.fc;
    help.toUpperCase();
    return String(help);
  }
  else if (var == "mbTCP_INPUT_SLAVE") {
    return String(mbTCPdata.remSlaveAdr);
  }
  else if (var == "mbTCP_INPUT_ADR") {
    return String(mbTCPdata.regAdr);
  }
  else if (var == "mbTCP_INPUT_VALUE") {
    return String(mbTCPdata.writeValue);
  }
  else if (var == "mbTCP_INPUT_FAKTOR") {
    return String(mbTCPdata.scale);
  }
  else if (var == "valueModbusTCPread") {
    return String(mbTCPdata.rcv);
  }
  else if (var == "mbTCP_IP1") {
    return String(mbTCPdata.IP1);
  }
  else if (var == "mbTCP_IP2") {
    return String(mbTCPdata.IP2);
  }
  else if (var == "mbTCP_IP3") {
    return String(mbTCPdata.IP3);
  }
  else if (var == "mbTCP_IP4") {
    return String(mbTCPdata.IP4);
  }
  else if (var == "mbTCP_remIP1") {
    return String(mbTCPdata.remIP1);
  }
  else if (var == "mbTCP_remIP2") {
    return String(mbTCPdata.remIP2);
  }
  else if (var == "mbTCP_remIP3") {
    return String(mbTCPdata.remIP3);
  }
  else if (var == "mbTCP_remIP4") {
    return String(mbTCPdata.remIP4);
  }
  else if (var == "mbTCP_GW1") {
    return String(mbTCPdata.GW1);
  }
  else if (var == "mbTCP_GW2") {
    return String(mbTCPdata.GW2);
  }
  else if (var == "mbTCP_GW3") {
    return String(mbTCPdata.GW3);
  }
  else if (var == "mbTCP_GW4") {
    return String(mbTCPdata.GW4);
  }
  else if (var == "mbTCP_SUB1") {
    return String(mbTCPdata.SUB1);
  }
  else if (var == "mbTCP_SUB2") {
    return String(mbTCPdata.SUB2);
  }
  else if (var == "mbTCP_SUB3") {
    return String(mbTCPdata.SUB3);
  }
  else if (var == "mbTCP_SUB4") {
    return String(mbTCPdata.SUB4);
  }
  else if (var == "mbTCP_pollTime") {
    return String(mbTCPdata.pollTime);
  }
  else if (var == "mbTCP_pollAnzahl") {
    return String(mbTCPdata.anzPoll);
  }

  return String();
}

class CaptivePortalHandler : public AsyncWebHandler {
  public:
    CaptivePortalHandler() {}
    virtual ~CaptivePortalHandler() {}

    bool canHandle(AsyncWebServerRequest *request) {
      return request->url() == "/";
       return true;
    }

    void handleRequest(AsyncWebServerRequest *request) {
      if (request->method() == HTTP_GET && request->url() == "/") {
        request->send_P(200, "text/html", webserver_WelcomePage, variablenBinderHTML); //request->send(200, "text/html", webserver_WelcomePage);
      } else {
        request->send(405, "text/plain", "Method Not Allowed"); //request->send_P(200, "text/html", webserver_WelcomePage, variablenBinderHTML);
      }
    }
};

void setupWebserver() {
  server.addHandler(new CaptivePortalHandler()).setFilter(ON_AP_FILTER);
  server.onNotFound([&](AsyncWebServerRequest * request) {
    Serial.println("!!! Seite nicht gefunden !!!");
    request->send_P(200, "text/html", webserver_WelcomePage, variablenBinderHTML); //request->send(200, "text/html", webserver_WelcomePage);
  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", webserver_WelcomePage, variablenBinderHTML); //request->send(200, "text/html", webserver_WelcomePage);
  });
  server.on("/generate_204", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", webserver_WelcomePage, variablenBinderHTML); //request->send(200, "text/html", webserver_WelcomePage);
  });
  server.onNotFound([](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", webserver_WelcomePage, variablenBinderHTML); //request->send(200, "text/html", webserver_WelcomePage); //redirect("/");
  });

  server.on("/header", HTTP_GET, [](AsyncWebServerRequest * request) {
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", "Ok");
    response->addHeader("Test-Header", "My header value");
    request->send(response);
  });

  //--- Ereignis Handling / Benutzereingabe ---
  server.on("/ereignis", HTTP_GET, [](AsyncWebServerRequest * request) {
    String fromPage = request->header("Referer");
    fromPage.toLowerCase();
    String parameter = "";
    String iValue = "";
    bool ok = false;
    Serial.println("fromPage" + String(fromPage));

    //********* Modbus RTU *********
    if (fromPage.indexOf("modbus") > 0 && fromPage.indexOf("rtu") > 0) {
      //--- baudrate ---
      parameter = "select_baudrate";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        if (isNumeric(iValue)) {
          mbRTUdata.serialBAUD = iValue.toInt();
          initModbus(); // Modbus mit neuen Einstellungen initialisieren
          ok = true;
          ausgabeDebug("modus " + String(mbRTUdata.serialBAUD));
        }
      }
      //--- modus ---
      parameter = "select_modus";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        if (iValue.indexOf("SERIAL_") >= 0) {
          iValue.replace("SERIAL_", "");
        }
        mbRTUdata.serialMOD = iValue;

        ausgabeDebug("modus " + String(mbRTUdata.serialMOD));
        initModbus(); // Modbus mit neuen Einstellungen initialisieren
        ok = true;
      }
      //--- regTyp ---
      parameter = "select_regTyp";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        iValue.toLowerCase();
        mbRTUdata.fc = iValue;
        ok = true;
        ausgabeDebug("FC " + String(mbRTUdata.fc));
      }
      //--- SlaveAdresse ---
      parameter = "slaveID";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        if (isNumeric(iValue)) {
          mbRTUdata.remSlaveAdr = iValue.toInt();
          initModbus(); // Modbus mit neuen Einstellungen initialisieren
          ok = true;
          ausgabeDebug("slave " + String(mbRTUdata.remSlaveAdr));
        }
      }
      //--- RegisterAdresse ---
      parameter = "registerAdr";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        if (isNumeric(iValue)) {
          mbRTUdata.regAdr = iValue.toInt();
          ok = true;
          ausgabeDebug("RegAdr.: " + String(mbRTUdata.regAdr));
        }
      }
      //--- Register wert ---
      parameter = "writeRegisterValue";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        mbRTUdata.writeValue = iValue;
        ok = true;
        ausgabeDebug("value: " + String(mbRTUdata.writeValue));
      }
      //--- RegisterAdresse ---
      parameter = "registerScale";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        if (isNumeric(iValue)) {
          mbRTUdata.scale = iValue.toInt();
          ok = true;
          ausgabeDebug("scale: " + String(mbRTUdata.scale));
        }
      }
      //--- Pollen Interval ---
      parameter = "pollTime";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        if (isNumeric(iValue)) {
          mbRTUdata.pollTime = iValue.toInt();
          ok = true;
          ausgabeDebug("pollTime: " + String(mbRTUdata.pollTime));
        }
      }
      //--- Pollen Anzahl ---
      parameter = "pollAnzahl";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        if (isNumeric(iValue)) {
          mbRTUdata.anzPoll = iValue.toInt();
          ok = true;
          ausgabeDebug("anzPoll: " + String(mbRTUdata.anzPoll));
        }
      }
    }

    //********* Modbus TCP *********
    if (fromPage.indexOf("modbus") > 0 && fromPage.indexOf("tcp") > 0) {
      //--- regTyp ---
      parameter = "select_regTyp";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        iValue.toLowerCase();
        mbTCPdata.fc = iValue;
        ok = true;
        ausgabeDebug("FC " + String(mbTCPdata.fc));
      }
      //--- SlaveAdresse ---
      parameter = "slaveID";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        if (isNumeric(iValue)) {
          mbTCPdata.remSlaveAdr = iValue.toInt();
          initModbus(); // Modbus mit neuen Einstellungen initialisieren
          ok = true;
          ausgabeDebug("slave " + String(mbTCPdata.remSlaveAdr));
        }
      }
      //--- RegisterAdresse ---
      parameter = "registerAdr";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        if (isNumeric(iValue)) {
          mbTCPdata.regAdr = iValue.toInt();
          ok = true;
          ausgabeDebug("RegAdr.: " + String(mbTCPdata.regAdr));
        }
      }
      //--- Register wert ---
      parameter = "writeRegisterValue";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        mbTCPdata.writeValue = iValue;
        ok = true;
        ausgabeDebug("value: " + String(mbTCPdata.writeValue));
      }
      //--- RegisterAdresse ---
      parameter = "registerScale";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        if (isNumeric(iValue)) {
          mbTCPdata.scale = iValue.toInt();
          ok = true;
          ausgabeDebug("scale: " + String(mbTCPdata.scale));
        }
      }
      //--- Pollen Interval ---
      parameter = "pollTime";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        if (isNumeric(iValue)) {
          mbTCPdata.pollTime = iValue.toInt();
          ok = true;
          ausgabeDebug("pollTime: " + String(mbTCPdata.pollTime));
        }
      }
      //--- Pollen Anzahl ---
      parameter = "pollAnzahl";
      if (request->hasParam(parameter)) {
        iValue = request->getParam(parameter)->value();
        if (isNumeric(iValue)) {
          mbTCPdata.anzPoll = iValue.toInt();
          ok = true;
          ausgabeDebug("anzPoll: " + String(mbTCPdata.anzPoll));
        }
      }
    }

    request->send_P(200, "text/html", webserver_ModbusRTUpage, variablenBinderHTML);
    //}
  });


  //--- Button Handling ---
  //*** Startseite ***
  // Button: start goto ModbusRTU
  server.on("/start/ModbusRTU", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", webserver_ModbusRTUpage, variablenBinderHTML); //request->send_P(200, "text/html", webserver_ModbusRTUpage, variablenBinderHTML);
    ausgabeDebug(String("BTN: ") + String("/start/ModbusRTU"));
  });
  // Button: start goto ModbusTCP
  server.on("/start/ModbusTCP", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", webserver_ModbusTCPpage, variablenBinderHTML); //request->send_P(200, "text/html", webserver_ModbusRTUpage, variablenBinderHTML);
    ausgabeDebug(String("BTN: ") + String("/start/ModbusTCP"));
  });
  // Button: start goto ModbusBridge
  server.on("/start/ModbusBridge", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", webserver_ModbusBridgePage, variablenBinderHTML); //request->send_P(200, "text/html", webserver_ModbusRTUpage, variablenBinderHTML);
    ausgabeDebug(String("BTN: ") + String("/start/ModbusBridge"));
  });
  // Button: start goto ModbusRepeater
  server.on("/start/ModbusRepeater", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", webserver_ModbusRepeaterPage, variablenBinderHTML); //request->send_P(200, "text/html", webserver_ModbusRTUpage, variablenBinderHTML);
    ausgabeDebug(String("BTN: ") + String("/start/ModbusRepeater"));
  });
  // Button: start goto Einstellungen
  server.on("/start/Einstellungen", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/html", webserver_SettingsPage, variablenBinderHTML); //request->send(200, "text/html", webserver_SettingsPage);
    ausgabeDebug(String("BTN: ") + String("/start/Einstellungen"));
  });
  // Button: start, speichern
  server.on("/start/speichernAllgemein", HTTP_GET, [](AsyncWebServerRequest * request) {
    datenSpeichern();
    request->send_P(200, "text/html", webserver_WelcomePage, variablenBinderHTML); //request->send(200, "text/html", webserver_WelcomePage);
    ausgabeDebug(String("BTN: ") + String("/start/speichernAllgemein"));
  });
  //*** Settings  ***
  // Button: settings, speichern
  server.on("/settings/speichernAllgemein", HTTP_GET, [](AsyncWebServerRequest * request) {
    datenSpeichern();
    request->send_P(200, "text/html", webserver_SettingsPage, variablenBinderHTML); //request->send(200, "text/html", webserver_SettingsPage);
    ausgabeDebug(String("BTN: ") + String("/settings/speichernAllgemein"));
  });
  // Button: settings, laden
  server.on("/settings/ladenAllgemein", HTTP_GET, [](AsyncWebServerRequest * request) {
    datenLaden();
    request->send_P(200, "text/html", webserver_SettingsPage, variablenBinderHTML); //request->send(200, "text/html", webserver_SettingsPage);
    ausgabeDebug(String("BTN: ") + String("/settings/ladenAllgemein"));
  });
  // Button: settings, Einstellungen zurücksetzen
  server.on("/settings/defaultSettings", HTTP_GET, [](AsyncWebServerRequest * request) {
    datenZuruecksetzen();
    request->send_P(200, "text/html", webserver_SettingsPage, variablenBinderHTML); //request->send(200, "text/html", webserver_SettingsPage);
    ausgabeDebug(String("BTN: ") + String("/settings/defaultSettings"));
  });
  // Button: settings, neustart
  server.on("/settings/neustart", HTTP_GET, [](AsyncWebServerRequest * request) {
    //datenSpeichern();
    Serial.println("Neustart in 5s !");
    delay(5000);
    ESP.restart();
    request->send_P(200, "text/html", webserver_SettingsPage, variablenBinderHTML);//request->send(200, "text/html", webserver_SettingsPage);
    ausgabeDebug(String("BTN: ") + String("/settings/neustart"));
  });

  //*** ModbusRTU ***
  // Button: ModbusRTU schreiben
  server.on("/modbusRTU/btn_write", HTTP_GET, [](AsyncWebServerRequest * request) {
    mbRTUdata.doWrite = true;
    request->send_P(200, "text/html", webserver_ModbusRTUpage, variablenBinderHTML);
    ausgabeDebug(String("BTN: ") + String("/modbusRTU/btn_write"));
  });
  // Button: ModbusRTU lesen
  server.on("/modbusRTU/btn_read", HTTP_GET, [](AsyncWebServerRequest * request) {
    mbRTUdata.doRead = true;
    request->send_P(200, "text/html", webserver_ModbusRTUpage, variablenBinderHTML);
    ausgabeDebug(String("BTN: ") + String("/modbusRTU/btn_read"));
  });
  // Button: ModbusRTU start polling
  server.on("/modbusRTU/btn_startPolling", HTTP_GET, [](AsyncWebServerRequest * request) {
    mbRTUdata.doRead = true;
    mbRTUdata.doPoll = true;
    request->send_P(200, "text/html", webserver_ModbusRTUpage, variablenBinderHTML);
    ausgabeDebug(String("BTN: ") + String("/modbusRTU/btn_startPolling"));
  });
  // Button: ModbusRTU stop polling
  server.on("/modbusRTU/btn_stopPolling", HTTP_GET, [](AsyncWebServerRequest * request) {
    mbRTUdata.doRead = false;
    mbRTUdata.doPoll = false;
    request->send_P(200, "text/html", webserver_ModbusRTUpage, variablenBinderHTML);
    ausgabeDebug(String("BTN: ") + String("/modbusRTU/btn_stopPolling"));
  });

  //*** ModbusTCP ***
  // Button: ModbusTCP schreiben
  server.on("/modbusTCP/btn_write", HTTP_GET, [](AsyncWebServerRequest * request) {
    mbRTUdata.doWrite = true;
    request->send_P(200, "text/html", webserver_ModbusTCPpage, variablenBinderHTML);
    ausgabeDebug(String("BTN: ") + String("/ModbusTCP/btn_write"));
  });
  // Button: ModbusTCP lesen
  server.on("/modbusTCP/btn_read", HTTP_GET, [](AsyncWebServerRequest * request) {
    mbRTUdata.doRead = true;
    request->send_P(200, "text/html", webserver_ModbusTCPpage, variablenBinderHTML);
    ausgabeDebug(String("BTN: ") + String("/ModbusTCP/btn_read"));
  });
  // Button: ModbusTCP start polling
  server.on("/modbusTCP/btn_startPolling", HTTP_GET, [](AsyncWebServerRequest * request) {
    mbRTUdata.doRead = true;
    mbRTUdata.doPoll = true;
    request->send_P(200, "text/html", webserver_ModbusTCPpage, variablenBinderHTML);
    ausgabeDebug(String("BTN: ") + String("/ModbusTCP/btn_startPolling"));
  });
  // Button: ModbusTCP stop polling
  server.on("/modbusTCP/btn_stopPolling", HTTP_GET, [](AsyncWebServerRequest * request) {
    mbRTUdata.doRead = false;
    mbRTUdata.doPoll = false;
    request->send_P(200, "text/html", webserver_ModbusTCPpage, variablenBinderHTML);
    ausgabeDebug(String("BTN: ") + String("/ModbusTCP/btn_stopPolling"));
  });


  //--- Daten Handling - GetData nachladen ---
  //*** ModbusRTU SerialMonitor ***
  server.on("/modbusRTU/getDataModbusRTUread", HTTP_GET, [](AsyncWebServerRequest * request) {
    static String data;
    static byte count;
    if (count > 100) {
      count = 0;
      data = "";
    }
    if (mbRTUdata.rcv.length() > 0) {
      data = data + "<br>" + mbRTUdata.rcv;
      mbRTUdata.rcv = "";
      count++;
    }
    request->send(200, "text/plain", data);
  });
  //*** ModbusTCP SerialMonitor ***
  server.on("/modbusTCP/getDataModbusTCPread", HTTP_GET, [](AsyncWebServerRequest * request) {
    static String data;
    static byte count;
    if (count > 100) {
      count = 0;
      data = "";
    }
    if (mbTCPdata.rcv.length() > 0) {
      data = data + "<br>" + mbTCPdata.rcv;
      mbTCPdata.rcv = "";
      count++;
    }
    request->send(200, "text/plain", data);
  });

  server.begin();
  Serial.println("Web server started");
}

void loopWebserver(void) {
  dnsServer.processNextRequest();

}
