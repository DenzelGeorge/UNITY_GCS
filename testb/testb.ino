#include <RadioLib.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

//Define pins for LoRa interface
#define NSS 4
#define DIO1 5
#define NRST 3
#define BUSY 2
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//Initializing Module
SX1262 radio = new Module(NSS,DIO1,NRST,BUSY);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//CAllSign 
char callsign[] = "UNITYSat";

//Flags
volatile bool interruptEnabled = true;
volatile bool transmissionReceived = false;

void onInterrupt() {
  if (!interruptEnabled) {
    return;
  }

  transmissionReceived = true;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("SX1268TL Initializing...");
  int state = radio.begin();
  if (state == ERR_NONE) {
    Serial.println(F("success!"));
  } 
  else {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true);
  }
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
  Serial.println("SSD1306 allocation failed");
  for(;;); // Don't proceed, loop forever
    }
  Serial.println("SSD1306 allocation failed");

}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Print on OLED
    delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE); 

  display.setCursor(0,10);   
  display.println("UNITYSAT Test2");
  display.setCursor(0,32);   
  display.println("RSSI: ");
  display.display();

  //LoRa Transmission Test
  Serial.println(F("Transmitting packet ... "));
  int state = radio.transmit("UNITYSat");

}
