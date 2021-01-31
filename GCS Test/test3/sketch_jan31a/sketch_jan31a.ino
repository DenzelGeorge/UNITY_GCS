int rotator_azimuth = 0;           //Stores the Azimuth Angle (Range : 0 - 450 degrees) from the rotator
int rotator_elevation = 0;         //Stores the Elevation Angle (Range : 0 - 180 degrees) from the rotator

int azimuth_angle = 90;           //Value to be set
int elevation_angle = 90;         //Value to be set

int _upPin      = 4;                       // +Elevation angle
int _downPin    = 5;             // -Elevation angle
int _westPin    = 6;             // -Azimuth angle (left)
int _eastPin    = 7;             // +Azimuth angle (right)
int _azSensePin = A0;
int _elSensePin = A1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(_upPin, OUTPUT);
  pinMode(_downPin, OUTPUT);
  pinMode(_eastPin, OUTPUT);
  pinMode(_westPin, OUTPUT);
  
  digitalWrite(_upPin, LOW);
  digitalWrite(_downPin, HIGH);
  digitalWrite(_eastPin, LOW);
  digitalWrite(_westPin, HIGH);
  
}

void loop() {
  // put your main code here, to run repeatedly:
 
  
 // rotor.setAz(90);
  
  /*
  rotor.setAz(90); 
  //rotor.setEl(90);*/
  /*rotator_azimuth = rotor.getAzDegrees();
  rotator_elevation = rotor.getElDegrees();
  
  //rotor.setAzEl(azimuth_angle, elevation_angle); //Set the rotator to the angle

  Serial.print("AZ=  " + String(rotator_azimuth));
  Serial.println(" EL=  " + String(rotator_elevation));*/
}
