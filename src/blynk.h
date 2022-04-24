#ifndef BLYNK_H
#define BLYNK_H

#include "BlynkParamPlus.h"

#define BLYNK_TEMPLATE_ID "TMPLtRVWKVjd"
#define BLYNK_DEVICE_NAME "Smart Garden"

#define BLYNK_FIRMWARE_VERSION "0.1.0"

#define SERIAL_DEBUG // Comment this out to disable Serial outputs
// #define TERMINAL_DEBUG

// #define BLYNK_PRINT
#define BLYNK_PRINT Serial
#define BLYNK_DEBUG

#define APP_DEBUG

// #define BLYNK_NO_BUILTIN // Disable built-in analog & digital pin operations
// #define BLYNK_NO_FLOAT // Disable float operations

#if defined(SERIAL_DEBUG)
#define TERMINAL_BAUD 115200
#define BLYNK_PRINT Serial // Print debug outputs to Serial port
// #define APP_DEBUG // Comment this out to disable debug prints
// #define BLYNK_DEBUG        // Optional, this enables more detailed prints
#define DEBUG(ARG) Serial.print(ARG)
#define DEBUGLN(ARG) Serial.println(ARG)
#elif defined(TERMINAL_DEBUG)
WidgetTerminal terminal(TERMINAL);
#define DEBUG(ARG) terminal.print(ARG)
#define DEBUGLN(ARG) terminal.println(ARG)
#elif defined(TERMINAL_SERIAL_DEBUG)
WidgetTerminal terminal(TERMINAL);
#define DEBUG(ARG)     \
    Serial.print(ARG); \
    terminal.print(ARG)
#define DEBUGLN(ARG)     \
    Serial.println(ARG); \
    terminal.println(ARG)
#else
#define DEBUG
#define DEBUGLN
#define BLYNK_PRINT
#endif

#if defined(APP_DEBUG)
#define DEBUG_PRINT(...) BLYNK_LOG1(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

#include "BlynkEdgent.h"

#endif #BLYNK_H