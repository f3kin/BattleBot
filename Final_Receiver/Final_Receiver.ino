// MOTOR SETUP

#define MAX_PWM 255
#define START_TEST 1
#define STOP_TEST 0

//Motor A
int enA = 9;
int inA1 = 8;
int inA2 = 7;

//Motor B
int enB = 13;
int inB1 = 12;
int inB2 = 11;

// RC SET UP

#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

int click_pin = 3;
int pos = 0;

void setup() {
  // MOTOR SETUP
  
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT); // determines the speed of motor A
  pinMode(enB, OUTPUT);
  pinMode(inA1, OUTPUT); //determines if motor A is turned on, will go to the set speed
  pinMode(inA2, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);
  
  // Turn off motors - Initial state
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);

  // RC SETUP
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(click_pin, OUTPUT);

  digitalWrite(click_pin, LOW);

  mySwitch.enableReceive(0);
  
  Serial.begin(9600);
}

void loop() {
  
  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value > 0) {
      
      //Serial.print(value);
      if (value == 5) {digitalWrite(click_pin, HIGH);}
      
      else{turn(value);}
      
    }
    
//    digitalWrite(click_pin, LOW);
    mySwitch.resetAvailable();
    
  }
  
}

void turn(int value) { //start just with forward, reverse, left, right, know value > 0
  analogWrite(enA, MAX_PWM);
  analogWrite(enB, MAX_PWM);
  
  if (value == 1){ //move forwards
    digitalWrite(inA2, HIGH);
    digitalWrite(inA1, LOW);
    digitalWrite(inB2, LOW);
    digitalWrite(inB1, HIGH);}
    
  else if (value == 2){ // move backwards
    digitalWrite(inA2, LOW);
    digitalWrite(inA1, HIGH);
    digitalWrite(inB2, HIGH);
    digitalWrite(inB1, LOW);}
    
  else if (value == 3){ // move left
    digitalWrite(inA2, LOW);
    digitalWrite(inA1, HIGH);
    digitalWrite(inB2, LOW);
    digitalWrite(inB1, HIGH);}

  else if (value == 4){ // move right
    digitalWrite(inA2, HIGH);
    digitalWrite(inA1, LOW);
    digitalWrite(inB2, HIGH);
    digitalWrite(inB1, LOW);}
    
  else if (value == 6){ //means deaedzone
    digitalWrite(inA2, LOW);
    digitalWrite(inA1, LOW);
    digitalWrite(inB2, LOW);
    digitalWrite(inB1, LOW);}
    
}
