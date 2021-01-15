#include <G5500.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

G5500 rotor = G5500();

/*const int AD_MIN_VALUE = 0;
const int AD_MAX_VALUE = 1023;
const float MIN_AZIMUTH_ANGLE = 0;
const float MAX_AZIMUTH_ANGLE = 450;
const float MIN_ELEVATION_ANGLE = 0;
const float MAX_ELEVATION_ANGLE = 180;*/

//Arduino Pin Declarations
const int azimuth_pin = 0;         //Connected to A0
const int elevation_pin = 1;       //Connected to A1
/*const int up_button = 10;           //Connected to D2
const int down_button = 8;         //Connected to D3
const int left_button = 12;         //Connected to D4
const int right_button = 22;        //Connected to D5*/
const int rotator_up = 4;
const int rotator_down = 5;
const int rotator_left = 6;
const int rotator_right = 7;
const int control_state_switch = 34;


//Variable declarations
int azimuth_analog = 0;            //Stores the analog value from the Azimuth Pin of the rotator (Range : 0 - 1023)
int elevation_analog = 0;          //Stores the analog value from the Elevation Pin of the rotator (Range : 0 - 1023)
float azimuth_angle = 0;           //Stores the converted value from Azimuth analog to Angle (Range : 0 - 450 degrees)
float elevation_angle = 0;         //Stores the converted value from Elevation analog to Angle (Range : 0 - 180 degrees)
int initial_delay = 1;             //To display the Booting message
/*int up_button_state = 0;           //Stores the state of the UP button
int down_button_state = 0;         //Stores the state of the DOWN button
int left_button_state = 0;         //Stores the state of the LEFT button
int right_button_state = 0;        //Stores the state of the RIGHT button*/
int control_state_switch_state = 0;
//String rotor_state = "";           //Depending on the button pressed, it stores which the value (UP, DOWN, LEFT, RIGHT)
String control_state = "";         //Depending on the toggle switch, this can be used to set to AUTOMATIC (A) or MANUAL (M).
//In Automatic Mode, the SATNOGS/Orbitron control the rotator.
//In Manual Mode, the user can manually control the rotator using the UP, DOWN, LEFT, RIGHT buttons.
String input_string = ""; //Current position values from Orbitron/SatNOGS


// Set the LCD address to 0x27 for a 16 chars and 4 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  Serial.begin(9600); //To read live AZ and EL values from Orbitron/SatNOGS
  Serial1.begin(9600); //For verification purposes, to view using Serial monitor

  /*pinMode(up_button, INPUT);
  pinMode(down_button, INPUT);
  pinMode(left_button, INPUT);
  pinMode(right_button, INPUT);*/

  pinMode(rotator_up, OUTPUT);
  pinMode(rotator_down, OUTPUT);
  pinMode(rotator_left, OUTPUT);
  pinMode(rotator_right, OUTPUT);
  

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
    //azimuth_analog = analogRead(azimuth_pin);
    //elevation_analog = analogRead(elevation_pin);
  
    azimuth_analog = rotor.getAzDegrees(); //Read the current value through analog pins
    elevation_analog = rotor.getElDegrees(); //Read the current value through analog pins
    azimuth_reading(); //Read the required value from Orbitron/SatNOGS value through Serial port
    elevation_reading(); //Read the required value from Orbitron/SatNOGS value through Serial port
  
    rotor.setAzEl(azimuth_angle, elevation_angle); //Set the rotator to the angle
  
    //rotor_state = rotor_button_state();  
    //Serial.println(rotor_state);
    //check_control_state(); //Shouldn't this be done first???
    lcd_display();
    /*Serial.println("AZIMUTH ANGLE =  " + String(azimuth_angle));
    Serial.println("ELEVATION ANGLE =  " + String(elevation_angle));
    Serial.println("CONTROL STATE =  " + String(control_state));
    Serial.println("BUTTON STATE  =  " + rotor_button_state());
    delay(1000);*/
    Serial1.println("AZIMUTH ANGLE =  " + String(azimuth_angle));
    Serial1.println("ELEVATION ANGLE =  " + String(elevation_angle));
    Serial1.println("CONTROL STATE =  " + String(control_state));
    delay(1000);
  }
  else{
    azimuth_analog = rotor.getAzDegrees(); //Read the current value through analog pins
    elevation_analog = rotor.getElDegrees(); //Read the current value through analog pins
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

void read_input(){
  while(Serial.available()){
    input_string = Serial.readString(); // Input String with format (AZ$EL)
  }
}
void azimuth_reading()
{
  if(Serial.available()){
    azimuth_angle= Serial.read();
  }
  //azimuth_angle = (azimuth_analog - AD_MIN_VALUE) * (MAX_AZIMUTH_ANGLE - MIN_AZIMUTH_ANGLE) / (AD_MAX_VALUE - AD_MIN_VALUE) + MIN_AZIMUTH_ANGLE;
}

void elevation_reading()
{
  if(Serial.available()){
    elevation_angle= Serial.read();
  }
  //elevation_angle = (elevation_analog - AD_MIN_VALUE) * (MAX_ELEVATION_ANGLE - MIN_ELEVATION_ANGLE) / (AD_MAX_VALUE - AD_MIN_VALUE) + MIN_ELEVATION_ANGLE;
}

/*void lcd_display(String rotor_state)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("----UNITYSAT GCS----");
  lcd.setCursor(0, 1);
  lcd.print("AZIMUTH: " + String(azimuth_angle));
  lcd.setCursor(0, 2);
  lcd.print("ELEVATION: " + String(elevation_angle));
  lcd.setCursor(0, 3);
  lcd.print("ROTOR: " + rotor_state);
  lcd.setCursor(18, 3);
  lcd.print(control_state);
}*/

void lcd_display()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("----UNITYSAT GCS----");
  lcd.setCursor(0, 1);
  //lcd.print("AZIMUTH: " + String(azimuth_angle));
  lcd.print("AZIMUTH: " + String(azimuth_analog));
  lcd.setCursor(0, 2);
  //lcd.print("ELEVATION: " + String(elevation_angle));
  lcd.print("ELEVATION: " + String(elevation_analog));
  /*lcd.setCursor(0, 3);
  lcd.print("ROTOR: " + rotor_state);*/
  lcd.setCursor(18, 3);
  lcd.print(control_state);
}

/*String rotor_button_state()   //Since manual control is on box, this is redundant
{
  up_button_state = digitalRead(up_button);
  down_button_state = digitalRead(down_button);
  left_button_state = digitalRead(left_button);
  right_button_state = digitalRead(right_button);

  if (control_state == "M")
  {
    if (up_button_state == HIGH )
    {
      digitalWrite(rotator_up, HIGH);
      digitalWrite(rotator_down, LOW);
      digitalWrite(rotator_left, LOW);
      digitalWrite(rotator_right, LOW);
      return "UP";
    }
    else if (down_button_state == HIGH )
    {
      digitalWrite(rotator_up, LOW);
      digitalWrite(rotator_down, HIGH);
      digitalWrite(rotator_left, LOW);
      digitalWrite(rotator_right, LOW);
      return "DOWN";
    }
    else if (left_button_state == HIGH )
    {
      digitalWrite(rotator_up, LOW);
      digitalWrite(rotator_down, LOW);
      digitalWrite(rotator_left, HIGH);
      digitalWrite(rotator_right, LOW);
      return "LEFT";
    }
    else if (right_button_state == HIGH )
    {
      digitalWrite(rotator_up, LOW);
      digitalWrite(rotator_down, LOW);
      digitalWrite(rotator_left, LOW);
      digitalWrite(rotator_right, HIGH);
      return "RIGHT";
    }
    else
    {
      digitalWrite(rotator_up, LOW);
      digitalWrite(rotator_down, LOW);
      digitalWrite(rotator_left, LOW);
      digitalWrite(rotator_right, LOW);
      return " ";
    }
  }
  else
  {
    return " ";
  }
}*/
