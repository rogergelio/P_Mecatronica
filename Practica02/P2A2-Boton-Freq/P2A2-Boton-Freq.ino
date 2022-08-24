
#define LED 13  
#define BTN 12 
int button_state;

void setup() {
  // put your setup code here, to run once:
  pinMode (LED,OUTPUT );
  pinMode (BTN, INPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  button_state = digitalRead (BTN);

  if (button_state == 1){
    //Rutina de 4 Hz
    digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(250);                       // wait for a second
    digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
    delay(250); 

  }

  else{
    
    //Rutina de 1 Hz
    digitalWrite (LED,HIGH);
    delay(1000);
    digitalWrite (LED,LOW);
    delay(1000);

  }
  
  
  
  


}
