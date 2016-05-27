#include <Mouse.h>
#include <Keyboard.h>

const int buttonNum = 4;

int triggerPin = 23;
int analogInputX = 11; // opravit pro Due
int analogInputY = 10; // opravit pro Due

int triggerState = 0;
int buttonPin[buttonNum] = {50,51,52,53};
int buttonState[buttonNum];
char buttonKey[buttonNum] = {'w', 'u', 's', 'g'};
int x;
int y;

//mouse settings
int offsetX = 330; // opravit podle joysticku
int offsetY = 330; // opravit podle joysticku
int stred = 0; // nastavit stred
int mouse_move_size_X = 8;
int mouse_move_size_Y = 8;

//on off button settings
int turnONButtonPin = 12;
int turnONLedPin = 13;
bool turnedON = false;
bool turnONButtonPressed = false;
int turnONButtonState = LOW;

int refresh = 5;
bool shouldRefresh = false;
unsigned long lastTimeRefresh;

void setup() {

  pinMode(analogInputX, INPUT);
  pinMode(analogInputY, INPUT);
  
  //don't know what this does
  //attachInterrupt(digitalPinToInterrupt(triggerPin),trigger,RISING);
  
  for (int i=0; i < buttonNum; i++) {
    pinMode(buttonPin[i], INPUT);
  }
  lastTimeRefresh = millis();
}

void loop() {
	//looking ahead for fMRI synchropuls
	if (digitalRead(triggerPin) == HIGH){
    SynchroPulse();
	}
  turnONButtonState = digitalRead(turnONButtonPin);
  if (turnONButtonState == HIGH && !turnedON) {
    TurnON();
  }
  //as we don't have update with delay, we check if the keyboards or mice were moved in last (refresh miliseconds)
  if ((millis() - lastTimeRefresh) > refresh){
    lastTimeRefresh = millis();
    shouldRefresh = true;
  }
  if (turnedON && shouldRefresh){
	  shouldRefresh = false;
    //reading the mouse
    x = -(analogRead(analogInputX) - offsetX);
    y = +(analogRead(analogInputY) - offsetY);
    
    if (x > stred) {
      Mouse.move(mouse_move_size_X,0);
    }
    if (x <= stred) {
      Mouse.move(-mouse_move_size_X,0);
    }
    if (y > stred) {
      Mouse.move(0,-mouse_move_size_Y);
    }
    if (y <= stred) {
      Mouse.move(0,mouse_move_size_Y);
    }
    for (int i=0; i < buttonNum; i++) {
      buttonState[i] = digitalRead(buttonPin[i]);
      if (buttonState[i] == HIGH) {
        Keyboard.press(buttonKey[i]);
      } else {
        Keyboard.release(buttonKey[i]);
      }
    }
  }
  if (turnONButtonState == LOW && turnedON) {
    TurnOFF();
  }
}
void TurnON(){
  turnedON = true;
  digitalWrite(turnONLedPin, HIGH);
  Keyboard.begin();
  Mouse.begin();
  Calibrate();
}
void TurnOFF(){
  Keyboard.end();
  Mouse.end();
  turnedON = false;
  digitalWrite(turnONLedPin, LOW);
}
void SynchroPulse() {
  Keyboard.write('o');
}
void Calibrate(){
  //setting up offset
  int defXInput[20] = {};
  int defYInput[20] = {};
  //getting the offsets right
  for (int n = 0; n < 19; n++){
    defXInput[n] = analogRead(analogInputX);
    defYInput[n] = analogRead(analogInputY);  
  }
  offsetX = GetOffsetMedian(defXInput);
  offsetY = GetOffsetMedian(defYInput);
}
// helpers
int GetOffsetMedian(int array[]){
  int median = array[sizeof(array)/2];
  return(median);
}
