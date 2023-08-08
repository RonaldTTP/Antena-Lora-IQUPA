

 //6 arriba ponteciometro
 //8 arduino
 //4 nano
#include <SPI.h>
#include <LoRa.h> //Download here: http://electronoobs.com/eng_arduino_LoRa_SX1278.php.php
//int pot = 34;
int luz_amarilla = 5;
int pulsador = 3;
volatile int contador = 0;

void encenderTodas() {
  digitalWrite(luz_amarilla, LOW);
  contador++;
}

void setup() {
  Serial.begin(9600);
  //pinMode(pot,INPUT);
  pinMode(luz_amarilla, OUTPUT);
  pinMode(pulsador, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulsador), encenderTodas, RISING);
  
  while (!Serial);  
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  digitalWrite(luz_amarilla, HIGH);
  //int val = map(analogRead(pot),0,1024,0,255);
  //Serial.println(val);
  Serial.println(contador);
  LoRa.beginPacket();  
  LoRa.print(contador);
  LoRa.endPacket();
  delay(500);
 
}