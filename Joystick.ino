#include <Joystick.h>
#include <Keyboard.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK ,
  8, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  true, true, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

int lastButtonState[8] = {0,0,0,0,0,0,0};

int numarButoane = 8;

int buttonPin[8] = {3, 4, 5, 6, 9, 10, 11, 12};

void setup() {
  // Initialize Button Pins

  for(int i = 0; i < numarButoane; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }

  // Initialize Joystick Library
  Joystick.begin();
  Keyboard.begin();
  
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(0, 1023);

  Joystick.setRxAxisRange(0, 1023);
  Joystick.setRyAxisRange(0, 1023);
}



void loop() {
  for(int i = 0; i < numarButoane; i++)
  {
    int currentButtonState = !digitalRead(buttonPin[i]);
    
    if (currentButtonState != lastButtonState[i])
    {
      Joystick.setButton(i, currentButtonState);
      lastButtonState[i] = currentButtonState;
    }
  }
  
  if(digitalRead(7) == 1) 
  {
    Keyboard.press(KEY_ESC);
  }
  else
  {
    Keyboard.releaseAll();
  }

  float xRange = analogRead(A2);
  float yRange = analogRead(A3);

  Joystick.setXAxis(1023 - xRange);
  Joystick.setYAxis(1023 - yRange);

  xRange = analogRead(A4);
  yRange = analogRead(A5);

  Joystick.setRxAxis(1023 - xRange);
  Joystick.setRyAxis(1023 - yRange);
  
  delay(5);
}
