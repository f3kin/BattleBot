#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

#define joyX A1
#define joyY A0
#define click_pin 2

int hozdead = 503;
int verdead = 493;
int pos = 0; 
int xValue = 0; //zeroes at 494
int yValue = 0; //zeroes at 504
int clickValue = 1; //will become zero if the button is pressed


void setup() {
  
  Serial.begin(9600);
  mySwitch.enableTransmit(10);
  
}

void loop() {
  
  //Read Joystick
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  clickValue = digitalRead(click_pin);

  Serial.print("x: ");
  Serial.print(xValue);
  Serial.print("\t");
  Serial.print("y: ");
  Serial.println(yValue);
  Serial.print("\t");
  Serial.print("Click: ");
  Serial.println(clickValue);
  Serial.print("\t");
  Serial.print("Position: ");
  
  //Joystick Up
  if (yValue > verdead + 30){pos = 1; Serial.println(pos);}
  
  //Joystick Down
  if (yValue < verdead - 30){pos = 2; Serial.println(pos);}
  
  //Joystick Left
  if (xValue > hozdead + 30){pos = 3; Serial.println(pos);}
  
  //Joystick Right
  if (xValue < hozdead - 30){pos = 4; Serial.println(pos);}
  
  //Joystick approx. centred
  if (yValue > verdead - 20 && yValue < verdead + 20 && xValue > hozdead - 20 && xValue < hozdead + 20)
  {pos=6; Serial.println(pos);}

  if (clickValue != 1){pos = 5;}
  
  mySwitch.send(pos, 24);

  pos = 0;
}
