#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include<ESP8266mDNS.h>
#include <WiFiClient.h> 
MDNSResponder mdns;
ESP8266WebServer server(80);


char* password = "12345678";
char* ssid ="tinkering_lab";

int light1 =16;
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

  Serial.begin(115200);
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

 
  

  server.on("/",[](){server.send_P(200,"text/html",webpage);});
  server.on("/l1",light_1);
  server.on("/l2",light_2);
  server.on("/l3",light_3);
  server.on("/l4",light_4);
  server.begin();

}

void loop() {

  server.handleClient();


}


