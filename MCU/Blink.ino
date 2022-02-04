#include <ESP8266WiFi.h>


const char* SSID = "";
const char* PSK = "";

WiFiServer server(80);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   
  initWiFi();
}

void loop() {
  WiFiClient client = server.available(); 
  
  if(!client)
    return ; 
  
  if(WiFi.status != WL_CONNECTED)
    initWiFi();
    
  String request = client.readStringUntil('r');
  client.flush();

  if(request == ""){
    client.stop();
    return;
  }


  //unterscheide zwichen anfragen 
  if(request.indexOf("mode=1")>=0){
    digitalWrite(LED_BUILTIN, HIGH);  
  }
  else if(request.indexOf("mode=0")>=0){
    digitalWrite(LED_BUILTIN, LOW);  
  }

  String antwort = "http/1.x 200 OK\n";
  antwort += "Content-Type: text/html;charset=UTF-8\n\n";
                      
}











///////////////////////funktionen

void initWiFi(){
  WiFi.begin(SSID,PSK);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
  server.begin();
}
