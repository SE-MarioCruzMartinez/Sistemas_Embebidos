#pragma once
#include <MD_Menu.h>
const bool AUTO_START = true; // Inicio automático del menú, 
                              //detección manual e inicio si es falso
//Seleccione los componentes de hardware de entrada / salida de usuario que se utilizarán
#define DISPLAY_SERIAL  0   // Pantalla de monitor en serie
#define DISPLAY_LCD  1

#define INPUT_SWITCH    1  // Entrada de los botones
#define INPUT_SERIAL    0  //Monitor serial de entrada para pruebas

///////////////////////////////////////////////////////////////////////////
#include <Wire.h>//lbreria de escritura
#include <LiquidCrystal_I2C.h>//Cargamos la libreria para la LCD
#define  LCD_ROWS  4
#define  LCD_COLS  20

const LiquidCrystal_I2C lcd(0x27, LCD_COLS, LCD_ROWS);//DECLARAMOS EL TIPO DE LCD
///////////////////////////////////////////////////////////////////////////

const uint32_t  BAUD_RATE = 57600;   // Velocidad del monitor serial
const uint16_t  MENU_TIMEOUT = 5000; // Tiempo del menu activo en milisegundos

//const uint8_t LED_PIN = LED_BUILTIN;  //para la fucnion myLEDCode, ahorra tiempo en procesamento
const uint8_t  LED_GREEN = 13;
const uint8_t  LED_YELLOW = 12;
const uint8_t  Pot= A1;

//Funciones prototipo para navegar/Display
void setupNav(void);//Llama la funcion
bool display(MD_Menu::userDisplayAction_t, char* = nullptr);
MD_Menu::userNavAction_t navigation(uint16_t &incDelta);

//Prototipos de funciones para funciones variables get / setón.
MD_Menu::value_t  *mnuLValueRqst(MD_Menu::mnuId_t id, bool bGet);
MD_Menu::value_t  *myLEDCode(MD_Menu::mnuId_t id, bool bGet);
MD_Menu::value_t  *mnuBValueRqst(MD_Menu::mnuId_t id, bool bGet);
MD_Menu::value_t  *lecturaPot(MD_Menu::mnuId_t id, bool bGet);
MD_Menu::value_t  *servo(MD_Menu::mnuId_t id, bool bGet);
