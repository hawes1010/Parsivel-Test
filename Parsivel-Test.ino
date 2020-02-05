/* UART Example, any character received on either the real
   serial port, or USB serial (or emulated serial to the
   Arduino Serial Monitor when using non-serial USB types)
   is printed as a message to both ports.

   This example code is in the public domain.
*/

// set this to the hardware serial port you wish to use
#define HWSERIAL Serial1
double intensity;
double rain_size;
double rain_attribute_0;
double rain_attribute_1;
double rain_attribute_2;
double rain_attribute_3;
int data_number = 0;
 int array_size;
void setup() {
	Serial.begin(9600);
	HWSERIAL.begin(38400);
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

void clearArray(char* a){
  
}

void loop() {
    char arr[70];
    int data_pointer = 0;
      while (Serial.available()) {
      char c =  Serial.read();

      //Serial.print(c, HEX); Serial.print("#"); Serial.println(c);
      
      if (c == 0xA) { //new line feed
        String datastring = convertToString(arr, array_size);
        data_number = 0;
        continue;
      }
      if (c == 0x3B){ //semicolon that separates out the values from parsivel
       
        continue;
      }
     arr[data_pointer++] = c;
     int array_size = sizeof(arr) / sizeof(char); 
   
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
}
