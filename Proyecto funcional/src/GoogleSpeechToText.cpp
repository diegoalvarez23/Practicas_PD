#include "GoogleSpeechToText.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

GoogleSpeechToText::GoogleSpeechToText(const String& apiKey) {
    _apiKey = apiKey;
}

String GoogleSpeechToText::transcribeBase64(const String& audioBase64) {
    HTTPClient http;
    String url = "https://speech.googleapis.com/v1/speech:recognize?key=" + _apiKey;
    http.begin(url);
    http.addHeader("Content-Type", "application/json");

    // Crear el JSON correctament
    DynamicJsonDocument doc(16384);  // 16KB de buffer
    JsonObject config = doc.createNestedObject("config");
    config["encoding"] = "LINEAR16";
    config["sampleRateHertz"] = 16000;
    config["languageCode"] = "es-ES";

    JsonObject audio = doc.createNestedObject("audio");
    audio["content"] = audioBase64;

    String payload;
    serializeJson(doc, payload);

    int httpCode = http.POST(payload);
    String response = http.getString();
    http.end();

    if (httpCode > 0) {
        return response;
    } else {
        return "Error HTTP: " + String(httpCode);
    }
}
