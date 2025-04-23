#include <LiquidCrystal.h>


// Initializing the library with the LCD interface pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 7, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


const int buttonPin = 10; // Button pin
unsigned long previousMillis = 0; // Used to store the last updated time
const long interval = 1000; // Interval for 1 second
bool timerActive = false; // Tracks whether the timer is running
unsigned long timerStartMillis = 0; // Time when the timer started
int score; //Keeps track of score
int lastButtonState = LOW; // Last state of the button
int currentButtonState; // Current state of the button


//setting up button and LCD
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(buttonPin, INPUT);
  lcd.setCursor(0, 1);
  lcd.print("Click to Start");
  lcd.setCursor(0, 0);
  lcd.print("Score: 0");
}


void loop() {


  //Getting the current time
  unsigned long currentMillis = millis();
 
  //Read the button state
  currentButtonState = digitalRead(buttonPin);


  //If button is clicked
  if (currentButtonState == HIGH && lastButtonState == LOW) {
   
    //Set timer active status
    timerActive = !timerActive;
   
    //If timer is active
    if (timerActive) {


      //Write 9 to cat arduino to initiate start of game
      Serial.write(9);


      timerStartMillis = currentMillis;


      //Display information on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Score: 0");
      lcd.setCursor(0, 1);
      lcd.print("Timer: 0 secs");


    }
  }


  // Update the timer display if the timer is active
  if (timerActive && currentMillis - previousMillis >= interval) {


    //updating time
    previousMillis = currentMillis;
    unsigned long elapsedSeconds = (currentMillis - timerStartMillis) / 1000;


    //Setting timer to be updating every second
    lcd.setCursor(0, 1);
    lcd.print("Timer: ");
    lcd.print(elapsedSeconds);
    lcd.print(" secs ");


    //If I recieve anything from mouse arduino
    if (Serial.available() > 0) {


      //store the count sent into a score int
      score = Serial.read();


      //If score is between 1 and 3, display it
      if (score >= 1 && score <= 3) {
        lcd.setCursor(0, 0);
        lcd.print("Score: ");
        lcd.print(score);
     
      }
    }


    //If score is at 3, the game is over
    if(score == 3) {
         
      //Write 8 to cat arduino to indicate game is over
      Serial.write(8);


      //Display score and game over message on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Score: ");
      lcd.print(score);
      lcd.setCursor(0, 1);
      lcd.print("GAME OVER! ");
     
      //reset active status of timer and score to 0
      timerActive = !timerActive;
      score = 0;


    }
  }


  //updating button state
  lastButtonState = currentButtonState;
}

