int remoteOneON =  2; //pin for 1 ON
int remoteOneOFF = 3; //pin for 1 OFF
int remoteTwoON = 4; //pin for 2 ON
int remoteTwoOFF = 5; //pin for 2 OFF
int remoteOneInd = 13; //pin for 1 LED
int remoteTwoInd = 12; //pin for 2 LED
int incomingByte = 0; //variable to hold incoming Serial data
// The setup() method runs once, when the sketch starts

void setup()   {
// initialize the digital pins as outputs:
pinMode(remoteOneON, OUTPUT);
pinMode(remoteOneOFF, OUTPUT);
pinMode(remoteTwoON, OUTPUT);
pinMode(remoteTwoOFF, OUTPUT);
pinMode(remoteOneInd, OUTPUT);
pinMode(remoteTwoInd, OUTPUT);
/*
digitalWrite(remoteOneInd, HIGH); //turn on #1 indicator LED
digitalWrite(remoteTwoInd, HIGH); //turn on #2 indicator LED
digitalWrite(remoteOneOFF, HIGH); //send the command to turn OFF #1
delay(500); //wait 1.5s
digitalWrite(remoteOneOFF, LOW); //pull the pin Low
digitalWrite(remoteTwoOFF, HIGH);    // send the command to turn OFF #2
delay(500); //wait 1.5s
digitalWrite(remoteTwoOFF, LOW); //pull the pin Low
digitalWrite(remoteOneInd, LOW); //turn off #1 LED
digitalWrite(remoteTwoInd, LOW); //turn off #2 LED
*/
Serial.begin(9600); //initialize serial comm at 9600 baud
}

// the loop() method runs over and over again,
// as long as the Arduino has power

void loop()
{
if (Serial.available() > 0) { //if Serial data is available
incomingByte = Serial.read(); //store the data in incoming byte
if(incomingByte == 'A'){ //A
digitalWrite(remoteOneInd, HIGH);
digitalWrite(remoteOneON, HIGH);
Serial.println("RemoteOneON High");
delay(100);
digitalWrite(remoteOneON, LOW);
Serial.println("RemoteOneON Low");

}
else if(incomingByte == 'B'){ //B
digitalWrite(remoteOneInd, LOW);
digitalWrite(remoteOneOFF, HIGH);
Serial.println("RemoteOneOFF High");
delay(100);
digitalWrite(remoteOneOFF, LOW);
Serial.println("RemoteOneOFF Low");
}

else if(incomingByte == 'C'){ //C
digitalWrite(remoteTwoInd, HIGH);
digitalWrite(remoteTwoON, HIGH);
Serial.println("RemoteTwoON High");
delay(100);
digitalWrite(remoteTwoON, LOW);
Serial.println("RemoteTwoOFF Low");
}

else if(incomingByte == 'D'){ //D
digitalWrite(remoteTwoInd, LOW);
digitalWrite(remoteTwoOFF, HIGH);
Serial.println("RemoteTwoOFF High");
delay(100);
digitalWrite(remoteTwoOFF, LOW);
Serial.println("RemoteTwoOFF Low");
}
}
}
