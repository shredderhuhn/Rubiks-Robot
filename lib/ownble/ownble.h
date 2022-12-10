/*
ownble.h defines all UART-BLE related setups

Gunter Wiedemann
10.12.2022
*/

#ifndef OWNBLE_H
#define OWNBLE_H

#include <Arduino.h>
#include <bluefruit.h>
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>

// BLE Service
extern BLEUart bleuart; // uart over ble

void blesetup();

#endif