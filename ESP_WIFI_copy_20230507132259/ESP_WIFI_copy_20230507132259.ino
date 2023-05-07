#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "telenet-A862E";
const char* password = "N4xvFUusGBMX";
const char* serverName = "http://192.168.0.102:8000"; // Change to your Python server address

WiFiClient client;
HTTPClient http;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    http.begin(client, serverName);

    int httpCode = http.GET();

    if (httpCode > 0) {
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        WiFiClient client;
        if (client.connect(serverName, 8000)) {
          while (true) {
            if (client.connected()) {
              int len = client.available();
              if (len) {
                uint8_t buffer[1024];
                len = client.readBytes(buffer, 1024);
                Serial.write(buffer, len);
              }
            } else {
              break;
            }
          }
          client.stop();
        } else {
          Serial.println("Unable to connect to server");
        }
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    Serial.println("WiFi not connected");
  }

  delay(1000);
}
