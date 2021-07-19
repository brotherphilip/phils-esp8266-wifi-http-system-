//Libraries to include
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "ESPAsyncWebServer.h"
#include <ESP8266WiFiMulti.h>

//Set instances
ESP8266WiFiMulti WiFiMulti;
AsyncWebServer server(80);
HTTPClient http;
WiFiClient wifiClient;

//name the network name and password as a constant char*
const char* ssid = "WiFi-DE3F";
const char* password = "pizzaslice";

//Sets the Server as a name which references an ip/address on the shared network
const char* serverNameTemp = "http://192.168.1.184";

// sets a name to a http reference on any given ip/address
//in this case, on the clients input called on and off
const char* On = "http://192.168.1.184/get?input1=on";
const char* Off = "http://192.168.1.184/get?input1=off";

void setup() 
{
  //turn on serial ports
  Serial.begin(9600);

 //lets user know connecting effort to network name
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  // begins network conection effort with earlier declared network values
  WiFi.begin(ssid, password);

  //while the network is connecting, print a fullstop every half second
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  //once wifi is connected print succsess message
  if ((WiFiMulti.run() == WL_CONNECTED))
  {
    Serial.print ("connected");
  }
}

void loop() 
{  
  //call function called "one".
  one();
  //delay next line by amount
  delay (1000);
  
  //call function called "two".
  two();
  //delay next line by amount
  delay (1000);
}

void one()
{
  /*begin a function for HTTPClient prepare to open the WiFiClient and
  trigger the address set to On*/ 
  http.begin(wifiClient,On); 
    
    //http.GET triggers the desired event above, and must be run per request.
    http.GET();
  
  }

  void two()
  {
    /*begin a function for HTTPClient prepare to open the WiFiClient and
  trigger the address set to Off*/ 
    http.begin(wifiClient,Off); 

    //http.GET triggers the desired event above, and must be run per request.
    http.GET();
    }
