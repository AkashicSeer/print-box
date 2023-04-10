#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/*Put your SSID & Password*/
const char* ssid = "NETGEAR35";           // Enter SSID here
const char* password = "fuzzyrabbit916";  //Enter Password here

ESP8266WebServer server(80);

bool insideLed1Status = LOW;
bool insideLed2Status = LOW;
bool outsideLedStatus = LOW;
bool boxHeater = LOW;
IPAddress ipAddress;
String setupServer() {

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
   WiFi.begin(ssid, password);
  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");
  
  ipAddress = WiFi.localIP();
  Serial.println(ipAddress);
  server.on("/", handle_OnConnect);
  server.on("/inside_led_1_on", HTTP_POST, handleInsideLed1On);
  server.on("/inside_led_1_off", HTTP_POST, handleInsideLed1Off);
  server.on("/inside_led_2_on", HTTP_POST, handleInsideLed2On);
  server.on("/inside_led_2_off", HTTP_POST, handleInsideLed2Off);
  server.on("/outside_led_on", HTTP_POST, handleOutsideLedOn);
  server.on("/outside_led_off", HTTP_POST, handleOutsideLedOff);
  server.on("/set-heater", HTTP_POST, handleSetHeater);
  server.on("/get_temp_humidity", HTTP_GET, getTempHumidity);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  return ipAddress.toString();
}

void handleRequest() {
  server.handleClient();
}

void handle_OnConnect() {
  Serial.println("Inside handle_OnConnect()");
  server.send(200, "text/html", getHTML());
}


void handleInsideLed1On() {
  Serial.println("Inside LED's #1 on");
  server.send(200, "text/html", "on");
}

void handleInsideLed1Off() {
  Serial.println("Inside LED's #1 off!");
  server.send(200, "text/html", "off");
}
void handleInsideLed2On() {
  Serial.println("Inside LED's #2 on!");
  server.send(200, "text/html", "on");
}

void handleInsideLed2Off() {
  Serial.println("Inside LED's #2 off!");
  server.send(200, "text/html", "off");
}
void handleOutsideLedOn() {
  Serial.println("Outside LED's on!");
  server.send(200, "text/html", "on");
}

void handleOutsideLedOff() {
  Serial.println("Outside LED off!");
  server.send(200, "text/html", "off");
}

void handleSetHeater() {
  Serial.println("Setting heater temp!");
  Serial.println(server.args());
  server.send(200, "text/plain", "on");
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String getHTML() {
  //float insideTempC = getBoxTemperatureInC();
  //float roomTempC = getRoomTemperatureInC();
  //float filamentTempC = getFilamentTempInC();
  float boxTempC = 22.3;
  float roomTempC = 22.5;
  float filamentTempC = 33.5;
  float boxHumidity = 55.4;
  float roomHumidity = 88.4;
  float filamentHumidity = 88.9;
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">";
  ptr += "<title>3D printer box control</title>\n";
  ptr += "<style>html { font-family: Helvetica;}\n";
  ptr += "body{margin-top: 50px;} \n h1 {margin: 20px auto; text-align: center;}\n";
  ptr += ".measurement {margin: 20px auto; text-align: center;}\n";
  ptr += "ul {display: inline-block; text-align: left; font-size: 24px; list-style-type: none;}\n";
  ptr += "span { font-weight: bolder;}\n";
  ptr += "button {border: 2px solid black; color: white; padding: 10px 10px; text-align: center;";
  ptr += "display: inline-block; font-size: 16px; margin: 0px 10px;}\n";
  ptr += ".activeButton {background-color: #4CAF50;}\n";
  ptr += ".inactiveButton {background-color: #c5c5c5;}\n";
  ptr += "form > ul > li {margin: 15px auto;}\n";
  ptr += "form {text-align: center;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP8266 Web Server</h1>";
  ptr += "<h1>Temperatures</h1>";
  ptr += "<div class=\"measurement\">";
  ptr += "<ul>";
  ptr += "<li>Inside box humidity ";
  ptr += "<span id='box-humidity'>" + String(boxHumidity) + "</span>";
  ptr += "</li>";
  ptr += "<li>Inside box temp in C ";
  ptr += "<span id='box-temp-c'>" + String(boxTempC) + "</span>";
  ptr += " Temp in F ";
  ptr += "<span id='box-temp-f'>" + String(convertCtoF(boxTempC)) + "</span>";
  ptr += "</li>";  //end of box temps
  ptr += "<li>Room Humidity ";
  ptr += "<span id='room-humidity'>" + String(roomHumidity) + "</span>";
  ptr += "</li>";
  ptr += "<li>Room temp in C ";
  ptr += "<span id='room-temp-c'>" + String(roomTempC) + "</span>";
  ptr += " Temp in F <span id='room-temp-f'>" + String(convertCtoF(roomTempC)) + "</span>";
  ptr += "</li>";
  ptr += "<li>Filament humidity <span id='filament-humidity'>";
  ptr += String(filamentHumidity) + "</span></li>";
  ptr += "<li>Filament temp in C <span id='filament-temp-c'>" + String(filamentTempC) + "</span>";
  ptr += " Filmanet temp in F <span id='filament-temp-f'>" + String(convertCtoF(filamentTempC)) + "</span></li>";
  ptr += "</ul>\n";
  ptr += "</div>\n";
  ptr += "<h1>Light controls</h1>";
  ptr += "<form>\n";
  ptr += "<ul id='lights'>";
  ptr += "<li>Inside lights #1 ";
  ptr += "<button id='inside-lights-1-on' type='button' class='inactiveButton' >On</button>";
  ptr += "<button id='inside-lights-1-off' type='button' class='activeButton' >Off</button>";
  ptr += "</li>\n";
  ptr += "<li>Inside lights #1";
  ptr += "<button id='inside-lights-2-on' type='button' class='inactiveButton' >On</button>";
  ptr += "<button id='inside-lights-2-off' type='button' class='activeButton' >Off</button>";
  ptr += "</li>\n";
  ptr += "<li>Outside lights ";
  ptr += "<button id='outside-lights-on' type='button' class='inactiveButton'>On</button>";
  ptr += "<button id='outside-lights-off' type='button' class='activeButton' >Off</button>";
  ptr += "</li></ul>\n";
  ptr += "<h1>Temperature control</h1>";
  ptr += "<ul>";
  ptr += "<li><label for='heater-temp'>Ideal temp</label>&nbsp;";
  ptr += "<input id='heater-temp' type='number' min='20' max='60' value='25' /></li>";
  ptr += "<li><button id='save-temps' type='button' class='activeButton' >Save temperature</button></li>";
  ptr += "</ul>";
  ptr += "</form>\n";
  ptr += "</body>\n";
  ptr += "<script>\n";
  ptr += "const lights = document.getElementById('lights');";
  ptr += "const saveTemps = document.getElementById('save-temps');";
  ptr += "saveTemps.addEventListener('click', performButtonAction, false);";
  ptr += "lights.addEventListener('click', performButtonAction, false);";
  ptr += "function performButtonAction(event){\n";
  ptr += "const targetId = event.target.id;\n";
  ptr += "let url = '" + ipAddress.toString() + "';\n";
  ptr += "url += '/' + targetId;\n";
  ptr += "console.log(url);\n";
  ptr += "let myHeaders = new Headers();";
  ptr += "myHeaders.append('Content-Type', 'text/plain');\n";
  ptr += "let requestJson = { method: 'POST', headers: myHeaders};\n";
  ptr += "if(targetId === 'save-temps'){\n";
  ptr += "const heaterTemp = document.getElementById('heater-temp');\n";
  ptr += "requestJson = { method: 'POST', headers: myHeaders, body:{'foo': heaterTemp},};\n";
  ptr += "console.log('temp is ' + heaterTemp.value );\n";
  ptr += "console.log('code to execute save temps');\n";
  ptr += "} else{\n";
  ptr += "console.log('code to turn lights on and off');\n";
  ptr += "}\n";
  ptr += "const request = new Request(url, requestJson);\n";
  ptr += "}\n";//end of function
  ptr += "</script>\n";
  ptr += "</html>\n";
  return ptr;
}

float convertCtoF(float temp) {
  return (temp * 1.8) + 32;
}

float getBoxHumidity() {
  float hdcHumidity = getHdc1080Humidity();
  float bmeHumidity = getBME280Humidity();
  return (hdcHumidity + bmeHumidity) / 2;
}
float getBoxTemperatureInC() {
  float hdcTemp = convertCtoF(getHdc1080TemperatureInC());
  float bmeTemp = convertCtoF(getBME280TempC());
  return (bmeTemp + hdcTemp) / 2;
}

float getRoomTemperatureInC() {
  return getHTU21DTempInC();
}

float getRoomHumidity() {
  float fakeNumber = 1.2;
  return fakeNumber;
}

float getFilamentHumidity() {
  return getHTU21DHumidity();
}

float getFilamentTempInC() {
  return getHTU21DTempInC();
}
String getTempHumidity() {
  float boxTempC;

  return String("");
}