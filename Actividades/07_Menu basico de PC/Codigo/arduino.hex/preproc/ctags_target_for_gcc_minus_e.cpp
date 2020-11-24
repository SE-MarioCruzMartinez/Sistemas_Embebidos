# 1 "C:\\Users\\jesus\\Desktop\\9° semestre\\Sistemas embebidos\\Aplicaciones\\Menu_Pc\\Menu_Pc.ino"
# 1 "C:\\Users\\jesus\\Desktop\\9° semestre\\Sistemas embebidos\\Aplicaciones\\Menu_Pc\\Menu_Pc.ino"
# 2 "C:\\Users\\jesus\\Desktop\\9° semestre\\Sistemas embebidos\\Aplicaciones\\Menu_Pc\\Menu_Pc.ino" 2
# 3 "C:\\Users\\jesus\\Desktop\\9° semestre\\Sistemas embebidos\\Aplicaciones\\Menu_Pc\\Menu_Pc.ino" 2




int valor;
int RGB;
int Led=8;
byte dato;
Servo servo1;

void setup() {
  Serial.begin(9600);
  pinMode(Led,0x1);
  servo1.attach(5);
}

void loop() {
  valor=analogRead(A0);
  RGB=map(valor,0,1023,0,255);
  Serial.print("R");
  Serial.println(RGB); delay(100);

  valor=analogRead(A1);
  RGB=map(valor,0,1023,0,255);
  Serial.print("G");
  Serial.println(RGB); delay(100);

  valor=analogRead(A2);
  RGB=map(valor,0,1023,0,255);
  Serial.print("B");
  Serial.println(RGB); delay(100);

  dato=Serial.read();
  if(dato == '1'){
    digitalWrite(Led,0x1);
  }
  if(dato == '2'){
    digitalWrite(Led,0x0);
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
