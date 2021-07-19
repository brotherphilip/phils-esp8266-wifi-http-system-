#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#else
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>


// Set your Static IP address, gateway and subnet adresses
IPAddress local_IP(192, 168, 1, 184);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);

//Initiate a AsyncWebSever, Server;
AsyncWebServer server(80);

//NETWORK CREDENTIALS
const char* ssid = "WiFi-DE3F";
const char* password = "pizzaslice";

//names the input/s
const char* PARAM_INPUT_1 = "input1";

// HTML web page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    input1: <input type="text" name="input1">
    <input type="submit" value="Submit">
  </form><br>
</body></html>)rawliteral";

//to alert if request not found, to avoid infinate loop
void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
 
// Set your Gateway IP address
if(!WiFi.config(local_IP, gateway, subnet)) {
  Serial.println("STA Failed to configure");}

  //begin serial port
  Serial.begin(9600);
  //sets wifi mode as a station
  WiFi.mode(WIFI_STA);
  //begin the wifi using network credentials
  WiFi.begin(ssid, password);

  //if it fails. say failed
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
  Serial.println("WiFi Failed!");
  return;
  }
  Serial.println();

  //if it worked. print newly set ip address if not made static at top of script
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

//set pin mode of "pin number" to output
  pinMode (5,OUTPUT);
    
  
//  Send web page with input fields to client
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
 {
  request->send_P(200, "text/html", index_html);
 });

// Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
   request->send_P(200, "text/html", index_html);
    String inputMessage;
    String inputParam;
    
  
    if (request->hasParam(PARAM_INPUT_1)) {
      
       inputMessage = request->getParam(PARAM_INPUT_1)->value();
       inputParam = PARAM_INPUT_1;
      
        Serial.println (PARAM_INPUT_1);
        Serial.println(inputMessage);
       
       
       if (inputMessage == "ON" || inputMessage == "on" )
         {
            On();
         }
         if (inputMessage == "OFF" || inputMessage == "off" )
         {
            Off();
         }
       }
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
   
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() 

{
  
}

void On()
{
  digitalWrite (5 ,HIGH);
}

void Off ()
{
   digitalWrite (5 ,LOW);
}
