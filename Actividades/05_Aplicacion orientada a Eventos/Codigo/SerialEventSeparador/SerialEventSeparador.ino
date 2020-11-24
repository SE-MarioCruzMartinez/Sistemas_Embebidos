

/*
 *******************************************************************************
 * SerialEvent Ejemplo:
 * En este ejemplo utilizaremos la libreria "separador" le pasamos por el canal 
 * serial tres elementos separados por comas y nos devuelve dichos elementos se-
 * parados.
 *Se requiere agregar libreria Separador
 * 
 */
//======[LIBRERIAS]=============================================================
#include <Separador.h>

Separador s;     //Estancia en separador
//======[AJUSTES PRINCIPALES]===================================================
void setup() {
//Inicio serial e indico accion a realizar.
Serial.begin(57600);
Serial.println("Ingresa un texto de tres palabras separados por coma. ");
Serial.println(" Ejemplo: Hola,como,estas");

}
//======[LAZO PRINCIPAL]========================================================
void loop() {
//Si se prodece un evento serial se ejecuta la funcion serialEvent.
if(Serial.available()){
    serialEvent();
}
  }
//======[fUNCION DE SERIALEVENT]=================================================
void serialEvent(){
  //Variable para almacenar la entrada del canal serial.
  String datosrecibidos=Serial.readString();
  //Separo de datos recibidos
  //Ala funcion de separado le debo pasar el string que quiero separar, 
  //el separador y el indice.
  String elemento1=s.separa(datosrecibidos,',',0);
  String elemento2=s.separa(datosrecibidos,',',1);
  String elemento3=s.separa(datosrecibidos,',',2);
  Serial.println();
  Serial.println("El elemento 1 es:  " + elemento1);
  Serial.println("El elemento 2 es:  " + elemento2);
  Serial.println("El elemento 3 es:  " + elemento3);
  Serial.println();

  Serial.println("Ingresa un texto de 3 palabras separadas por coma. ");
 Serial.println("Ejemplo: Hola,como,estas");
  }
