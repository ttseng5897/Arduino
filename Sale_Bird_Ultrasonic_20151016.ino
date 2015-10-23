#include <Ultrasonic.h>

const byte ledPin = 13;
const byte pirButtonStatus = A0;
const byte soundButtonStatus = A1;

//PIR
const byte pirPin = 12;
const byte ledPIRPin = 7;
//Camera
const byte zoomPin = 0;
const byte shootPin = 1;

//Sound
#define trigPin   3
#define echoPin   4
const byte ledSoundPin = 8;
Ultrasonic ultrasonic(trigPin, echoPin);


void zoomShootNow() {
    
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledSoundPin, LOW);
    digitalWrite(ledPIRPin, LOW);
    Serial.println("Zoom....");
    digitalWrite(zoomPin, HIGH);
    delay(2000);
    digitalWrite(shootPin, HIGH);
    Serial.println("Shoot....");
    delay(1500);
    digitalWrite(zoomPin, LOW);
    digitalWrite(shootPin, LOW);
    Serial.println("Shoot finished....");
    digitalWrite(ledPin, LOW);
    
}

void setStatusButtonNow(int btnSound, int btnPIR) {
  Serial.println(btnSound);
  Serial.println(btnPIR);
  Serial.println("=============================");

    if(btnSound==1) {
        digitalWrite(ledSoundPin, HIGH);
        digitalWrite(ledPIRPin, LOW);     
        digitalWrite(ledPin, LOW);  
    }else if(btnPIR==1) {
        digitalWrite(ledSoundPin, LOW);
        digitalWrite(ledPIRPin, HIGH);
        digitalWrite(ledPin, LOW); 
    }else{
      digitalWrite(ledSoundPin, LOW);
        digitalWrite(ledPIRPin, LOW);
        digitalWrite(ledPin, HIGH); 
    }
}

void setup() {
 
  Serial.begin(9600);

  pinMode(ledPIRPin, OUTPUT);
  pinMode(ledSoundPin, OUTPUT);
  digitalWrite(ledPIRPin, LOW);
  digitalWrite(ledSoundPin, LOW);
 
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(zoomPin, OUTPUT);
  pinMode(shootPin, OUTPUT);
  pinMode (trigPin, OUTPUT);
  pinMode (echoPin, INPUT);
  pinMode (pirButtonStatus, INPUT);
  pinMode (soundButtonStatus, INPUT);
}

void loop() {
  int buttonSOUND = digitalRead(soundButtonStatus);
  int buttonPIR = digitalRead(pirButtonStatus);
  Serial.println(buttonSOUND);
  Serial.println(buttonPIR);
  Serial.println("-------------------------");
  setStatusButtonNow(buttonSOUND, buttonPIR);
 
  if(buttonSOUND==1) {    
    float cmMsec, inMsec;
    long microsec = ultrasonic.timing();
    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM); // 計算距離，單位: 公分
    
    Serial.println("MS: ");
    Serial.print(microsec);
    Serial.print(", CM: ");
    Serial.println(cmMsec);    
    
    if(cmMsec<90) {
      Serial.println("Distance < 90 detected!");
      zoomShootNow();
    }
  }
 
  if(buttonPIR==1) {    
    boolean val = digitalRead(pirPin);
    if (val) {
        Serial.println("PIR detected!");
        zoomShootNow();
        //delay(1000);
    }
  }
 
  delay(1000);
}
