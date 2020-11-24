#include <Arduino.h>
#line 1 "C:\\Users\\jesus\\Desktop\\9° semestre\\Sistemas embebidos\\Aplicaciones\\Menu_Pc\\Menu_Pc.ino"
#line 1 "C:\\Users\\jesus\\Desktop\\9° semestre\\Sistemas embebidos\\Aplicaciones\\Menu_Pc\\Menu_Pc.ino"
#include <Servo.h>
#include<Wire.h>

#define pR A0
#define pG A1
#define pB A2
int valor;
int RGB;
int Led=8;
byte dato;
Servo servo1;

#line 13 "C:\\Users\\jesus\\Desktop\\9° semestre\\Sistemas embebidos\\Aplicaciones\\Menu_Pc\\Menu_Pc.ino"
void setup();
#line 19 "C:\\Users\\jesus\\Desktop\\9° semestre\\Sistemas embebidos\\Aplicaciones\\Menu_Pc\\Menu_Pc.ino"
void loop();
#line 13 "C:\\Users\\jesus\\Desktop\\9° semestre\\Sistemas embebidos\\Aplicaciones\\Menu_Pc\\Menu_Pc.ino"
void setup() {
  Serial.begin(9600);
  pinMode(Led,OUTPUT);
  servo1.attach(5);
}

void loop() {
  valor=analogRead(pR);
  RGB=map(valor,0,1023,0,255);
  Serial.print("R");
  Serial.println(RGB); delay(100);

  valor=analogRead(pG);
  RGB=map(valor,0,1023,0,255);
  Serial.print("G");
  Serial.println(RGB); delay(100);

  valor=analogRead(pB);
  RGB=map(valor,0,1023,0,255);
  Serial.print("B");
  Serial.println(RGB); delay(100);

  dato=Serial.read();
  if(dato == '1'){
    digitalWrite(Led,HIGH);
  }
  if(dato == '2'){
    digitalWrite(Led,LOW);
  }
  if(dato == '0'){
    servo1.write(0);
  }
  if(dato == '3'){
     servo1.write(90);
  }
  if(dato == '4'){
     servo1.write(180);
  }
}

