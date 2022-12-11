/*
ownble.h defines all servo related setups

Gunter Wiedemann
11.12.2022
*/

#include <Arduino.h>

#ifndef OWNSERVO_H
#define OWNSERVO_H

#define TIMER_INTERRUPT_DEBUG       1
#define ISR_SERVO_DEBUG             1


#define MIN_MICROS        500         //500 - 2500 sind 270deg, es ist ein bisschen größer, damit Ungenautigkeiten ausgeglichen werden können
#define MAX_MICROS        2500

#define SERVO_PIN_1       A0
#define SERVO_PIN_2       A1


#define NUM_SERVOS            2

// functions


/// @brief sets up the interrupt routines for 2 servos at A0 and A1
/// @param  void
/// @return bool true = successful initialisation, false = non-successful initialisation
bool servosetup(void);

void setOwnServoPosition(int servoNumber, int angle);

#endif