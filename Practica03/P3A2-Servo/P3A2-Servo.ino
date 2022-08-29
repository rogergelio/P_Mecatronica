#include <Servo.h>

#define pot A0

float value = 0;
int angulo = 0;

Servo servo1;


void setup() {
  servo1.attach(3);  
  Serial.begin(9600);
}


void loop() {

  value = analogRead(pot);
  //angulo = map(variable, valmin, valmax, valmin, valmax);
  angulo = map(value, 0, 1023, 0, 180);
  servo1.write(angulo);
  delay(100);
  
}
