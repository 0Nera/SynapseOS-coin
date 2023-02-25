/**
 * @file tools.c
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief 
 * @version 0.1.0
 * @date 25-02-2023
 * 
 * @copyright Арен Елчинян (c) 2023
 * 
 */

#pragma GCC optimize ("-Ofast")

#include <SHA256.h>
#include <ESP8266WiFi.h>
#include "tools.h"


/**
 * @brief 
 * 
 * @param hash 
 */
void print_hash(uint8_t *hash) {
    for (byte i = 0; i < 32; i++) {
        Serial.print("0123456789ABCDEF"[hash[i] >> 4]);
        Serial.print("0123456789ABCDEF"[hash[i]&0xf]);
    }
    Serial.println();
}