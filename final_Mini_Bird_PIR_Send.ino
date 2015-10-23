#include <VirtualWire.h>

//PIR
const byte pirPin = 12;
const byte ledPin = 13;
//Wireless
const byte rfSendPin =  6;
boolean wirelessShoot = true;

void send (char *message)
{
  digitalWrite(ledPin, HIGH);
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(ledPin, LOW);
}

void setup() {
  
  Serial.begin(9600);
  vw_set_tx_pin(rfSendPin);
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
  
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.println("Ready!");
}

void loop() {
   
  boolean val = digitalRead(pirPin);
  
  if (val) {
    Serial.println("PIR detected!");
    send("A");
    delay(500);
  }
}
