#include "Menu_Prueba.h"
// Rutinas para hardware de navegación de usuario específico, definiendo
// - Archivos de encabezado apropiados
// - Definiciones de hardware
// - Objetos de biblioteca global
// - Función de devolución de llamada de navegación

#if INPUT_SERIAL
// Usar las entradas serial
// 'U' y 'D' mapear INC y DEC
// 'R' y 'L' mapear la salida (ESC)
// 'S' mapear SEL (Seleccionar)

void setupNav(void)
{
}

MD_Menu::userNavAction_t navigation(uint16_t &incDelta)
{
  char c = 0;
  if(Serial.available()>0)
    c = Serial.read();

  incDelta = 1;
  switch (c)
  {
  case 'D':  return(MD_Menu::NAV_DEC);
  case 'U':  return(MD_Menu::NAV_INC);
  case 'S':  return(MD_Menu::NAV_SEL);
  case 'R':  return(MD_Menu::NAV_ESC);
  case 'L':  return(MD_Menu::NAV_ESC);
  }

  return(MD_Menu::NAV_NULL);
}
#endif


#if INPUT_SWITCH
//Se hara uso de tres botones para realiar la accion de
//Decremento e incremento
//Para hacer uso de las acciones click (Seleccionar)
//y long clock (ESC) se hara uso de la libreria MD_UISwitch
#include <MD_UISwitch.h>

const uint8_t INC_PIN = 2;//Subir
const uint8_t DEC_PIN = 3;//Bajar
const uint8_t CTL_PIN = 10;//Seleccionar
const uint8_t ESC_PIN = 11;//Salir
uint8_t pins[] = { INC_PIN, DEC_PIN, CTL_PIN, ESC_PIN};

//Creamos la funcion especial para el manejo de los botones
//de la libreria MD_UISwitch
MD_UISwitch_Digital swNav(pins, ARRAY_SIZE(pins), LOW);

void setupNav(void)
{
  swNav.begin();
  swNav.enableRepeat(false);
}

//Creamos la funcion para la navegacion en la LCD
MD_Menu::userNavAction_t navigation(uint16_t &incDelta)
{
  MD_Menu::userNavAction_t nav = MD_Menu::NAV_NULL;

  switch (swNav.read())
  {
    case MD_UISwitch::KEY_LONGPRESS:
    {
      Serial.print(swNav.getKey());
      switch (swNav.getKey())
      {
      case INC_PIN: nav = MD_Menu::NAV_INC; break;
      case DEC_PIN: nav = MD_Menu::NAV_DEC; break;
      case CTL_PIN: nav = MD_Menu::NAV_SEL; break;
      case ESC_PIN: nav = MD_Menu::NAV_ESC; break;
      }
    }
    break;
    /*
    case MD_UISwitch::KEY_RPTPRESS:
    {
      if (swNav.getKey() == 2)
        nav = MD_Menu::NAV_ESC;
    }
    break;*/
  }
  incDelta = 1;
  
  return(nav);
}
#endif
