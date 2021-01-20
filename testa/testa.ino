#include <RadioLib.h>

//Define pins for LoRa interface
#define NSS 4
#define DIO1 5
#define NRST 3
#define BUSY 2

//Initializing Module
SX1262 radio = new Module(NSS,DIO1,NRST,BUSY);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print(F("SX1268TL Initializing..."));
  int state = radio.begin();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } 
  else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(F("[SX1262] Transmitting packet ... "));
}
