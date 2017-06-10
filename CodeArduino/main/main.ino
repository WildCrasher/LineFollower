#include "Ultrasonic.h"
#define TRIGG 0
#define ECHO 1
#define LED 2
int czy_przeszkoda = 0;
int range = 0;  
int blad, pop_blad = 0, Kp = 2, Kd = 5;    //kp=3 kd=1 // kp=2 kd =5
int przestrzelony=0;
Ultrasonic odl(TRIGG,ECHO,1160);

void setup() {
              
  initialize();  

}

void loop() {
    odl.Timing();
    if( odl.Ranging(1) <= 15 )
    {
      avoid();
    } 
  
  czytaj_adc();
  blad = licz_blad();
  int regulacja=PD();
  PWM(235+regulacja, 235-regulacja);
  delay(10);
   
 /* digitalWrite(20,HIGH);
  digitalWrite(21,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW);
      analogWrite(9,0);
      analogWrite(10,255);*/
    
  
}


