#include <WiFi.h>              
#include <ESP32WebServer.h>    
#include <SD.h> 


const char* ssid = "Perfect vision 4G";
const char* password = "love2030vision";
ESP32WebServer server(80);
String webpage = "";
bool SD_present = false;



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("\nConnected to "+WiFi.SSID()+" Use IP address: "+WiFi.localIP().toString()); 


  
  Serial.print(F("Initializing SD card...")); 
  if (!SD.begin(5)) { 
    Serial.println(F("Card failed or not present, no SD Card data logging possible..."));
    SD_present = false; 
  } 
  else {
    Serial.println(F("Card initialised... file access enabled..."));
    SD_present = true; 
  }


  server.on("/",         HomePage);
  server.on("/download", File_Download);
  server.begin();
  Serial.println("HTTP server started");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void loop(){
  server.handleClient();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void HomePage(){  
  webpage  = F("<!DOCTYPE html><html><head><title>File Server</title></head><body>"); 
  webpage += F("<a href='/download'>Download File</a></body></html>");
  server.sendContent(webpage);
  webpage = "";
  server.sendContent("");
  server.client().stop(); 
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void File_Download(){ 
  if (server.args() > 0 ) { 
    if (server.hasArg("download")) SD_file_download(server.arg(0));
  }
  else SelectInput("File Download","Enter filename to download","download","download");
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void SD_file_download(String filename){
  if (SD_present) { 
    File download = SD.open("/"+filename);
    if (download) {
      server.sendHeader("Content-Type", "text/text");
      server.sendHeader("Content-Disposition", "attachment; filename="+filename);
      server.sendHeader("Connection", "close");
      server.streamFile(download, "application/octet-stream");
      download.close();
    } else ReportFileNotPresent("download"); 
  } else ReportSDNotPresent();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void SelectInput(String heading1, String heading2, String command, String arg_calling_name){
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate"); 
  server.sendHeader("Pragma", "no-cache"); 
  server.sendHeader("Expires", "-1"); 
  server.setContentLength(CONTENT_LENGTH_UNKNOWN); 
  server.send(200, "text/html", "");
  
  webpage  = F("<!DOCTYPE html><html><head><title>File Server</title></head><body>"); 
  webpage += F("<FORM action='/");
  webpage += command + "' method='post'>"; 
  webpage += F("<input type='text' name='"); 
  webpage += arg_calling_name;
  webpage += F("' value=''><br>");
  webpage += F("<type='submit' name='"); 
  webpage += arg_calling_name; 
  webpage += F("' value=''><br><br>");
  webpage += F("</body></html>");
  
  server.sendContent(webpage);
  webpage = "";
  server.sendContent("");
  server.client().stop(); 
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ReportSDNotPresent(){
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate"); 
  server.sendHeader("Pragma", "no-cache"); 
  server.sendHeader("Expires", "-1"); 
  server.setContentLength(CONTENT_LENGTH_UNKNOWN); 
  server.send(200, "text/html", ""); 

  
  webpage  = F("<!DOCTYPE html><html><head><title>File Server</title></head><body>"); 
  webpage += F("<h3>No SD Card present</h3></body></html>");

  
  server.sendContent(webpage);
  webpage = "";
  server.sendContent("");
  server.client().stop(); 
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ReportFileNotPresent(String target){
  server.sendHeader("Cache-Control", "no-cache, no-store, must-revalidate"); 
  server.sendHeader("Pragma", "no-cache"); 
  server.sendHeader("Expires", "-1"); 
  server.setContentLength(CONTENT_LENGTH_UNKNOWN); 
  server.send(200, "text/html", ""); 

  
  webpage  = F("<!DOCTYPE html><html><head><title>File Server</title></head><body>"); 
  webpage += F("<h3>File does not exist</h3></body></html>");

  
  server.sendContent(webpage);
  webpage = "";
  server.sendContent("");
  server.client().stop(); 
}
