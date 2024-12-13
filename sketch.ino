#include <WiFi.h>
#include <HTTPClient.h>

#define led_amarelo 9 // Pino utilizado para controle do led amarelo
#define led_verde 2 // Pino utilizado para controle do led verde
#define led_vermelho 40 // Pino utilizado para controle do led vermelho

uint8_t buttonPin = 18;  // pino do botao


uint8_t ldrPin = 4;  // pino do sensor ldr

// variaveis de tempo
unsigned long tempoAtual = 0;
unsigned long ultimaMedidaAmareloPisca = 0;
unsigned long tempoTroca = 0;
unsigned long horaEntrouNoBotao = 0;

bool botao_apertou = false;
uint8_t num_semaforo = 0;
bool pisca = false;


void setup() {

  // Configuração inicial dos pinos para controle dos leds como OUTPUTs (saídas) do ESP32
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_verde, OUTPUT);
  pinMode(led_vermelho, OUTPUT);

  // Inicialização das entradas
  pinMode(buttonPin, INPUT);
  pinMode(ldrPin, INPUT);


  digitalWrite(led_amarelo, LOW);
  digitalWrite(led_verde, LOW);
  digitalWrite(led_vermelho, LOW);

  Serial.begin(9600); // Configuração para debug por interface serial entre ESP e computador com baud rate de 9600

}

void loop() {
  tempoAtual = millis();
  uint8_t ldrstatus = digitalRead(ldrPin); // verifica o estado do sensor de luminosidade
  bool estado_botao = digitalRead(buttonPin); // verifica o estado do botão
  // ativa modo noturno
  if (ldrstatus == LOW) {
    Serial.println("Tá de noite");
    // logica para contar o tempo do piscar o led amarelo  
    if (tempoAtual - ultimaMedidaAmareloPisca >= 1000) {
      pisca = !pisca;
      ultimaMedidaAmareloPisca = tempoAtual;
    }
    // pisca o led
    if (pisca) {
      digitalWrite(led_amarelo, HIGH);
    }
    else {
      digitalWrite(led_amarelo, LOW);
    }
    tempoTroca = tempoAtual;

  } else {
    Serial.println("Tá claro");
    if(tempoAtual - tempoTroca >= 5000){
      num = num +1
    }
    switch (num_semaforo) {
      case 0:
        if (tempoAtual - tempoTroca >= 5000) {
          tempoTroca = tempoAtual;
          num_semaforo = 1;
          break;
        } else {
          Serial.print("Vermelho");
          digitalWrite(led_verde, LOW);
          digitalWrite(led_amarelo, LOW);
          digitalWrite(led_vermelho, HIGH);
        }
      case 1:
        Serial.print("Amarelo");
        digitalWrite(led_verde, LOW);
        digitalWrite(led_amarelo, HIGH);
        digitalWrite(led_vermelho, LOW);

        if (tempoAtual - tempoTroca >= 2000) {
          tempoTroca = tempoAtual;
          num_semaforo = 2;
          break;
        } else {
          Serial.print("Amarelo");
          digitalWrite(led_verde, LOW);
          digitalWrite(led_amarelo, HIGH);
          digitalWrite(led_vermelho, LOW);
        }

      case 2:

        if (tempoAtual - tempoTroca >= 3000) {
          tempoTroca = tempoAtual;
          num_semaforo = 0;
          break;
        } else {
          Serial.print("VERDE");
          digitalWrite(led_verde, HIGH);
          digitalWrite(led_amarelo, LOW);
          digitalWrite(led_vermelho, LOW);
        }

    }
  }


}