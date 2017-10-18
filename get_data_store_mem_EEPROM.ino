#include <Time.h>
#include <TimeLib.h>

//initialization - check address 0, wipe ram, collect data to EEPROM, reserve starting  records
//esp8266
///build buffer into iphone 

#include <OneWire.h>
#include <DallasTemperature.h>
//include to store flash isntead of SRAM
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
  
  // read bean board values
  String nameToPrint = "bean_2";
  Bean.setBeanName("bean_2");
}
    //float bodyTemp; //4b
    //int beanTemp;  //2b
    //int bTime; ///?
    char data[10];
  
void loop()
{ 
  //if connected read EEPROM into Flash Memory Variable and send
  //read in the pointer
  int p;
  int eeAddress = 0;
  float lastBodyTemp = 00.00;
  EEPROM.get(eeAddress, p);
  Serial.print(p);
  
  for(int l = 0; l <= p; l++)
  {
    EEPROM.get(l, data);
    Serial.print(data);
    } 
   
  //once connected and sent, wipe the EEPROM memory
  //if not connected, its going to loop and overwrite
  int bTime;
  p = 0; //first variable to store in EEPROM
  eeAddress = 0;//location for data to be put

  EEPROM.put(eeAddress, p); //place pointer in EERPOM
  
  for(int i = 0; i < 660; i++)
{   
  bool connectionState = Bean.getConnectionState();
  if (connectionState == false) {
  // Blink Red LED to alert user device is not connected
  Bean.setLed(0, 0, 100);
  Bean.sleep(100);
  Bean.setLed(0, 0, 0);
  Bean.sleep(5000); 
  } else if (connectionState == true){ //Blinkn Green to alert user device is connected
    Bean.setLed(0, 255, 0);
    Bean.sleep(250);
    Bean.setLed(0, 0, 0);
    }
  

  sensors.setWaitForConversion(true);  // changed from false
  sensors.requestTemperatures();

  AccelerationReading currentAccel = Bean.getAcceleration();
  int xToPrint = currentAccel.xAxis;
  int yToPrint = currentAccel.yAxis;
  int zToPrint = currentAccel.zAxis;

  uint16_t batteryReading = Bean.getBatteryVoltage();
  int beanTemp = Bean.getTemperature();

  float temp = sensors.getTempFByIndex(0);
  double d;
  float f;
  char s[30];
  dtostrf(temp, 8, 2, s);
  f = temp;

 Bean.setScratchNumber(1, f);
 uint32_t bodyTemp = Bean.readScratchNumber(1);

 Serial.print(bodyTemp);
 Serial.print(xToPrint);
 Serial.print(yToPrint);
 Serial.print(zToPrint);
 Serial.print(beanTemp);
 Serial.print(batteryReading);
 bTime = now(); // Store the current time in time  

 if (bodyTemp == lastBodyTemp && i >120 && i< 420) {
  continue;
  } else {
  eeAddress = eeAddress + p + 1; // set address to 1 + size of object
  EEPROM.put(eeAddress, bodyTemp); // put last reading at the address
  
  eeAddress = eeAddress + sizeof(bodyTemp);//moving pointer
  EEPROM.put(eeAddress, beanTemp);

  eeAddress = eeAddress + sizeof(beanTemp);//moving pointer
  EEPROM.put(eeAddress, bTime);

  p = eeAddress + sizeof(bTime);// reset the address to include size of latest reading
  }

//sleep for 1 minute
 Bean.sleep(60000);
 }
 Bean.sleep(0xFFFFFFFF);
}
