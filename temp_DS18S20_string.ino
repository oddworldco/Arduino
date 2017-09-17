#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
 sensors.begin();
}
 
 
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  //Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");

  AccelerationReading currentAccel = Bean.getAcceleration();

  uint16_t batteryReading = Bean.getBatteryVoltage();
  int beanTemp = Bean.getTemperature();
  String nameToPrint = "bean_1";
  int xToPrint = currentAccel.xAxis;
  int yToPrint = currentAccel.yAxis;
  int zToPrint = currentAccel.zAxis;
  
 
  float temperatureInF = sensors.getTempFByIndex(0);
  //String tempF = String(temperatureInF, 4);
  char outstr[25];
  dtostrf(temperatureInF, 6, 2, outstr);
  Serial.print("name: "+ nameToPrint+ ", battery: "+ batteryReading+", x: "+ xToPrint+ ", y: "+ yToPrint+ ", z: "+zToPrint+", BodyTemp: "+ String(outstr));
  //Serial.print(temperatureInF, 4); // Why "byIndex"? 
    // You can have more than one IC on the same bus. 
    // 0 refers to the first IC on the wire
  Bean.sleep(30000);
 
}
