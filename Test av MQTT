
#include "UbidotsEsp32Mqtt.h"

/****************************************
 * Define Constants
 ****************************************/
const char *UBIDOTS_TOKEN = "BBFF-L0jKhRyJqxVf5FbauBYDlI05581S9H";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "OmegaV";      // Put here your Wi-Fi SSID
const char *WIFI_PASS = "GullSkop";      // Put here your Wi-Fi password
const char *DEVICE_LABEL = "testmqtt";   // Put here your Device label to which data  will be published
const char *VARIABLE_LABEL = "potmeter"; // Put here your Variable label to which data  will be published

const int PUBLISH_FREQUENCY = 5000; // Update rate in milliseconds

unsigned long timer;
uint8_t analogPin = 34; // Pin used to read data from GPIO34 ADC_CH6.

Ubidots ubidots(UBIDOTS_TOKEN);


void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String beskjed;
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
    beskjed += (char)payload[i]; 
  }
  Serial.println(beskjed);
  Serial.println();
  if (beskjed == "1.0"){
    Serial.println("på");
    digitalWrite(13, HIGH);
  }
  else {
    Serial.println("av");
    digitalWrite(13, LOW);
  }
}

/****************************************
 * Main Functions
 ****************************************/

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  // ubidots.setDebug(true);  // uncomment this to make debug messages available
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
  ubidots.subscribeLastValue(DEVICE_LABEL, "led");

  timer = millis();
  pinMode(13, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (!ubidots.connected())
  {
    ubidots.reconnect();
    ubidots.subscribeLastValue(DEVICE_LABEL, "led");
  }
  if ((millis() - timer) > PUBLISH_FREQUENCY) // triggers the routine every 5 seconds
  {
    float value = analogRead(analogPin);
    value= map(value,0 ,4096,0,100);
    ubidots.add(VARIABLE_LABEL, value); // Insert your variable Labels and the value to be sent
    ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }
  ubidots.loop();
}
