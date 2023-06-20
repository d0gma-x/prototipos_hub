#include <SoftwareSerial.h>

#define RX_PIN 2 // Tx SDS011
#define TX_PIN 3 // Rx SDS011

SoftwareSerial sdsSerial(RX_PIN, TX_PIN);

void setup() {
  Serial.begin(9600);
  sdsSerial.begin(9600);
}

void loop() {
  if (sdsSerial.available()) {
    uint8_t data[10];
    size_t bytesRead = sdsSerial.readBytes(data, 10);

    // Comprobamos que se hayan leído los 10 bytes correctamente
    if (bytesRead == 10) {
      if (data[0] == 0xAA && data[1] == 0xC0) {
        uint8_t checksum = 0;
        for (int i = 2; i < 8; i++) {
          checksum += data[i];
        }
        if (checksum == data[8]) {
          // Calculamos los valores de PM2.5 y PM10
          float pm25 = ((data[3] << 8) + data[2]) / 10.0;
          float pm10 = ((data[5] << 8) + data[4]) / 10.0;

          Serial.print("PM2.5: ");
          Serial.print(pm25);
          Serial.print(" ug/m3\tPM10: ");
          Serial.print(pm10);
          Serial.println(" ug/m3");
        }
      }
    }
  }
  delay(1000);
}
