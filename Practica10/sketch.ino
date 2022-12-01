/**
 * @author Diego Hernández Delgado 
 * @author Sebastián González Hacker
 * @author Rogelio Torres Olivera
 * @author Santiago Moreno Rojas
 * @professor Sergio Hernández Sánchez
 * @date 23-11-2022
 * @university ITAM
 * @subject Principios de Mecatrónica
 * @details Hola
*/

// Definición de puertos y variables
#define LED 13

int estado;
int light_dif;

// Función de setup 
void setup() {
  //Definición del puerto como salida y baudaje de 9600 en el Serial
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}


// Función loop
void loop() {
  //Switch con el estado que le da sentido a la máquina de estado
  switch(estado){
    case 0:
      Serial.println("Estado 0");
      estado = 1;
      break;
      
    case 1:
      Serial.println("Estado 1");
      digitalWrite(LED, LOW); //Se apaga el led
      lightSensor();
      //Si la diferencia de luz entre el fotorresistor derecho y el izquierdo es menor a 30, 
      // se pasa al estado dos y si no se pasa al estado 0
      if( abs(light_dif) < 30 ){
        estado = 2; 
      }else{
        estado = 0;
      }
      break;
      
    case 2:
      Serial.println("Estado 2");
      digitalWrite(LED, HIGH); // Se enciende el led
      delay(1000);
      break;
  }
}

//Función auxiliar que simula la diferencia de los sensores de luz
void lightSensor(){
  light_dif = 20;
  
}
