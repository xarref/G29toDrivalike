#include <Servo.h>
#include "CRSF.h"  // https://github.com/crteensy/CRSF

// ===== Pin Definitions =====
#define CRSF_RX_PIN   0  // UART1 RX (pin 0) for CRSF input
#define SERVO_PIN     2  // PWM output to steering servo
#define ESC_PIN       3  // PWM output to motor ESC

// ===== Global Objects =====
HardwareSerial& crsfSerial = Serial1;  // UART1: RX=pin 0, TX=pin 1 (unused)
CRSF crsf;

Servo steeringServo;
Servo motorESC;

void setup() {
  Serial.begin(115200);

  // Initialize UART1 for CRSF at 420000 baud
  crsfSerial.begin(420000);
  crsf.begin(&crsfSerial);

  // Attach actuators
  steeringServo.attach(SERVO_PIN);
  motorESC.attach(ESC_PIN);
}

void loop() {
  // Parse incoming CRSF packets
  crsf.loop();

  if (crsf.hasChannels()) {
    uint16_t* channels = crsf.getChannels();

    // Map CRSF channel values (0–2047) to PWM pulse widths (1000–2000 µs)
    int steerPulse = map(constrain(channels[0], 172, 1811),
                         172, 1811, 1000, 2000);
    int motorPulse = map(constrain(channels[1], 172, 1811),
                         172, 1811, 1000, 2000);

    // Send PWM to actuators
    steeringServo.writeMicroseconds(steerPulse);
    motorESC.writeMicroseconds(motorPulse);

    // Optional debug output
    Serial.print("Steering PWM: "); Serial.print(steerPulse);
    Serial.print(" | Throttle PWM: "); Serial.println(motorPulse);
  }
}
