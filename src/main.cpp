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
#include <ownservo.h>



void setup()
{
  blesetup();
  while (!bleuart.available()) {}; // Es muss ein Zeichen gesendet werrden, damit es weiter geht, ENTER reicht nicht
  bleuart.flush();
  bleuart.print("BLE-Verbindung steht.");

  bool servostate = servosetup();
  if (servostate == true) {
    //bleuart.println(NRF52_ISR_SERVO_VERSION); 
    bleuart.print("Servos initialised.");
  } else {
    bleuart.print("Servo Initialisation failed. Controller stopped.");
    while(true);
  }

}


void loop()
{

  bleuart.print("Servo startet.");

  int position;      // position in degrees

  for (position = 0; position <= 270; position += 10)
  {
    // goes from 0 degrees to 180 degrees
    // in steps of 10 degree
    for (int index = 0; index < NUM_SERVOS; index++)
    {
      setOwnServoPosition(index, position);
    }

    // waits 1s for the servo to reach the position
    delay(1000);
  }

  bleuart.print("Bewegung endet");

  for (int index = 0; index < NUM_SERVOS; index++)
  {
    //NRF52_ISR_Servos.setPosition(index, 0);
  }
  
  delay(5000);



  // Forward from BLEUART to HW Serial
  if ( bleuart.available() )
  {
    String msg = bleuart.readString();
    bleuart.print("Text empfangen:");
    bleuart.print(msg);
  }
  
}

