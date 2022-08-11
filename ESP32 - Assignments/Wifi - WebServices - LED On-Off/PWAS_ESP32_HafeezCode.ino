String webpage = "";
#include "header.h"
#include "footer.h"

#include <WiFi.h>
const char* ssid = "Perfect vision 4G";
const char* password = "love2030vision";
WiFiServer server(80);
String myHeaderReq;
String output26State = "off";
const int output26 = 26;
unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup() {
  Serial.begin(115200);
  pinMode(output26, OUTPUT);
  digitalWrite(output26, LOW);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(ssid);
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){

  WiFiClient client = server.available();
  if (client) {                             
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          
    String currentLine = "";                
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  
      currentTime = millis();
      if (client.available()) {             
        char c = client.read();             
        myHeaderReq += c;
        if (c == '\n') {                    


            
            if (myHeaderReq.indexOf("GET /26/on") >= 0) {
              Serial.println("GPIO 26 on");
              output26State = "on";
              digitalWrite(output26, HIGH);
            } else if (myHeaderReq.indexOf("GET /26/off") >= 0) {
              Serial.println("GPIO 26 off");
              output26State = "off";
              digitalWrite(output26, LOW);
            }




            
            header_html_function();
            if (output26State=="off") {
              webpage += F("<p><a href='/26/on'><button>ON</button></a></p>");
            }
            else {
              webpage += F("<p><a href='/26/off'><button>OFF</button></a></p>");
            } 
            footer_html_function();
            client.println(webpage);





               
            break;
        } 
      }
    }

    myHeaderReq = "";
    client.stop();
    Serial.println("Client disconnected.");
  }
}
