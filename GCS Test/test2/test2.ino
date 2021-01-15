void setup(){
  Serial.begin(9600);
}

void loop(){
  String AzEl = "213.9$-37.7";
  int ind = AzEl.indexOf("$");
  String Az = AzEl.substring(0,ind);
  String El = AzEl.substring(ind + 1);
  int azimuth_angle = Az.toInt();
  int elevation_angle = El.toInt();
  Serial.print("AZ: " +azimuth_angle);
  Serial.println(" EL: " +elevation_angle);
}
