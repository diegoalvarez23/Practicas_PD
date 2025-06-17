#include "SDManager.h"
#include <SD.h>
#include <SPI.h>

bool SDManager::begin(int csPin) {
    SPI.begin(17, 35, 18, csPin);  // SCK, MISO, MOSI, CS
    return SD.begin(csPin);
}

bool SDManager::saveWav(const char* filename, const int16_t* data, size_t sampleCount, uint32_t sampleRate) {
    File file = SD.open(filename, FILE_WRITE);
    if (!file) return false;

    uint32_t dataSize = sampleCount * sizeof(int16_t);
    uint32_t chunkSize = 36 + dataSize;

    // ✨ Capçalera WAV (PCM 16-bit mono, 16000 Hz)
    file.write((const uint8_t*)"RIFF", 4);
    file.write((uint8_t*)&chunkSize, 4);
    file.write((const uint8_t*)"WAVE", 4);
    file.write((const uint8_t*)"fmt ", 4);

    uint32_t subchunk1Size = 16;
    uint16_t audioFormat = 1; // PCM
    uint16_t numChannels = 1;
    uint16_t bitsPerSample = 16;
    uint32_t byteRate = sampleRate * numChannels * bitsPerSample / 8;
    uint16_t blockAlign = numChannels * bitsPerSample / 8;

    file.write((uint8_t*)&subchunk1Size, 4);
    file.write((uint8_t*)&audioFormat, 2);
    file.write((uint8_t*)&numChannels, 2);
    file.write((uint8_t*)&sampleRate, 4);
    file.write((uint8_t*)&byteRate, 4);
    file.write((uint8_t*)&blockAlign, 2);
    file.write((uint8_t*)&bitsPerSample, 2);

    file.write((const uint8_t*)"data", 4);
    file.write((uint8_t*)&dataSize, 4);

    // 💾 Escriure les dades d'àudio
    file.write((const uint8_t*)data, dataSize);

    file.close();
    return true;
}
