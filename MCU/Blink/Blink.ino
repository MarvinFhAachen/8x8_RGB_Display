// Library für WiFi-Verbindung
#include <ESP8266WiFi.h>

// Daten des WiFi-Netzwerks

const char* ssid = "FRITZ!Box 7590 ZV";
const char* password = "35119823661631901660";

// Port des Web Servers auf 80 setzen
WiFiServer server(80);


String server_logic(WiFiClient* client);
void respanse_example();

// Variable für den HTTP Request
String header;

void setup() {
  Serial.begin(115200);

  // Mit dem WiFi-Netzwerk verbinden
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Lokale IP-Adresse im Seriellen Monitor ausgeben und Server starten
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Auf Clients (Server-Aufrufe) warten
	
	if(client){
		server_logic(&client);//get request data
    //<-----------------------------------------------------------------------------------------------------------------------------------------------------respanse funktion hier einbauen auf basis der returnwerte sihe beispiel funktion unten
    
    client.stop();    Serial.println("Client disconnected");//close conection
    Serial.println("");
		}


  
}

String server_logic(WiFiClient* ptr_client){ //soll einen pointer auf das objeckt bekommen 
	                             // Bei einem Aufruf des Servers
    Serial.println("Client available");
    String currentLine = "";                // String definieren für die Anfrage des Clients

    while (ptr_client->connected()) { // Loop, solange Client verbunden ist

		if (ptr_client->available()) {
			char c = ptr_client->read();             // Ein (1) Zeichen der Anfrage des Clients lesen
			Serial.write(c);                    // und es im Seriellen Monitor ausgeben
			header += c;
			if (c == '\n') {                    // bis eine Neue Zeile ausgegeben wird

			  // Wenn der Client eine Leerzeile sendet, ist das Ende des HTTP Request erreicht
			  if (currentLine.length() == 0) {
          
					respanse_example(ptr_client);
					// Den Loop beenden
					break;
				}
			  else { // Bei einer Neuen Zeile, die Variable leeren
				currentLine = "";//<-------------------------------------------------------------------------------------------------------vor löchen auf return werd adieren
			  }
			} 
			else if (c != '\r') {  // alles andere als eine Leerzeile wird
			  currentLine += c;      // der Variable hinzugefüht
			}
		}
    }
    // Variable für den Header leeren
    header = "";

  return "test";
}

void respanse_example(WiFiClient* ptr_client){
	// Der Server sendet nun eine Antwort an den Client
	ptr_client->println("HTTP/1.1 200 OK");
	ptr_client->println("Content-type:text/html");
	ptr_client->println("Connection: close");
	ptr_client->println();

	// Die Webseite anzeigen
	ptr_client->println("<!DOCTYPE html><html>");
	ptr_client->println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
	ptr_client->println("<link rel=\"icon\" href=\"data:,\"></head>");
	ptr_client->println("<body><h1 align=\"center\">Hier spricht dein Server! :)</h1></body></html>");

	// Die Antwort mit einer Leerzeile beenden
	ptr_client->println();
  return;
}
