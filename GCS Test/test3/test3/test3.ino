#include <G5500.h>


G5500 rotor = G5500();

int rotator_azimuth = 0;           //Stores the Azimuth Angle (Range : 0 - 450 degrees) from the rotator
int rotator_elevation = 0;         //Stores the Elevation Angle (Range : 0 - 180 degrees) from the rotator

int azimuth_angle = 0;           //Stores the converted value from SatNOGS/Orbitron
int elevation_angle = 0;         //Stores the converted value from SatNOGS/Orbitron

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:

  rotator_azimuth = rotor.getAzDegrees();
  rotator_elevation = rotor.getElDegrees();

  read_input();
  
  rotor.setAzEl(azimuth_angle, elevation_angle);
  //rotor.setAz(30);
  //rotor.setEl(45);

  
  Serial.print("AZ=  " + String(rotator_azimuth));
  Serial.println(" EL=  " + String(rotator_elevation));
}

void read_input(){
  while(Serial.available()){
    String AzEl = Serial.readString(); //Data is formatted as AZ$EL
    int ind = AzEl.indexOf("$");
    String Az = AzEl.substring(0,ind);
    String El = AzEl.substring(ind + 1);
    azimuth_angle = Az.toInt();
    elevation_angle = El.toInt();
  }
}
