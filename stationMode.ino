//#include <WebServer.h>
#include <WiFi.h>
//#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

//#include "pitches.h"  

#define DHTPIN 26 

#define DHTTYPE    DHT11 

DHT_Unified dht(DHTPIN, DHTTYPE);

float temperatura;
float umidade;

//DHT dht(26, DHT11);

//const char* ssid = "Exception_2G";
//const char* ssid = "SALA-602";// nombre de la red
const char* ssid = "fino";
//const char* ssid = "SETREM-LAB01";
//const char* ssid = "RESTAURANTE";

const char* password = "finodofino";
//const char* password = "exc4pt1oN";

const int luz_azul = 15;
const int luz_branca = 4;
const int luz_vermelha = 13;
// rgb
const int redPin = 17;
const int greenPin = 27;
const int bluePin = 18;

const int presenca = 34;

const int luminosidade = 35;
const int ledLuminosidade = 21;

int acionamento;
const int alarme = 19;
unsigned int frequencia;

//temperatura
//#define DHT11PIN 26
//DHT dht(DHT11PIN, DHT11);

String resposta;

AsyncWebServer server(80);

void ligarAlarme(){
  if(digitalRead(presenca) == HIGH) {
      digitalWrite(alarme, HIGH);
       delay(2000);
  }    
  else{
      digitalWrite(alarme, LOW); 
  }
}

void ligarLedLuminosidade(){
  int valorLuminosidade = analogRead(luminosidade);
  //Serial.println(valorLuminosidade);
  if(valorLuminosidade < 50){
    digitalWrite(ledLuminosidade, HIGH);
    
  }
  else{
    digitalWrite(ledLuminosidade, LOW);
  }
}

void setColor(int red, int green, int blue){
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}

void pegaTempUmid(){
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }
}
void setup() {
  dht.begin();
  Serial.begin(115200);
  pinMode(luz_azul, OUTPUT);
  pinMode(luz_branca, OUTPUT);
  pinMode(luz_vermelha, OUTPUT);
  pinMode(presenca, INPUT);
  pinMode(alarme, OUTPUT);
  pinMode(luminosidade, INPUT);
  pinMode(ledLuminosidade, OUTPUT);
  //ledcAttachPin(alarme, 0);
  //ledcSetup(0, 2000, 1);
  

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
    
    resposta = String("{\"nome\":\""+acao_arduino+"\"}");
    
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
      AsyncWebParameter* requisicaoRed = request->getParam(1);
      String redTexto = requisicaoRed->value();
      int redValor = redTexto.toInt();
      
      AsyncWebParameter* requisicaoGreen = request->getParam(2);
      String greenTexto = requisicaoGreen->value();
      int greenValor = greenTexto.toInt();
      
      AsyncWebParameter* requisicaoBlue = request->getParam(3);
      String blueTexto = requisicaoBlue->value();
      int blueValor = blueTexto.toInt();
      
      Serial.println(redValor);
      Serial.println(greenValor);
      Serial.println(blueValor);
      setColor(redValor, greenValor, blueValor);
    }
    
    if(acao_arduino == "temperatura"){
      //pegaTempUmid();
      resposta = String("{\"nome\":\""+String(temperatura)+"\"}");
    }
    if(acao_arduino == "teste")
    {
        resposta = String("{\"nome\":\"""chegou no teste""\"}");
    }
    
    request->send(200, "application/json", resposta);
    
  });

  server.begin();
}
 
void loop() {
  ligarAlarme();
  ligarLedLuminosidade();

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    //Serial.print(event.temperature);
    temperatura = event.temperature;
    Serial.print(temperatura);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    //Serial.print(event.relative_humidity);
    umidade = event.relative_humidity;
    Serial.print(umidade);
    Serial.println(F("%"));
  }
}
