#include <G5500.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Include the string library */


G5500 rotor = G5500();
const int control_state_switch = 34;


//Variable declarations
int rotator_azimuth = 0;           //Stores the Azimuth Angle (Range : 0 - 450 degrees) from the rotator
int rotator_elevation = 0;         //Stores the Elevation Angle (Range : 0 - 180 degrees) from the rotator

int azimuth_angle = 0;           //Stores the converted value from SatNOGS/Orbitron
int elevation_angle = 0;         //Stores the converted value from SatNOGS/Orbitron


int initial_delay = 1;             //To display the Booting message
int control_state_switch_state = 0;

String control_state = "A";         //Depending on the toggle switch, this can be used to set to AUTOMATIC (A) or MANUAL (M). Automatic by default

LiquidCrystal_I2C lcd(0x27, 20, 4); // Set the LCD address to 0x27 for a 16 chars and 4 line display

void setup()
{
  Serial.begin(9600); //To read live AZ and EL values from Orbitron/SatNOGS
  Serial1.begin(9600); //For verification purposes, to view using Serial monitor AKA Troubleshooting

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("********************");
  lcd.setCursor(4, 1);
  lcd.print("UNITYSAT GCS");
  lcd.setCursor(5, 2);
  lcd.print("Booting...");
  lcd.setCursor(0, 3);
  lcd.print("********************");
  
}

void loop()
{
  if (initial_delay)
  {
    delay(3000);
    initial_delay = 0;
  }
  
  check_control_state();
  if(control_state == "A"){
    
    rotator_azimuth = rotor.getAzDegrees(); //Read the current value through analog pins
    rotator_elevation = rotor.getElDegrees(); //Read the current value through analog pins
    read_input(); //Read the required value from Orbitron/SatNOGS value through Serial port
 
    rotor.setAzEl(azimuth_angle, elevation_angle); //Set the rotator to the angle
  
    lcd_display();
    
    Serial1.println("ROTATOR AZIMUTH ANGLE =  " + String(rotator_azimuth));
    Serial1.println("INPUT AZIMUTH ANGLE =  " + String(azimuth_angle));
    Serial1.println("ROTATOR ELEVATION ANGLE =  " + String(rotator_elevation));
    Serial1.println("INPUT ELEVATION ANGLE =  " + String(elevation_angle));
    Serial1.println("CONTROL STATE =  " + String(control_state));
    delay(1000);
  }
  else
  {
    rotator_azimuth = rotor.getAzDegrees(); //Read the current value through analog pins
    rotator_elevation = rotor.getElDegrees(); //Read the current value through analog pins
    
    lcd_display();
    
    Serial1.println("AZIMUTH ANGLE =  " + String(rotator_azimuth));
    Serial1.println("ELEVATION ANGLE =  " + String(rotator_elevation));
    Serial1.println("CONTROL STATE =  " + String(control_state));
    delay(1000);
  }
}

void check_control_state()
{
  control_state_switch_state = digitalRead(control_state_switch);
  if (control_state_switch_state == HIGH)
  {
    control_state = "M";
  }
  else
  {
    control_state = "A";
  }
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



void lcd_display()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("----UNITYSAT GCS----");
  lcd.setCursor(0, 1);
  lcd.print("AZIMUTH: " + String(rotator_azimuth));
  lcd.setCursor(0, 2);
  lcd.print("ELEVATION: " + String(rotator_elevation));
  lcd.setCursor(18, 3);
  lcd.print(control_state);
}
