#include "DisplayManager.h"

void DisplayManager::begin() {
    Wire.begin(20, 21);  // SDA = 20, SCL = 21
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Display inicialitzat");
}

void DisplayManager::clear() {
    lcd.clear();
}

void DisplayManager::showMessage(const String& msg) {
    lcd.clear();
    int row = 0;
    int len = msg.length();

    for (int i = 0; i < len && row < 4; i += 20) {
        lcd.setCursor(0, row++);
        lcd.print(msg.substring(i, i + 20));
    }
}

void DisplayManager::showLines(const String& line1, const String& line2, const String& line3, const String& line4) {
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print(line1);
    lcd.setCursor(0, 1); lcd.print(line2);
    lcd.setCursor(0, 2); lcd.print(line3);
    lcd.setCursor(0, 3); lcd.print(line4);
}
