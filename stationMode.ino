//#include <WebServer.h>
#include <WiFi.h>
//#include <HTTPClient.h>
#include "ESPAsyncWebServer.h"

const char* ssid = "Exception_2G";
//const char* ssid = "SALA-602";// nombre de la red
//const char* ssid = "fino";
//const char* ssid = "SETREM-LAB01";

//const char* password = "finodofino";
const char* password = "exc4pt1oN";

const int luz_azul = 15;
const int luz_branca = 4;
const int luz_vermelha = 13;
// rgb
const int redPin = 17;
const int greenPin = 27;
const int bluePin = 18;

 
//WebServer server(80);  // puerto por defecto 80
AsyncWebServer server(80);

void setColor(int red, int green, int blue)
  {
    #ifdef COMMON_ANODE
      red = 255 - red;
      green = 255 - green;
      blue = 255 - blue;
    #endif
    analogWrite(redPin, red);
    analogWrite(greenPin, green);
    analogWrite(bluePin, blue);  
  }
  /*void ligarColors(){
    setColor(255, 255, 255);
    delay(1000);
    setColor(80, 0, 80);  // purple
    delay(1000);
    setColor(255, 0, 0);  // red
    delay(1000);
    setColor(0, 255, 0);  // green
    delay(1000);
    setColor(0, 0, 255);  // blue
    delay(1000);
    setColor(255, 255, 0);  // yellow
    delay(1000);  
    
      // aqua
    
  }*/


void setup() {
  pinMode(luz_azul, OUTPUT);
  pinMode(luz_branca, OUTPUT);
  pinMode(luz_vermelha, OUTPUT);
  Serial.begin(115200);

  //WiFi.begin(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());  // imprimimos la ip
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    int paramsNr = request->params();
    //Serial.println(request);
    Serial.println("params: ");
    Serial.println(paramsNr);
    
    AsyncWebParameter* p = request->getParam(0);
    String acao_arduino = p->value();

    Serial.println("acao: ");
    Serial.println(acao_arduino);
    
    String resposta = String("{\"nome\":\""+acao_arduino+"\"}");
    if(acao_arduino == "luz_azul"){
      digitalWrite(luz_azul, HIGH);
    }
    if(acao_arduino == "desliga_luz_azul"){
      digitalWrite(luz_azul, LOW);
    }
    if(acao_arduino == "luz_branca"){
      digitalWrite(luz_branca, HIGH);
    }
    if(acao_arduino == "desliga_luz_branca"){
      digitalWrite(luz_branca, LOW);
    }
    if(acao_arduino == "luz_vermelha"){
      digitalWrite(luz_vermelha, HIGH);
    }
    if(acao_arduino == "desliga_luz_vermelha"){
      digitalWrite(luz_vermelha, LOW);
    }
    if(acao_arduino == "led_rgb"){
      setColor(255, 255, 0);
    }
    request->send(200, "application/json", resposta);
    
  });

  server.begin();
  

}
 
void loop() {
  
}
