#include <ezButton.h>

#define MAX_PWM 255
#define START_TEST 1
#define STOP_TEST 0

//swtich
ezButton button(10);
int loopState = STOP_TEST;

//Motor A
int enA = 9;
int inA1 = 8;
int inA2 = 7;

//Motor B
int enB = 13;
int inB1 = 12;
int inB2 = 11;

int count = 1;

void setup() {
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

  // Define button
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
  Serial.begin(9600);

}

void loop() {
  button.loop(); // MUST call the loop() function first
   if (button.isPressed()) {
    Serial.print("pressed");
    if (loopState == STOP_TEST)
      loopState = START_TEST;
    else if(loopState == START_TEST)
      loopState = STOP_TEST;
  }
  Serial.print(count);
  if (count % 2 == 0){
    loopState = STOP_TEST;
  }
  if (loopState == START_TEST){
    Serial.print("yes");
    turn();
    speed_test();
    count++;
  }
  loopState = STOP_TEST;
}

void turn(){
  
  //Set Max motor speed
  analogWrite(enA, MAX_PWM);
  analogWrite(enB, MAX_PWM);

  //Go one way
  digitalWrite(inA2, LOW);
  digitalWrite(inA1, HIGH);
  digitalWrite(inB2, LOW);
  digitalWrite(inB1, HIGH);

  //Pause
  delay(2000);

  //Go the other way
  digitalWrite(inB1, LOW);
  digitalWrite(inA1, LOW);

  delay(2000);
  
  digitalWrite(inB2, HIGH);
  digitalWrite(inA2, HIGH);

  //Pause
  delay(2000);

  //turn off motors
  digitalWrite(inB2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inA1, LOW);

  delay(1000);
}

void speed_test(){
  //Turn on motors in first direction
  digitalWrite(inB2, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inA1, HIGH);


  //Go up to maximum speed
  for(int i = 0; i < MAX_PWM + 1; i++){
    analogWrite(enB, i);
    analogWrite(enA, i);
    delay(20);
  }

  //Pause
  delay(1000);

  //Decelerate back to zero
  for(int i = 255; i >= 0; i--){
    analogWrite(enB, i);
    analogWrite(enA, i);
    delay(20);
  }

  //turn off motors

  digitalWrite(inB2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inA1, LOW);
}
