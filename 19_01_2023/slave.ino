#include <SPI.h>      // import the SPI library for communication with the nRF24L01
#include <nRF24L01.h> // import the nRF24L01 library
#include <RF24.h>     // import the RF24 library
#include <Servo.h>    // import the Servo library

RF24 radio(7, 8);                 // create an RF24 object, specifying the CE and CSN pins
const byte address[6] = "00001";  // specify the address of the master device
Servo myservo;                    // create a Servo object to control the servomotor
int escPin = 3;                   // specify the pin for the ESC
int ledPin = 13;                  // specify the pin for the LED
int brake = 0;                    // variable to store the brake value
int steering = 0;                 // variable to store the steering value
int throttle = 0;                 // variable to store the throttle value
int clutch = 0;                   // variable to store the clutch value
unsigned long previousMillis = 0; // variable to store the previous time
const long interval = 100;        // interval at which to send the data to the serial monitor

void setup()
{
  radio.begin();                     // start the radio
  radio.openReadingPipe(1, address); // open a pipe for reading from the master device
  radio.setPALevel(RF24_PA_LOW);     // set the power level to low
  radio.startListening();            // start listening for incoming messages
  myservo.attach(9);                 // attach the servo to pin 9
  pinMode(escPin, OUTPUT);           // set the pin for the ESC as an output
  pinMode(ledPin, OUTPUT);           // set the pin for the LED as an output
  Serial.begin(9600);                // start serial communication
}

void loop()
{
  if (radio.available())
  { // check if a message is available
    String data;
    radio.read(&data, sizeof(data)); // read the message into a string
    // extract the values of the pedals, wheel position, etc from the data string
    sscanf(data.c_str(), "B:%dG:%dC:%dS:%d", &brake, &throttle, &clutch, &steering);
    // move the servomotor based on the steering value

    // write steering limiting the angle to 45 degrees
    if (steering > 90)
    {
      steering = 90;
    }
    else if (steering < -90)
    {
      steering = -90;
    }
    myservo.write(steering);

    // control the RPM of the brushless motor based on the throttle value
    analogWrite(escPin, throttle);
    // check if the brake value is greater than a certain threshold
    if (brake > 50)
    {
      // reverse the rotation of the brushless motor
      digitalWrite(escPin, HIGH);   // ! this is not the correct way to reverse the rotation
      // turn on the red LED
      digitalWrite(ledPin, HIGH); 
    }
    else
    {
      // turn off the red LED
      digitalWrite(ledPin, LOW);
    }

    // check if the clutch value is greater than a certain threshold
    if (clutch > 50)
    {
      // stop the rotation of the brushless motor
      analogWrite(escPin, 0);
    }

    

  }

  //! Function to write the values on the serial monitor
  // check if the interval has passed
  if (millis() - previousMillis >= interval)
  {
    previousMillis = millis(); // update the previous time
    // send the data to the serial monitor
    Serial.print("Brake: ");
    Serial.print(brake);
    Serial.print(" Throttle: ");

    Serial.print(throttle);
    Serial.print(" Clutch: ");
    Serial.print(clutch);
    Serial.print(" Steering: ");
    Serial.println(steering);
  }
}
