#include <Wire.h>
#include <RTClib.h>
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  if (!rtc.begin())
  {
    Serial.println("Modilo RTC no encontrado !");
    while(1);
  }
  //rtc.adjust(DateTime(__DATE__,__TIME__));
}
void loop() {
  
}
