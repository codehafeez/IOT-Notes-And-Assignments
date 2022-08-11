String webpage = "";

#include "header.h"
#include "footer.h"

#include <WiFi.h>
const char* ssid = "Perfect vision 4G"; 
const char* password = "love2030vision";
WiFiServer espServer(80);

void setup() 
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("*");
    delay(100);
  }
  Serial.print("\n");
  Serial.println("Connected Wi-Fi: ");
  Serial.println(WiFi.SSID());
  Serial.print("\n");
  Serial.println("Connected Wi-Fi IP Address : ");
  espServer.begin();
  Serial.println(WiFi.localIP());
}

void loop() {
  
    WiFiClient client = espServer.available();
    if(!client) { return; }
    while (client.connected())
    {
      if (client.available())
      {
          char c = client.read();
          Serial.write(c);

          header_html_function();
          webpage += F("<h2 style='text-align:center;'>This is page body</h2>");                    
          footer_html_function();
          client.println(webpage);
          client.println("<h2 class='txt'>Connected Wi-Fi : "+WiFi.SSID()+"</h2>");
          client.println("<h2 class='txt text1'>Connected Wi-Fi IP : "+WiFi.localIP().toString()+"</h2>");
          break;
      }
    }
   
    client.stop();
    Serial.println("Client disconnected");
}
