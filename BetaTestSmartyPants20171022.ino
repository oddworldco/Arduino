#include <OneWire.h>
#include <DallasTemperature.h>
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

ScratchData scratchCommand;
ScratchData scratchBlank;

void setup()
{
  // start serial port
  Serial.begin(9600);
  // Start up the library
 sensors.begin();

  //set up buffer for scratch values
  uint16_t buffer [10] = { '   ' };
  
  //initialize scratch 2 with blank space
  //Bean.setScratchData(2, buffer, 10);
}
 
 
void loop()
{
  // call sensors.requestTemperatures() to issue a global temperature request to all devices on the bus
  //Serial.print(" Requesting temperatures...");

  
  for(int i = 0; i < 720; i++)
{
  sensors.setWaitForConversion(true);  // changed from false
  sensors.requestTemperatures();

  // Do something else while temp is been reading by the sensor'
  AccelerationReading currentAccel = Bean.getAcceleration();
  uint16_t batteryReading = Bean.getBatteryVoltage();
  int beanTemp = Bean.getTemperature();
  String nameToPrint = "bean_2";
  int xToPrint = currentAccel.xAxis;
  int yToPrint = currentAccel.yAxis;
  int zToPrint = currentAccel.zAxis;
  
  //new attempt to read into buffer @ bank 2
  // get temperature

  float fTemp = sensors.getTempFByIndex(0);
  //Serial.print("F");
  //Serial.print(fTemp);
  float fxTemp = fTemp * 100;
  //Serial.print("Fx");
  //Serial.print(fxTemp);
  uint16_t bTemp = (uint16_t) fxTemp;
  //Serial.print("B");
  //Serial.print(bTemp);
  //float aTemp = (float) bTemp;
  //Serial.print("Fa");
  //Serial.print(aTemp);

  String strTemp = ""+(String) bTemp;
  //Serial.print(strTemp);
  uint8_t bufTemp[16];
  for ( int i=0; i<strTemp.length(); i++ )
  {
    bufTemp [i] = strTemp.charAt(i);
    //Serial.write(bufTemp[i]);
  }
  //write temp array to scratch 2
  Bean.setScratchData( 2, bufTemp, strTemp.length() );

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
  String TempPrint = "name: "+ nameToPrint+", bodyTemp: "+s+", beanTemp:"+beanTemp;
  String AccelPrint = "name: "+ nameToPrint+", x: "+ xToPrint+ ", y: "+ yToPrint+ ", z: "+zToPrint;
  String BattPrint = "name: "+ nameToPrint+", battery: "+batteryReading;
  

  Serial.print(number);
  Serial.print(TempPrint);
  Serial.print(AccelPrint);
  Serial.print(BattPrint);
  }
  else
  {
    continue;
  }
  Bean.sleep(10000);
 }
}
