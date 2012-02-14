//Heartbeat LED
//elCalvoMike 12-6-2008
#define LED  13 //analog pin location for ArduinoMini - change for other boards
int i = 0;
int pmw = 255;  //set PWM max - this can differ for other board pins
int rate = 25;  //this is the beats per minute (60000 ms)
               //because there are two beats to simulate the 'lub-dub' of the heart,
               // a 60 beat heart rate is only a value of 30 in the rate variable
               //the delay is the key to this programs realism - divide the rate into a minute, then weight it and divide by the pmw
               //you can modify the weight by changing the fractions (i.e .1, .2, .6) but to keep the timing correct, they should total 1
               //.1+.2+.1+.6 = 1

void setup() {
 pinMode(LED, OUTPUT);
}

void loop(){
 for(i = 0; i < pmw; i++) {
   analogWrite(LED,i);
   delay(((60000/rate)*.1)/pmw);
 }
 
 for (i = pmw; i > 0; i--){
   analogWrite(LED,i);
   delay(((60000/rate)*.2)/pmw);
 }
 
   for(i = 0; i < pmw; i++) {
   analogWrite(LED,i);
   delay(((60000/rate)*.1)/pmw);
 }
 
 for (i = pmw; i > 0; i--){
   analogWrite(LED,i);
   delay(((60000/rate)*.6)/pmw);
 }
 
}
