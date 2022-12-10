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


/**********************************************
 * Start der Servo Initialisierung            *
**********************************************/

#define TIMER_INTERRUPT_DEBUG       1
#define ISR_SERVO_DEBUG             1

#include "NRF52_ISR_Servo.h"

// Published values for SG90 servos; adjust if needed
#define MIN_MICROS        450         //500 - 2500 sind 270deg, es ist ein bisschen größer, damit Ungenautigkeiten ausgeglichen werden können
#define MAX_MICROS        2550

#define SERVO_PIN_1       A0
#define SERVO_PIN_2       A1
#define SERVO_PIN_3       A2
#define SERVO_PIN_4       A3
#define SERVO_PIN_5       A4
#define SERVO_PIN_6       A5

typedef struct
{
  int     servoIndex;
  uint8_t servoPin;
} ISR_servo_t;

#define NUM_SERVOS            2

ISR_servo_t ISR_servo[] =
{
  { -1, SERVO_PIN_1 }, { -1, SERVO_PIN_2 }, { -1, SERVO_PIN_3 }, { -1, SERVO_PIN_4 }, { -1, SERVO_PIN_5 }, { -1, SERVO_PIN_6 }
};

/**********************************************
 * Ende der Servo Initialisierung             *
**********************************************/

void setup()
{
  blesetup();
  while (!bleuart.available()) {}; // Es muss ein Zeichen gesendet werrden, damit es weiter geht, ENTER reicht nicht
  bleuart.flush();
  bleuart.print("Verbindung steht. Servo-Version: ");
  bleuart.println(NRF52_ISR_SERVO_VERSION);

    for (int index = 0; index < NUM_SERVOS; index++)
  {
    ISR_servo[index].servoIndex = NRF52_ISR_Servos.setupServo(ISR_servo[index].servoPin, MIN_MICROS, MAX_MICROS);

    if (ISR_servo[index].servoIndex != -1)
    {
      bleuart.print(F("Setup OK, Servo index = "));
      bleuart.print(ISR_servo[index].servoIndex);
      NRF52_ISR_Servos.setPosition(ISR_servo[index].servoIndex, 0);
    }
    else
    {
      bleuart.print(F("Setup Failed, Servo index = "));
      bleuart.print(ISR_servo[index].servoIndex);
    }
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
      NRF52_ISR_Servos.setPosition(ISR_servo[index].servoIndex, position);
    }

    // waits 1s for the servo to reach the position
    delay(1000);
  }

  bleuart.print("Bewegung endet");

  for (int index = 0; index < NUM_SERVOS; index++)
  {
    NRF52_ISR_Servos.setPosition(ISR_servo[index].servoIndex, 0);
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

