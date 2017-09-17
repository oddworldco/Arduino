#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

void setup()
{
  // start serial port
  Serial.begin(9600);
  
  // Start up the library
  sensors.begin();
}
 
 
void loop()
{
  
  float TempInC; 
  float TempInF;
  float BodyTemp;
  
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures

  TempInC = sensors.getTempCByIndex(0);
  TempInF = sensors.getTempFByIndex(0);
  BodyTemp = (TempInF,2);

   //float temp = sensors.getTempCByIndex(0); // Why "byIndex"? 
    // You can have more than one IC on the same bus. 
    // 0 refers to the first IC on the wire

  AccelerationReading currentAccel = Bean.getAcceleration();
  uint16_t batteryReading = Bean.getBatteryVoltage();
  int beanTemp = Bean.getTemperature();
  String nameToPrint = "rachel_bean";

  uint16_t battToPrint = batteryReading;
  int beanTempToPrint = beanTemp;
  int xToPrint = currentAccel.xAxis;
  int yToPrint = currentAccel.yAxis;
  int zToPrint = currentAccel.zAxis;
  //check processing converting float to 
  int bodyTempToPrint = BodyTemp;

  String object = "name:" + nameToPrint + ", bodyTemp:" + bodyTempToPrint + ", beanTemp:" + beanTempToPrint + ", x:" + xToPrint + ", y:" + yToPrint + ", z:" + zToPrint + ", battery:" + battToPrint;
  
  Serial.print(object);
  Bean.sleep(3000);
 
 
}
