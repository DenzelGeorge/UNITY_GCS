#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
void setup(){
  Serial.begin(9600);
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

void loop(){
  //String AzEl = "213.9$-37.7";
   while(Serial.available()){
     String AzEl = Serial.readString();
    int ind = AzEl.indexOf("$");
    String Az = AzEl.substring(0,ind);
    String El = AzEl.substring(ind + 1);
    int azimuth_angle = Az.toInt();
    int elevation_angle = El.toInt();
    lcd_display(azimuth_angle,elevation_angle);
   //Serial.print("AZ: "+String(azimuth_angle));
   //Serial.println(" EL: "+String(elevation_angle));
   }   
}

void lcd_display(int Azimuth, int Elevation)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("----UNITYSAT GCS----");
  lcd.setCursor(0, 1);
  lcd.print("AZIMUTH: " + String(Azimuth));
  lcd.setCursor(0, 2);
  lcd.print("ELEVATION: " + String(Elevation));
 // lcd.setCursor(18, 3);
 // lcd.print(control_state);
}
