#define pot A0
#define led 13

float value = 0;
float voltaje;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600); //Nos permite comunicarnos entre la computadora y el arduino a esa velocidad de 9600 

}

void loop() {
  value = analogRead(pot);
  voltaje = value/1023*5;
  Serial.print("Voltaje: ");
  Serial.println(voltaje);

  if(voltaje > 3){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
  
  delay(100);
}
