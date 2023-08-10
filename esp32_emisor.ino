/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/ttgo-lora32-sx1276-arduino-ide/
*********/
//com 13 arriba negrito
//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>



//define the pins used by the LoRa transceiver module
#define SCK 18
#define MISO 19
#define MOSI 23
#define SS 5
#define RST 32
#define DIO0 33

//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 433E6



//packet counter
int counter = 0;



void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);


  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  delay(2000);
}

void loop() {
   
  Serial.print("Sending packet: ");
  Serial.println(counter);

  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;
  
  delay(10000);
}