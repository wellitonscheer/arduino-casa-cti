//#include <WebServer.h>
#include <WiFi.h>
//#include <HTTPClient.h>
#include "ESPAsyncWebServer.h"

const char* ssid = "Exception_2G";  // nombre de la red
const char* password = "exc4pt1oN";

const int luz_azul = 15;
const int luz_branca = 4;
const int luz_vermelha = 13;
 
//WebServer server(80);  // puerto por defecto 80
AsyncWebServer server(80);

void setup() {
  pinMode(luz_azul, OUTPUT);
  pinMode(luz_branca, OUTPUT);
  pinMode(luz_vermelha, OUTPUT);
  Serial.begin(115200);

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
    
    //String resposta = "{\"nome\":\""+acao_arduino+"\"}";
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
    

    //request->send(200, "text/plain", "message received");
    request->send(200, "application/json", resposta);
  });

  /*server.on("/luz_azul", LuzAzul);
  server.on("/desliga_luz_azul", DesligaLuzAzul);
  
  server.on("/luz_branca", LuzBranca);
  server.on("/desliga_luz_branca", DesligaLuzBranca);

  server.on("/luz_vermelha", LuzVermelha);
  server.on("/desliga_luz_vermelha", DesligaLuzVermelha);*/

  server.begin();

}
 
void loop() {
  //server.handleClient();
}
 
/*void LuzAzul() {
  Serial.println("chego nessa porcaria");
  const char* respuesta = "{\"nome\":\"LuzAzul\"}";
  digitalWrite(luz_azul, HIGH);
  server.send(200, "application/json", respuesta);
}
void DesligaLuzAzul() {
  Serial.println("passou luz");
  const char* respuesta = "{\"nome\":\"DesligaLuzAzul\"}";
  digitalWrite(luz_azul, LOW);
  server.send(200, "application/json", respuesta);
}



void LuzBranca() {
  Serial.println("passou fungo");
  const char* respuesta = "{\"nome\":\"LuzBranca\"}";
  digitalWrite(luz_branca, HIGH);
  server.send(200, "application/json", respuesta);
}
void DesligaLuzBranca() {
  Serial.println("passou luz");
  const char* respuesta = "{\"nome\":\"DesligaLuzBranca\"}";
  digitalWrite(luz_branca, LOW);
  server.send(200, "application/json", respuesta);
}

void LuzVermelha() {
  Serial.println("passou fungo");
  const char* respuesta = "{\"nome\":\"LuzVermelha\"}";
  digitalWrite(luz_vermelha, HIGH);
  server.send(200, "application/json", respuesta);
}
void DesligaLuzVermelha() {
  Serial.println("passou luz");
  const char* respuesta = "{\"nome\":\"DesligaLuzVermelha\"}";
  digitalWrite(luz_vermelha, LOW);
  server.send(200, "application/json", respuesta);
}*/
