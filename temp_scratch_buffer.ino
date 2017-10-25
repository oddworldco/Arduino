#include <TimeLib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h>
 
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

  //set up buffer for scratch values
  uint16_t buffer [10] = { '   ' };
  
  //In case we need to reset the EEPROM data
  //for (int i = 0 ; i < EEPROM.length() ; i++) {
  //  EEPROM.write(i, 0);}
}

uint16_t data; //data from memory
     
void loop()
{
//check conntection state
bool connectionState = Bean.getConnectionState();

//create a pointer
int p;
int eeAddress = 0; //location for the data

if (connectionState == true){
  //first, loop through each pointer for the length of EEPROM
  //write each to the ScratchData3 bank
  for(int l = 0; l <= EEPROM.length(); l++)
  {
    EEPROM.get(l, data);
    String strData = ""+(String) data;
    Bean.setScratchData( 3, data, strData.length() );//write value to scratch
  }
  p = 0; //reset pointer to 0 once memory is unloaded
  } else {
      continue // if connectionState is not true, it will store/overwrite
  }
  EEPROM.put(eeAddress, p); //place pointer in place 0 in buffer 

  if (connectionState == false){
    //blink red LED to alert device is not connected
  Bean.setLed(0, 0, 100);
  Bean.sleep(100);
  Bean.setLed(0, 0, 0);
  Bean.sleep(5000);     
    } else {
      continue // if connectionState is true, it continues
  }
  
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
  
  //read into buffer @ bank 2
  // convert from float to uint16_t
  
  time_t t = now();//get time of reading

  float fTemp = sensors.getTempFByIndex(0);
  float fxTemp = fTemp * 100;
  uint16_t bTemp = (uint16_t) fxTemp;
  String strTemp = ""+(String) bTemp;
  uint8_t bufTemp[16];
  for ( int i=0; i<strTemp.length(); i++ )
  {
    bufTemp [i] = strTemp.charAt(i);
  }
  //write temp array to scratch 2
  Bean.setScratchData( 2, bufTemp, strTemp.length() );

  //write temp array to eeprom once program has been running for 1 hour but less that 7 hours, take a reading 1x every 10 min
  if (i > 60 && i < 420 && (i%10 = 0)) {
    eeAddress = eeAddress + p + 1;//set address to 1 + size of memory
    EEPROM.put(eeAddress, bTemp);//put last reading at address

    eeAddress = eeAddress + sizeof(bTemp); //adjust the address
    EEPROM.put(eeAddress, t); //add timestamp

    eeAddress = eeAddress +sizeof(t); //adjust the address
    EEPROM.put(eeAddress, beanTemp);// add temp of device

    p = eeAddress + sizeof(beanTemp); //recalculate the pointer
    }

  //code for web app
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

 

  //validate the size of the temperature object before printing
  if ((sizetemp) == 4){
  f = temp;
  d = (double) f;
 
  String TempPrint = "name: "+ nameToPrint+", bodyTemp: "+s+", beanTemp:"+beanTemp;
  String AccelPrint = "name: "+ nameToPrint+", x: "+ xToPrint+ ", y: "+ yToPrint+ ", z: "+zToPrint;
  String BattPrint = "name: "+ nameToPrint+", battery: "+batteryReading;

  Serial.print(number);
  Serial.print(TempPrint);
  Serial.print(AccelPrint);
  Serial.print(BattPrint);
  } else {
    continue;
  }
  Bean.sleep(10000);
 }
}
