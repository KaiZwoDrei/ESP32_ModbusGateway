const char webserver_SettingsPage[] PROGMEM = R"=====(
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
	max-width: 400px;
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
  width: 120px;
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
.buttonYellow {
	background-color: #ffff00;
	border: 2px solid #ffff00;
  color: #000000;
}
.buttonYellow:hover {
  background-color: #ffff00;
  border: 2px solid #010101;
  color: #000000;
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
	<title>Settings-ModbusGateway</title>

</head>

<body>
  <h1>Einstellungen</h1>

  <label class="labelBasic" >Parameter</label>
  <div class="group">  
  <div class="button-group">
  <form action="/settings/ladenAllgemein" method="get">
    <input class="button buttonXblue" type="submit" value="laden">
  </form>  
  <form action="/settings/speichernAllgemein" method="get">
    <input class="button buttonXblue" type="submit" value="speichern">
  </form>  
  <form action="/settings/defaultSettings" method="get">
    <input class="button buttonYellow" type="submit" value="zurücksetzen">
  </form>
  </div>
  </div>
  <br>
    <label class="labelBasic" >System</label>
  <div class="group"> 
  <form id="neustart" action="/settings/neustart" method="get">
    <input class="button buttonRed" type="submit" value="Neustart">
  </form>
  </div>
  
  <br><br>

  <script>

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
