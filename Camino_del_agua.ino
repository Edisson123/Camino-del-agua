#include <Keyboard.h>

int led[] = {2, 3, 4, 5, 6, 7, 8};
//           0, 1, 2, 3, 4, 5, 6


#define echoPin 9 // Echo Pin azul
#define trigPin 10 // Trigger Pin blanco 
int maximumRange = 200;
int minimumRange = 10;
int contador = 0;
long duration, distance;

 

void setup() {


  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);
  pinMode(led[4], OUTPUT);
  pinMode(led[5], OUTPUT);
  pinMode(led[6], OUTPUT);
  pinMode(led[7], OUTPUT);


  pinMode(trigPin, OUTPUT  );
  pinMode(echoPin,  INPUT);


 
}

void loop() {
  
  
  delay(100); 
  if(ultra_sonico() != -1){
    contador += 1;
  }else{ 
    contador = 0;
  }
  if(contador >= 2){
    pulso();
    contador = 0;
  }
  

}

void pulso() {

  
  //inicializacion de la experiencia, se preciona space para reproducir el audio
  Keyboard.press((char) 0x20);
  delay(5);
  Keyboard.releaseAll();
  //------------------------------------------

 

  int lecturas[1];
  for (int i = 6; i >= 1; i=i) {

    digitalWrite(led[i - 1], HIGH);
    delay(133);
    digitalWrite(led[i - 1], LOW);
    digitalWrite(led[i], HIGH);
    digitalWrite(led[i - 2], HIGH);
    delay(1080);
    digitalWrite(led[i], LOW);
    digitalWrite(led[i - 2], LOW);
    digitalWrite(led[i - 1], HIGH);
    delay(800);
    lecturas[0] = ultra_sonico();
    digitalWrite(led[i - 1], LOW);
    delay(960);

    // este if hace que cuando llegue al final de 3 ciclos mas en los ultimos 2 leds
    
    if (i == 1) {


      for (int k = 0; k < 2; k++) {

        digitalWrite(led[i - 1], HIGH);
        delay(133);
        digitalWrite(led[i - 1], LOW);
        digitalWrite(led[i], HIGH);
        digitalWrite(led[i], HIGH);


        delay(1080);
        digitalWrite(led[i], LOW);
        digitalWrite(led[i - 2], LOW);
        digitalWrite(led[i - 1], HIGH);
        delay(800);
        digitalWrite(led[i - 1], LOW);
        delay(960);

      }
      delay(300);
 
    }

    int contador = 0;
    for (int j = 0; j < 1; j++) {

      if (lecturas[j] == -1) {
        contador += 1;
      }
      else {
        contador = 0; 
      }

    }

    if ( contador == 1) {
      i = 0;
    }

    
  }


  //Aqui se rebobina el audio para cuando llegue otro usuario
  Keyboard.press((char) 0x20);
  delay(5);
  Keyboard.releaseAll();

  Keyboard.press(KEY_LEFT_ARROW);
  delay(1500);
  Keyboard.releaseAll() ;


}


int ultra_sonico() {

  int retorno = -2;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);


  distance = duration / 58.2;

  if (distance >= maximumRange || distance <= minimumRange) {
    retorno = -1;
  }
  else
  {
    retorno = distance;
  }
  
  return retorno;

}
