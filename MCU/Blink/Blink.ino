#include <ESP8266WiFi.h>

const char* SSID = "FRITZ!Box 7590 ZV";
const char* PSK = "35119823661631901660";

void initWiFi();

//String home();

WiFiServer server(80);

void setup() {
	Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
	initWiFi();
}

void loop() {
  WiFiClient client = server.available(); 
  digitalWrite(LED_BUILTIN, HIGH);
  if(!client)
    return ; 
  
  if(WiFi.status() != WL_CONNECTED)
    initWiFi();
  
  String request = "";
  while(client.available() ){
    request = client.readStringUntil('\n');
    client.flush();
    Serial.println(request);
    }
    client.print(home());
	  client.stop();

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


                      
}











///////////////////////funktionen

void initWiFi(){
	Serial.print("Connecting to ");
	WiFi.begin(SSID,PSK);
	while(WiFi.status() != WL_CONNECTED){
		delay(500);
	}
	server.begin();
	Serial.println("");
	Serial.println("WiFi connected.");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	return;
}

///////////////////////////////////////////////////////Websites
String home(){
	String ret = "";
		ret += "HTTP/1.1 200 OK\n"							;
		ret += "Content-Type: text/html;charset=UTF-8\n"	;
		ret += "Connection: close\n\n"						;
		ret += "<!DOCTYPE html><html><head></head><body>\n";
		ret += "<h1>Hallo welt</h1>"                  		;
		ret += "";
		ret += "</body></html>\n"							;
		Serial.print(ret);
	return ret ;  
}


  //String antwort = "http/1.x 200 OK\n";
  //antwort += "Content-Type: text/html;charset=UTF-8\n\n";
  
  
  
  
	//client.println("<!DOCTYPE html><html>");
	//client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
	//client.println("<link rel=\"icon\" href=\"data:,\">");
	
	//client.println("HTTP/1.1 200 OK");
	//client.println("Content-type:text/html");
	//client.println("Connection: close");
	//client.println();
