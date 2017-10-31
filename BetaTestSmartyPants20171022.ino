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
  // call sensors.requestTemperatures() to issue a global temperature request to all devices on the bus
  //Serial.print(" Requesting temperatures...");

  
  for(int i = 0; i < 720; i++)
{
  //sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");
  //delay(1000);
  //float temperatureInF = sensors.getTempFByIndex(0);
  //temperatureInF = (temperatureInF * 100);
  //char outstr[30];
  //outstr = sensors.getTempFByIndex(0);
  //dtostrf(temperatureInF, 8, 4, outstr);
  //String bodyTempPrint = (outstr);

  sensors.setWaitForConversion(true);  // changed from false
  sensors.requestTemperatures();
  sensors.setWaitForConversion(true);

  // Do something else while temp is been reading by the sensor'
  AccelerationReading currentAccel = Bean.getAcceleration();
  uint16_t batteryReading = Bean.getBatteryVoltage();
  int beanTemp = Bean.getTemperature();
  String nameToPrint = "heather";
  int xToPrint = currentAccel.xAxis;
  int yToPrint = currentAccel.yAxis;
  int zToPrint = currentAccel.zAxis;
   
  float temp = sensors.getTempFByIndex(0);
  double a = 99.99;
  int sizetemp;
  sizetemp = sizeof(temp);
  double d;
  float f;
  //String s;
  char s[30];
  dtostrf(temp, 8, 2, s);

  Bean.setScratchNumber(1, f); //added 09/17
 uint32_t number = Bean.readScratchNumber(1);

  //Serial.print(AllPrint);
  //Serial.print(a);
 

  if ((sizetemp) == 4)
  {
  f = temp;
  d = (double) f;
  //s = (String) d;
    
  //Serial.print(f, 2);
  //Serial.print(s);
  //Serial.print(AllPrint+", bodyTemp: "+s);
  String TempPrint = "n: "+ nameToPrint+", bdy: "+s+", bn:"+beanTemp+", x: "+ xToPrint+ ", y: "+ yToPrint+ ", z: "+zToPrint+", battery: "+batteryReading;
   
  Serial.print(TempPrint);

  }
  else
  {
    continue;
  }
  Bean.sleep(60000);
 }
}
