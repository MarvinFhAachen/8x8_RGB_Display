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
		String request = server_logic(&client);//get request data
		Serial.print(request);
    //<-----------------------------------------------------------------------------------------------------------------------------------------------------respanse funktion hier einbauen auf basis der returnwerte sihe beispiel funktion unten
    
    client.stop();    Serial.println("Client disconnected");//close conection
    Serial.println("");
		}


  
}

String server_logic(WiFiClient* ptr_client){ //soll einen pointer auf das objeckt bekommen 
	                             // Bei einem Aufruf des Servers
    Serial.println("Client available");
    String currentLine = "";                // String definieren für die Anfrage des Clients
    String ret = ""; 
	  bool ret_bool = true;

    while (ptr_client->connected()) { // Loop, solange Client verbunden ist

		if (ptr_client->available()) {
			char c = ptr_client->read();             // Ein (1) Zeichen der Anfrage des Clients lesen
			//Serial.write(c);                    // und es im Seriellen Monitor ausgeben
			header += c;
			if (c == '\n') {                    // bis eine Neue Zeile ausgegeben wird

			  // Wenn der Client eine Leerzeile sendet, ist das Ende des HTTP Request erreicht
			  if (currentLine.length() == 0) {
          
					respanse_example(ptr_client);
					// Den Loop beenden
					break;
				}
			  else { // Bei einer Neuen Zeile, die Variable leeren
				if(ret_bool){
					ret+= currentLine + "\n";
					ret_bool=false;
				}
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

  return ret;
}

void respanse_example(WiFiClient* ptr_client){
	// Der Server sendet nun eine Antwort an den Client
	ptr_client->println("HTTP/1.1 200 OK");
	ptr_client->println("Content-type:text/html");
	ptr_client->println("Connection: close");
	ptr_client->println();
	ptr_client->print("<!DOCTYPE html><html>	<head>		<style>			pre {margin:0 padding:0;}			.pointer{				cursor: pointer;			}			.block1 {				width: 50px;				height: 50px;				border:1px solid;				border-color:gray;				margin:0;				padding:0;				background:red;			}			.spalte0   {				width: wrap;				height:100%;				float: left;				display:inline-block;				margin:0;				padding:0;			}			.farben   {				width: wrap;				height: wrap;				float: left;				border:1px solid;				border-color:gray;				margin-left:10px;				padding:0;				background:black;				color:white;			}			.spectrum-wrapper {			  cursor: crosshair;			  width: 360px;			  position: relative;			  height: 20px;			  user-select: none;			  user-drag: none;			}			.spectrum-layer {			  height: 100%;			  width: 100%;			  background: linear-gradient(				to right,				rgb(255 0 0),				rgb(255 255 0),				rgb(0 255 0),				rgb(0 255 255),				rgb(0 0 255),				rgb(255 0 255),				rgb(255 0 0)			  );			}		</style>	</head>	<body style=\"background: black;\">		<div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick =\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick =\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>		</div>		<div class=\"farben\" onmouseover=\"document.getElementById(\'favcolor\').click();\">			<div>			  <br/>			  Klick here to select a colore:			  <br/><br/>			  <input  type=\"color\" id=\"favcolor\" name=\"favcolor\" value=\"#ff0000\">			  <br/>			  <br/>			  <br/>			  <br/>			  <br/>			  <br/>			  <br/>			  <br/>			  <br/>			  <br/>			  <br/>			  <br/>			  <br/>			  <br/>			  <br/>			  <br/>					  <br/>			</div>			<button onclick=\"senden()\">Send </button>			<button onclick=\"loechen();\" >Delete </button>			<button onclick=\"setColor(\'r\',0);setColor(\'g\',0);setColor(\'b\',0); 		document.getElementById(\'favcolor\').value = \'#000000\';\">	Black </button>			<button onclick=\"setColor(\'r\',255);setColor(\'g\',255);setColor(\'b\',255);	document.getElementById(\'favcolor\').value = \'#FFFFFF\';\">	White </button>			<div id=\"farb_vorschau\" style=\"width: 50px;height: 50px;margin:0;padding:0; float:right;\"></div>		</div>		<script>		let { r, g, b } = {r:255,g:255,b:1};console.log(r+g+b);		function senden(){			let send = \"\";			var all = document.getElementsByClassName(\'block1\');			for (var i = 0; i < all.length; i++) {			  let cur = all[i].style.backgroundColor;				cur = cur.slice(4,-1);				send += cur +\",\";			}			let send2 = send.replace(/\s/g, \'\');			console.log( send2);			    var xmlHttp = new XMLHttpRequest();				xmlHttp.send( null );		}		function loechen(){			var all = document.getElementsByClassName(\'block1\');			for (var i = 0; i < all.length; i++) {			  all[i].style.backgroundColor = \"rgb(0,0,0)\";			}		}		function kli(event){			event.style.backgroundColor = \'rgb(\'+r+\',\'+g+\',\'+b+\')\';		}		function hexTorgb(hex) {			return [\'0x\' + hex[1] + hex[2] | 0, \'0x\' + hex[3] + hex[4] | 0, \'0x\' + hex[5] + hex[6] | 0];		}		function setColor( x ,y ){		if(y>255)			y=255;		if(y<0)			y = 0;		if(x == \"r\"){		r = y;		document.getElementById(\"farb_vorschau\").style.backgroundColor = \"rgb(\"+r+\",\"+g+\",\"+b+\")\";		}		else if(x == \"g\"){		g = y;		document.getElementById(\"farb_vorschau\").style.backgroundColor = \"rgb(\"+r+\",\"+g+\",\"+b+\")\";		}		else if(x == \"b\"){		b = y;		document.getElementById(\"farb_vorschau\").style.backgroundColor = \"rgb(\"+r+\",\"+g+\",\"+b+\")\";		}		}		var mouseDown = 0;		document.body.onmousedown = function() {		  ++mouseDown;		  if(mouseDown>1 || mouseDown<0)			mouseDown = 0 ;		}		document.body.onmouseup = function() {		  --mouseDown;			if(mouseDown>1 || mouseDown<0)				mouseDown = 0 ;		  }		let list = document.getElementsByClassName(\"block1\");			for (var i = 0; i < list.length; i++) {			  list[i].addEventListener(\"mouseover\",function(e){ if(mouseDown) this.style.backgroundColor = \"rgb(\"+r+\",\"+g+\",\"+b+\")\";});			}		var theInput = document.getElementById(\"favcolor\");		var theColor = theInput.value;		theInput.addEventListener(\"input\", function() {		document.getElementById(\"farb_vorschau\").style.backgroundColor = theInput.value;		let test = hexTorgb(theInput.value);		r = test[0];		g = test[1];		b = test[2];		}, false);	</script>	</body></html>");
	// Die Webseite anzeigen
	//ptr_client->println("<!DOCTYPE html><html>");
	//ptr_client->println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
	//ptr_client->println("<link rel=\"icon\" href=\"data:,\"></head>");
	//ptr_client->println("<body><h1 align=\"center\">Hier spricht dein Server! :)</h1></body></html>");

	// Die Antwort mit einer Leerzeile beenden
	ptr_client->println();
  return;
}
