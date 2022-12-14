//Librerias
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>    //Librería para pantalla LCD
#include "DHT.h"                

//Puertos motores
#define enable1 2
#define enable2 7
#define control1A 4
#define control1B 3
#define control2A 5
#define control2B 6
#define divisor A0

//Puertos sensores
#define outLed 13                 //Led   
#define inVoltVoltimetro A0       //Sensor de voltaje
#define inVoltLuminosidad_L A1      //Sensor de luminosidad
#define inVoltLuminosidad_B A2      //Sensor de luminosidad
#define inVoltLuminosidad_F A3      //Sensor de luminosidad
#define inVoltLuminosidad_R A4      //Sensor de luminosidad
#define DHTPIN 10                 //Sensor de temperatura
#define DHTTYPE DHT11             //Define luminosidad
#define echoPin1 53                 //Puerto de echo, sensor ultrasónico
#define trigPin1 51                //Puerto de trigger, sensor ultrasónico
#define echoPin2 49                 //Puerto de echo, sensor ultrasónico
#define trigPin2 47                //Puerto de trigger, sensor ultrasónico
#define inVoltSharp1 A8            //Sensor Sharp1
#define inVoltSharp2 A9            //Sensor Sharp2
//LCD
LiquidCrystal_I2C lcd(0x27,16,2);  //Set the LCD address to 0x27 for a 16 chars and 2 line display
//Voltaje batería 
int voltaje;
int battery;
//Luminosidad
float voltLuminosidad_L;
float voltLuminosidad_R;
float voltLuminosidad_F;
float voltLuminosidad_B;
float pwmLuminosidad_L;
float pwmLuminosidad_R;
float pwmLuminosidad_F;
float pwmLuminosidad_B;
float L_LDR;
float R_LDR;
float F_LDR;
float B_LDR;
float light_dif;
//Temperatura-Humedad
float tempC;
DHT dht(DHTPIN, DHTTYPE);
//Ultrasónico
long duracionUltrasonico;
int US_Sensor1;
int US_Sensor2;
//Sharp
long voltajeInSharp1;
long L_Sensor;
long voltajeInSharp2;
long R_Sensor;

int estado= 0; 
float L_Diff1; 
float L_Diff2; 
float L, R, F, B; 
int U1, U2, S1, S2, T; 
void setup() {
  Serial.begin(9600);
  //setup motores 
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  pinMode(control1A, OUTPUT);
  pinMode(control1B, OUTPUT);
  pinMode(control2A, OUTPUT);
  pinMode(control2B, OUTPUT);
  //setup sensores
  pinMode(outLed, OUTPUT);
  pinMode(inVoltLuminosidad_L, INPUT);
  pinMode(inVoltLuminosidad_R, INPUT);
  pinMode(inVoltLuminosidad_F, INPUT);
  pinMode(inVoltLuminosidad_B, INPUT);
  pinMode(inVoltVoltimetro, INPUT);
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT); 
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT); 
  pinMode(inVoltSharp1, INPUT); 
  pinMode(inVoltSharp2, INPUT); 
  //Inicialización del la pantalla LCD
  lcd.init();    
  lcd.backlight();
  //lcd.setCursor(0,0);
  //lcd.clear();
  Serial.println("lcd");
  //Inicialización de la comunicación con el sensor de humedad
  dht.begin();
}

void loop() {
  L = L_L(); 
  R = R_L(); 
  F = F_L(); 
  B = B_L(); 
  L_Diff1 = R-L;
  L_Diff2 = F-B;  
  T = temperatureSensor(); 
  U1 = US1(); 
  U2 = US2(); 
  S1 = sharp1(); 
  S2 = sharp2(); 
  switch(estado){
    case 0://stop o inicio 
      estado = 1; 
      //LCD_print("Stop");
      driveRobot(0,0); 
      delay(500); 
      break; 
    case 1://mover adelante si no hay obstaculos y si luz está adelante
      if(L_Diff1>50 || L_Diff1<25 ){
        estado = 2;
      }else if (L_Diff2<25){
        estado = 3;
      }else{
        estado = 0; 
        //driveRobot(-1, -1); 
        LCD_print("Adelante", L_Diff1);
      }
      break; 
    case 2: //Mover hacia algún lado si se encuentra un obstáculo
      if(L_Diff1>45){ //Movimiento hacia la derecha
        estado = 0; 
        driveRobot(-1, 1); 
        LCD_print("Derecha", L_Diff1); 
      }else if(L_Diff1<25){ //Movimiento hacia la izquierda
        estado = 0; 
        driveRobot(1, -1); 
        LCD_print("Izquierda", L_Diff1); 
      } 
      break;  
    case 3:  //Rotamos el robot para evadir ostáculos
      estado = 0; 
      driveRobot(-1, 1); 
      LCD_print("Rotando", L_Diff1); 
      break;
  }
}


void driveRobot(float LSignal, float RSignal){ //función driverobot
  //utiliza ifs para setear los lows, highs y bits para realizar cada movimiento
  //atras
  if(LSignal==1 && RSignal==1){
    analogWrite(enable1, 220); 
    digitalWrite(control1A, HIGH);
    digitalWrite(control1B, LOW); 
    analogWrite(enable2, 255);
    digitalWrite(control2A, HIGH);
    digitalWrite(control2B, LOW); 
    }
    //adelante
    if(LSignal==-1 && RSignal==-1){
    analogWrite(enable1, 200); 
    digitalWrite(control1A, LOW);
    digitalWrite(control1B, HIGH); 
    analogWrite(enable2, 255);
    digitalWrite(control2A, LOW);
    digitalWrite(control2B, HIGH); 
    }
    //izquierda
    if(LSignal==1 && RSignal==-1){
    analogWrite(enable1, 220); 
    digitalWrite(control1A, HIGH);
    digitalWrite(control1B, LOW); 
    analogWrite(enable2, 255);
    digitalWrite(control2A, LOW);
    digitalWrite(control2B, HIGH); 
    }
    //derecha
    if(LSignal==-1 && RSignal==1){
    analogWrite(enable1, 220); 
    digitalWrite(control1A, LOW);
    digitalWrite(control1B, HIGH); 
    analogWrite(enable2, 255);
    digitalWrite(control2A, HIGH);
    digitalWrite(control2B, LOW); 
    }
    //stop
    if(LSignal==0 && RSignal==0){
    analogWrite(enable1, 0); 
    digitalWrite(control1A, LOW);
    digitalWrite(control1B, LOW); 
    analogWrite(enable2, 0);
    digitalWrite(control2A, LOW);
    digitalWrite(control2B, LOW); 
    }
}


void voltageSensor(){ //Utilizamos este método para sacar energía de la pila según lo necesitamos
  voltaje = analogRead(inVoltVoltimetro); //*5/1023;
  Serial.print("V: ");
  Serial.print(voltaje*5/1023);
  Serial.print(" v -- ");
  if(voltaje < 687)  //687 bits ==> 6.4 V
    battery = 0;
  else
    battery = 1;
}

float L_L(){ //Luminosidad izquierda
  voltLuminosidad_L = analogRead(inVoltLuminosidad_L);  
  L_LDR = map(voltLuminosidad_L, 0, 1023, 0, 255);
  return L_LDR; 
  }
float R_L(){//Luminosidad derecha
  voltLuminosidad_R = analogRead(inVoltLuminosidad_R);  
  R_LDR = map(voltLuminosidad_R, 0, 1023, 0, 255);
  return R_LDR; 
  }
float F_L(){//Luminosidad de frente
  voltLuminosidad_F = analogRead(inVoltLuminosidad_F);  
  F_LDR = map(voltLuminosidad_F, 0, 1023, 0, 255);
  return F_LDR; 
  }
float B_L(){//Luminosidad trasera
  voltLuminosidad_B = analogRead(inVoltLuminosidad_B);  
  B_LDR = map(voltLuminosidad_B, 0, 1023, 0, 255);
  return B_LDR; 
  }

int temperatureSensor(){ //Utilizamos este método para eer el valor de la temperatura
    tempC = dht.readTemperature();
    if ( isnan(tempC)  ) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return 1;
    } else {
     return tempC;
     }  
}

int US1(){//sensor ultrasónico de la izquierda
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duracionUltrasonico = pulseIn(echoPin1, HIGH);
  US_Sensor1 = duracionUltrasonico * 0.0343 / 2;
  return US_Sensor1; 
  }
int US2(){//sensor ultrasónico de la derecha
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duracionUltrasonico = pulseIn(echoPin2, HIGH);
  US_Sensor2 = duracionUltrasonico * 0.0343 / 2;
  return US_Sensor2; 
  }
long sharp1(){//sensor sharp de la izquierda
   voltajeInSharp1 = analogRead(inVoltSharp1);
   //L_Sensor = pow(voltajeInSharp1/758.73,-1/.486);
   return voltajeInSharp1; 
  }
long sharp2(){//sensor sharp de la derecha
  voltajeInSharp2 = analogRead(inVoltSharp2);
  //R_Sensor = pow(voltajeInSharp2/758.73,-1/.486);
  }
void LCD_print(String mensaje, int L_Diff){ //Utilizamos este método para imprimir mnensajes en la pantalla LCD
  lcd.setCursor(0,0);
  lcd.print("                  ");
  lcd.setCursor(0,1);
  lcd.print("                  ");
  lcd.setCursor(0,0);
  lcd.print(mensaje);
  lcd.setCursor(0,1);
  lcd.print(String(L_Diff));
  }
