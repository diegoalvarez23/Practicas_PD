#ifndef GOOGLE_SPEECH_TO_TEXT_H
#define GOOGLE_SPEECH_TO_TEXT_H

#include <Arduino.h>

class GoogleSpeechToText {
public:
    GoogleSpeechToText(const String& apiKey);
    String transcribeBase64(const String& audioBase64);
private:
    String _apiKey;
};

#endif
