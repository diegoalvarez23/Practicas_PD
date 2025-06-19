#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <LiquidCrystal_I2C.h>

class DisplayManager {
public:
    void begin();
    void showMessage(const String& msg);
    void showLines(const String& line1, const String& line2 = "", const String& line3 = "", const String& line4 = "");
    void clear();

private:
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4); // Dirección I2C y tamaño del LCD
};

#endif
