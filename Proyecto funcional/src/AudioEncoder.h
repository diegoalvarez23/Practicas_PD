#ifndef AUDIO_ENCODER_H
#define AUDIO_ENCODER_H

#include <Arduino.h>

String encodeToBase64(const int16_t* buffer, size_t len);

#endif

