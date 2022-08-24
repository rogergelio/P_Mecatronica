#define R1 8
#define Y1 9
#define G1 10
#define R2 11
#define Y2 12
#define G2 13

void setup() {
  pinMode(R1,OUTPUT);
  pinMode(Y1,OUTPUT);
  pinMode(G1,OUTPUT);
  pinMode(R2,OUTPUT);
  pinMode(Y2,OUTPUT);
  pinMode(G2,OUTPUT);
}// setup

void loop() {
  digitalWrite(Y1,LOW);
  digitalWrite(R2,LOW);
  digitalWrite(R1,HIGH);
  digitalWrite(G2,HIGH);
  delay(5000);
  digitalWrite(G2,LOW);
  digitalWrite(Y2,HIGH);
  delay(1000);
  digitalWrite(Y2,LOW);
  digitalWrite(R2,HIGH);
  digitalWrite(R1,LOW);
  digitalWrite(G1,HIGH);
  delay(5000);
  digitalWrite(G1,LOW);
  digitalWrite(Y1,HIGH);
  delay(1000);
  
  
}// loop
