#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiClient client;

unsigned long myChannelNumber = YOUR_CHANNEL_NUMBER;
const char* myWriteAPIKey = "YOUR_API_KEY";

int analogPin = A0;
float voltage;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  ThingSpeak.begin(client);
}

void loop() {
  int sensorValue = analogRead(analogPin);
  voltage = sensorValue * (5.0 / 1023.0) * 2; // Voltage divider

  ThingSpeak.writeField(myChannelNumber, 1, voltage, myWriteAPIKey);

  Serial.print("Battery Voltage: ");
  Serial.println(voltage);

  delay(15000); // ThingSpeak delay
}
