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

int azimuth_angle = 0;           //Stores the converted value from Azimuth analog to Angle (Range : 0 - 450 degrees)
int elevation_angle = 0;         //Stores the converted value from Elevation analog to Angle (Range : 0 - 180 degrees)


int initial_delay = 1;             //To display the Booting message

int control_state_switch_state = 0;

String control_state = "";         //Depending on the toggle switch, this can be used to set to AUTOMATIC (A) or MANUAL (M).
//In Automatic Mode, the SATNOGS/Orbitron control the rotator.
//In Manual Mode, the user can manually control the rotator using the UP, DOWN, LEFT, RIGHT buttons.

// Set the LCD address to 0x27 for a 16 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  Serial.begin(9600); //To read live AZ and EL values from Orbitron/SatNOGS
  Serial1.begin(9600); //For verification purposes, to view using Serial monitor

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
    azimuth_reading(); //Read the required value from Orbitron/SatNOGS value through Serial port
    elevation_reading(); //Read the required value from Orbitron/SatNOGS value through Serial port
  
    rotor.setAzEl(azimuth_angle, elevation_angle); //Set the rotator to the angle
  
    lcd_display();
    Serial1.println("AZIMUTH ANGLE =  " + String(rotator_azimuth));
    Serial1.println("ELEVATION ANGLE =  " + String(rotator_elevation));
    Serial1.println("CONTROL STATE =  " + String(control_state));
    delay(1000);
  }
  else
  {
    rotator_azimuth = rotor.getAzDegrees(); //Read the current value through analog pins
    rotator_elevation = rotor.getElDegrees(); //Read the current value through analog pins
    lcd_display();
    Serial1.println("AZIMUTH ANGLE =  " + String(azimuth_angle));
    Serial1.println("ELEVATION ANGLE =  " + String(elevation_angle));
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

void azimuth_reading()
{
  if(Serial.available())
  {
	  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  You need to first read the entire string and extract the substring from it using the String library.
	  Function name : Substring(from, to)*/
	  //read_az - Serial.read
	  //Extract_pos = indexof()
	  //Extract = .substring(0, Extract_pos+1)
	  //Use toInt() TO CONVERT STRING TO INTEGER
    azimuth_angle = 
  }
}

void elevation_reading()
{	
  if(Serial.available())
  {
	  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	  You need to first read the entire string and extract the substring from it using the String library.
	  Function name : Substring(from, to)*/
	  
	   //read_el = Serial.read()
	  //Extract_pos = indexof()
	  //Extract = .substring(0, Extract_pos+1)
	  
	  //Use toInt() TO CONVERT STRING TO INTEGER
    elevation_angle = 
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

