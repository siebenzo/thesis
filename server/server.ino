#include "esp_camera.h"
#include <WiFi.h>

const char* ssid = "Sabine";
const char* password = "kitties123";

WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());

  // Set GPIO 15 as output
  pinMode(15, OUTPUT);
}

void loop() {
  // Check for a client connection
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait for the client to send a request
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);

  // Handle the request
  if (req.indexOf("/stream") != -1) {
    // Send the HTTP headers
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: multipart/x-mixed-replace; boundary=frame");

    // Loop through the video frames
    while (true) {
      // Capture a frame from the camera
      camera_fb_t* fb = esp_camera_fb_get();
      if (!fb) {
        Serial.println("Camera capture failed");
        break;
      }

      // Send the JPEG data as a chunked HTTP response
      client.println("--frame");
      client.println("Content-Type: image/jpeg");
      client.println(String("Content-Length: ") + fb->len);
      client.println();
      client.write(fb->buf, fb->len);
      client.println();

      // Free the frame buffer
      esp_camera_fb_return(fb);

      // Check for any signals from the client
      if (client.available()) {
        String signal = client.readStringUntil('\r');
        Serial.println(signal);
        if (signal.indexOf("/signal?300") != -1) {
          // Set GPIO 15 to HIGH if a signal is received
          Serial.println("Signal received!");
          digitalWrite(15, HIGH);
        }
      }
    }
  }

  // Wait for the client to disconnect
  delay(1);
  client.stop();
}
