 #include<ESP8266WiFi.h>
#include "ThingSpeak.h"
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include <ArduinoJson.h>
const char* ssid = "chpr";//Replace with your network SSID
const char* password = "prudhvi9915";//Replace with your network password
unsigned long Channel_ID = 1229480; // Your Channel ID
const char * myWriteAPIKey = "691REHCVCRATE3YL"; //Your write API key
ESP8266WebServer server(80);
String page = "";
int data1, data2, data3;
const int Field_Number_1 = 1;
const int Field_Number_2 = 2;
const int Field_Number_3 = 3;
WiFiClient  client;

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);

while (WiFi.status() != WL_CONNECTED)
  {
  delay(500);
  Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  server.on("/", []()
  {
    page = "<html><head><title>Embedded System project</title></head><style type=\"text/css\">";
    page += "table{border-collapse: collapse;}th {background-color:  green ;color: white;}table,td {border: 4px solid black;font-size: x-large;";
    page += "text-align:center;border-style: groove;border-color: rgb(255,0,0);}</style><body><center>";
    page += "<h1>Smart Irrigation System</h1><br><br><table style=\"width: 1200px;height: 450px;\"><tr>";
    page += "<th>Parameters</th><th>Value</th><th>Units</th></tr><tr><td>Soil Moisture</td><td>"+String(data1)+"</td><td>bars</td></tr>";
    page += "<tr><td>Water level in tank 1</td><td>"+String(data2)+"</td><td>m</td></tr><tr><td>Water level in tank 2</td><td>"+String(data3)+"</td><td>m</td>";
    page += "<meta http-equiv=\"refresh\" content=\"3\">";
    server.send(200, "text/html", page);
  });
  server.begin();
}
void loop()
{
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(Serial);
  if (root == JsonObject::invalid())
  {
    return;
    Serial.println("invalid");
  }
  data1 = root["a1"];
  data2 = root["a2"];
  data3 = root["a3"];
  Serial.println(data1);
  Serial.println(data2);
  Serial.println(data3);
  upload();

  server.handleClient();
}
void upload()
{
  ThingSpeak.writeField(Channel_ID, Field_Number_1, data1, myWriteAPIKey);
  delay(1000);
  ThingSpeak.writeField(Channel_ID, Field_Number_2, data2, myWriteAPIKey);
  delay(1000);
  ThingSpeak.writeField(Channel_ID, Field_Number_3, data3, myWriteAPIKey);
  delay(1000);
  

}
