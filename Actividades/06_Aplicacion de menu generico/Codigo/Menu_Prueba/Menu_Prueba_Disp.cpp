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


#if DISPLAY_LCD
//Utiliacion de LCD de 20X4 para el manejor del Sistema

bool display(MD_Menu::userDisplayAction_t action, char *msg)
{
  static char szLine[LCD_COLS + 1] = { '\0' };

  switch (action)
  {
  case MD_Menu::DISP_INIT:
    lcd.begin(LCD_COLS, LCD_ROWS);
    lcd.clear();
    lcd.noCursor();
    memset(szLine, ' ', LCD_COLS);
    break;
  
  case MD_Menu::DISP_CLEAR:
    lcd.clear();
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
