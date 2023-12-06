#include <SPI.h>
#include <MFRC522.h>

// RFID Reader Pins
// IRQ              UNCONNECTED
// SCK              13
// MISO             12
// MOSI             11
const int SDA_PIN = 10;
const int RST_PIN = 9;

// Sample Output LED Pins
const int pPLED = 4;
const int nPLED = 5;
const int pNLED = 2; 
const int nNLED = 3;

MFRC522 mfrc522(SDA_PIN, RST_PIN);

void setup() {
  pinMode(pPLED, OUTPUT);
  pinMode(nPLED, OUTPUT);
  pinMode(pNLED, OUTPUT);
  pinMode(nNLED, OUTPUT);

  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {// Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) return;
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) return;

  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "8E DD E7 C6" || // Lawrence
      content.substring(1) == "3E 38 E1 C6" || // Jerome
      content.substring(1) == "DE 23 93 C0" || // Ryan
      content.substring(1) == "EE D2 92 C0" || // Vhenise
      content.substring(1) == "CE 83 90 C0" || // Sophia
      content.substring(1) == "FE 23 AE C0" || // David
      content.substring(1) == "CE FB F4 C5" || // Aouien
      content.substring(1) == "DE AE B0 C0") // Nicole
  {
    digitalWrite(pPLED, HIGH);
    digitalWrite(nPLED, LOW);
    Serial.println("Authorized access");
    Serial.println();
    delay(1000);
    digitalWrite(pPLED, LOW);
    digitalWrite(nPLED, LOW);
  }
 
 else   {
    digitalWrite(pNLED, HIGH);
    digitalWrite(nNLED, LOW);
    Serial.println("Access denied");
    Serial.println();
    delay(1000);
    digitalWrite(pNLED, LOW);
    digitalWrite(nNLED, LOW);
  }
}
