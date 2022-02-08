// Library für WiFi-Verbindung
#include <ESP8266WiFi.h>


//HILFS SACHEN FÜR LED/////////////////////////////////////////////////////////////////
#include <FastLED.h>
const uint8_t kMatrixWidth = 8;
const uint8_t kMatrixHeight = 8;
#define MAX_DIMENSION ((kMatrixWidth>kMatrixHeight) ? kMatrixWidth : kMatrixHeight)
#define NUM_LEDS (kMatrixWidth * kMatrixHeight)
int myxy(int x, int y){
	if(x>7 ||x<0 || y>7 || y<0 )
		return -1 ; 
	return ((7-x)+(y*8));
}
uint16_t XY( uint8_t x, uint8_t y)
{
  uint16_t i;
  i = (y * kMatrixWidth) + x;
  return i;
}
CRGB leds[kMatrixWidth * kMatrixHeight];
//FILFSSACJEN FÜR LED ENDE/////////////////////////////////////////////////////////////////
//HILFS SACHEN FÜR Webseite/////////////////////////////////////////////////////////////////
const char* ssid = "FRITZ!Box 7590 ZV";
const char* password = "35119823661631901660";
WiFiServer server(80);
String server_logic(WiFiClient* client);
void respanse_example();
String header;
//HILFS SACHEN FÜR Webseiteende/////////////////////////////////////////////////////////////////

//HILFSACHEN FÜR COMPUTERGRAFIK/////////////////////////////////////////////////////////////////
//objeck mit vertices farbe pro vertice matrix verschieben + matrix rotation // vor rendern move und rotate verbinden 


/*
float runden(float x){
	if( abs(x-(int)x) >= (0.5))
        if(x>0)
			return (int)x+1;
		else 
			return (int)x-1;
  else   
      return (int)x;
}
void v_m(float v[3],float m[3][3]){
    float ret[3] = {v[0],v[1],v[2]};
    v[0] = (m[0][0]*ret[0] + m[0][1]*ret[1]+ m[0][2]*ret[2]);
    v[1] = (m[1][0]*ret[0] + m[1][1]*ret[1]+ m[1][2]*ret[2]);    
    v[2] = (m[2][0]*ret[0] + m[2][1]*ret[1]+ m[2][2]*ret[2]);
    
}
void move(int x,int y,float m[3][3]){
    m[0][2] = m[0][2] + x;
    m[1][2] = m[1][2] + y;
}
void m_m2(float m1[3][3], float m2[3][3]){
	float ms[3][3] = {{m1[0][0],m1[0][1],m1[0][2]},{m1[1][0],m1[1][1],m1[1][2]},{m1[2][0],m1[2][1],m1[2][2]}};
	float product = 0.0f;
 int i,j,k;
	for (i = 0; i < 3; i++){
		for (j = 0; j < 3; j++){
			 product = 0; 
			 for (k = 0; k < 3; k++){
				product += ms[i][k] * m2[k][j];
			 }
			 m1[i][j] = product;

		}
	}  
		
	
}
void lh(float m[3][3]){float mr[3][3] = {{0.7,-0.7,0},{0.7,0.7,0},{0,0,1}}; m_m2(m,mr);}
void lg(float m[3][3]){float mr[3][3] = {{0,-1,0},{1,0,0},{0,0,1}}; 		m_m2(m,mr);}
void rh(float m[3][3]){float mr[3][3] = {{0.7,0.7,0},{-0.7,0.7,0},{0,0,1}}; m_m2(m,mr);}
void rg(float m[3][3]){float mr[3][3] = {{0,1,0},{-1,0,0},{0,0,1}}; 		m_m2(m,mr);}
*/

static const int num_vert = 4;
//fix firtel umdrehungen 
class MyObjeck{
	

	private:
	void v_m(float v[3],float m[3][3]){
		float ret[3] = {v[0],v[1],v[2]};
		v[0] = (m[0][0]*ret[0] + m[0][1]*ret[1]+ m[0][2]*ret[2]);
		v[1] = (m[1][0]*ret[0] + m[1][1]*ret[1]+ m[1][2]*ret[2]);    
		v[2] = (m[2][0]*ret[0] + m[2][1]*ret[1]+ m[2][2]*ret[2]);
	}

	void m_m2(float m1[3][3], float m2[3][3]){
		float ms[3][3] = {{m1[0][0],m1[0][1],m1[0][2]},{m1[1][0],m1[1][1],m1[1][2]},{m1[2][0],m1[2][1],m1[2][2]}};
		float product = 0.0f;
	 int i,j,k;
		for (i = 0; i < 3; i++){
			for (j = 0; j < 3; j++){
				 product = 0; 
				 for (k = 0; k < 3; k++){
					product += ms[i][k] * m2[k][j];
				 }
				 m1[i][j] = product;

			}
		}  
			
		
	}


	public:

  MyObjeck(){}
  MyObjeck(int x , int y){move(x,y);}
 
	void lh(){float fmr[3][3] = {{0.7,-0.7,0},{0.7,0.7,0},{0,0,1}}; m_m2(mr,fmr);}
	void lg(){float fmr[3][3] = {{0,-1,0},{1,0,0},{0,0,1}}; 		m_m2(mr,fmr);}
	void rh(){float fmr[3][3] = {{0.7,0.7,0},{-0.7,0.7,0},{0,0,1}}; m_m2(mr,fmr);}
	void rg(){float fmr[3][3] = {{0,1,0},{-1,0,0},{0,0,1}}; 		m_m2(mr,fmr);}
	void move(int x,int y){
		mv[0][2] = mv[0][2] + x;
		mv[1][2] = mv[1][2] + y;
	}
	
	float vert1[num_vert][3] = {{0,0,1},{1,0,1},{-1,0,1},{0,1,1}};
	float mv[3][3]  = {{1,0,0},{0,1,0},{0,0,1}} ;
	float mr[3][3]  = {{1,0,0},{0,1,0},{0,0,1}} ;
	void draw(){
		float cur[3][3] = {{1,0,0},{0,1,0},{0,0,1}} ;
		m_m2(cur,mv);
		m_m2(cur,mr);
		for(int i = 0 ; i<num_vert;i++){
			float curv[3]  ={0,0,0};
			curv[0]=  vert1[i][0];
			curv[1]=  vert1[i][1];
			curv[2]=  vert1[i][2];
			v_m(curv,cur);
			leds[myxy(curv[0],curv[1])] = CRGB(10,10,10);
			FastLED.show();
		}	
	}
};


//HILFSACHEN FÜR COMPUTERGRAFIK ende /////////////////////////////////////////////////////////////////



bool gliter = false;
bool bspektrum = false;

	//MyObjeck tetris1 =  MyObjeck(2,1);
  //MyObjeck tetris2 =  MyObjeck(6,1);
  //MyObjeck tetris3 =  MyObjeck(2,6);
  //MyObjeck tetris4 =  MyObjeck(6,6);
	

void setup() {
  Serial.begin(115200);
  
  FastLED.addLeds<WS2811,2,GRB>(leds,NUM_LEDS);//.setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(50);
  
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

	//tetris.move(2,1);
	//move(2,1, tetris.mv);

}


//
//merke rotation + rotations funktion sucht nur eine matrix aus    0 nicht gedreht  -- links45   ++rechts45  8=0 -8=0 
//



void loop() {
  WiFiClient client = server.available();   // Auf Clients (Server-Aufrufe) warten
	
	if(client){
		String request = server_logic(&client);//get request data
		Serial.print(request);
		parse_answer2(request);

    //<-----------------------------------------------------------------------------------------------------------------------------------------------------respanse funktion hier einbauen auf basis der returnwerte sihe beispiel funktion unten
    
		client.stop();    Serial.println("Client disconnected");//close conection
		Serial.println("");
	}
	if(gliter){
		leds[random(0,63)] = CRGB(random(0,255),random(0,255),random(0,255));
		FastLED.show();

	}
 if(bspektrum){
    sspektrum();
    FastLED.show();

  }
  
	//tetris1.draw();
  //tetris2.draw();
  //tetris3.draw();
 // tetris4.draw();
  //delay(500);
  //tetris1.rg();
  //tetris2.rg();
  //tetris3.rg();
  //tetris4.rg();
  
 // FastLED.clear();
  
  //return ; 
}


void sspektrum(){
  //oben links
  for(int y = 0 ,fy=0; y<4;y++,fy++){
    for(int x = 0 ,fx=0; x<4;x++,fx++){
      leds[XY(x,y)] = CRGB(fy*20+5,fx*20+5,0);
    }
  }
  //unten rechts 
    for(int y = 4,fy=0 ; y<8;y++,fy++){
    for(int x = 4, fx=0; x<8;x++,fx++){
      leds[XY(x,y)] = CRGB(0,fy*20+5,fx*20+5);
    }
  }
    for(int y = 0 ,fy=0; y<4;y++,fy++){
    for(int x = 4, fx=0; x<8;x++,fx++){
      leds[XY(x,y)] = CRGB(fy*20+5,0,fx*20+5);
    }
  }
    for(int y = 4 ,fy=0; y<8;y++,fy++){
    for(int x = 0, fx=0; x<4;x++,fx++){
      leds[XY(x,y)] = CRGB(fy*20+5,fx*20,100);
    }
  }
}
void parse_answer2(String rst){
	    
	int val[192];
	int val_pos = 0; 
	String cur = "";

  if(rst[5]=='s')
    bspektrum = !bspektrum;
  if(rst[5]=='g')
    gliter = !gliter; 
  if(rst[5] !='r' )
      return;
  
	for(int i = 6;i<rst.length();i++){
		if(rst[i] == ' ' )
			break;
		if(rst[i] == ','){
			val[val_pos] = cur.toInt();
			cur = "";
			val_pos++;
		}else{
			cur += rst[i];
		}
	}
	for(int i = 0,y=0 ;i<192; i=i+3 , y++){
		Serial.print("->");
		Serial.print(val[i]);
		Serial.print(",");
		Serial.print(val[i+1]);
		Serial.print(",");
		Serial.println(val[i+2]);
    leds[XY(y/8,y%8)] = CRGB(val[i],val[i+1],val[i+2]);
      
		
	}
  Serial.print("BEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");
  FastLED.show();
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

	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String send = "";	
send +=" \n ";
send +="<!DOCTYPE html> \n ";
send +="<html> \n ";
send +="  <head> \n ";
send +="    <style> \n ";
send +="      pre {margin:0 padding:0;} \n ";
send +="      .pointer{ \n ";
send +="        cursor: pointer; \n ";
send +="      } \n ";
send +="      .block1 { \n ";
send +="        width: 50px; \n ";
send +="        height: 50px; \n ";
send +="        border:1px solid; \n ";
send +="        border-color:gray; \n ";
send +="        margin:0; \n ";
send +="        padding:0; \n ";
send +="        background:red; \n ";
send +="      } \n ";
send +=" \n ";
send +="      .spalte0   { \n ";
send +="        width: wrap; \n ";
send +="        height:100%; \n ";
send +="        float: left; \n ";
send +="        display:inline-block; \n ";
send +="        margin:0; \n ";
send +="        padding:0; \n ";
send +="      } \n ";
send +="      .farben   { \n ";
send +="        width: wrap; \n ";
send +="        height: wrap; \n ";
send +="        float: left; \n ";
send +="        border:1px solid; \n ";
send +="        border-color:gray; \n ";
send +="        margin-left:10px; \n ";
send +="        padding:0; \n ";
send +="        background:black; \n ";
send +="        color:white; \n ";
send +="      } \n ";
send +=" \n ";
send +="      .spectrum-wrapper { \n ";
send +="        cursor: crosshair; \n ";
send +="        width: 360px; \n ";
send +="        position: relative; \n ";
send +="        height: 20px; \n ";
send +="        user-select: none; \n ";
send +="        user-drag: none; \n ";
send +="      } \n ";
send +="      .spectrum-layer { \n ";
send +="        height: 100%; \n ";
send +="        width: 100%; \n ";
send +="        background: linear-gradient( \n ";
send +="        to right, \n ";
send +="        rgb(255 0 0), \n ";
send +="        rgb(255 255 0), \n ";
send +="        rgb(0 255 0), \n ";
send +="        rgb(0 255 255), \n ";
send +="        rgb(0 0 255), \n ";
send +="        rgb(255 0 255), \n ";
send +="        rgb(255 0 0) \n ";
send +="        ); \n ";
send +="      } \n ";
send +=" \n ";
send +=" \n ";
send +="    </style> \n ";
send +="  </head> \n ";
send +=" \n ";
send +=" \n ";
send +="  <body style=\"background: black;\"> \n ";
send +="    <div> \n ";
send +=" \n ";
send +="      <div class=\"spalte0 pointer \"> \n ";
send +="        <div id=\"0_0\" class=\"block1\" onclick =\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="      </div> \n ";
send +="      <div class=\"spalte0 pointer \"> \n ";
send +="        <div id=\"0_0\" class=\"block1\" onclick =\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="      </div> \n ";
send +="      <div class=\"spalte0 pointer \"> \n ";
send +="        <div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="      </div> \n ";
send +="      <div class=\"spalte0 pointer \"> \n ";
send +="        <div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="      </div> \n ";
send +="      <div class=\"spalte0 pointer \"> \n ";
send +="        <div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="      </div> \n ";
send +="      <div class=\"spalte0 pointer \"> \n ";
send +="        <div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="      </div> \n ";
send +="      <div class=\"spalte0 pointer \"> \n ";
send +="        <div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="      </div> \n ";
send +="      <div class=\"spalte0 pointer \"> \n ";
send +="        <div id=\"0_0\" class=\"block1\" onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="        <div class=\"block1\"onclick=\"kli(this);\"></div> \n ";
send +="      </div> \n ";
send +="    </div> \n ";
send +="    <div class=\"farben\" onmouseover=\"document.getElementById(\'favcolor\').click();\"> \n ";
send +="      <div> \n ";
send +="        <br/> \n ";
send +="        Klick here to select a colore:        <br/><br/> \n ";
send +="        <input  type=\"color\" id=\"favcolor\" name=\"favcolor\" value=\"#ff0000\"> \n ";
send +="        <br/> \n ";
send +="        <br/>       <br/> \n ";
send +="        <br/>       <br/> \n ";
send +="        <br/>       <br/> \n ";
send +="        <br/>       <br/> \n ";
send +="        <br/>       <br/> \n ";
send +="        <br/>       <br/>       <br/> \n ";
send +="        <br/>       <br/> \n ";
send +="            <br/> \n ";
send +=" \n ";
send +=" \n ";
send +="      </div> \n ";
send +=" \n ";
send +=" \n ";
send +=" \n ";
send +="      <button onclick=\"senden()\">Send </button> \n ";
send +="      <button onclick=\"loechen();\" >Delete </button> \n ";
send +="      <button onclick=\"setAll();\" >setAll </button> \n ";
send +="      <button onclick=\"setColor(\'r\',0);setColor(\'g\',0);setColor(\'b\',0);    document.getElementById(\'favcolor\').value = \'#000000\';\"> Black </button> \n ";
send +="      <button onclick=\"setColor(\'r\',255);setColor(\'g\',255);setColor(\'b\',255);  document.getElementById(\'favcolor\').value = \'#FFFFFF\';\"> White </button> \n ";
send +="      <div id=\"farb_vorschau\" style=\"width: 50px;height: 50px;margin:0;padding:0; float:right;\"></div> \n ";
send +="    </div> \n ";
send +=" \n ";
send +="    <div> \n ";
send +="    <input type=\"text\" id=\"comand\"></input> \n ";
send +="    <button onclick=\"senden_comand()\">Send </button><br/> \n ";
send +="    <text id=\"answer\" style=\"color:white\">Test test test</text> \n ";
send +="    </div> \n ";
send +=" \n ";
send +="    <script> \n ";
send +=" \n ";
send +="    let { r, g, b } = {r:255,g:255,b:1};console.log(r+g+b); \n ";
send +=" \n ";
send +="    function senden_comand(){ \n ";
send +="      let send = \"r\"; \n ";
send +="      var all = document.getElementById(\'comand\'); \n ";
send +="      var xmlHttp = new XMLHttpRequest(); \n ";
send +="      xmlHttp.open( \"GET\", all.value, false ); \n ";
send +="      xmlHttp.send( null ); \n ";
send +=" \n ";
send +="    } \n ";
send +="    function senden(){ \n ";
send +="      let send = \"r\"; \n ";
send +="      var all = document.getElementsByClassName(\'block1\'); \n ";
send +="      for (var i = 0; i < all.length; i++) { \n ";
send +="        let cur = all[i].style.backgroundColor; \n ";
send +="        cur = cur.slice(4,-1); \n ";
send +="        send += cur +\",\"; \n ";
send +="      } \n ";
send +="      let send2 = send.replace(/\\s/g, \'\'); \n ";
send +="      console.log( send2); \n ";
send +="          var xmlHttp = new XMLHttpRequest(); \n ";
send +="        xmlHttp.open( \"GET\", send2, false ); \n ";
send +="        xmlHttp.send( null ); \n ";
send +=" \n ";
send +="    } \n ";
send +="    function loechen(){ \n ";
send +="      var all = document.getElementsByClassName(\'block1\'); \n ";
send +="      for (var i = 0; i < all.length; i++) { \n ";
send +="        all[i].style.backgroundColor = \"rgb(0,0,0)\"; \n ";
send +="      } \n ";
send +="    } \n ";
send +="    function setAll(){ \n ";
send +="      var all = document.getElementsByClassName(\'block1\'); \n ";
send +="      for (var i = 0; i < all.length; i++) { \n ";
send +="        all[i].style.backgroundColor = \'rgb(\'+r+\',\'+g+\',\'+b+\')\'; \n ";
send +="      } \n ";
send +="    } \n ";
send +="    function kli(event){ \n ";
send +="      event.style.backgroundColor = \'rgb(\'+r+\',\'+g+\',\'+b+\')\'; \n ";
send +="    } \n ";
send +="    function hexTorgb(hex) { \n ";
send +="      return [\'0x\' + hex[1] + hex[2] | 0, \'0x\' + hex[3] + hex[4] | 0, \'0x\' + hex[5] + hex[6] | 0]; \n ";
send +="    } \n ";
send +="    function setColor( x ,y ){ \n ";
send +="    if(y>255) \n ";
send +="      y=255; \n ";
send +="    if(y<0) \n ";
send +="      y = 0; \n ";
send +="    if(x == \"r\"){ \n ";
send +="    r = y; \n ";
send +="    document.getElementById(\"farb_vorschau\").style.backgroundColor = \"rgb(\"+r+\",\"+g+\",\"+b+\")\"; \n ";
send +="    } \n ";
send +="    else if(x == \"g\"){ \n ";
send +="    g = y; \n ";
send +="    document.getElementById(\"farb_vorschau\").style.backgroundColor = \"rgb(\"+r+\",\"+g+\",\"+b+\")\"; \n ";
send +="    } \n ";
send +="    else if(x == \"b\"){ \n ";
send +="    b = y; \n ";
send +="    document.getElementById(\"farb_vorschau\").style.backgroundColor = \"rgb(\"+r+\",\"+g+\",\"+b+\")\"; \n ";
send +="    } \n ";
send +="    } \n ";
send +=" \n ";
send +=" \n ";
send +=" \n ";
send +="    var mouseDown = 0; \n ";
send +="    document.body.onmousedown = function() { \n ";
send +="      ++mouseDown; \n ";
send +="      if(mouseDown>1 || mouseDown<0) \n ";
send +="      mouseDown = 0 ; \n ";
send +="    } \n ";
send +="    document.body.onmouseup = function() { \n ";
send +="      --mouseDown; \n ";
send +="      if(mouseDown>1 || mouseDown<0) \n ";
send +="        mouseDown = 0 ; \n ";
send +="      } \n ";
send +="    let list = document.getElementsByClassName(\"block1\"); \n ";
send +="      for (var i = 0; i < list.length; i++) { \n ";
send +="        list[i].addEventListener(\"mouseover\",function(e){ if(mouseDown) this.style.backgroundColor = \"rgb(\"+r+\",\"+g+\",\"+b+\")\";}); \n ";
send +=" \n ";
send +="      } \n ";
send +=" \n ";
send +=" \n ";
send +="    var theInput = document.getElementById(\"favcolor\"); \n ";
send +="    var theColor = theInput.value; \n ";
send +="    theInput.addEventListener(\"input\", function() { \n ";
send +=" \n ";
send +=" \n ";
send +="    document.getElementById(\"farb_vorschau\").style.backgroundColor = theInput.value; \n ";
send +="    let test = hexTorgb(theInput.value); \n ";
send +="    r = test[0]; \n ";
send +="    g = test[1]; \n ";
send +="    b = test[2]; \n ";
send +=" \n ";
send +="    }, false); \n ";
send +=" \n ";
send +=" \n ";
send +="  </script> \n ";
send +="  </body> \n ";
send +="</html> \n ";





ptr_client->print(send);

	
	
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Die Webseite anzeigen
	//ptr_client->println("<!DOCTYPE html><html>");
	//ptr_client->println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
	//ptr_client->println("<link rel=\"icon\" href=\"data:,\"></head>");
	//ptr_client->println("<body><h1 align=\"center\">Hier spricht dein Server! :)</h1></body></html>");

	// Die Antwort mit einer Leerzeile beenden
	ptr_client->println();
  return;
}


//void setup() {
// // groesse des arrays ermitteln
// int zufall = random(2,5);
//
// //erstmal nur ein zeiger auf das array
// int* zufallsarray;
//  
//  //speicher in der passenden groesse reservieren
//  zufallsarray = (int*)malloc(zufall*(sizeof(int)));
//
//  //an allen stellen auf 0 setzen (optional)
//  for (int i=0;i<zufall;i++) {
//    zufallsarray[0] = 1;
//  }
//}
//...
//void loop() {
//    ....
