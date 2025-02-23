const char webserver_ModbusBridgePage[] PROGMEM = R"=====(
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
	<title>Bridge-ModbusGateway</title>

</head>

<body>
  <h1>ModbusBridge (RTU <-> TCP)</h1>




  <script>

</script>

  <footer>
    <form action="/" method="get">
    <input class="button buttonBlue" type="submit" value="home">
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
