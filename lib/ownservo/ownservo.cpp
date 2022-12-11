#include <ownservo.h>
#include <NRF52_ISR_Servo.h>

typedef struct
{
  int     servoIndex;
  uint8_t servoPin;
} ISR_servo_t;


ISR_servo_t ISR_servo[] =
{
  { -1, SERVO_PIN_1 }, { -1, SERVO_PIN_2 },
};


bool servosetup(void) {
    for (int index = 0; index < NUM_SERVOS; index++)
    {
        ISR_servo[index].servoIndex = NRF52_ISR_Servos.setupServo(ISR_servo[index].servoPin, MIN_MICROS, MAX_MICROS);

        if (ISR_servo[index].servoIndex != -1)
        {
            return true; //setup ok
        }
    }
    return false;
}

void setOwnServoPosition(int servoNumber, int angle) {
    NRF52_ISR_Servos.setPosition(ISR_servo[servoNumber].servoIndex, angle);
}