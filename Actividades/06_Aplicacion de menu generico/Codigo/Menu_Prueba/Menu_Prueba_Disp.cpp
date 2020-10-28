#include "Menu_Prueba.h"

// Rutinas para hardware de pantalla específico, definiendo
// - Archivos de encabezado apropiados
// - Definiciones de hardware
// - Objetos de biblioteca global
// - Mostrar función de devolución de llamada

#if DISPLAY_SERIAL
// Mostrar la salida al monitor serial
// Esto es útil para depurar y solucionar problemas de la estructura del
// definiciones de menú sin utilizar el dispositivo de salida final.

bool display(MD_Menu::userDisplayAction_t action, char *msg)
{
  switch (action)
  {
  case MD_Menu::DISP_INIT:
    Serial.begin(BAUD_RATE);
    break;
    
  case MD_Menu::DISP_CLEAR:
    Serial.println("\n-> CLS");
    break;

  case MD_Menu::DISP_L0:
    Serial.print("\n0> ");
    Serial.println(msg);
    break;

  case MD_Menu::DISP_L1:
    Serial.print("\n1> ");
    Serial.println(msg);
    break;
  }

  return(true);
}
#endif


#if LCD_20X4
//Utiliacion de LCD de 20X4 para el manejor del Sistema
//Incluimos las librerias necesarias
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Dependiendo del las conecciones, sera la direccion 0x2X 
//para su comunicacion I2C
LiquidCrystal_I2C lcd(0x27,20,4);
bool display(MD_Menu::userDisplayAction_t action, char *msg)
{
  //Variable es estatica que solo es creada cuando al funcion es llamada
  //Al terminar la funcion, es desctruida
  static char szLine[20 + 1] = { '\0'};
  switch (action)
  {
  case MD_Menu::DISP_INIT:
    lcd.init(); //Inicialiamos la LCD
    lcd.backlight();//PRENDEMOS LA LUZ DE FONDO DE LA LCD
    lcd.clear(); //Limpiamos pantalla
    lcd.noCursor();
    memset(szLine, ' ', 20);//Vaciamos
    break;
    
  case MD_Menu::DISP_CLEAR:
    lcd.clear();//limpiamos LCD
    break;

  case MD_Menu::DISP_L0:
    lcd.setCursor(0, 0);
    lcd.print(szLine);
    lcd.setCursor(0, 0);
    lcd.print(msg);
    break;

  case MD_Menu::DISP_L1:
    lcd.setCursor(0, 1);
    lcd.print(szLine);
    lcd.setCursor(0, 1);
    lcd.print(msg);
    break;
  }

  return(true);
}
#endif
