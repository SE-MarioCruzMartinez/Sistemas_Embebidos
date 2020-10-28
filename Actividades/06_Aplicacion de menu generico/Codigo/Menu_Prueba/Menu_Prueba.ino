//Tomando el ejemplo de la libreria, solo se mostrara un menu basico y se
//Navegara en el

#include "Menu_Prueba.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Dependiendo del las conecciones, sera la direccion 0x2X 
//para su comunicacion I2C
LiquidCrystal_I2C lcd(0x27,20,4);

// Definiciones y datos del menú global
uint8_t fruit = 2;
bool bValue = true;

MD_Menu::value_t engValue = { 999900, 3 };

MD_Menu::value_t vBuf;  // búfer de interfaz para valores

//Encabezados de menú
//Mas informacion en su depositorio github de su estructura
const PROGMEM MD_Menu::mnuHeader_t mnuHdr[] =
{
  { 10, "MD_Menu",      10, 11, 0 }, //ID | Nombre | ID de inicio | ID final | ID actual
  { 11, "Listas IN",    20, 21, 0 },
  { 12, "LED Menu",     30, 32, 0 },
  { 13, "Status LEDG",  40, 41, 0 }, //Prender y apagar LED
  { 14, "Status LEDY",  42, 43, 0 },
  { 15, "Status LEDR",  44, 45, 0 },
};

//Elementos de menú
const PROGMEM MD_Menu::mnuItem_t mnuItm[] =
{
  // Inicializacion principal (Root) menu
  { 10, "Listas", MD_Menu::MNU_MENU, 11 }, //ID inicio | Nombre | tipo de accion | Id accion
  { 11, "LED",    MD_Menu::MNU_MENU, 12 },

  // Input Data submenu
  { 20, "List Frutas", MD_Menu::MNU_INPUT, 10 },
  { 21, "Boolean",     MD_Menu::MNU_INPUT, 11 },
  
  // LED
  { 30, "LED Verde",     MD_Menu::MNU_MENU, 13 },
  { 31, "LED Amarillo",  MD_Menu::MNU_MENU, 14 },
  { 32, "LED Rojo",      MD_Menu::MNU_MENU, 15 },

  //LED ON OFF
  { 40, "Off",MD_Menu::MNU_INPUT, 40},
  { 41, "ON" ,MD_Menu::MNU_INPUT, 41},
  { 42, "Off",MD_Menu::MNU_INPUT, 42},
  { 43, "ON" ,MD_Menu::MNU_INPUT, 43},
  { 44, "Off",MD_Menu::MNU_INPUT, 44},
  { 45, "ON" ,MD_Menu::MNU_INPUT, 45},
};

//Elementos de entrada del menu
const PROGMEM char listFruit[] = "Manana|Platano|Naranja|Banana|Mango|Pera";

const PROGMEM MD_Menu::mnuInput_t mnuInp[] =
{
  { 10, "List",     MD_Menu::INP_LIST,  mnuLValueRqst, 6,       0, 0,      0, 0,  0, listFruit },
  { 11, "Bool",     MD_Menu::INP_BOOL,  mnuBValueRqst, 1,       0, 0,      0, 0,  0, nullptr },

  { 40, "Confirm", MD_Menu::INP_RUN, myLEDCode, 0, 0, 0, 0, 0, 0, nullptr },  // prueba usando índice en el código de ejecución
  { 41, "Confirm", MD_Menu::INP_RUN, myLEDCode, 0, 0, 0, 0, 0, 0, nullptr },
  { 42, "Confirm", MD_Menu::INP_RUN, myLEDCode, 0, 0, 0, 0, 0, 0, nullptr },
  { 43, "Confirm", MD_Menu::INP_RUN, myLEDCode, 0, 0, 0, 0, 0, 0, nullptr },
  { 44, "Confirm", MD_Menu::INP_RUN, myLEDCode, 0, 0, 0, 0, 0, 0, nullptr },
  { 45, "Confirm", MD_Menu::INP_RUN, myLEDCode, 0, 0, 0, 0, 0, 0, nullptr },
};

// juntarlo todo en el objeto de menú global
MD_Menu M(navigation, display,        // Uso de navegacion y display
          mnuHdr, ARRAY_SIZE(mnuHdr), // datos del encabezado del menú
          mnuItm, ARRAY_SIZE(mnuItm), // datos del elemento del menú
          mnuInp, ARRAY_SIZE(mnuInp));// datos de entrada del menú

// Código de devolución de llamada para configurar el menú / obtener valores de entrada
MD_Menu::value_t *mnuLValueRqst(MD_Menu::mnuId_t id, bool bGet)
// Devolución de llamada de solicitud de valor para la variable de selección de lista
{
  if (id == 10)
  {
    if (bGet)
    {
      vBuf.value = fruit;
      return(&vBuf);
    }
    else
    {
      fruit = vBuf.value;
      lcd.print(F("\nLa lista cambió a "));
      lcd.print(fruit);
    }
  }
}

MD_Menu::value_t *mnuBValueRqst(MD_Menu::mnuId_t id, bool bGet)
{//Value requiere CallBack para variables boleanas
  MD_Menu::value_t *r = &vBuf;
  if(id == 11)
  {
    if(bGet)
    {
      vBuf.value=bValue;
    }
    else
    {
      bValue = vBuf.value;
      lcd.print(F("\nBoolean cambio a "));
      lcd.print(bValue);
    }
  }
  else
  r = nullptr;
  return(r);
}

MD_Menu::value_t *myLEDCode(MD_Menu::mnuId_t id, bool bGet)
// Devolución de llamada de solicitud de valor para la entrada del código de ejecución
// Utilice solo el índice aquí
{
  lcd.print(F("\nSwitching LED "));//Mueve las cadenas a la memoria flash, liberando
  //memoria RAM. Dado que la cadena no se mueve a SRAM, tiene la propiedad PROGMEM y se 
  //ejecuta desde flash.
  //Puede pasar cadenas basadas en memoria flash a Serial.print () envolviéndolas con F ()
  if(id==40||id==41){
    lcd.print(id == 40 ? F("off") : F("on"));
    digitalWrite(LED_GREEN, id == 40 ? LOW : HIGH);
  }

  else if(id==42||id==43){
    lcd.print(id == 42 ? F("off") : F("on"));
    digitalWrite(LED_YELLOW, id == 42 ? LOW : HIGH);
  }

  else if(id==44||id==45){
    lcd.print(id == 44 ? F("off") : F("on"));
    digitalWrite(LED_RED, id == 44 ? LOW : HIGH);
  }

  return(nullptr);
}
void setup() {
  //Serial.begin(BAUD_RATE);
  lcd.init(); //Inicialiamos la LCD
  lcd.backlight();//PRENDEMOS LA LUZ DE FONDO DE LA LCD
  lcd.clear(); //Limpiamos pantalla
  lcd.noCursor();
  lcd.print("\n[Menu principal]");

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(INC_PIN,INPUT);
  pinMode(DEC_PIN,INPUT);
  pinMode(CTL_PIN,INPUT);

  display(MD_Menu::DISP_INIT);
  setupNav();

  M.begin();
  M.setMenuWrap(true);
  M.setAutoStart(AUTO_START);
  M.setTimeout(MENU_TIMEOUT);
}

void loop() {
static bool prevMenuRun = true;

  // Detectamos si necesitamos iniciar la ejecución del código de usuario normal
  if (prevMenuRun && !M.isInMenu())
  lcd.print("\n\nEJECUTANDO\n");
  prevMenuRun = M.isInMenu();

  // Si no estamos corriendo y no arrancamos automáticamente
   // verifica si hay una razón para iniciar el menú
  if (!M.isInMenu() && !AUTO_START)
  {
    uint16_t dummy;

    if (navigation(dummy) == MD_Menu::NAV_SEL)
      M.runMenu(true);
  }

  M.runMenu();   // simplemente ejecuta el código del menú
}
