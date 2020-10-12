/*===============================================================================
Intruciones.
Genere un letrero en la terminal del canal serial asíncrono (Tx, Rx, a 57.600 
bauds) que especifique cuando ocurre la interrupción
===============================================================================*/
//===============================================================================
//Declaración de variables
int a=0;
//===============================================================================

//===============================================================================
//Void Setup
//===============================================================================
void setup() {
  //Se inicializa el puerto serial
  Serial.begin(57600);
}

//===============================================================================
//Void loop
//===============================================================================
void loop() {
  //Se activa las interrupciones en el pin 2
  attachInterrupt(digitalPinToInterrupt(2),interrupcion,LOW);
}

//===============================================================================
//Void que llama attachInterrupt
//===============================================================================
void interrupcion(){
  //Escribimos en la terminal serial
  Serial.println("Interrupcion No. ");
  //Contamos el número de interrupciones
  a=a+1;
  //Se imprime el número de interrupciones
  Serial.println(a);
  Serial.println();//Dejamos un espacio en blanco
}
