/* UART Example, any character received on either the real
   serial port, or USB serial (or emulated serial to the
   Arduino Serial Monitor when using non-serial USB types)
   is printed as a message to both ports.

   This example code is in the public domain.
*/

// set this to the hardware serial port you wish to use
#define HWSERIAL Serial1
String Parsivel_ID;
String intensity;
String rain_amount;
String weather_code;
String radar_reflectivity;
String mor_visibility;
String kinetic_energy;
String housing_temp;
String laser_signal;
String num_valid_particles;
String sensor_status;
int command_num = 0;
int array_size;
//#include <array>
//#include <iostream>
#include <SD.h>
#include <TimeLib.h>
File myFile;
 
char fileName[20];  //fileName built from date
char dateTime[30];  // dateTime to be written to SD card header
const int chipSelect = BUILTIN_SDCARD; //For Teensy 3.5, SPI for SD card is separate

void setup() {
	Serial.begin(9600);
	HWSERIAL.begin(19200);
}



void clearArray(char* a){
  int len = sizeof(a) / sizeof(char);
  int length = len;
  int i;

  for (i = 0; i < length; i++)
    a[i] = NULL;
}

void loop() {
    char* arr;
    int data_pointer = 0;
      while (HWSERIAL.available()) {
      char c =  HWSERIAL.read();
      
      if (c == 0xA) { //new line feed
        command_num = 0;
        data_pointer = 0;
        clearArray(arr);
        clearStrings();
        continue;
      }
      if (c == 0x3B){ //semicolon that separates out the values from parsivel
       data_pointer = 0;
       String datastring = convertToString(arr, array_size);
       parseMessage(datastring, command_num);
       command_num++;
       clearArray(arr);
        continue;
      }
     arr[data_pointer++] = c;
     int array_size = sizeof(arr) / sizeof(char); 
   
      }
  
}

String convertToString(char* a, int size) 
{ 
    int i; 
    String s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    return s; 
} 
void clearStrings(){
String Parsivel_ID = "" ;
String intensity = "" ;
String rain_amount = "" ;
String weather_code = "" ;
String radar_reflectivity = "" ;
String mor_visibility = "" ;
String kinetic_energy = "" ;
String housing_temp = "" ;
String laser_signal = "" ;
String num_valid_particles = "" ;
String sensor_status = "" ;
}

char monthChar[5];
char dateChar[5];
char hourChar[5];
char minuteChar[5];
char secondChar[5];
boolean isDST = false;
int writeNum;
void saveData() {

  if (writeNum == 0)
  {
    buildDateTime();
    setfileName();
  }
  myFile = SD.open(fileName, FILE_WRITE);
  // open the file for write at end like the Native SD library
  if (!myFile) {
    Serial.println("opening sd file for write failed");
  } else
  {

    Serial.println("File opened");

    // if the file opened okay, write to it:
    Serial.print("Writing to "); Serial.println(fileName);
    Serial.print("writeNum = "); Serial.println(writeNum);
    if (writeNum == 0)
    {

      writeNum++;
      Serial.println("Writing header");   //Write headers
      Serial.println("");

      myFile.print("Parsivel Post ");
     
      myFile.println(" ## ");
      myFile.println("");
      //int localHours = hour(local);
      //int utcHours = hour(utc);

      myFile.println("TIMESTAMP(EST),BottleNumber (/24),level Reading (/1024),Battery Voltage (V)");
    }
    
    myFile.close();
    Serial.println("done.");
  }


}


void setfileName()
{
  int y = sprintf(fileName, "%s%s%i%s", monthChar, dateChar, year(), ".txt");
  Serial.print("Filename is: "); Serial.println(fileName);
}


void buildDateTime()
{

  if (month() < 10)
  {
    int y = sprintf(monthChar, "%c%i", '0', month());
  } else
  {
    int y = sprintf(monthChar, "%i", month());
  }

  if (day() < 10)
  {
    int y = sprintf(dateChar, "%c%i", '0', day());
  } else
  {
    int y = sprintf(dateChar, "%i", day());
  }

  if (hour() < 10)
  {
    int y = sprintf(hourChar, "%c%i", '0', hour());
  } else
  {
    int y = sprintf(hourChar, "%i", hour());
  }

  if (minute() < 10)
  {
    int y = sprintf(minuteChar, "%c%i", '0', minute());
  } else
  {
    int y = sprintf(minuteChar, "%i", minute());
  }

  if (second() < 10)
  {
    int y = sprintf(secondChar, "%c%i", '0', second());
  } else
  {
    int y = sprintf(secondChar, "%i", second());
  }


  //int y = sprintf(dateTimeVIPER, "%i%s%s%s%s%s%s%s%s%s%s%s%i%s", year(localNow), "-", localMonthChar, "-", localDateChar, "T", localHourChar, ":", minuteChar, ":", secondChar, "-0",tzOffset,":00");
  //Serial.println("In build");
  //Serial.print("DTV -- "); Serial.println(dateTimeVIPER);
  sprintf(dateTime, "%i%s%s%s%s%s%s%s%s%s%s", year(), "-", monthChar, "-", dateChar, "T", hourChar, ":", minuteChar, ":", secondChar);
}



void parseMessage(String a, int comm){
   switch(comm){
    case 0: 
    Parsivel_ID = a;
    break;
    
    case 1:
    intensity = a;
    break;

    case 2:
    rain_amount = a;
    break;

    case 3:
    weather_code = a;
    break;

    case 4:
    radar_reflectivity = a;
    break;

    case 5:
    mor_visibility = a;
    break;

    case 6:
    kinetic_energy = a;
    break;

     case 7:
    housing_temp = a;
    break;

     case 8:
    laser_signal = a;
    break;
    
     case 9:
    num_valid_particles = a;
    break;

     case 10:
    sensor_status = a;
    break;
    
    default: 
    break;
   }
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

/*
  }
  if (HWSERIAL.available() > 0) {
    incomingByte = HWSERIAL.read();
    Serial.print("UART received: ");
    Serial.println(incomingByte, DEC);
    HWSERIAL.print("UART received:");
    HWSERIAL.println(incomingByte, DEC);
  }
 */
