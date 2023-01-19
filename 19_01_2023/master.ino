#include <SPI.h> // import the SPI library for communication with the nRF24L01
#include <nRF24L01.h> // import the nRF24L01 library
#include <RF24.h> // import the RF24 library

RF24 radio(7, 8); // create an RF24 object, specifying the CE and CSN pins
const byte address[6] = "00001"; // specify the address of the slave device

void setup() {
  radio.begin(); // start the radio
  radio.openWritingPipe(address); // open a pipe for writing to the slave device
  radio.setPALevel(RF24_PA_LOW); // set the power level to low
  radio.stopListening(); // stop listening for incoming messages
}

void loop() {
  if (Serial.available() > 0) { // check if data is available from the computer
    String data = Serial.readString(); // read the data as a string
    radio.write(&data, sizeof(data)); // send the data over the radio
  }
}
