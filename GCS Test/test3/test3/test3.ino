#include <G5500.h>
G5500 rotor = G5500();

int rotator_azimuth = 0;           //Stores the Azimuth Angle (Range : 0 - 450 degrees) from the rotator
int rotator_elevation = 0;         //Stores the Elevation Angle (Range : 0 - 180 degrees) from the rotator

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:

  rotator_azimuth = rotor.getAzDegrees();
  rotator_elevation = rotor.getElDegrees();

  Serial.print("AZ=  " + String(rotator_azimuth));
  Serial.println(" EL=  " + String(rotator_elevation));
}
