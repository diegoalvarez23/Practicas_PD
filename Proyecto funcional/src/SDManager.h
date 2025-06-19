#ifndef SD_MANAGER_H
#define SD_MANAGER_H

#include <Arduino.h>

class SDManager {
public:
    bool begin(int csPin);
    bool saveWav(const char* filename, const int16_t* data, size_t sampleCount, uint32_t sampleRate);
};

#endif
