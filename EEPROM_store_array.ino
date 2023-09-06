#include <EEPROM.h>

const int buttons[6] = {2, 3, 4, 5, 6, 7};
const int writeButton = 8; 
const int deleteButton = 9;
const int clearEEPROMButton = 10;

struct Coordinates {
  long latitude;
  long longitude;
};

const int EEPROM_SIZE = 8 * 6;

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 6; i++) {
    pinMode(buttons[i], INPUT_PULLUP); 
  }
  pinMode(writeButton, INPUT_PULLUP);
  pinMode(deleteButton, INPUT_PULLUP);
  pinMode(clearEEPROMButton, INPUT_PULLUP);

  if (EEPROM.length() < EEPROM_SIZE) {
    Serial.println("EEPROM size is not sufficient!");
  }
}

void loop() {
  for (int i = 0; i < 6; i++) {
    if (digitalRead(buttons[i]) == LOW) {
      if (digitalRead(writeButton) == LOW) {
        Coordinates coords;
        coords.latitude = random(0, 1000000);
        coords.longitude = random(0, 1000000);
        EEPROM.put(i * sizeof(Coordinates), coords);
        delay(500);
      }

      if (digitalRead(deleteButton) == LOW) {
        Coordinates zeroCoords = {0, 0};
        EEPROM.put(i * sizeof(Coordinates), zeroCoords);
        delay(500);
      }
    }
  }

  if (digitalRead(clearEEPROMButton) == LOW) {
    for (int i = 0; i < EEPROM.length(); i++) {
      EEPROM.write(i, 0);
    }
    delay(500);
  }

  for (int i = 0; i < 6; i++) {
    Coordinates storedCoords;
    EEPROM.get(i * sizeof(Coordinates), storedCoords);
    Serial.print("Position ");
    Serial.print(i);
    Serial.print(": Latitude = ");
    Serial.print(storedCoords.latitude);
    Serial.print(", Longitude = ");
    Serial.println(storedCoords.longitude);
  }

  delay(1000);
}