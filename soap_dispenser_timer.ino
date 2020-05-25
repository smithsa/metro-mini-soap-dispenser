#include <millisDelay.h>
int redLightPin = 2;
int greenLightPin = 4;
int blueLightPin = 0;
int virbationSensor;
millisDelay scrubDelay;
millisDelay washDelay;
millisDelay finishedCycleDelay;
int scrubDuration = 21000; // adding extra second for padding
int washDuration = 21000; // adding extra second for padding
int finishedCycleDuration = 6000; // adding extra second for padding

void setup() {
  pinMode(redLightPin, OUTPUT);
  pinMode(greenLightPin, OUTPUT);
  pinMode(blueLightPin, OUTPUT);
  setDefaultColor();
}

void loop() {
  virbationSensor = analogRead(A0);
  
  // started scrubbing, virbration sensor was triggered
  if (virbationSensor < 1022){
    scrubDelay.start(scrubDuration);
    if(scrubDelay.isRunning()){
      scrubDelay.restart();
    }
  }

  // color to indicate should be scrubbing 
  if(scrubDelay.isRunning()){
    setColorByRGB(0,255,0);
    delay(500);
    setColorByRGB(0,0,0);
    delay(500); 
  }

  // finished scrubbing and started washing
  if (scrubDelay.justFinished()) {
    setColorByRGB(0,255,0);
    washDelay.start(washDuration);
  }

  // color to indicate should be washing 
  if(washDelay.isRunning()){
    setColorByRGB(0,255,0);
  }

  // finished washing
  if (washDelay.justFinished()) {
    finishedCycleDelay.start(finishedCycleDuration);
  }

  // color to indicate finish hand washing process cycle 
  if(finishedCycleDelay.isRunning()){
    setColorByRGB(255,0,0);
  }
  
  // finish hand washing process cycle
  if (finishedCycleDelay.justFinished()) {
    setDefaultColor();
  }
}

void setColorByRGB(int redLightValue, int greenLightValue, int blueLightValue) {
  digitalWrite(redLightPin, redLightValue);
  digitalWrite(greenLightPin, greenLightValue);
  digitalWrite(blueLightPin, blueLightValue);
}

void setDefaultColor(){
  setColorByRGB(0, 0, 0);
}
