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
  Serial.print(F("[SX1262] Waiting for incoming transmission ... "));

  String str;
  int state = radio.receive(str);

   if (state == ERR_NONE) {
    // packet was successfully received
    Serial.println(F("success!"));

    // print the data of the packet
    Serial.print(F("[SX1262] Data:\t\t"));
    Serial.println(str);

    // print the RSSI (Received Signal Strength Indicator)
    // of the last received packet
    Serial.print(F("[SX1262] RSSI:\t\t"));
    Serial.print(radio.getRSSI());
    Serial.println(F(" dBm"));

    // print the SNR (Signal-to-Noise Ratio)
    // of the last received packet
    Serial.print(F("[SX1262] SNR:\t\t"));
    Serial.print(radio.getSNR());
    Serial.println(F(" dB"));

  }else if (state == ERR_RX_TIMEOUT) {
    // timeout occurred while waiting for a packet
    Serial.println(F("timeout!"));

  } else if (state == ERR_CRC_MISMATCH) {
    // packet was received, but is malformed
    Serial.println(F("CRC error!"));

  } else {
    // some other error occurred
    Serial.print(F("failed, code "));
    Serial.println(state);

  }
  
}
