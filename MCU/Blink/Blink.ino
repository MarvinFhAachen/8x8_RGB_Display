#include <ESP8266WiFi.h>

const char* SSID = "FRITZ!Box 7590 ZV";
const char* PSK = "35119823661631901660";

void initWiFi();
String home();
String WebsiteHandler();

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


String WebsiteHandler(){

	return "nichts";
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
		ret += "<!DOCTYPE html><html>	<head>		<style>			pre {margin:0 padding:0;}			.pointer{				cursor: pointer;			}			.block1 {				width: 50px;				height: 50px;				border:1px solid;				border-color:gray;				margin:0;				padding:0;				background:red;			}			.spalte0   {				width: wrap;				height:100%;				float: left;				display:inline-block;				margin:0;				padding:0;			}			.farben   {				width: wrap;				height: wrap;				float: left;				border:1px solid;				border-color:gray;				margin-left:10px;				padding:0;				background:black;				color:white;			}			.spectrum-wrapper {			  cursor: crosshair;			  width: 360px;			  position: relative;			  height: 20px;			  user-select: none;			  user-drag: none;			}			.spectrum-layer {			  height: 100%;			  width: 100%;			  background: linear-gradient(				to right,				rgb(255 0 0),				rgb(255 255 0),				rgb(0 255 0),				rgb(0 255 255),				rgb(0 0 255),				rgb(255 0 255),				rgb(255 0 0)			  );			}		</style>	</head>	<body style=\"background: black;\">		<div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick =\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick =\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>			<div class=\"spalte0 pointer \">				<div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>				<div class=\"block1\"onclick=\"kli(this);\"></div>			</div>		</div>		<div class=\"farben\">			<div class=\"spectrum-wrapper\">			  <div class=\"spectrum-layer\"></div>			</div>			<div>			  <br />			  Move your mouse over color spectrum to see respective rgb and hex values			  <br />			  <br />			</div>			<div>Red: <span class=\"red\"></span>	   <input id=\"red_num\" type=\"number\" style=\"padding-left:6px;width:40px;\"  oninput=\"setColor(\'r\', this.value)\" onchange=\"setColor(\'r\', this.value)\" value=\"100\" min=\"0\" max=\"255\"></div>			<div>Green: <span class=\"green\"></span><input id=\"green_num\" type=\"number\" style=\"padding-left:6px;width:40px;\"  oninput=\"setColor(\'g\', this.value)\" onchange=\"setColor(\'g\', this.value)\" value=\"100\" min=\"0\" max=\"255\"></div>			<div>Blue: <span class=\"blue\"></span>  <input id=\"blue_num\" type=\"number\" style=\"padding-left:6px;width:40px;\"  oninput=\"setColor(\'b\', this.value)\" onchange=\"setColor(\'b\', this.value)\" value=\"100\" min=\"0\" max=\"255\"></div>			<div>Hex: <span class=\"hex\"> </div>			<button onclick=\"senden()\">Send </button>			<button onclick=\"loechen();\" >Delete </button>			<button onclick=\"setColor(\'r\',0);setColor(\'g\',0);setColor(\'b\',0); 		document.getElementById(\'red_num\').value = 0;			document.getElementById(\'green_num\').value = 0;				document.getElementById(\'blue_num\').value = 0;\">	Black </button>			<button onclick=\"setColor(\'r\',255);setColor(\'g\',255);setColor(\'b\',255);	document.getElementById(\'red_num\').value = 255;			document.getElementById(\'green_num\').value = 255;			document.getElementById(\'blue_num\').value = 255;\">	White </button>			<div id=\"farb_vorschau\" style=\"width: 50px;height: 50px;margin:0;padding:0; float:right;\"></div>		</div>		<script>		let { r, g, b } = {r:255,g:255,b:1};console.log(r+g+b);		function senden(){			let send = \"\";			var all = document.getElementsByClassName(\'block1\');			for (var i = 0; i < all.length; i++) {			  let cur = all[i].style.backgroundColor;				cur = cur.slice(4,-1);				send += cur +\",\";			}			let send2 = send.replace(/\s/g, \'\');			console.log( send2);		}		function loechen(){			var all = document.getElementsByClassName(\'block1\');			for (var i = 0; i < all.length; i++) {			  all[i].style.backgroundColor = \"rgb(0,0,0)\";			}		}		function kli(event){			event.style.backgroundColor = \'rgb(\'+r+\',\'+g+\',\'+b+\')\';		}		function setColor( x ,y ){		if(y>255)			y=255;		if(y<0)			y = 0;		if(x == \"r\"){		r = y;		document.getElementById(\"farb_vorschau\").style.backgroundColor = \"rgb(\"+r+\",\"+g+\",\"+b+\")\";		}		else if(x == \"g\"){		g = y;		document.getElementById(\"farb_vorschau\").style.backgroundColor = \"rgb(\"+r+\",\"+g+\",\"+b+\")\";		}		else if(x == \"b\"){		b = y;		document.getElementById(\"farb_vorschau\").style.backgroundColor = \"rgb(\"+r+\",\"+g+\",\"+b+\")\";		}		}		const getSpectrumWrapper = () => document.querySelector(\".spectrum-wrapper\");		const spectrumRanges = [		  { from: [255, 0, 0], to: [255, 255, 0] },		  { from: [255, 255, 0], to: [0, 255, 0] },		  { from: [0, 255, 0], to: [0, 255, 255] },		  { from: [0, 255, 255], to: [0, 0, 255] },		  { from: [0, 0, 255], to: [255, 0, 255] },		  { from: [255, 0, 255], to: [255, 0, 0] }		];		const findColorValue = (from, to, leftRatio) => {		  return Math.round(from + (to - from) * leftRatio);		};		const findRgbFromMousePosition = (event) => {		  const wrapper = getSpectrumWrapper();		  const { clientX } = event;		  const { left, width } = wrapper.getBoundingClientRect();		  const leftDistance = Math.min(Math.max(clientX - left, 0), width - 1);		  const totalRanges = spectrumRanges.length;		  const rangeWidth = width / totalRanges;		  const includedRange = Math.floor(leftDistance / rangeWidth);		  const leftRatio = ((leftDistance % rangeWidth) / rangeWidth).toFixed(2);		  const { from, to } = spectrumRanges[includedRange];		  return {			r: findColorValue(from[0], to[0], leftRatio),			g: findColorValue(from[1], to[1], leftRatio),			b: findColorValue(from[2], to[2], leftRatio)		  };		};		const rgbToHex = (r, g, b) => {		  const toHex = (rgb) => {			let hex = Number(rgb).toString(16);			if (hex.length < 2) {			  hex = `0${hex}`;			}			return hex;		  };		  const red = toHex(r);		  const green = toHex(g);		  const blue = toHex(b);		  return `#${red}${green}${blue}`;		};		getSpectrumWrapper().addEventListener(\"mousemove\", (e) => {		   const p = findRgbFromMousePosition(e);		   r = p.r;		   g = p.g;		   b = p.b;		  const hexValue = rgbToHex(r, g, b);		  document.getElementById(\"red_num\").value = r;		  document.getElementById(\"green_num\").value = g;		  document.getElementById(\"blue_num\").value = b;		  document.querySelector(\".hex\").innerText = hexValue;		  document.getElementById(\"farb_vorschau\").style.backgroundColor = hexValue;		});	</script>	</body></html>"                  		;
							
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
