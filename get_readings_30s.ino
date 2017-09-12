void setup() {
  // put your setup code here, to run once:
  Serial.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  AccelerationReading currentAccel = Bean.getAcceleration();
  
  uint16_t batteryReading =  Bean.getBatteryVoltage(); 
  
  int temperature = Bean.getTemperature();
  
  String nameToPrint = String();
  nameToPrint = "andrew_bean";
  String stringToPrint = String();
  stringToPrint = stringToPrint + "Battery voltage: " + batteryReading/100 + "." + batteryReading%100 + " V";
  
  Serial.println(stringToPrint);
  Serial.println(nameToPrint);

  Serial.print("Temperature:");
  Serial.print(temperature);
  Serial.print("x:");
  Serial.print(currentAccel.xAxis);
  Serial.print("y:");
  Serial.print(currentAccel.yAxis);
  Serial.print("z:");
  Serial.print(currentAccel.zAxis);
  
  Bean.sleep(30000);
}
