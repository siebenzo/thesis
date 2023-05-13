#include "esp32cam.h"
#include "esp32cam/http/LiveFeed.h"
#include "eloquent.h"
#include <WiFi.h>;
#include <TimeLib.h>
#include <esp_heap_caps.h>


// Replace with your WiFi credentials
#define WIFI_SSID "telenet-A862E"
#define WIFI_PASS "N4xvFUusGBMX"
#define CAMERA_MODEL_WROVER_KIT
#include "eloquent/vision/camera/wrover.h"


// 80 is the port to listen to
// You can change it to whatever you want, 80 is the default for HTTP
Eloquent::Esp32cam::Cam cam;
Eloquent::Esp32cam::Http::LiveFeed feed(cam, 80);
//WiFiServer server(81);
WiFiServer server(80);
WiFiClient client;


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
  server.begin();
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
}

void print_memory(){
    // Get free and minimum free memory
    size_t freeMem = heap_caps_get_free_size(MALLOC_CAP_8BIT);
    size_t minFreeMem = heap_caps_get_minimum_free_size(MALLOC_CAP_8BIT);

    // Get total heap memory
    size_t totalHeapMem = esp_get_free_heap_size();

    // Calculate percentage of memory used by the program
    float memUsedPercent = 100.0 * (totalHeapMem - freeMem) / totalHeapMem;

    Serial.print("Free Memory: ");
    Serial.print(freeMem);
    Serial.print(" bytes, Minimum Free Memory: ");
    Serial.print(minFreeMem);
    Serial.print(" bytes, Memory Used: ");
    Serial.print(memUsedPercent, 2);
    Serial.println("%");
    Serial.println("bytes used: " + totalHeapMem - freeMem);
}

void loop() {
  //SOCKET als je socket wilt zet here dan true
  if(1 == 1) {
    // Read the data sent by the client
    String data = "";
    // Check if a client has connected
    if (client.connected()) {
      // Read any data that has been sent
      //Serial.println("client connnected!");
      while (client.available()) {
        char c = client.read();
        //Serial.print(c);
        digitalWrite(15, HIGH);
        data += c;
        // Convert the data to an integer
        int message = data.toInt();
        print_memory();

        // Print the received message
        //Serial.print("Received message: ");
        //Serial.println(message);
        if (message == 3) {
          Serial.println("Message received -> memory used:");
          print_memory();
          // Turn on the LED
          digitalWrite(2, HIGH);
          delay(3000);
          digitalWrite(2, LOW);
        }
      }

      // If the client has disconnected, close the connection
      if (!client.connected()) {
        client.stop();
        digitalWrite(15, LOW);
        Serial.println("Client disconnected");
        
      }
    } else {
      // If no client is connected, wait for a new connection
      client = server.available();
      //Serial.println("Waiting for client");
    }
  }



  //HTTP REQUEST
  else {
    WiFiClient client = server.available();

    if (client) {
      Serial.println("New client connected.");
      print_memory();
      while (client.connected()) {
        // Read the data sent by the client
        String data = "";
        // Read any data that has been sent
        while (client.available()) {
          char c = client.read();
          data += c;
        }
        // Parse the request for "data" parameter
        if (data.indexOf("/?data=3") != -1) {
          Serial.println("Message received -> memory used:");
          print_memory();
          // Turn on the LED for 3 seconds
          digitalWrite(2, HIGH);
          delay(500);
          digitalWrite(2, LOW);
        }
      }
      // Close the connection
      client.stop();
      digitalWrite(15, LOW);
      Serial.println("Client disconnected.");
    }
  }
}