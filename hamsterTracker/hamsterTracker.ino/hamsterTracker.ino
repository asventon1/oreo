/**
 * PostHTTPClient.ino
 *
 *  Created on: 21.11.2016
 *
 */

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

#include <ESP8266HTTPClient.h>

#define USE_SERIAL Serial

ESP8266WiFiMulti WiFiMulti;

const long utcOffsetInSeconds = 3600;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

unsigned long epoch = 0;

int rotations = 0;
int lastSensor = 1;

void setup() {

    USE_SERIAL.begin(115200);
   // USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFiMulti.addAP("MyHouse", "new1house2router");
    timeClient.begin();
    timeClient.update();
    delay(1000);
    timeClient.update();
    epoch = timeClient.getEpochTime();

    pinMode(16, INPUT_PULLDOWN_16);
    
}

void loop() {

    if(digitalRead(16) == 0 && lastSensor == 1) {
      rotations++;
    }

    lastSensor = digitalRead(16);

    //Serial.println(rotations);

    if((epoch+((unsigned long)millis())/1000) % 60 == 0){
    
      // wait for WiFi connection
      //if((WiFiMulti.run() == WL_CONNECTED)) {
  
      HTTPClient http;
  
      USE_SERIAL.print("[HTTP] begin...\n");
      // configure traged server and url
      http.begin("http://192.168.150.2:3000/postdata/"); //HTTP
      http.addHeader("Content-Type", "application/json");
  
      USE_SERIAL.print("[HTTP] POST...\n");
      // start connection and send HTTP header and body
      int httpCode = http.POST("{\"rpm\":"+(String)rotations+", \"time\":"+(String)(epoch+((unsigned long)millis())/1000)+"}");
      rotations = 0;
  
      // httpCode will be negative on error
      if(httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          USE_SERIAL.printf("[HTTP] POST... code: %d\n", httpCode);
  
          // file found at server
          if(httpCode == HTTP_CODE_OK) {
              String payload = http.getString();
              USE_SERIAL.println(payload);
          }
      } else {
          USE_SERIAL.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
  
      http.end();
      //}
      delay(1000);

    }
}
