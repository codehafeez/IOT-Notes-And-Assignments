void header_html_function(){
  webpage = F("<!DOCTYPE HTML>");
  webpage += F("<html>");
  webpage += F("<head>");
  webpage += F("<meta charset='utf-8'>");
  webpage += F("<meta name='viewport' content='width=device-width, initial-scale=1'>");
  webpage += F("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css'>");
  webpage += F("<title>Connected Wifi - ESP32 WebServices</title>");
  webpage += F("<style>");
  webpage += F("body { margin:20px; }");
  webpage += F(".txt { text-align:center; }");
  webpage += F(".text1 { color:#ad594c; text-align:center; }");
  webpage += F("</style>");
  webpage += F("</head>");
  webpage += F("<body>");
  webpage += F("<h1>This is header</h1>");
}
