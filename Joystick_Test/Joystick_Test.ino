#define joyX A0
#define joyY A1
#define click_pin 2
int xValue = 0; //zeroes at 494
int yValue = 0; //zeroes at 504
int clickValue = 1; //will become zero if the button is pressed
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  clickValue = digitalRead(click_pin);
 
  //print the values with to plot or view
  Serial.print(xValue);
  Serial.print("\t");
  Serial.println(yValue);
  Serial.print("\t");
  Serial.println(clickValue);
}
