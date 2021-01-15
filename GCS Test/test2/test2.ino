void setup(){
  Serial.begin(9600);
}

void loop(){
  String AzEl = "213.9$-37.7";
  int ind = AzEl.indexOf("$");
  String Az = AzEl.substring(0,ind);
  String El = AzEl.substring(ind);
  Serial.println("AZ: " + Az + " EL: " + El);
}
