const char webserver_WelcomePage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<style>
.card{
    max-width: 300px;
     min-height: 350px;
     background: #02b875;
     padding: 0px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
.label {
  text-align: left;
  text-decoration: none;
  font-size: 16px;
 }
 .labelBasic {
  text-align: left;
  text-decoration: none;
  font-size: 16px;
  font-weight: 1000;
}
.rahmen{
  border: 5px outset red;
  background-color: lightblue;    
  text-align: center;
}
.group{
	max-width: 300px;
	background-color: #DCDCDC; 
     margin:0px 20px;
	padding: 0px	
}
.inputField {
  width: 50px;
  height: 20px;
}
.inputField_IP{
  width: 30px;
  height: 20px;
}
.selectBox {
  width: 65px;
  height: 20px;
}
.button-group {
         display: flex;
      }
.button {
  width: 60px;
  height: 30px;
  border: 2px solid;
  color: white;
  //padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  font-size: 16px;  
  cursor: pointer;
  margin: 2px 2px;
  display: inline-block;
}
.buttonStaticSize {
  width: 180px;
  height: 30px;
  border: 2px solid;
  color: white;
  //padding: 15px 32px;
  text-align: center;
  text-decoration: none;
  font-size: 16px;  
  cursor: pointer;
  margin: 2px 2px;
  display: inline-block;
}
.buttonGreen {
background-color: #04AA6D;
 border: 2px solid #04AA6D;
}
.buttonGreen:hover {
  background-color: #04AA6D;
  border: 2px solid #010101;
  color: white;
}
.buttonBlue {
background-color: #008CBA;
 border: 2px solid #008CBA;
}
.buttonBlue:hover {
  background-color: #008CBA;
  border: 2px solid #010101;
  color: white;
}
.buttonRed {
background-color: #ff0000;
 border: 2px solid #ff0000;
}
.buttonRed:hover {
  background-color: #ff0000;
  border: 2px solid #010101;
  color: white;
}
.buttonXblue {
background-color: #0000EE;
 border: 2px solid #0000EE;
}
.buttonXblue:hover {
  background-color: #0000EE;
  border: 2px solid #010101;
  color: white;
}
</style>

<head>
	<meta name="viewport" content="width=device-width, initial-scale=1.0" charset="utf-8">
	<title>Start-ModbusGateway</title>

</head>

<body>
  <h1>ModbusGateway</h1>
  <p>not for permanent site installation</p>
  <br>
    
  <form action="/start/ModbusRTU" method="get">
    <input class="buttonStaticSize buttonGreen" type="submit" value="Modbus RTU">
  </form>
  <form action="/start/ModbusTCP" method="get">
    <input class="buttonStaticSize buttonGreen" type="submit" value="Modbus TCP">
  </form>
  <form action="/start/ModbusBridge" method="get">
    <input class="buttonStaticSize buttonGreen" type="submit" value="Modbus Bridge">
  </form>
  <form action="/start/ModbusRepeater" method="get">
    <input class="buttonStaticSize buttonGreen" type="submit" value="Modbus Repeater">
  </form>
  <form action="/start/Einstellungen" method="get">
    <input class="buttonStaticSize buttonBlue" type="submit" value="Service">
  </form>

  <br>
  <br>
  
  <form action="/start/speichernAllgemein" method="get" hidden>
    <input class="button buttonRed" type="submit" value="speichern">
  </form>
  
  <footer>
    <p>Author: Kai Vollprecht & Jens Bensmann</p>
    <p>Erstellt: Feb.2025</p>
    <p>Änderung: %DATUM_AENDERUNG%</p>
    <p>Version: %NR_VERSION%</p>
    <p>Webbrowseradresse: 192.168.11.1</p>
  </footer>

</body>
</html>
)=====";
