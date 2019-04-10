/* in this code we are using multi wifi function. */



#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include<ESP8266mDNS.h>
#include<ESP8266WiFiMulti.h>
ESP8266WiFiMulti wifiMulti;
MDNSResponder mdns;
ESP8266WebServer server;

char* ssid = "SM";
char* password = "Shivam12";
char* Ssid ="EARL";
IPAddress ip(192,168,11,4);
IPAddress gateway(192,168,11,1);
IPAddress subnet(255,255,255,0);
int light1 =D2;
int light2 =D3;
int light3 =D4;
int light4 =D5;
char webpage[] PROGMEM = R"====(
<html>
<head>
</head>
<body>

<button>
<a href=\l1>Light 1
</a>
</button>
<button>
<a href=\l2>Light 2
</a>
</button>
<button>
<a href=\l3>light 3
</a>
</button>
<button>
<a href=\l4>light 4
</a>
</button>

</body>
</html>
)====";

  void light_1()
{
  digitalWrite(light1,!digitalRead(light1));
  server.send_P(200,"text/html",webpage);
  
  }
  void light_2()
{
  digitalWrite(light2,!digitalRead(light2));
  server.send_P(200,"text/html",webpage);
  
  }
  void light_3()
{
  digitalWrite(light3,!digitalRead(light3));
  server.send_P(200,"text/html",webpage);
  
  }
  void light_4()
{
  digitalWrite(light4,!digitalRead(light4));
  server.send_P(200,"text/html",webpage);
  
  }
void setup() {
 
  pinMode(light1,OUTPUT);
  pinMode(light2,OUTPUT);
  pinMode(light3,OUTPUT);
  pinMode(light4,OUTPUT);
  WiFi.mode(WIFI_AP_STA);
  wifiMulti.addAP(ssid,password);
   wifiMulti.addAP("Moto G(4)","qequzatup#123");
     Serial.begin(115200);
  if(mdns.begin("roboticslab",WiFi.localIP()))
  {
    Serial.println("MDNS Responder Started");
  }

  server.on("/",[](){server.send_P(200,"text/html",webpage);});
  server.on("/l1",light_1);
  server.on("/l2",light_2);
  server.on("/l3",light_3);
  server.on("/l4",light_4);
  server.begin();
  MDNS.addService("http","tcp",80);
  WiFi.softAPConfig(ip,gateway,subnet);
  WiFi.softAP(Ssid,password);
}

void loop() {
  if(wifiMulti.run()!=WL_CONNECTED)
  {
    Serial.println(".");
    delay(500);
  }
  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) {
        Serial.println("");
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
}
  server.handleClient();


}


