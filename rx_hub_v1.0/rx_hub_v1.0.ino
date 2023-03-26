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
unsigned long lastMillis_bmp180 = 0;
unsigned long interval_bmp180 = 500;

RF24 radio(9, 10);
const uint64_t rAddress[] = {0x7878787878LL, 0xB3B4B5B6F1LL, 0xB3B4B5B6CDLL, 0xB3B4B5B6A3LL, 0xB3B4B5B60FLL, 0xB3B4B5B605LL};
char msgBuffer[32];
unsigned long lastMillis_rx = 0;
unsigned long interval_rx = 100;

const int ledPower = 5;
const int ledData = 6;
unsigned long lastMillis_ledPower = 0;
unsigned long interval_ledPower = 1000;

void setup() {
  Serial.begin(115200);
  Serial.println("Hi! AvaxScript...");

  if (bmp180.begin())
    Serial.println("bmp180 OK!");
  else
  {
    Serial.println("bmp180 ERROR!");
    while (1);
  }

  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(108);

  for (int i = 0; i < 6; i++) {
    radio.openReadingPipe(i, rAddress[i]);
  }

  radio.startListening();

  pinMode(ledPower, OUTPUT);
  pinMode(ledData, OUTPUT);
  //  Serial.println("void setup() OK!");
}

void receive() {
  //    Serial.println("void receiver() OK!")
  uint8_t pipe;
  if (radio.available(&pipe)) {
    //Serial.print("radio.available() in pipe ");
    //Serial.println(pipe);
    radio.read(&msgBuffer, 32);
    Serial.print("RX <-- [");
    Serial.print(msgBuffer);
    Serial.println("]");
    //    digitalWrite(ledData, !digitalRead(ledData));
  } else {
    //Serial.println("No Radio");
  }
  digitalWrite(ledData, !digitalRead(ledData));
}

void sensor_bmp180() {
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
          Serial.print("t_bmp/p_bmp:");
          Serial.println(String(t) + "/" + String(p));
        }
      }
    }
  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastMillis_ledPower >= interval_ledPower) {
    lastMillis_ledPower = currentMillis;
    digitalWrite(ledPower, !digitalRead(ledPower));
  }

  if (currentMillis - lastMillis_bmp180 >= interval_bmp180) {
    lastMillis_bmp180 = currentMillis;
    sensor_bmp180();
  }

  if (currentMillis - lastMillis_rx >= interval_rx) {
    lastMillis_rx = currentMillis;
    receive();
  }
  //  Serial.println("void loop() OK!");
}
