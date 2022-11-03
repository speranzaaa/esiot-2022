#include "Led.h"
#include "Timer.h"
#include "ButtonImpl.h"

#define LED_PIN 13
#define BUTTON_PIN 2 

Light* led;
Button* button;
Timer timer;

enum { ON, OFF, SWITCHING_ON, SWITCHING_OFF} state;

void setup(){
  Serial.begin(9600);
  led = new Led(LED_PIN); 
  button = new ButtonImpl(BUTTON_PIN);
  state = OFF;
  timer.setupPeriod(50);
}

void step(){
  button->sync();
  switch (state){    
    case OFF:
      if (button->isPressed()){
        state = SWITCHING_ON;
      }
      break;
    case SWITCHING_ON:
      led->switchOn();
      Serial.println("ON");
      state = ON;
      break;
    case ON:
      if (!button->isPressed()){
        state = SWITCHING_OFF;
      }
      break;
    case SWITCHING_OFF:
      led->switchOff();
      Serial.println("OFF");
      state = OFF;
      break;
  }
}

void loop(){
  timer.waitForNextTick();
  step();
};
