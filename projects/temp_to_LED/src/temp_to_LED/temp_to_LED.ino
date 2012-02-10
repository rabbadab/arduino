
#include <SoftwareSerial.h>
#include <Wire.h>

// Set the address of the TMP102 breakout sensor. 0x48 = ground to adr 
int tmp102Address = 0x48;

// RX to the 3 pin
SoftwareSerial mySerial(2, 3); 

// Set 1 if you want to see the Celcius in the serial monitor
int debug = 0;


void setup(){
  Serial.begin(9600);
// Set the transfer rate to the display. Default 9600  
  mySerial.begin(9600);
//Clear the display
  mySerial.print("xxxx");
  Wire.begin();
}

void loop(){

  float celsius = getTemperature();

// Serial monitor debug
 if(debug == 1){
  Serial.print("Celsius: ");
  Serial.println(celsius);
  }
  
  
// Reset the display
  mySerial.write(0x76);
// set the comma 
  mySerial.write(0x77);
  mySerial.write(0x02);
 // Move the float?? 
  int TempCelsius = celsius * 100;
  mySerial.print(TempCelsius);
  
 /* 
 Farenheit calculation 
 
  float fahrenheit = (1.8 * celsius) + 32;
  Serial.print("Fahrenheit: ");
  Serial.println(fahrenheit);
*/
 // delay(200); //adjust here to slow down the output. You can remove this
}

float getTemperature(){
  Wire.requestFrom(tmp102Address,2); 

  byte MSB = Wire.read();
  byte LSB = Wire.read();

  //it's a 12bit int, using two's compliment for negative
  int TemperatureSum = ((MSB << 8) | LSB) >> 4; 

  float celsius = TemperatureSum*0.0625;
  
  return celsius;
}
