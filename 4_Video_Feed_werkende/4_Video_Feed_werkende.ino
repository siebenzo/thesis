#include "esp32cam.h"
#include "esp32cam/http/LiveFeed.h"
#include "eloquent.h"

// Replace with your WiFi credentials
#define WIFI_SSID "Sabine"
#define WIFI_PASS "kitties123"

#define CAMERA_MODEL_WROVER_KIT
#include "eloquent/vision/camera/wrover.h"

// Define the server port number
#define SERVER_PORT 8080

// Define the GPIO pin number for LED
#define LED_GPIO 15

Eloquent::Esp32cam::Cam cam;
Eloquent::Esp32cam::Http::LiveFeed feed(cam, SERVER_PORT);


WiFiServer server(SERVER_PORT);

void setup() {
  Serial.begin(115200);
  delay(500);
  
  pinMode(LED_GPIO, OUTPUT);
  pinMode(2, OUTPUT);

  Serial.println("Init");

  cam.wrover();
  //cam.lowQuality();
  cam.highQuality();
  cam.qqvga();

  while (!cam.begin())
    Serial.println(cam.getErrorMessage());

  while (!cam.connect(WIFI_SSID, WIFI_PASS))
    Serial.println(cam.getErrorMessage());

  while (!feed.begin())
    Serial.println(feed.getErrorMessage());

  if (!cam.viewAt("esp32cam"))
    Serial.println("Cannot create alias, use the IP address");
  else
    Serial.println("Live Feed available at http://esp32cam.local");
    Serial.println(WiFi.localIP());

  Serial.println(feed.getWelcomeMessage());
  Serial.println(WiFi.localIP());
}

/*void loop() {
  WiFiClient client = server.available();


  while (client.connected() && !client.available()) {
    delay(1);
  }

  if (client) {
    String request = client.readStringUntil('\r');
    digitalWrite(2, HIGH);
    if (request.indexOf("GET /?data=32") != -1) {
      Serial.println("Received number 32 over WiFi. Pulling GPIO 15 high.");
      digitalWrite(LED_GPIO, HIGH);
      //digitalWrite(2, HIGH);
      delay(1000);
      digitalWrite(LED_GPIO, LOW);
      //digitalWrite(2, LOW);
      
    }


    client.flush();
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
  }

  delay(1);
}*/

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait for the client to send some data
  while (!client.available()) {
    delay(1);
  }

  // Read the data sent by the client
  String data = "";
  while (client.available()) {
    char c = client.read();
    data += c;
  }

  // Convert the data to an integer
  int message = data.toInt();

  // Print the received message
  Serial.print("Received message: ");
  Serial.println(message);

  // Do something with the received message
  if (message == 32) {
    // Turn on the LED
    digitalWrite(LED_GPIO, HIGH);
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(LED_GPIO, LOW);
    digitalWrite(2, LOW);
  }

  // Close the connection
  client.stop();
}
