//Tomando el ejemplo de la libreria, solo se mostrara un menu basico y se
//Navegara en el

#include "Menu_Prueba.h"

// Definiciones y datos del menú global
uint8_t fruit = 2;
int16_t ANG=90;
int8_t BIT=1;
bool bValue = true;

////////////////////////////////////////////////////////////////////////////
MD_Menu::value_t vBuf;  // búfer de interfaz para valores

//Encabezados de menú
//Mas informacion en su depositorio github de su estructura
const PROGMEM MD_Menu::mnuHeader_t mnuHdr[] =
{
  //Entrada al menu principal
  { 10, "MD_Menu",      10, 14, 0 }, //ID | Nombre | ID de inicio | ID final | ID actual
  { 11, "Listas IN",    20, 21, 0 },
  { 12, "LED Menu",     30, 32, 0 },
  { 13, "Status LEDG",  40, 41, 0 }, //Prender y apagar LED
  { 14, "Status LEDY",  42, 43, 0 },

  { 16, "Analogico",    50, 50, 0 },
  { 17, "Motor",        60, 60, 0 },
  { 18, "Frecuencia",   70, 70, 0 },
  
};

//Elementos de menú
const PROGMEM MD_Menu::mnuItem_t mnuItm[] =
{
  // Inicializacion principal (Root) menu
  { 10, "Listas", MD_Menu::MNU_MENU, 11}, //ID inicio | Nombre | tipo de accion | Id accion
  { 11, "LED",    MD_Menu::MNU_MENU, 12},
  { 12, "Sensor", MD_Menu::MNU_MENU, 16},
  { 13, "Servo",  MD_Menu::MNU_MENU, 17},
  { 14, "Buzer",  MD_Menu::MNU_MENU, 18},

  // Input Data submenu
  { 20, "List Frutas", MD_Menu::MNU_INPUT, 10 },
  { 21, "Boolean",     MD_Menu::MNU_INPUT, 11 },
  
  // LED
  { 30, "LED Verde",     MD_Menu::MNU_MENU, 13 },
  { 31, "LED Amarillo",  MD_Menu::MNU_MENU, 14 },
  
  //LED ON OFF
  { 40, "Off",MD_Menu::MNU_INPUT, 40},
  { 41, "ON" ,MD_Menu::MNU_INPUT, 41},
  { 42, "Off",MD_Menu::MNU_INPUT, 42},
  { 43, "ON" ,MD_Menu::MNU_INPUT, 43},
  { 44, "Off",MD_Menu::MNU_INPUT, 44},
  { 45, "ON" ,MD_Menu::MNU_INPUT, 45},

  //Analogico
  { 50, "POT" ,MD_Menu::MNU_INPUT, 13},

  //Motores
  { 60, "SERVO 01" ,MD_Menu::MNU_INPUT, 14},

  //BUZER
  { 70, "Buzer 01" ,MD_Menu::MNU_INPUT, 15},
};

//Elementos de entrada del menu
const PROGMEM char listFruit[] = "Manana|Platano|Naranja|Banana|Mango|Pera";

const PROGMEM MD_Menu::mnuInput_t mnuInp[] =
{
  { 10, "List",   MD_Menu::INP_LIST,  mnuLValueRqst, 6,       0, 0,      0, 0,  0, listFruit },
  { 11, "Bool",   MD_Menu::INP_BOOL,  mnuBValueRqst, 1,       0, 0,      0, 0,  0, nullptr },
  { 12, "°",      MD_Menu::INP_BOOL,  mnuBValueRqst, 1,       0, 0,      0, 0,  0, nullptr },
  { 13, "LECTURA",MD_Menu::INP_INT,     lecturaPot,  0,       0, 0,      0, 0,  0, nullptr},
  { 14, "ANGULO", MD_Menu::INP_INT,          servo,  4,       0, 0,    180, 0, 10, nullptr},
  { 15, "No. BIP",MD_Menu::INP_INT,          servo,  4,       0, 0,     10, 0, 10, nullptr},
  
  
  { 40, "Confirm", MD_Menu::INP_RUN, myLEDCode, 0, 0, 0, 0, 0, 0, nullptr },  // prueba usando índice en el código de ejecución
  { 41, "Confirm", MD_Menu::INP_RUN, myLEDCode, 0, 0, 0, 0, 0, 0, nullptr },
  { 42, "Confirm", MD_Menu::INP_RUN, myLEDCode, 0, 0, 0, 0, 0, 0, nullptr },
  { 43, "Confirm", MD_Menu::INP_RUN, myLEDCode, 0, 0, 0, 0, 0, 0, nullptr },
};

// juntarlo todo en el objeto de menú global
MD_Menu M(navigation, display,        // Uso de navegacion y display
          mnuHdr, ARRAY_SIZE(mnuHdr), // datos del encabezado del menú
          mnuItm, ARRAY_SIZE(mnuItm), // datos del elemento del menú
          mnuInp, ARRAY_SIZE(mnuInp));// datos de entrada del menú

////////////////////////////////////////////////////////////////////////////
/////////////////////////////FUNCIONES CALLBACK/////////////////////////////
////////////////////////////////////////////////////////////////////////////
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
      Serial.print(F("\nLa lista cambió a "));
      Serial.print(fruit);
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
      Serial.print(F("\nBoolean cambio a "));
      Serial.print(bValue);
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
  Serial.print(F("\nSwitching LED "));//Mueve las cadenas a la memoria flash, liberando
  //memoria RAM. Dado que la cadena no se mueve a SRAM, tiene la propiedad PROGMEM y se 
  //ejecuta desde flash.
  //Puede pasar cadenas basadas en memoria flash a Serial.print () envolviéndolas con F ()
  if(id==40||id==41){
    Serial.print(id == 40 ? F("off") : F("on"));
    digitalWrite(LED_GREEN, id == 40 ? LOW : HIGH);
  }

  else if(id==42||id==43){
    Serial.print(id == 42 ? F("off") : F("on"));
    digitalWrite(LED_YELLOW, id == 42 ? LOW : HIGH);
  }

  return(nullptr);
}

MD_Menu::value_t *lecturaPot(MD_Menu::mnuId_t id, bool bGet)
{
  int value=0;      //variable que almacena la lectura analógica raw
  int position;   //posicion del potenciometro en tanto por ciento
  int a=0;
  while (a<11)
  {
    value = analogRead(Pot);          // realizar la lectura analógica raw
    position = map(value, 0, 1023, 0, 100);  // convertir a porcentaje
    lcd.setCursor(0,2);
    lcd.print(value);
    //...hacer lo que se quiera, con el valor de posición medido
    delay(1000);
    a=a+1;
    lcd.setCursor(0,2);
    lcd.print("      ");
  }
  a=0;
  return(nullptr);
}

MD_Menu::value_t  *servo(MD_Menu::mnuId_t id, bool bGet)
{
   MD_Menu::value_t *r = &vBuf;
   switch (id)
   {
    case 14:
    if (bGet)
        vBuf.value = ANG;
      else
      {
        ANG = vBuf.value;
        Serial.print(F("\nANG cambio a "));
        Serial.print(ANG);
      }
    break;
    case 15:
    if (bGet)
        vBuf.value = BIT;
      else
      {
        BIT = vBuf.value;
        Serial.print(F("\nANG cambio a "));
        Serial.print(BIT);
      }
    break;
   }
  return (r);
}
////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(BAUD_RATE);
  Serial.print("\n[Menu Prueba]");
  lcd.begin(LCD_COLS, LCD_ROWS);

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);

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
  {
    Serial.print("EJECUTANDO");
    lcd.setCursor(0,0);
    lcd.print("\nEquipo 5");
    lcd.setCursor(0,1);
    lcd.print("\nActividad 06");
    lcd.setCursor(0,2);
    lcd.print("\nMenu generico");
    lcd.setCursor(0,3);
    lcd.print("\nCod. Usuario ACT.");
  
  }
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
