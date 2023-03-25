//  Rx_Test_HUB
//  HUB_TUNQUEN_HILL
//  NRF24L01/BMP180
//  25-03-2023

#include "nRF24L01.h"
#include "RF24.h"
#include <SFE_BMP180.h>
#include <Wire.h>
#include <SPI.h>

SFE_BMP180 bmp180;
char status;
double t, p;

RF24 radio(9, 10);

const uint64_t rAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};
char msgBuffer[32];

const int ledPower = 5;
const int ledData = 6;
unsigned long lastMillis_ledPower = 0;
unsigned long lastMillis_ledData = 0;
unsigned long interval_ledPower = 1000;
unsigned long interval_ledData = 2000;

void receive() {
  //  Serial.println("void receiver() OK!");
  uint8_t pipe;
  if (radio.available(&pipe)) {
    //Serial.print("radio.available() in pipe ");
    //Serial.println(pipe);
    radio.read(&msgBuffer, 32);
    Serial.print("RX <-- [");
    Serial.print(msgBuffer);
    Serial.println("]");
  } else {
    //Serial.println("No Radio");
  }
}
//
//int counter = 0;
//unsigned long lastMillis = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Hi! AvaxScript...");

  if (bmp180.begin())
    Serial.println("BMP180 OK!");
  else
  {
    Serial.println("BMP180 ERROR!");
    while (1);
  }

  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(108);

  // Open up to six pipes for PRX to receive data
  radio.openReadingPipe(0, (uint64_t*)rAddress[0]);
  radio.openReadingPipe(1, (uint64_t*)rAddress[1]);
  radio.openReadingPipe(2, (uint64_t*)rAddress[2]);
  radio.openReadingPipe(3, (uint64_t*)rAddress[3]);
  radio.openReadingPipe(4, (uint64_t*)rAddress[4]);
  radio.openReadingPipe(5, (uint64_t*)rAddress[5]);

  radio.startListening();
  //  lastMillis = millis();

  pinMode(ledPower, OUTPUT);
  pinMode(ledData, OUTPUT);
  //  Serial.println("void setup() OK!");
}

void loop() {
  // Aqui se puede ubicar cualquier actividad que requiere periodicidad aproximada de 1 segundo
  //  if ((millis() - lastMillis) > 1000) {
  //    //Serial.print("millis difference is now ");
  //    //Serial.println(millis() - lastMillis);
  //    lastMillis = millis();
  //
  //    counter = counter + 1;
  //    if (counter > 59) {
  //      counter = 0;
  //    }
  //  }

  unsigned long currentMillis = millis();

  if (currentMillis - lastMillis_ledPower >= interval_ledPower) {
    lastMillis_ledPower = currentMillis;
    digitalWrite(ledPower, !digitalRead(ledPower));
  }

  if (currentMillis - lastMillis_ledData >= interval_ledData) {
    lastMillis_ledData = currentMillis;
    digitalWrite(ledData, !digitalRead(ledData));
  }

  status = bmp180.startTemperature();
  if (status != 0)
  {
    delay(status);
    status = bmp180.getTemperature(t);
    if (status != 0)
    {
      status = bmp180.startPressure(3);
      if (status != 0)
      {
        delay(status);
        status = bmp180.getPressure(p, t);
        if (status != 0)
        {
        }
      }
    }
  }

  Serial.print("t_bmp/p_bmp:");
  Serial.println(String(t) + "/" + String(p));

  receive();
  delay(1);
  //  Serial.println("void loop() OK!");
}
