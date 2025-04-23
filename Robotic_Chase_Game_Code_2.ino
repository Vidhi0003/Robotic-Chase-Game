#include <SoftwareSerial.h>
#include <Servo.h>


Servo myservo; //servo motor
SoftwareSerial mySerial(0, 1);


int pos = 0;    // variable to store the servo position
const int trigPin = 9; //pin output ultrasonic sensor
const int echoPin = 10; //pin input ultrasonic sensor


float duration, distance;//stored distance of ultrasonic sensor


bool catch1=false;
int prevDistance=0;//tracker same dist not read twice
unsigned long previousMillis=0;// tracker for trig pin millis
unsigned long previousMillis2=0;// tracker for trig pin Millis2
unsigned long previousMillis3=0;// tracker for trig pin Millis3
unsigned long catchMillis=0;// tracker for catch
unsigned long ctMillis=0;// tracker for counter
unsigned long sMillis=0;// tracker for servoMillis


const long interval=.002;//interval
const long interval2=.01;//interval2
const long interval3=2000;//interval3
const long sInterval=.01;//servo Interval
const long cInterval=200;//count Interval
int serDirection=8;//position direction


bool start=false;//bool to trigger start


int ready=0;//reader from lcd arduino to start


int counter = 0; //tracker for catch
int currentState = 0;//pos of current direction
int previousState = 0;//pos of prev direction


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  myservo.attach(5);  // attaches the servo on pin 9 to the Servo object
}


void loop() {
  unsigned long currentMillis = millis();  //current time
  if(mySerial.available() > 0){
      ready=mySerial.read(); //stores read in value from LCD ARDUINO
      if(ready==9){//lcd arduino sends 9 to indicate ready
        start=true; //triggers game to start
      }
      else{ //sends 8 to stop catch
        start=false; //triggers game to stop
        mySerial.write(ready);//send to mouse arduino to stop
        counter=0;//reset count
        currentState=0; //reset currentState
      }
      Serial.println(ready);//print value read in
  }
    if(start==true){
      if(currentMillis-sMillis>=sInterval){ //moves servo
        pos+= serDirection;//increments pos by 8
        myservo.write(pos); //write pos to servo
        if(pos>=180 || pos<=0){ //make sure the servo rotates 180
          serDirection=-serDirection; //resets serDirection
        }
        sMillis=currentMillis; //servo rotating to .01 milliseconds


      }
      if (currentMillis - previousMillis >= interval){ //pause reading and outputting pins of ultrasonic sensor
          digitalWrite(trigPin, LOW);
          if(currentMillis-previousMillis2>=interval2){
          digitalWrite(trigPin, HIGH);
          if(currentMillis-previousMillis3>=interval2){
            digitalWrite(trigPin, LOW);
            previousMillis=currentMillis;
            previousMillis2=currentMillis;
            previousMillis3=currentMillis;


              }
            }
          }
              duration = pulseIn(echoPin, HIGH); //reading in from ultrasonic sensor
              distance = (duration/2) / 29.1; //converting distance cm
        if(currentMillis-catchMillis>=interval3){
              Serial.println(distance); //prints distance detected
              Serial.println("distance");
              if (distance <10){  //if distance less 10cm-catch triggered
                currentState = 1;
              }
              else {
              currentState = 0; //no catch
              }
              if(currentState != previousState){
                if(currentState == 1 && counter<=2){ //catch detected and count is not over 2
                  if(millis()-ctMillis>=cInterval){ //pause to increment count and sending it
                    counter = counter + 1; //counter should stop at 3
                    mySerial.write(counter);
                    Serial.println(counter);
                    ctMillis=currentMillis;
                  }
              }
              previousState=currentState;//ensures no same distance is detected
              catchMillis=currentMillis;//updates catchMillis
            }
         
      }
    }
}
