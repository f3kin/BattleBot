#include <RCSwitch.h>
RCSwitch mySwitch = RCSwitch();

int pos = 0;

void setup() {
  
  Serial.begin(9600);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  mySwitch.enableReceive(0);
}

void loop() {

  if (mySwitch.available()) {
    
    int value = mySwitch.getReceivedValue();
    
    if (value > 0) {
      Serial.print(value);
      if (value == 1){digitalWrite(9, HIGH);} //means up
      else if (value == 2){digitalWrite(8, HIGH);} //means down
      else if (value == 3){digitalWrite(6, HIGH);} //means left
      else if (value == 4){digitalWrite(5, HIGH);} //means right
      else if (value == 5){digitalWrite(4, HIGH);} //means click
      else if (value == 6){ //means deaedzone
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
      }
    }
    mySwitch.resetAvailable();
  }
}
