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
        String datastring = convertToString(arr, array_size);
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

/*
 * 
 * String Parsivel_ID;
 * String intensity;
 * String rain_amount;
 * String weather_code;
 * String radar_reflectivity;
 * String mor_visibility;
 * String kinetic_energy;
 * String housing_temp;
 * String laser_signal;
 * String num_valid_particles;
 * String sensor_status;
 */
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

/*
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    Serial.print("USB received: ");
    Serial.println(incomingByte, DEC);
    HWSERIAL.print("USB received:");
    HWSERIAL.println(incomingByte, DEC);
  }
  if (HWSERIAL.available() > 0) {
    incomingByte = HWSERIAL.read();
    Serial.print("UART received: ");
    Serial.println(incomingByte, DEC);
    HWSERIAL.print("UART received:");
    HWSERIAL.println(incomingByte, DEC);
  }
 */
