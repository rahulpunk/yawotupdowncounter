#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
const int analogPin = A4; 
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7);

//Compatible with the Arduino IDE 1.0
//Library version:1.1




// this constant won't change:
const int  Up_buttonPin   = 6;    // the pin that the pushbutton is attached to
const int  Down_buttonPin = 7;

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int up_buttonState = 0;         // current state of the up button
int up_lastButtonState = 0;     // previous state of the up button

int down_buttonState = 0;         // current state of the up button
int down_lastButtonState = 0;     // previous state of the up button
bool bPress = false;

void setup()
{
  Serial.begin(9600);
  pinMode( Up_buttonPin , INPUT_PULLUP);
  pinMode( Down_buttonPin , INPUT_PULLUP);
  lcd.begin (16,2); // for 16 x 2 LCD module
 lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Yawot Up Down");
  lcd.setCursor(2,1);
  lcd.print("Pulse Counter   ");
  lcd.setCursor(20,1);
  lcd.print(buttonPushCounter);
 
}


void loop()
{
   checkUp();
   checkDown();

   if( bPress){
       bPress = false;
      lcd.setCursor(20,1);
      lcd.print("               ");
      lcd.setCursor(20,1);
      lcd.print(buttonPushCounter);
   }
  
}

void checkUp()
{
  up_buttonState = digitalRead(Up_buttonPin);

  // compare the buttonState to its previous state
  if (up_buttonState != up_lastButtonState) {
    // if the state has changed, increment the counter
    if (up_buttonState == LOW) {
        bPress = true;
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  up_lastButtonState = up_buttonState;
}
void checkDown()
{
  down_buttonState = digitalRead(Down_buttonPin);

  // compare the buttonState to its previous state
  if (down_buttonState != down_lastButtonState) {
    // if the state has changed, increment the counter
    if (down_buttonState == LOW) {
        bPress = true;
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter--;
     
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  down_lastButtonState = down_buttonState;
}
