#ifndef INMP441_H
#define INMP441_H

#include <Arduino.h>

class INMP441 {
public:
    void begin();
    void read(int16_t* buffer, size_t len);
};

#endif
