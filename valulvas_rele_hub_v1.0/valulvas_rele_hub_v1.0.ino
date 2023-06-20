//  Valvulas_Rele_HUB
//  HUB_TUNQUEN_HILL
//  CONTROL DE RELES PARA SIMULACION DE VALVULAS
//  23-03-2023

const int rele[4] = {9, 8, 7, 6};
const int highState = HIGH;
const int lowState = LOW;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 4; i++) {
    pinMode(rele[i], OUTPUT);
  }

  digitalWrite(rele[0], highState);
  digitalWrite(rele[1], highState);
  digitalWrite(rele[2], highState);
  digitalWrite(rele[3], highState);
}

void loop() {
  digitalWrite(rele[0], lowState);
  digitalWrite(rele[1], highState);
  digitalWrite(rele[2], highState);
  digitalWrite(rele[3], highState);
  //  Serial.println("Rele1 && Rele3 ON!");
  //  Serial.println("Rele2 && Rele4 OFF!");
  delay(2000);

  digitalWrite(rele[0], highState);
  digitalWrite(rele[1], lowState);
  digitalWrite(rele[2], highState);
  digitalWrite(rele[3], highState);
  //  Serial.println("Rele1 && Rele3 OFF!");
  //  Serial.println("Rele2 && Rele4 ON!");
  delay(2000);

  digitalWrite(rele[0], highState);
  digitalWrite(rele[1], highState);
  digitalWrite(rele[2], lowState);
  digitalWrite(rele[3], highState);
  //  Serial.println("Rele1 && Rele3 ON!");
  //  Serial.println("Rele2 && Rele4 ON!");
  delay(2000);

  digitalWrite(rele[0], highState);
  digitalWrite(rele[1], highState);
  digitalWrite(rele[2], highState);
  digitalWrite(rele[3], lowState);
  //  Serial.println("Rele1 && Rele3 ON!");
  //  Serial.println("Rele2 && Rele4 ON!");
  delay(2000);

  
}
