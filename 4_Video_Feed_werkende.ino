#include "esp32cam.h"
#include "esp32cam/http/LiveFeed.h"
#include "eloquent.h"


// Replace with your WiFi credentials
#define WIFI_SSID "thuis"
#define WIFI_PASS "HanneloreQ"
#define CAMERA_MODEL_WROVER_KIT
#include "eloquent/vision/camera/wrover.h"

// 80 is the port to listen to
// You can change it to whatever you want, 80 is the default for HTTP
Eloquent::Esp32cam::Cam cam;
Eloquent::Esp32cam::Http::LiveFeed feed(cam, 80);
WiFiServer server(80);

void setup() {
    Serial.begin(115200);
    delay(3000);
    Serial.println("Init");

    // see 3_Get_Your_First_Picture for more details
    cam.wrover();
    cam.highQuality();
    cam.qqvga();
    
    

    while (!cam.begin())
        Serial.println(cam.getErrorMessage());

    // Connect to WiFi
    // If something goes wrong, print the error message
    while (!cam.connect(WIFI_SSID, WIFI_PASS))
        Serial.println(cam.getErrorMessage());

    //Initialize live feed http server
    // If something goes wrong, print the error message
    while (!feed.begin())
        Serial.println(feed.getErrorMessage());

    // make the camera accessible at http://esp32cam.local
    if (!cam.viewAt("esp32cam"))
        Serial.println("Cannot create alias, use the IP address");
    else
        Serial.println("Live Feed available at http://esp32cam.local");

    // display the IP address of the camera
    Serial.println(feed.getWelcomeMessage());
}


void loop() {
  /*
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
*/
}
