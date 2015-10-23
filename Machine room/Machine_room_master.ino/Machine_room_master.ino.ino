#include <VirtualWire.h>
const byte ledPowerPin = 13;
const byte ledReceivePin = 5;
const byte ledSendPin = 6;
const byte rfRecvPin =  2; 
const byte rfSendPin = 3;

uint8_t message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
uint8_t messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
char inData[20];
String receiveMSG;

void send (char *message)
{
  setLED('B');
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
  delay(500);
  setLED('A');
}

void setLED(char txtStatus) {
  switch (txtStatus) {
    case 'A':
      digitalWrite(ledPowerPin, HIGH);
      digitalWrite(ledSendPin, LOW);
      digitalWrite(ledReceivePin, LOW);
      break;
    case 'B':
      digitalWrite(ledPowerPin, LOW);
      digitalWrite(ledSendPin, HIGH);
      digitalWrite(ledReceivePin, LOW);
      break;
    case 'C':
      digitalWrite(ledPowerPin, LOW);
      digitalWrite(ledSendPin, LOW);
      digitalWrite(ledReceivePin, HIGH);
      break;
    default: 
      digitalWrite(ledPowerPin, LOW);
      digitalWrite(ledSendPin, LOW);
      digitalWrite(ledReceivePin, LOW);
    break;
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(ledPowerPin, OUTPUT);
  pinMode(ledReceivePin, OUTPUT);
  pinMode(ledSendPin, OUTPUT);  

  // Initialize the IO and ISR
  vw_set_rx_pin(rfRecvPin);
  vw_setup(2000); // Bits per sec
  vw_rx_start(); // Start the receiver

  Serial.println("Device is ready");
  setLED('A');
}
void loop()
{
  if (vw_get_message(message, &messageLength)) // Non-blocking
  {
    setLED('C');
    receiveMSG = '';
      int i;
      for (i = 0; i < messageLength; i++)
      {
        //Serial.print(i);Serial.print(":");Serial.println(message[i]);
        //Serial.print(' ');
        char txtReceived = message[i];
        receiveMSG = receiveMSG + txtReceived;    
      }  
    Serial.println();
    Serial.println("Received " + String(i) + " words is " + receiveMSG);
    delay(500);
    setLED('A');
  }
}
