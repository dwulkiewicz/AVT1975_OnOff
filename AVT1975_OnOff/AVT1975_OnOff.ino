/************************************************************************/
/*                                                                      */
/*              Project:  AVT1975_OnOff                                 */
/*              Hardware: ATtiny 25/85                                  */
/*                                                                      */
/*              Author: Dariusz Wulkiewicz                              */
/*                      d.wulkiewicz@gmail.com                          */
/*                                                                      */
/*              Date: 02.2021                                           */
/************************************************************************/
#include <Arduino.h>
#include <math.h>


const int dimmingTimePin = A2; //PB4; //3;  // Regulacja czasu zjaśniania / zciemniania 
const int ledStatusPin   = PB1; //6;  // Status LED
const int switchStatePin = PB2; //7;  // wejście stanu przełącznika 
const int outputPin      = PB0; //5;  // wyjście PWM do LED

const boolean stateOn = LOW;
const boolean stateOff = HIGH;

const int offLevel = 0; 
const int onLevel = 255;

//Dzielenie poprzez przesunięcie w prawo o pozycję czyli podział o 2 w jednym kroku 
// np. 6 kroków daje podział przez 64 czyli 1024 / 64 to daje 16ms na jeden krok zmiany PWM
// 255 kroków PWM * 16ms na krok daje 4080 ms maksymalnego czas ściemniania / rozjaśniania (minimium to 1ms * 255 kroków = 255ms) 
const int shiftDimmingSteps = 6;

int currentLevel = 0; 

void setup() {
  pinMode(ledStatusPin, OUTPUT); 
  pinMode(switchStatePin, INPUT);
  pinMode(outputPin, OUTPUT); 
}

void loop() {
  boolean switchState = digitalRead(switchStatePin);
  if(switchState == stateOn && currentLevel < onLevel) {    
    currentLevel += 5;      
    digitalWrite(ledStatusPin, HIGH);  
    delay(analogRead(dimmingTimePin) >> shiftDimmingSteps);
    digitalWrite(ledStatusPin, LOW);           
    analogWrite(outputPin, currentLevel);     
  }  
  else if(switchState == stateOff && currentLevel > offLevel) {    
    currentLevel -= 5;  
    digitalWrite(ledStatusPin, HIGH);  
    delay(analogRead(dimmingTimePin) >> shiftDimmingSteps);
    digitalWrite(ledStatusPin, LOW);      
    analogWrite(outputPin, currentLevel);     
  } 
}
