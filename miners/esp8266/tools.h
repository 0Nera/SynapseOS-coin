/**
 * @file tools.h
 * @author Арен Елчинян (a2.dev@yandex.com)
 * @brief 
 * @version 0.1.0
 * @date 25-02-2023
 * 
 * @copyright Арен Елчинян (c) 2023
 * 
 */


#ifndef _N_TOOLS_H
#define _N_TOOLS_H 1

#include <SHA256.h>
#include <ESP8266WiFi.h>

void print_hash(uint8_t *hash);

#endif // tools.h