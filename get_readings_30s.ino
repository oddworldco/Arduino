void setup() {
  // put your setup code here, to run once:
  Serial.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  AccelerationReading currentAccel = Bean.getAcceleration();
  
  uint16_t batteryReading =  Bean.getBatteryVoltage(); 
  int temperature = Bean.getTemperature();
  String nameToPrint = "rachel_bean";

  uint16_t stringToPrint = batteryReading;
  int tempToPrint = temperature;
  int xToPrint = currentAccel.xAxis;
  int yToPrint = currentAccel.yAxis;
  int zToPrint = currentAccel.zAxis;
  
  String object = "name:" + nameToPrint + ", temp:" + tempToPrint + ", x:" + xToPrint + ", y:" + yToPrint + ", z:" + zToPrint + ", battery:" + stringToPrint;


  //Serial.println(nameToPrint);
  //Serial.println(stringToPrint);
  //Serial.print(tempToPrint);
  //Serial.print(xToPrint);
  //Serial.print(yToPrint);
  //Serial.print(zToPrint);

  Serial.print(object);
  
  Bean.sleep(30000);
}
