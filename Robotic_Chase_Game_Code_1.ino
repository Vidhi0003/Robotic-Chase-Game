#include "pitches.h"
#include <SoftwareSerial.h>
#include <Wire.h>

SoftwareSerial mySerial(0, 1);

int note = NOTE_B5;

const int buzzer = 8;

const int button = 3;

//The pins for the LEDs
const int ledPin = 4;
const int ledPin2 = 5;
const int ledPin3 = 6;

// Used to update the state of the LEDs
int ledState = LOW;
int ledState2 = LOW;
int ledState3 = LOW;

int count = 0;

// This will help keep track of how long the buzzer buzzes
unsigned long previousMillis = 0;

int interval = 0;

void setup() {
  // This sets up the leds as an output
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);

//This starts the serial monitor for my device
  mySerial.begin(9600);
}

//This runs the code as a loop that will show any changes made
void loop() {

  //This gets the current time spent causing the buzzer to buzz
  unsigned long currentMillis = millis();

  //This reads in from other arduino
  if(mySerial.available() > 0)
  {

    //This reads in the value given by the other Arduino
    count = mySerial.read();

    // When 8 is read, the devices will all reset
    if(count == 8)
    {
      // This resets the LEDs
      ledState = LOW;
      ledState2 = LOW;
      ledState3 = LOW;
      digitalWrite(ledPin, ledState);
      digitalWrite(ledPin2, ledState2);
      digitalWrite(ledPin3, ledState3);

      //Turns off the buzzer and the count resets to 0
      count = 0;
      noTone(buzzer);
    }
    else
    {
      Serial.println(count);

      // LED lights up when the mouse is first caught
      if(count == 1)
      {
        ledState = HIGH;
        digitalWrite(ledPin, ledState);

        ledState2 = LOW;
        ledState3 = LOW;

        //Tells the scoreboard to update to 1 for the arduino it sends information to
        mySerial.write(1);
      }
      //LED lights up when the mouse if caught a second time
      else if(count == 2)
      {
        ledState2 = HIGH;
        digitalWrite(ledPin2, ledState2);

        //Tells the scoreboard to update to 2 for the arduino it sends information to
        mySerial.write(2);
      }
      //The third LED lights up when the mouse is caught and this will help determine if the buzzer buzzes or not
      else if(count == 3)
      {
        ledState3 = HIGH;
        digitalWrite(ledPin3, ledState3);

        //Tells the scoreboard to update to 3 and say game over
        mySerial.write(3);
      }

      //If the cat has caught the mouse for the third time, this signifies game over with the buzzer buzzing
      if(ledState3 == HIGH)
      {
        if(currentMillis - previousMillis >= interval)
        {
          //This is the noise the buzzer will make
          tone(buzzer, note, 2000);
            
          //This takes into account the time spent with making this sound
          previousMillis = currentMillis;
        }
      }   
    }
  }
}





