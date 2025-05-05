#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9    // GPIO 9 per Reset
#define SS_PIN 10    // GPIO 10 per Chip Select

MFRC522 mfrc522(SS_PIN, RST_PIN); // Creem l’objecte RC522

void setup() {
  Serial.begin(115200);
  SPI.begin(12, 13, 11, 10); // SCK, MISO, MOSI, SS
  mfrc522.PCD_Init();       // Iniciem el lector RC522
  Serial.println("📡 Apropa una targeta RFID...");
}

void loop() {
  // Mirem si hi ha una targeta nova
  if (mfrc522.PICC_IsNewCardPresent()) {
    // Llegim la targeta
    if (mfrc522.PICC_ReadCardSerial()) {
      Serial.print("🆔 UID: ");
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        if (mfrc522.uid.uidByte[i] < 0x10) Serial.print("0");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
      mfrc522.PICC_HaltA(); // Aturem la lectura
    }
  }
}
  