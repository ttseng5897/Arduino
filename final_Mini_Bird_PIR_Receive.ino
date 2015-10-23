/*
SimpleReceive
This sketch displays text strings received using VirtualWire
Connect the Receiver data pin to Arduino pin 11
*/
#include <VirtualWire.h>

const byte rfRecvPin = 3; 
const byte ledPin = 13;
const byte zoomPin = 4;
const byte shootPin = 5;

uint8_t message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
uint8_t messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
char inData[20];
String receiveMSG;

void zoomShootNow() {
    digitalWrite(ledPin, HIGH);
    Serial.println("Zoom....");
    digitalWrite(zoomPin, HIGH);
    delay(1000);
    digitalWrite(shootPin, HIGH);
    Serial.println("Shoot....");
    delay(1000);
    digitalWrite(zoomPin, LOW);
    digitalWrite(shootPin, LOW);
    Serial.println("Shoot finished....");
    digitalWrite(ledPin, LOW);
    delay(5000);
}

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  Serial.println("Device is ready");
  
  // Initialize the IO and ISR
  vw_set_rx_pin(rfRecvPin);
  vw_setup(2000); // Bits per sec
  vw_rx_start(); // Start the receiver
}
void loop()
{
    
  if (vw_get_message(message, &messageLength)) // Non-blocking
  {
    receiveMSG = "";
      digitalWrite(ledPin, HIGH);
      Serial.print("Received: ");
      for (int i = 0; i < messageLength; i++)
      {
        receiveMSG = receiveMSG + message[i];     
      }
    Serial.println(" ---> " + receiveMSG);
    digitalWrite(ledPin, LOW);

    if( receiveMSG == "65" ) {
      Serial.println(" Shoot! ");
      zoomShootNow();
    }else{
      Serial.println(" No! ");
    }
  }else{
    digitalWrite(ledPin, LOW);
  }
}
