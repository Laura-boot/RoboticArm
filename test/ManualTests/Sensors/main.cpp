/*************************************************************
 * RoboCore - Kit Robo Explorer - Leitura dos Sensores de Linha
 * Codigo para ler os valores dos sensores de linha do kit.
*************************************************************/
#include <WiFi.h>
#include <AsyncTCP.h> // https://github.com/me-no-dev/AsyncTCP
#include <ESPAsyncWebServer.h> // https://github.com/me-no-dev/ESPAsyncWebServer
#include <ArduinoJson.h> // https://arduinojson.org/

#include <RoboCore_Vespa.h>

//declaracao dos pinos conectados aos sensores
const int SENSOR_ESQUERDO = 36;
const int SENSOR_DIREITO = 39;

//declaracao das variaveis que armazenam as leituras
int leitura_esquerdo = 0;
int leitura_direito = 0;

void setup() {

  //inicializacao da comunicacao serial
  Serial.begin(9600);

  //configuracao dos pinos conectados aos sensores como entradas
  pinMode(SENSOR_ESQUERDO, INPUT);
  pinMode(SENSOR_DIREITO, INPUT);

}

void loop() {

  //armazena as leituras analogicas dos sensores nas respectivas variaveis
  leitura_esquerdo = analogRead(SENSOR_ESQUERDO);
  leitura_direito = analogRead(SENSOR_DIREITO);

  //exibe os valores no monitor serial
  Serial.print("Valor lido na esquerda: ");
  Serial.print(leitura_esquerdo);
  Serial.print(" | na direita: ");
  Serial.println(leitura_direito);

  delay(100); //aguarda 100 ms para nova leitura

}