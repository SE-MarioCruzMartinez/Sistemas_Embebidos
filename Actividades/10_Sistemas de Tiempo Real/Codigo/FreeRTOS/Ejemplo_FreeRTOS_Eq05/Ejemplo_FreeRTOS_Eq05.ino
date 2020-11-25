//==============================================================================
// Ejemplo del uso de FreeRTOS - Para ESP32
//--------------------------------------------
// EJERCICIO PARA TAREA, A EXPLICAR EN EQUIPO:
//--------------------------------------------
// Aumentar el número de tareas a 8, considerando:
// 1.) Para verificar la secuencia de ejecución de las tareas, utilice la
// siguiente notación para la ocurrencia de las tareas:
//
// Tarea 1: --- 01
// Tarea 2: ----- 02
// Tarea 3: ------- 03
// Tarea 4: --------- 04
// Tarea 5: ----------- 05
// Tarea 6: ------------- 06
// Tarea 7: --------------- 07
// Tarea 8: ----------------- 08
//
// En la ocurrencia de la tarea agregar si recibió o envió datos a otras
// Tareas, por ejemplo, la siguiente línea indicaría que en esta instancia
// la Tarea 6 envió algo a la Tarea 4:
// Tarea 6: ------------- 06 [-> 4]
// En el siguiente caso, la Tarea 5 recibió algo de la Tarea 2.
// Tarea 5: ----------- 05 [<-2]

// 2.) Cambiar los siguientes parámetros para ejercitar las diversas opciones:
// [HECHO] a.) Prioridades de las tareas
// [HECHO] b.) Frecuencia de ejecución de las tareas. Algunas de ellas se ejecutarán
//             más veces que otras. que la 8 se haga tres veces
// [HECHO] c.) Conclusión de las tareas. Algunas tareas terminarán antes que otras.// que la 7 se haga menos veces
// [HECHO] d.) Comunicación entre tareas. Verificar cuáles son las funciones o
//             directivas que se pueden emplear para que una tarea comunique algo a otra.
//             Ejercitar que las comunicaciones se den después de que pasaron varias
//             ejecuciones, por ejemplo, que la tarea 3 comunique a la tarea 5 después de
//             que la tarea 3 ha ocurrido por quinta vez. Hacer algo similar para otros
//             casos.
// [HECHO] e.) Ejercitar dos características más que crea importantes de FreeRTOS en el
//             mismo ejemplo.
// [HECHO] f.) Comentar adecuadamente las líneas del código.
// [HECHO] g.) Para la presentación, puede emplear el monitor serial, simulado o real,
//             verificando que efectivamente ocurre la secuencia que planeó.
//==============================================================================
#include <Arduino.h>
//---------------------
//-----[ AJUSTES ]-----
//---------------------
int val1,periferico=0; //Variables de control
char dato;
void setup() {
  Serial.begin(112500);//inicializacion del puerto serial
  Serial.println("-- INICIO --");
  delay(1000);//Tiempo de es epera
  // Creación de las tareas:
  xTaskCreate(
    Tarea1,     // Función que ejecuta la tarea
    "Tarea1",   // Cadena con el nombre de la tarea
    10000,      // Tamaño del "Stack"
    NULL,       // Parámetro pasado como entrada
    8,          // Prioridad de la tarea
    NULL);      // Manejador (Handle) de la tarea
  xTaskCreate(Tarea2, "Tarea2", 10000, NULL, 7, NULL);
  xTaskCreate(Tarea3, "Tarea3", 10000, NULL, 3, NULL);
  xTaskCreate(Tarea4, "Tarea4", 10000, NULL, 4, NULL);
  xTaskCreate(Tarea5, "Tarea5", 10000, NULL, 5, NULL);
  xTaskCreate(Tarea6, "Tarea6", 10000, NULL, 2, NULL);
  xTaskCreate(Tarea7, "Tarea7", 10000, NULL, 1, NULL);
  xTaskCreate(Tarea8, "Tarea8", 10000, NULL, 6, NULL);
}
//-----------------------
//-----[ PRINCIPAL ]-----
//-----------------------
void loop() {
  delay(1000);              // Retardo para imprimir ocurrencias
}
//==============================================================================
//---------------------
//-----[ TAREA 1 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea1( void * parameter ) {
  for ( int i = 0; i < 10; i++ ) { // Número de veces que ocurre esta tarea
    switch (i) {
      case 0:     // Primera ejecución T1
        Serial.println("--- 01");   // Evidencia de ocurrencia
        break;
      case 1:     // Segunda ejecución T1
        Serial.println("--- 01");   // Evidencia de ocurrencia
        break;
      case 2:     // Tercera ejecución T1
        Serial.println("--- 01");   // Evidencia de ocurrencia
        break;
      case 3:     // Cuarta ejecución T1
        Serial.println("--- 01");   // Evidencia de ocurrencia
        break;
      case 4:     // Quinta ejecución T1
        Serial.println("--- 01");   // Evidencia de ocurrencia
        break;
      case 5:     // Sexta ejecución T1
        Serial.println("--- 01");   // Evidencia de ocurrencia
        periferico = 1;
        Serial.println("--- 01 [-> 08]");//Envio de dato a la 
                                        //tarea 08
        break;
      case 6:     // Séptima ejecución T1
        Serial.println("--- 01");   // Evidencia de ocurrencia
        break;
      case 7:     // Octava ejecución T1
        Serial.println("--- 01");   // Evidencia de ocurrencia
        break;
      case 8:     // Novena ejecución T1
        Serial.println("--- 01");   // Evidencia de ocurrencia
        break;
      case 9:     // Décima ejecución T1
        Serial.println("--- 01");   // Evidencia de ocurrencia
        break;
      default:
        Serial.println("--- 01");   // Evidencia de ocurrencia
        break;
    }
    delay(1000);              // Espera...
  }
  Serial.println("--> 01");     // Conclusión de la tarea
  vTaskDelete( NULL );          // Se "Borra"
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 2 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea2( void * parameter) {
  for ( int i = 0; i < 10; i++ ) {
    Serial.println("----- 02");//Ejecucion de la tarea 02
    if (val1 == 3)
    {
      Serial.println("----- 02 [<-07]");//Se recibio el dato de la tarea 07
      val1 = 0;
    }
    else if (i == 7)
    {
      Serial.println("----- 02 [->05]");//Se envia el dato a la tarea 05
      val1 = 7;
    }
    delay(1000);
  }
  Serial.println("--> 02");   // Conclusión de la tarea
  vTaskDelete( NULL );
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 3 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea3( void * parameter) {
  for ( int i = 0; i < 10; i++ ) {
    Serial.println("------- 03");//Ejecucion de la tarea
    delay(1000);
  }
  Serial.println("--> 03");   // Conclusión de la tarea
  vTaskDelete( NULL );
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 4 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea4( void * parameter) {
  for ( int i = 0; i < 10; i++ ) {
    Serial.println("--------- 04");//Ejecucion de la tarea
    delay(1000);
  }
  Serial.println("--> 04");   // Conclusión de la tarea
  vTaskDelete( NULL );
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 5 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea5( void * parameter) {
  for ( int i = 0; i < 10; i++ ) {
    Serial.println("----------- 05");//Ejecucion de la tarea
    if (val1 == 7)
    {
      Serial.println("----------- 05 [<-02]");//Se recibe el dato de la tarea 02
      val1 = 0;
    }
    delay(1000);
  }
  Serial.println("--> 05");   // Conclusión de la tarea
  vTaskDelete( NULL );
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 6 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea6( void * parameter) {
  //Esta tarea solo se ejecutara si ninguna otra puede hacerlo
  for (;;) {
    if(Serial.available())
    {
      dato=Serial.read();
      if(dato=='e')break;
      else
        Serial.println("------------- 06");
    //El tiempo activo es más corto
    }
    delay(1000);
  }
  Serial.println("--> 06");   // Conclusión de la tarea
  vTaskDelete( NULL );
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 7 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea7( void * parameter) {
  for ( int i = 0; i < 5; i++ ) {
    Serial.println("--------------- 07");//Ejecucion de la tarea
    delay(1000);
  }
  val1 = 3;
  Serial.println("--------------- 07 [-> 02]");//Se encia el dato a la tarea 02
  Serial.println("--> 07");   // Conclusión de la tarea
  vTaskDelete( NULL );
}
//------------------------------------------------------------------------------
//---------------------
//-----[ TAREA 8 ]-----
//---------------------
//------------------------------------------------------------------------------
void Tarea8( void * parameter) {
  for(int i=0;i<10;i++)
  {
    //En espera de recibir el dato de la tarea 01
    if (periferico == 1)
    {
      Serial.println("----------------- 08 [<-01]");//Se recibe el dato
      periferico = 2;
      i=8;//Se establece la realizacion de la tarea a dos
    }
    else if(periferico == 2)
    {
      Serial.println("----------------- 08");//Se ejecuta la tarea
    }
    delay(1000);
  }
  Serial.println("--> 08");   // Conclusión de la tarea
  periferico=0;
  vTaskDelete( NULL );
}
//**********
