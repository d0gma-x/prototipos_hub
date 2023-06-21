#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3

SoftwareSerial SoftSerial(rxPin, txPin);
unsigned char lastcharacter[10];
unsigned int count = 0;
unsigned int pm100 = 0;

void setup() {
  Serial.begin(9600);
  SoftSerial.begin(9600);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
}

void loop() {
  if (SoftSerial.available() < 32) {
    count = 0;
    while (SoftSerial.available()) {
      lastcharacter[count] = SoftSerial.read();
      count++;
    }
    pm100 = (((unsigned int)lastcharacter[4]) + ((unsigned int)lastcharacter[5]) * 256) / 10;

    Serial.print("PM100: ");
    Serial.print(pm100);
    Serial.println(" µg/m³");

    delay(500);
  }
}
