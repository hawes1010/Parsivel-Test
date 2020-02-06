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
String rain_size;
String rain_attribute_0;
String rain_attribute_1;
String rain_attribute_2;
String rain_attribute_3;
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


void parseMessage(String a, int comm){
   switch(comm){
    case 0: 
    Parsivel_ID = a;
    break;
    
    case 1:
    intensity = a;
    break;

    case 2:
    rain_size = a;
    break;

    case 3:
    rain_attribute_0 = a;
    break;

    case 4:
    rain_attribute_1 = a;
    break;

    case 5:
    rain_attribute_2 = a;
    break;

    default:
    //save the data: SD card?  
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
