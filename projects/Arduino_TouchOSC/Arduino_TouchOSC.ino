
//Receive from TouchOSC http://hexler.net/software/touchosc and apply to arduino pins via OSC .

//Credits to Jerome Dupraz & Retocama  

//Colorsound 011
// you can download arduino z-osc library from here https://github.com/djiamnot/Z_OSC
// you can download arduino code and vvvv patch from here: http://vvvv.org/contribution/arduinoosc

//Set ip and port in Touch Osc as you have in here . 
//Set Simple layout , in this code you will control the first 3 fader and the first 2 down buttons . 

#include <SPI.h>
#include <Ethernet.h> // Tested in version IDE 0022 Arduino UNO

#include <Z_OSC.h>


byte myMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte myIp[]  = { 192, 168, 1, 12 };
int  serverPort  = 10000;


float dw3 = 0;  // Variable to set value for Digital pin 2 to digitalWrite 
float dw5 = 0;

/*
float pwm3 = 0; // Variable to set value for Digital pin 3 to pwm
float pwm5 = 0;
float pwm6 = 0; 
*/
Z_OSCServer server;

Z_OSCMessage *rcvMes;

void setup(){ 
  //Pins 4,10 are used for the Ethernet shield . Adding pins 8 and 9 for use made this code buggy. 
  
  //Set pins as Outputs 
 pinMode(2, OUTPUT);
 pinMode(7, OUTPUT);

 pinMode(3, OUTPUT);
 pinMode(5, OUTPUT);
 pinMode(6, OUTPUT);

  
 Serial.begin(19200);
 
 Ethernet.begin(myMac ,myIp); 
 
 server.sockOpen(serverPort);
   
}
  
void loop(){

 if(server.available()){
   
  rcvMes=server.getMessage();

 logMessage();
  
  
  
      
      //Pwm Pins
  /*    
      
     //PWM Pin 3 
     if( !strcmp( rcvMes->getZ_OSCAddress() ,  "/1/fader1" ) ) 
     {
    
      pwm3 = rcvMes->getFloat(0); //Get first value from incoming /arduino/out
      pwm3=pwm3*255;//Map the value from TouchOsc to Pwm (0,255)
      analogWrite(3,pwm3);  // set pwm value on PIN
     }
  
     //PWM Pin 5
     if( !strcmp( rcvMes->getZ_OSCAddress() ,  "/1/fader2" ) ) 
     {
      pwm5 = rcvMes->getFloat(0);//Get second value from incoming /arduino/out
      pwm5=pwm5*255;//Map the value from TouchOsc to Pwm (0,255)
       
      Serial.println(pwm5);
     
     
      analogWrite(5,pwm5);  // set pwm value on PIN
     }
     
      //PWM Pin 6 
     if( !strcmp( rcvMes->getZ_OSCAddress() ,  "/1/fader3" ) ) 
     {
      
      pwm6 = rcvMes->getFloat(0); //Get first value from incoming /arduino/out
      pwm6=pwm6*255;//Map the value from TouchOsc to Pwm (0,255)
      analogWrite(6,pwm6);  // set pwm value on PIN
     }
  
    */
  
  
  //Digital pins 
      
      // Digital Pin 2
      if ( !strcmp( rcvMes->getZ_OSCAddress() ,  "/1/toggle1" )) 
      {
        
      dw3 = rcvMes->getFloat(0); //Get fith value from incoming /arduino/out
      dw3 = constrain(dw3, 0, 1); // limit the value to 0-1
      Serial.println(dw3);
     if ( dw3 == 1 ) {
      digitalWrite(3,HIGH);  // set pwm value on PIN
      delay(100);
      digitalWrite(3,LOW); 
                   }
      else {
      digitalWrite(2,HIGH);
      delay(100);
      digitalWrite(2,LOW);
         }
      }   
      
      // Digital Pin 7
     if ( !strcmp( rcvMes->getZ_OSCAddress() ,  "/1/toggle2" )) 
      {
        
      dw5 = rcvMes->getFloat(0); //Get fith value from incoming /arduino/out
      dw5 = constrain(dw5, 0, 1); // limit the value to 0-1
      Serial.println("dw5");
      Serial.println(dw5);
      
     if ( dw5== 1 ) {
      digitalWrite(5,HIGH);  // set pwm value on PIN
      delay(100);
      digitalWrite(5,LOW); 
                   }
      else {
      digitalWrite(6,HIGH);
      delay(100);
      digitalWrite(6,LOW);
         }
      }     
      
      
   }
 }
  
  
  //Log maker 
  
void logMessage(){
    uint16_t i;
    byte *ip=rcvMes->getIpAddress();
    
    long int intValue;
    float floatValue;
    char *stringValue;
    
    Serial.print(ip[0],DEC);
    Serial.print(".");
    Serial.print(ip[1],DEC);
    Serial.print(".");
    Serial.print(ip[2],DEC);
    Serial.print(".");
    Serial.print(ip[3],DEC);
    Serial.print(":");
    
    Serial.print(rcvMes->getPortNumber());
    Serial.print(" ");
    Serial.print(rcvMes->getZ_OSCAddress());
    Serial.print(" ");
    Serial.print(rcvMes->getTypeTags());
    Serial.print("--");
    
    for(i=0 ; i<rcvMes->getArgsNum(); i++){
      
     switch( rcvMes->getTypeTag(i) ){
      
        case 'i':       
          intValue = rcvMes->getInteger32(i);
          
          Serial.print(intValue);
          Serial.print(" ");
         break; 
         
         
        case 'f':        
          floatValue = rcvMes->getFloat(i);
        
          Serial.print(floatValue);
          Serial.print(" ");
         break; 
        
        
         case 's':         
          stringValue = rcvMes->getString(i);
         
          Serial.print(stringValue);
          Serial.print(" ");
         break; 
       
     }
    
      
    }
     Serial.println("");
}
