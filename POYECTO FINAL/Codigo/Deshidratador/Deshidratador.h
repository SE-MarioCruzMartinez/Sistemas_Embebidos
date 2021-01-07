#pragma once
#include <MD_Menu.h>
const bool AUTO_START = true; // Inicio automático del menú, 
                              //detección manual e inicio si es falso
///////////////////////////////////////////////////////////////////////////
#define DISPLAY_SERIAL  0   // Pantalla de monitor en serie
#define DISPLAY_OLED 0  //Pantalla OLED
#define DISPLAY_LCD  1 //Pantlla LCD 20x4

#define INPUT_SERIAL    0  //Monitor serial de entrada para pruebas
#define INPUT_RENCODER 0  //Encoder rotativo
#define INPUT_SWITCH    1  // Entrada de los botones
///////////////////////////////////////////////////////////////////////////
#define GATE 6//PIN de control de diparo del TRIAC
#define AIRE 22//PIN de interruptor da ventiladores

#include <RTClib.h>

///////////////////////////////////////////////////////////////////////////
#include <DHT.h>//Libreria sensor DHT (AM2302)
#include <DHT_U.h>
#define DHTPIN 5 //PIN 5 sera su entrada
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321 Escojemos el modelo
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
///////////////////////////////////////////////////////////////////////////
//Declaracion de librerias para manejo de pnatalla OLED
#include <Wire.h>//lbreria de escritura
#include <Adafruit_GFX.h>//Libreria para coordenadas
#include <Adafruit_SSD1306.h> //Libreria para pantalla
#define OLED_COLS 128 //No. de pixeles columnas
#define OLED_ROWS 64 //No. pixeles filas
#define OLED_RESET 4 //El reset no es necesario para nuestra pantalla pero, 
//la libreria fue diseñada con esta variable, se tiene que declarar. 

///////////////////////////////////////////////////////////////////////////
//Librerias para LCD 20x4 y sensor DHT22
#include <LiquidCrystal_I2C.h>//Cargamos la libreria para la LCD
#define  LCD_ROWS  4 //Columnas
#define  LCD_COLS  20 //Filas
const LiquidCrystal_I2C lcd(0x27, LCD_COLS, LCD_ROWS);//DECLARAMOS EL TIPO DE
//LCD

///////////////////////////////////////////////////////////////////////////
const uint32_t  BAUD_RATE = 57600;   // Velocidad del monitor serial
const uint16_t  MENU_TIMEOUT = 5000; // Tiempo del menu activo en milisegundos
///////////////////////////////////////////////////////////////////////////

//Funciones prototipo para navegar/Display
void setupNav(void);//Llama la funcion
bool display(MD_Menu::userDisplayAction_t, char* = nullptr);
MD_Menu::userNavAction_t navigation(uint16_t &incDelta);

MD_Menu::value_t  *AUTO(MD_Menu::mnuId_t id, bool bGet);
MD_Menu::value_t  *Manual(MD_Menu::mnuId_t id, bool bGet);
MD_Menu::value_t  *PCalen(MD_Menu::mnuId_t id, bool bGet);
MD_Menu::value_t  *inicio(MD_Menu::mnuId_t id, bool bGet);
