#include <ArduinoJson.h>
#include "eloquent.h"
#include "eloquent/print.h"
#include "eloquent/tinyml/voting/quorum.h"
#include <esp_adc_cal.h>


// replace 'm5wide' with your own model
// possible values are 'aithinker', 'eye', 'm5stack', 'm5wide', 'wrover'
#include "eloquent/vision/camera/wrover.h"

#include "Pipeline.h"
#include "Classifier.h"
#define V_REF   1100        // ADC reference voltage
//#define ADC_PIN ADC1_CHANNEL_35          // ADC input pin
#define BAT_VOLT_DIV 2.0    // Voltage divider ratio

Eloquent::TinyML::Voting::Quorum<7> quorum;
int data = 40;
unsigned cpuUsage = 0;
//esp_adc_cal_characteristics_t adc_char;


void setup() {
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 3, 1);
  delay(3000);
  Serial.println("Begin");

  pinMode(2, OUTPUT);
  pinMode(15, OUTPUT);

  digitalWrite(2, HIGH);
  digitalWrite(15, HIGH);

  digitalWrite(2, LOW);
  digitalWrite(15, LOW);

  camera.qqvga();
  camera.grayscale();
 // adc1_config_width(ADC_WIDTH_BIT_12);
  //adc1_config_channel_atten(ADC_PIN, ADC_ATTEN_DB_11);
  //esp_adc_cal_characteristics_t adc_char;
  //esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, V_REF, &adc_char);

  while (!camera.begin())
    Serial.println("Cannot init camera");
  
  
}

void loop() {
  unsigned long startTime = millis();
  if (!camera.capture()) {
    Serial.println(camera.getErrorMessage());
    delay(1000);
    return;
  }
  // apply HOG pipeline to camera frame
    unsigned long hogStartTime = millis();
    hog.transform(camera.buffer);
    unsigned long hogEndTime = millis();
    unsigned long hogLatency = hogEndTime - hogStartTime;


  // get a stable prediction
  // this is optional, but will improve the stability of predictions
  unsigned long classifierStartTime = micros();
  uint8_t prediction = classifier.predict(hog.features);
  unsigned long classifierEndTime = micros();
  unsigned long classifierEndTimeMillies = millis();
  unsigned long classifiertime = classifierEndTime - classifierStartTime;
  int8_t stablePrediction = quorum.vote(prediction);
  unsigned long total = hogStartTime;
 // Serial2.println(total);


  if (quorum.isStable()) {   
    eloquent::print::printf(
      Serial,
      "Stable prediction: %s \t(DSP: %d ms, Classifier: %d us)\n",
      classifier.getLabelOf(stablePrediction),
      hog.latencyInMillis(),
      classifier.latencyInMicros());
    if (stablePrediction == 1)  //gezicht gedetecteerd
    {
      digitalWrite(2, HIGH);
      Serial2.println(data);
      
    }
    else 
    {
      digitalWrite(2, LOW);
    }
      unsigned long processingTime = millis() - startTime;
      Serial2.printf("processingTime = %d ms and hogLatency = %d ms and classifier = %d us",processingTime, hogLatency, classifiertime);
      Serial2.println(stablePrediction);
  }

  camera.free();
  
  unsigned long loopTime = classifierEndTimeMillies - hogStartTime;
  cpuUsage += loopTime;
  unsigned long currentTime = millis();
  float totalTime = (float)(currentTime - startTime) ;
  
  float cpuUsagePercentage = ((float)cpuUsage / totalTime) * 100.0;
  //Serial2.print("CPU Usage Percentage ML: ");
  //Serial2.print(cpuUsagePercentage);
  //Serial2.println("%");
  

  cpuUsage = 0;
  startTime = currentTime;
  /*
  int raw = adc1_get_raw(ADC_PIN);
  float voltage = esp_adc_cal_raw_to_voltage(raw, &adc_char);
  float batteryLevel = (voltage * BAT_VOLT_DIV) / 3.7;
  Serial2.print("Battery Level: ");
  Serial2.print(batteryLevel);
  Serial2.println(" %");
  delay(1000);
  */
  
  
}