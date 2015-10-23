#include <DHT.h>
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
#include <VirtualWire.h>

const byte ledPowerPin = 13;
const byte ledReceivePin = 5;
const byte ledSendPin = 6;
const byte rfSendPin = 3;
const byte rfRecvPin = 2;
const byte soundPin = 4;
const byte sensorTemperaturePin = 7;
const byte sensorPIRPin = 8;

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

void sendData(String stringSend, char charType) {

  Serial.println(); Serial.print("Received string: ");Serial.println(stringSend);
  int tmpNumberValue = stringSend.toInt();
  String stringVal =  charType + String(tmpNumberValue, DEC) + ' ';  
  Serial.print("stringVal to number: ");Serial.println(stringVal); //display string
  char finalArray[stringVal.length()];
  stringVal.toCharArray(finalArray,stringVal.length());
  setLED('B');
  vw_send((uint8_t *)finalArray, sizeof(finalArray));
  vw_wait_tx(); // Wait until the whole message is gone
  setLED('A');
}


void setup() {
  Serial.begin(9600);
  pinMode(ledPowerPin, OUTPUT);
  pinMode(ledReceivePin, OUTPUT);
  pinMode(ledSendPin, OUTPUT);    
  pinMode(soundPin, OUTPUT);
  pinMode(sensorTemperaturePin, INPUT);
  pinMode(sensorPIRPin, INPUT);
  
  vw_set_tx_pin(rfSendPin);
  // Initialize the IO and ISR
  vw_setup(2000); // Bits per sec
  dht.begin();
  Serial.println("Device is ready");  
  setLED('A');
}

void loop(){
  // Wait a few seconds between measurements.
  delay(5000);
  boolean statusPIR = digitalRead(sensorPIRPin);
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  //溫度 
  int tmpNumberValue;
  char tmpArrayValue[3];               //temporarily holds data from vals 
  
  dtostrf(t, 3, 0, tmpArrayValue);  
  String stringTVal = String(tmpArrayValue);
  //Serial.print("Send this string: ");Serial.println(stringTVal); //display string
  sendData(stringTVal,'T');

  delay(5000);

  dtostrf(h, 3, 0, tmpArrayValue); 
  String stringHVal = String(tmpArrayValue);
  sendData(stringHVal,'H');


  //stringSend = "A-Sensor:" + String(statusPIR) + "|" + stringHVal + "|" + stringTVal+":End";

  

  
}
