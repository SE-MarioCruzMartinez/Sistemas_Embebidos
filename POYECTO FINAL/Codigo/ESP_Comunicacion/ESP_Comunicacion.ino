#include <WiFi.h>
#include <PubSubClient.h>

#define WIFISSID "INFINITUM2033_2.4"// Put your WifiSSID here
#define PASSWORD "kUIaOra2j9" // Put your wifi password here
#define TOKEN "BBFF-ZBrgJl0N4KDmjbuGLbLCFKLM1qKhCQ" // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "2988382608"// MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string; 

#define VARIABLE_LABEL "sensor" // Assing the variable label
#define DEVICE_LABEL "esp32" // Assig the device label

#define DEBUG(a) Serial.println(a);

#define RXD2 16
#define TXD2 17

char mqttBroker[]  = "industrial.api.ubidots.com";
char payload[100];
char topic[150];
char str_sensor[10];

WiFiClient ubidots;
PubSubClient client(ubidots);
void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);
  Serial.write(payload, length);
  Serial.println(topic);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    
    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}
void setup() {
  Serial.begin(115200);
  Serial2.begin(57600,SERIAL_8N1,RXD2,TXD2);
  WiFi.begin(WIFISSID, PASSWORD);
   Serial.println();
  Serial.print("Esperando Wifi...");
   while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi Conectado");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);  
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", ""); // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL); // Adds the variable label
  
  String text = Serial2.readString();
  float sensor = text.toFloat();
  DEBUG(sensor);

  dtostrf(sensor, 4, 2, str_sensor);
  sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor); // Adds the value
  Serial.println("Publishing data to Ubidots Cloud");
  client.publish(topic, payload);
  client.loop();
  delay(1000);
}
