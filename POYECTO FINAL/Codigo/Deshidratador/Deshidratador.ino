#include "Deshidratador.h"
DHT dht (DHTPIN, DHTTYPE); //Objeto sensor DHT
RTC_DS3231 rtc;
Adafruit_SSD1306 oled(OLED_COLS, OLED_ROWS, &Wire, OLED_RESET); //Objeto
//pantalla OLED 

uint8_t fruit = 2;
//Temperatura y tiempo preestablecidos para los programas automaticos
int16_t temp[]={45,35,55,60,45}, hora[]={0,0,1,0};
int minutos;
byte u=0,i=0,i2=0;//byte de control del tiempo
float sensor = 0.0, lum=10.0; //Variable que guardara la temperatura (sensor)
//y variable de control de potencia (lum)

MD_Menu::value_t vBuf;  // búfer de interfaz para valores

//Encabezados de menú
//Mas informacion en su depositorio github de su estructura
const PROGMEM MD_Menu::mnuHeader_t mnuHdr[] =
{
  //Entrada al menu principal
  { 10, "Menu",         10, 12, 0 }, //ID | Nombre | ID de inicio | ID final | ID actual
  { 11, "Tipo",         20, 23, 0 },
  { 12, "Parametros",   30, 32, 0 },
  { 15, "",  60, 61, 0 },   
};

//Elementos de menú
const PROGMEM MD_Menu::mnuItem_t mnuItm[] =
{
  // Inicializacion principal (Root) menu
  { 10, "Precalentar",      MD_Menu::MNU_INPUT, 13}, //ID inicio | Nombre | tipo de accion | Id accion
  { 11, "Programas Auto",   MD_Menu::MNU_MENU, 11},
  { 12, "Conf. Manual",     MD_Menu::MNU_MENU, 12},

  // Programas automaticos
  { 20, "Hierbas y especias", MD_Menu::MNU_INPUT, 10 },
  { 21, "Verduras",           MD_Menu::MNU_INPUT, 14 },
  { 22, "Frutas",             MD_Menu::MNU_INPUT, 15 },
  { 23, "Carnes y pescados",  MD_Menu::MNU_INPUT, 16 },
  
  // Parametros Manuales
  { 30, "Temperatura", MD_Menu::MNU_INPUT, 11 },
  { 31, "Tiempo",      MD_Menu::MNU_INPUT, 12 },
  { 32, "ARRANCAR",    MD_Menu::MNU_INPUT, 17 },

  { 60, "Iniciando D"    ,MD_Menu::MNU_INPUT, 18 },
};

const PROGMEM MD_Menu::mnuInput_t mnuInp[] =
{
  { 10, "DESHIDRATANDO HyE",MD_Menu::INP_RUN,            AUTO, 0,       0, 0,      0, 0,  0, nullptr },
  { 11, "TEMPERATURA",      MD_Menu::INP_INT,          Manual, 3,      35, 0,    105, 0, 10, nullptr },
  { 12, "HORAS",            MD_Menu::INP_INT,          Manual, 2,       1, 0,      9, 0, 10, nullptr },
  { 13, "Precalentando",    MD_Menu::INP_RUN,          PCalen, 0,       0, 0,      0, 0,  0, nullptr },
  { 14, "DESHIDRATANDO V",  MD_Menu::INP_RUN,            AUTO, 0,       0, 0,      0, 0,  0, nullptr },
  { 15, "DESHIDRATANDO F",  MD_Menu::INP_RUN,            AUTO, 0,       0, 0,      0, 0,  0, nullptr },
  { 16, "DESHIDRATANDO C",  MD_Menu::INP_RUN,            AUTO, 0,       0, 0,      0, 0,  0, nullptr },
  { 17, "DESHIDRATANDO...", MD_Menu::INP_RUN,         inicio,  0,       0, 0,      0, 0,  0, nullptr },
};

// juntarlo todo en el objeto de menú global
MD_Menu M(navigation, display,        // Uso de navegacion y display
          mnuHdr, ARRAY_SIZE(mnuHdr), // datos del encabezado del menú
          mnuItm, ARRAY_SIZE(mnuItm), // datos del elemento del menú
          mnuInp, ARRAY_SIZE(mnuInp));// datos de entrada del menú

////////////////////////////////////////////////////////////////////////////
/////////////////////////////FUNCIONES CALLBACK/////////////////////////////
////////////////////////////////////////////////////////////////////////////
//Funcion zeroCrossin que controla los tiempo para disparo del TRIAC  
  void zeroCrossingInterrupt(){ 
  if(lum>90)lum=90;//Limitamos la variable
  if(lum<10)lum=10.0;
  long t1=8200L*(100L-lum)/100L;
  delayMicroseconds(t1);
  digitalWrite(GATE,HIGH);
  delayMicroseconds(10);
  digitalWrite(GATE,LOW);
  u++;
  if(u==120){
    sensor = dht.readTemperature();//Leo la temperatura del sensor cada seg. 
    Serial.print(sensor);
    u=0;
    //segundostotal--;
    if(temp[i]>sensor)lum=lum+0.1;//Aumento potencia (Mayor temperatura)
    if(sensor>temp[i])lum=lum-0.1;//Redusco potencia (Menor temperatura)
  }
}
//Código de devolución de llamada para configurar el menú / obtener valores de entrada
MD_Menu::value_t *AUTO(MD_Menu::mnuId_t id, bool bGet)
{
  DateTime fecha = rtc.now();
  switch (id)
  {
    case 10:
    i=1;//Selecciono temepratura 35 grados
    hora[1]=5+fecha.minute();
    if(hora[0]>=60)hora[0]=hora[0]-60;
    minutos=fecha.second();
    digitalWrite(AIRE,LOW);//ENCENDIENDO VENTILADORES
    attachInterrupt(digitalPinToInterrupt(3),zeroCrossingInterrupt,RISING);
    while(1){
    DateTime fecha = rtc.now(); 
    if(fecha.minute()==hora[1]&&fecha.second()==minutos)
    {
      detachInterrupt(digitalPinToInterrupt(3));//Detener la interrupcion
      Serial.print("FIN");
      digitalWrite(AIRE,HIGH);//APAGANDO VENTILADORES
      delay(3500);
      break; //Rompemos el ciclo While
    }
   }
   break;

   case 14:
   i=2;
    hora[1]=7+fecha.minute();
    if(hora[0]>=60)hora[0]=hora[0]-60;
    minutos=fecha.second();
    digitalWrite(AIRE,LOW);//ENCENDIENDO VENTILADORES
    attachInterrupt(digitalPinToInterrupt(3),zeroCrossingInterrupt,RISING);
    while(1){
    DateTime fecha = rtc.now(); 
    if(fecha.minute()==hora[1]&&fecha.second()==minutos)
    {
      detachInterrupt(digitalPinToInterrupt(3));//Detener la interrupcion
      Serial.print("FIN");
      digitalWrite(AIRE,HIGH);//APAGANDO VENTILADORES
      delay(3500);
      break; //Rompemos el ciclo While
    }
   }
   break;

   case 15:
   i=2;
    hora[1]=9+fecha.minute();
    if(hora[0]>=60)hora[0]=hora[0]-60;
    minutos=fecha.minute();
    digitalWrite(AIRE,LOW);//ENCENDIENDO VENTILADORES
    attachInterrupt(digitalPinToInterrupt(3),zeroCrossingInterrupt,RISING);
    
    while(1){
    DateTime fecha = rtc.now();
    if(fecha.minute()==hora[1]&&fecha.second()==minutos)
    {
      detachInterrupt(digitalPinToInterrupt(3));//Detener la interrupcion
      Serial.print("FIN");
      digitalWrite(AIRE,HIGH);//APAGANDO VENTILADORES
      delay(3500);
      break; //Rompemos el ciclo While
    }
   }
   break;

   case 16:
   i=3;
    hora[1]=5+fecha.minute();
    if(hora[0]>=60)hora[0]=hora[0]-60;
    minutos=fecha.second();
    digitalWrite(AIRE,LOW);//ENCENDIENDO VENTILADORES
    attachInterrupt(digitalPinToInterrupt(3),zeroCrossingInterrupt,RISING);
    
    while(1){
    DateTime fecha = rtc.now(); 
    if(fecha.minute()==hora[1]&&fecha.second()==minutos)
    {
      detachInterrupt(digitalPinToInterrupt(3));//Detener la interrupcion
      Serial.print("FIN");
      digitalWrite(AIRE,HIGH);//APAGANDO VENTILADORES
      delay(3500);
      break; //Rompemos el ciclo While
    }
   }
   break;
  }
}

MD_Menu::value_t  *Manual(MD_Menu::mnuId_t id, bool bGet)
{
  MD_Menu::value_t *r = &vBuf;
  switch (id)
   {
    case 11:
    if (bGet)
        vBuf.value = temp[4];
      else
      {
        temp[4] = vBuf.value;
        Serial.print(F("\nCentigrados es "));
        Serial.print(temp[4]);
      }
    break;
    case 12:
    if (bGet)
        vBuf.value = hora[2];
      else
      {
        hora[1] = vBuf.value;
        Serial.print(F("\nCentigrados es "));
        Serial.print(hora[2]);
      }
    break;
   }
  return (r);
}

MD_Menu::value_t *PCalen(MD_Menu::mnuId_t id, bool bGet)
{
  i=0;
  DateTime fecha = rtc.now(); 
  hora[0]=6+fecha.minute();
  if(hora[0]>=60)hora[0]=hora[0]-60;
  minutos=fecha.second();
  digitalWrite(AIRE,LOW);//ENCENDIENDO VENTILADORES
  attachInterrupt(digitalPinToInterrupt(3),zeroCrossingInterrupt,RISING);
  while(1){
    DateTime fecha = rtc.now(); 
    if(fecha.minute()==hora[0]&&fecha.second()==minutos)
    {
      detachInterrupt(digitalPinToInterrupt(3));//Detener la interrupcion
      Serial.print("FIN");
      digitalWrite(AIRE,HIGH);//APAGANDO VENTILADORES
      delay(3500);
      break; //Rompemos el ciclo While
    }
   }
}

MD_Menu::value_t *inicio(MD_Menu::mnuId_t id, bool bGet)
{
  i=4;//Escojo la temperatura seleccionada manualmente
  DateTime fecha = rtc.now(); 
  hora[3]=hora[2]+fecha.hour();
  if(hora[3]>=24)hora[3]=hora[3]-24;
  minutos=fecha.minute();
  digitalWrite(AIRE,LOW);//ENCENDIENDO VENTILADORES
  attachInterrupt(digitalPinToInterrupt(3),zeroCrossingInterrupt,RISING);
  while(1){
    DateTime fecha = rtc.now(); 
    if(fecha.hour()==hora[3]&&fecha.minute()==minutos)
    {
      detachInterrupt(digitalPinToInterrupt(3));//Detener la interrupcion
      Serial.print("FIN");
      digitalWrite(AIRE,HIGH);//APAGANDO VENTILADORES
      delay(3500);
      break; //Rompemos el ciclo While
    }
   }
}

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("\n[Programa beta]");
  Wire.begin();
  lcd.begin(LCD_COLS, LCD_ROWS);
  lcd.backlight();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(DHTPIN,INPUT);
  pinMode(GATE,OUTPUT);
  pinMode(AIRE,OUTPUT);
  digitalWrite(GATE,LOW);//LO INISIALIZAMOS EN CERO
  digitalWrite(AIRE,HIGH);//LO INISIALIZAMOS EN UNO - APAGADO
  dht.begin();

  if (!rtc.begin())
  {
    Serial.println("Modilo RTC no encontrado !");
    while(1);
  }

  display(MD_Menu::DISP_INIT);
  setupNav();

  M.begin();
  M.setMenuWrap(true);
  M.setAutoStart(AUTO_START);
  M.setTimeout(MENU_TIMEOUT);
}

void loop() {
  static bool prevMenuRun = true;
    if (prevMenuRun && !M.isInMenu())
  {
    lcd.home(); 
    lcd.print("EQUIPO 5");
    DateTime fecha = rtc.now(); 
    lcd.setCursor(0,2);
    lcd.print(fecha.hour());
    lcd.print(":");
    lcd.print(fecha.minute());
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
