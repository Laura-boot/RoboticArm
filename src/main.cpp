/*************************************************************
 * Robo Seguidor de Linha com braco acoplado
 * 
 * O robo ira andar sempre sobre a linha, 
 * caso ele saia da pista, ele se mantera parado.
 * caso a esp receba o dado do sensor de carga/descarga, ele se mantem parado por um tempo
 * neste ultimo caso, o braço robotico deve funcionar durante o tempo com o carro parado
*************************************************************/

//adiciona a biblioteca de controle de motores ao codigo
#include <RoboCore_Vespa.h>

VespaMotors motores;

/*************************************************************
 * Variaveis do carro seguidor de linha
*************************************************************/

#define SENSOR_ESQUERDO 36
#define SENSOR_DIREITO 39

int leitura_esquerdo = 0; //leituras dos sensores de linha
int leitura_direito = 0;

#define VALOR_CORTE 3000  //valor de corte para as leituras dos sensores
#define VELOCIDADE 70     //velocidade em linha reta do robo
#define VELOCIDADE_SOMA 30 //valor somado a velocidade de rotacao dos motores
#define VELOCIDADE_SUBTRACAO 50 //valor subtraido da valocidade de rotacao dos motores
#define CONTAGEM_MAXIMA 10000 //valor maximo de contagem de parada
int contador_parada = 0; //contador para parar o robo caso ele fuja da pista

/*************************************************************
 * Variaveis do posionamento do carro
*************************************************************/

int leitura_carga = 0; //leituras dos sensores das entradas dos setores de carga e descarga
int leitura_desgarga = 0;

/*************************************************************
 * Variaveis do braco robotico
*************************************************************/


void setup() {
   
  pinMode(SENSOR_ESQUERDO, INPUT);
  pinMode(SENSOR_DIREITO, INPUT);

}

void loop() {

  //realiza a leitura dos sensores de linha
  leitura_esquerdo = analogRead(SENSOR_ESQUERDO);
  leitura_direito = analogRead(SENSOR_DIREITO);
  //realiza a leitura dos sensores de posicionamento
  //leitura_carga = info de outra esp no setor de carga
  //leitura_descarga = info de outra esp no setor de descarga

  //if(leitura_carga =! 0) {motores.stop(); Arm(ArmState::CARGA));}
  //else if(leitura_descarga =! 0) {motores.stop(); braco(ArmState::DESCARGA));}

  if((leitura_esquerdo > VALOR_CORTE) && (leitura_direito > VALOR_CORTE)) {
    //movimenta o robo para frente
    motores.forward(VELOCIDADE);
    contador_parada = 0; //zera o contador de parada
  }
  else if((leitura_esquerdo < VALOR_CORTE) && (leitura_direito < VALOR_CORTE)){
    contador_parada++; //incrementa o contador de parada
  }
  else if(leitura_direito > VALOR_CORTE) {
    //gira o robo para a esquerda ajustando a velocidade dos motores
    motores.turn(VELOCIDADE+VELOCIDADE_SOMA, VELOCIDADE-VELOCIDADE_SUBTRACAO);
    contador_parada = 0; //zera o contador de parada
  }
  else if(leitura_esquerdo > VALOR_CORTE) {
    //gira o robo para a direita ajustando a velocidade dos motores
    motores.turn(VELOCIDADE-VELOCIDADE_SUBTRACAO, VELOCIDADE+VELOCIDADE_SOMA);
    contador_parada = 0; //zera o contador de parada
  }
  
  if(contador_parada >= CONTAGEM_MAXIMA){
    motores.stop(); //para o robo
    contador_parada = CONTAGEM_MAXIMA; //fixa a contagem de parada
  }

  //realiza um tempo de espera na execucao do codigo
  delay(0); //alterar esse valor diminui a sensibilidade do robo
  
}

enum class ArmState {
  CARGA,
  DESCARGA
};

//definir funcao do braco que recebe a entrada "carga" ou "descarga"
void Arm(ArmState state){
  switch (state) {
    case ArmState::CARGA: {
      
      break;
    }
    case ArmState::DESCARGA: {
      
      break;
    }
  }
}