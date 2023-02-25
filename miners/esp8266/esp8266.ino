/**
 * @file esp8266.ino
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief 
 * @version 0.1.0
 * @date 25-02-2023
 * 
 * @copyright Арен Елчинян (c) 2023
 * 
 */

#pragma GCC optimize ("-Ofast")

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <SHA256.h>
#include "tools.h"

void *data;
unsigned long long d = 0;
uint8_t result[64];
bool ready = false;
SHA256 sha256;

const char *ssid = "E-2,4G";
const char *password = "Elina2008&";


/**
 * @brief 
 * 
 */
void setup() {
    Serial.begin(9600);

    Serial.println();
    Serial.println();
    Serial.println();

    //Connect to Wi-Fi
    //WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
        delay(250);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.print(WiFi.localIP());
    Serial.printf(", status: %d\n", WiFi.status());

    data = &d;
    
    sha256.reset();
    sha256.update(data, sizeof(d));
    sha256.finalize(result, 32);
    Serial.print("Ready! Hash: ");

    print_hash(result);

    Serial.println();

    ready = true;
}


/**
 * @brief 
 * 
 */
void loop() {
    if (ready) {
        std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

        // Ignore SSL certificate validation
        client->setInsecure();
        
        //create an HTTPClient instance
        HTTPClient https;
        
        //Initializing an HTTPS communication using the secure client
        Serial.print("[HTTPS] begin...\n");
        if (https.begin(*client, "https://osmaker.0nera.ru/api/version/")) {  // HTTPS
            Serial.print("[HTTPS] GET...\n");
            // start connection and send HTTP header
            int httpCode = https.GET();
            // httpCode will be negative on error
            if (httpCode > 0) {
                // HTTP header has been send and Server response header has been handled
                Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
                // file found at server
                if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
                    String payload = https.getString();
                    Serial.println(payload);
                }
            } else {
                Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
            }

            https.end();
        } else {
            Serial.printf("[HTTPS] Unable to connect\n");
        }
    }
    Serial.println();
    Serial.println("Waiting 2min before the next round...");
    delay(120000);
}