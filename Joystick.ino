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

Gains mygains[2];
EffectParams myeffectparams[2];
int32_t forces[2] = {0};

void setup() {
  // Initialize Button Pins

  for(int i = 0; i < numarButoane; i++)
  {
    pinMode(i, INPUT_PULLUP);
  }

  pinMode(13, OUTPUT);

  // Initialize Joystick Library
  Joystick.begin();
  Keyboard.begin();
  
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(0, 1023);

  Joystick.setRxAxisRange(0, 1023);
  Joystick.setRyAxisRange(0, 1023);

   mygains[0].totalGain = 100;
   mygains[0].springGain = 100;

   Joystick.setGains(mygains);
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

  int value = analogRead(A2);
  //set X Axis Spring Effect Param
  myeffectparams[0].springMaxPosition = 1023;
  myeffectparams[0].springPosition = value;

  Joystick.setEffectParams(myeffectparams);
  Joystick.getForce(forces);
  if(forces[0] > 0){
    digitalWrite(13,HIGH);
  }else{
    digitalWrite(13,LOW);
  }
}
