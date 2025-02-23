const char webserver_ModbusRTUpage[] PROGMEM = R"=====(
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
	<title>ModbusGateway</title>

</head>

<body>
  <h1>ModbusRTU</h1>
  
  <label for="Modbus" class="labelBasic" >Modbus</label>
  <div class="group">
<label for="baudrate">baudrate:</label>
<select name="baudrate" class="selectBox" id="select_baudrate">
  <option selected>%mbRTU_BAUDRATE%</option>
  <option value="4800">4800</option>
  <option value="9600">9600</option>
  <option value="115200">115200</option>
</select>

<label for="modus">modus:</label>
<select name="modus" class="selectBox" id="select_modus">
  <option selected>%mbRTU_MODUS%</option>
  <option value="8N1">8N1</option>
  <option value="8E1">8E1</option>
  <option value="8E2">8E2</option>
</select>
<br>
<label for="regTyp">regTyp:</label>
	<select name="regTyp" class="selectBox" id="select_regTyp">
  <option selected>%mbRTU_REG_TYP%</option>
   <option value="IREG">IREG</option>
	  <option value="HREG">HREG</option>
	  <option value="COIL">COIL</option>
    <option value="DINP">DINP</option>
	</select>
 
 <label for="faktor">Faktor:</label>
 <select name="faktor" class="selectBox" id="registerScale">
  <option selected>%mbRTU_INPUT_FAKTOR%</option>
   <option value="1">1</option>
    <option value="10">10</option>
    <option value="100">100</option>
    <option value="1000">1000</option>
  </select>
  
  <br>
 
   Slave ID: <input type="number" id="slaveID" value=%mbRTU_INPUT_SLAVE%  min="1" max="128" class="inputField">
   <br>
   Adr.: <input type="number" id="registerAdr" value=%mbRTU_INPUT_ADR% min="0" max="499999" class="inputField">
   Value: <input type="number" id="writeRegisterValue" value=%mbRTU_INPUT_VALUE% class="inputField">
   </div>  
    <br>

   <label for="write/read" class="labelBasic">write/read</label>
   <div class="group">
   <div class="button-group">
    <form action="/modbusRTU/btn_write" method="get">
      <input class="button buttonXblue" type="submit" value="write">
    </form>
    <form action="/modbusRTU/btn_read" method="get">
      <input class="button buttonXblue" type="submit" value="read">
    </form>
  </div>
   </div>
	
  <br>

	<label for="pollen" class="labelBasic">pollen</label>
	<div class="group">
 <label for="Interval (sek.)">Interval (sek.):</label>
 <select name="pollTime" class="selectBox" id="pollTime">
  <option selected>%mbRTU_pollTime%</option>
   <option value="1">1</option>
    <option value="2">2</option>
    <option value="5">5</option>
    <option value="10">10</option>
  </select>
  &nbsp
  <label for="anzahl">anzahl:</label>
 <select name="pollAnzahl" class="selectBox" id="pollAnzahl">
  <option selected>%mbRTU_pollAnzahl%</option>
   <option value="10">10</option>
    <option value="20">20</option>
    <option value="30">30</option>
    <option value="50">50</option>
    <option value="100">100</option>
  </select>
  
	<div class="button-group">
    <form action="/modbusRTU/btn_startPolling" method="get">
      <input class="button buttonGreen" type="submit" value="start">
    </form>
    <form action="/modbusRTU/btn_stopPolling" method="get">
      <input class="button buttonRed" type="submit" value="stop">
    </form>
  </div>
  </div>
  
  <br>
  
<label class="labelBasic">Monitor / Ausgabe</label>
<div class="card">
  <h1><span id="valueModbusRTUread">nothing</span> </h1><br>
</div>

<script>
setInterval(function() { // Call a function repetatively with 1 Second interval
  getData();
}, 500); // 500ms //1000mSeconds update rate
function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("valueModbusRTUread").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "/modbusRTU/getDataModbusRTUread", true);
  xhttp.send();
}

document.getElementById("select_baudrate").onchange = function() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/ereignis?select_baudrate=" + this.value, true);
  xhr.send();
};
document.getElementById("select_modus").onchange = function() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/ereignis?select_modus=" + this.value, true);
  xhr.send();
};
document.getElementById("select_regTyp").onchange = function() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/ereignis?select_regTyp=" + this.value, true);
  xhr.send();
};

document.getElementById("slaveID").onchange = function() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/ereignis?slaveID=" + this.value, true);
  xhr.send();
};
document.getElementById("registerAdr").onchange = function() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/ereignis?registerAdr=" + this.value, true);
  xhr.send();
};
document.getElementById("writeRegisterValue").onchange = function() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/ereignis?writeRegisterValue=" + this.value, true);
  xhr.send();
};
document.getElementById("registerScale").onchange = function() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/ereignis?registerScale=" + this.value, true);
  xhr.send();
};
document.getElementById("pollTime").onchange = function() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/ereignis?pollTime=" + this.value, true);
  xhr.send();
};
document.getElementById("pollAnzahl").onchange = function() {
  var xhr = new XMLHttpRequest();
  xhr.open("GET", "/ereignis?pollAnzahl=" + this.value, true);
  xhr.send();
};

</script>


  <footer>
    <form action="/" method="get">
    <input class="button buttonBlue" type="submit" value="home">
  </form>
  
    <p>Author: Kai Vollprecht & Jens Bensmann</p>
    <p>Erstellt: Feb.2025</p>
    <p>Änderung: %DATUM_AENDERUNG%</p>
    <p>Version: %NR_VERSION%</p>
    <p>Webbrowseradresse: 192.168.11.1</p>
  </footer>
</body>
</html>
)=====";
