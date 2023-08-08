#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>			// libreria para bus I2C
#include <Adafruit_GFX.h>		// libreria para pantallas graficas
#include <Adafruit_SSD1306.h>		// libreria para controlador SSD1306
 
#define ANCHO 128			// reemplaza ocurrencia de ANCHO por 128
#define ALTO 32				// reemplaza ocurrencia de ALTO por 64

#define OLED_RESET 4			// necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);	// crea objeto

//int LED = 3;
String inString = "";    // string to hold input
//int val = 0;
int contador = 0;

void setup() {
  Serial.begin(9600);
  //pinMode(LED,OUTPUT);
  Wire.begin();					// inicializa bus I2C
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(433E6)) { // or 915E6
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) { 
    // read packet    
    while (LoRa.available())
    {
      int inChar = LoRa.read();
      inString += (char)inChar;
      contador = inString.toInt();       
    }
    inString = "";     
    LoRa.packetRssi();    
  }
  
  Serial.println(contador);  
  oled.clearDisplay();			// limpia pantalla
  oled.setTextColor(WHITE);		// establece color al unico disponible (pantalla monocromo)
  oled.setCursor(0, 0);			// ubica cursor en inicio de coordenadas 0,0
  oled.setTextSize(1);			// establece tamano de texto en 1
  oled.println("Contador:");
  oled.setTextSize(2);
  oled.setCursor(0, 10);
  oled.println(contador);
  oled.display();
  //analogWrite(LED, val);
}
