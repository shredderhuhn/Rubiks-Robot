#include <Arduino.h>

/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/
#include <bluefruit.h>
#include <Adafruit_LittleFS.h>
#include <InternalFileSystem.h>
#include <ownble.h>


void setup()
{
  blesetup();
  //while (!bleuart.available()) {}; // Es muss ein Zeichen gesendet werrden, damit es weiter geht, ENTER reicht nicht
  //bleuart.print("Verbindung steht");
}


void loop()
{
  // Forward data from HW Serial to BLEUART
  /*
  while (Serial.available())
  {
    // Delay to wait for enough input, since we have a limited transmission buffer
    delay(2);
      uint8_t buf[64];
    int count = Serial.readBytes(buf, sizeof(buf));
    bleuart.write( buf, count );
  
  }
  */

  // Forward from BLEUART to HW Serial
  if ( bleuart.available() )
  {
    String msg = bleuart.readString();
    bleuart.print("Text empfangen:");
    bleuart.print(msg);
  }
  
}

