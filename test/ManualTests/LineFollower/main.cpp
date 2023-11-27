/*************************************************************
 * RoboCore - Kit Robo Explorer - Robo Seguidor de Linha
 * Codigo fonte do projeto do robo seguidor de linha do kit.
 * 
 * Monte um circuito com a fita isolante preta inclusa no kit
 * em uma superficie branca e coloque o robo sobre a linha
 * desta pista. O robo ira andar sempre sobre a linha, e, caso 
 * ele saia da pista, ele se mantera parado.
*************************************************************/

//adiciona a biblioteca de controle de motores ao codigo
#include <RoboCore_Vespa.h>
#include "FS.h"

//declaracao do objeto "motores"
VespaMotors motores;

//declaracao dos pinos conectados aos sensores de linha
const int SENSOR_ESQUERDO = 36;
const int SENSOR_DIREITO = 39;

//declaracao das variaveis que armazenam as leituras dos sensores
int leitura_esquerdo = 0;
int leitura_direito = 0;

//declaracao da variavel que armazena o valor de corte para as leituras dos sensores
const int VALOR_CORTE = 3000;
//declaracao da variavel que armazena a velocidade em linha reta do robo
const int VELOCIDADE = 100; 
//declaracao da variavel que armazena o valor que sera somado a velocidade de rotacao dos motores
const int VELOCIDADE_SOMA = 0;
//declaracao da variavel que armazena o valor que sera subtraido da valocidade de rotacao dos motores
const int VELOCIDADE_SUBTRACAO = 70;
//declaracao da variavel que armazena o valor maximo de contagem de parada
const int CONTAGEM_MAXIMA = 10000;
//declaracao da variavel do contador para parar o robo caso ele fuja da pista
int contador_parada = 0;

void setup() {
  Serial.begin(9600);
  //configuracao dos pinos conectados aos sensores como entrada  
  pinMode(SENSOR_ESQUERDO, INPUT);
  pinMode(SENSOR_DIREITO, INPUT);

}

void loop() {

  //realiza a leitura dos sensores
  leitura_esquerdo = analogRead(SENSOR_ESQUERDO);
  leitura_direito = analogRead(SENSOR_DIREITO);

  //verifica se ambas as leituras dos sensores sao maiores que o valor de leitura de corte
  //ou seja se os dois sensores estao sobre a linha da pista
  if((leitura_esquerdo > VALOR_CORTE) && (leitura_direito > VALOR_CORTE)) { //se for verdadeiro
    //movimenta o robo para frente
    motores.forward(VELOCIDADE);
    //Serial.println("frente");
    contador_parada = 0; //zera o contador de parada
  }

  //verifica se ambas as leituras dos sensores sao menores que o valor de leitura de corte
  //ou seja se os dois sensores estao fora da linha da pista
  else if((leitura_esquerdo < VALOR_CORTE) && (leitura_direito < VALOR_CORTE)){//se for verdadeiro
    contador_parada++; //incrementa o contador de parada
  }

  //verifica se apenas a leitura do sensor da direita e menor que o valor de leitura de corte
  //ou seja se apenas o sensor da direta esta sobre a linha da pista
  else if(leitura_direito > VALOR_CORTE) { //se for verdadeiro
    //gira o robo para a esquerda ajustando a velocidade dos motores
    motores.turn(VELOCIDADE+VELOCIDADE_SOMA, VELOCIDADE-VELOCIDADE_SUBTRACAO);
    //Serial.println("esquerda");
    contador_parada = 0; //zera o contador de parada
  }

  //verifica se apenas a leitura do sensor da esquerda e menor que o valor de leitura de corte
  //ou seja se apenas o sensor da esquerda esta sobre a linha da pista
  else if(leitura_esquerdo > VALOR_CORTE) {
    //gira o robo para a direita ajustando a velocidade dos motores
    motores.turn(VELOCIDADE-VELOCIDADE_SUBTRACAO, VELOCIDADE+VELOCIDADE_SOMA);
    //Serial.println("direita");
    contador_parada = 0; //zera o contador de parada
  }

  //verifica se o contador de parada e maior ou igual que o valor de contagem maxima
  //ou seja se o robo ficou muito tempo fora da pista
  if(contador_parada >= CONTAGEM_MAXIMA){ //se for verdadeiro
    motores.stop(); //para o robo
    Serial.println("parado");
    contador_parada = CONTAGEM_MAXIMA; //fixa a contagem de parada
  }

  //realiza um tempo de espera na execucao do codigo
  delay(0); //altere esse valor caso queira diminuir a sensibilidade do robo
  
}