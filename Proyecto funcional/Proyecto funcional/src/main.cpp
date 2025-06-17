#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "INMP441.h"
#include "AudioEncoder.h"
#include "DisplayManager.h"  // 👈 NUEVO

#define BUTTON_PIN 8

const char* ssid = "Pixel_8349";
const char* password = "9htd3nf4ef6pxu4";
const char* API_KEY = "AIzaSyCEAgc9_IVYqrj1TFfrDuHcdcOgZgShYfM";

const char* GOOGLE_SPEECH_API = "https://speech.googleapis.com/v1/speech:recognize?key=";
const char* GOOGLE_TRANSLATE_API = "https://translation.googleapis.com/language/translate/v2?key=";

INMP441 mic;
DisplayManager display;  // 👈 NUEVO

#define SAMPLE_RATE 16000
#define NUM_CHANNELS 1
#define BITS_PER_SAMPLE 16

void generateWavHeader(uint8_t* header, uint32_t pcmDataSize) {
    uint32_t fileSize = pcmDataSize + 36;
    uint32_t byteRate = SAMPLE_RATE * NUM_CHANNELS * (BITS_PER_SAMPLE / 8);
    uint16_t blockAlign = NUM_CHANNELS * (BITS_PER_SAMPLE / 8);
    uint16_t audioFormat = 1;
    uint32_t subchunk1Size = 16;
    uint16_t numChannels = NUM_CHANNELS;
    uint32_t sampleRate = SAMPLE_RATE;
    uint16_t bitsPerSample = BITS_PER_SAMPLE;

    memcpy(header, "RIFF", 4);
    memcpy(header + 4, &fileSize, 4);
    memcpy(header + 8, "WAVE", 4);
    memcpy(header + 12, "fmt ", 4);
    memcpy(header + 16, &subchunk1Size, 4);
    memcpy(header + 20, &audioFormat, 2);
    memcpy(header + 22, &numChannels, 2);
    memcpy(header + 24, &sampleRate, 4);
    memcpy(header + 28, &byteRate, 4);
    memcpy(header + 32, &blockAlign, 2);
    memcpy(header + 34, &bitsPerSample, 2);
    memcpy(header + 36, "data", 4);
    memcpy(header + 40, &pcmDataSize, 4);
}

void connectToWiFi() {
    display.showMessage("Connexió WiFi...");
    Serial.print("📡 Connectant a WiFi: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\n✅ Connectat a WiFi");
    display.showMessage("WiFi connectat!");
}

String translateText(String sourceText) {
    display.showMessage("Traduint...");
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient https;
    String url = String(GOOGLE_TRANSLATE_API) + API_KEY;
    https.begin(client, url);
    https.addHeader("Content-Type", "application/json");

    String payload = "{"
        "\"q\": \"" + sourceText + "\","
        "\"source\": \"ca\","
        "\"target\": \"en\","
        "\"format\": \"text\""
    "}";

    int httpCode = https.POST(payload);
    String response = https.getString();
    https.end();

    Serial.println("📥 Resposta de traducció:");
    Serial.println(response);

    int transIndex = response.indexOf("\"translatedText\":");
    if (transIndex != -1) {
        int start = response.indexOf("\"", transIndex + 18) + 1;
        int end = response.indexOf("\"", start);
        return response.substring(start, end);
    }
    return "❌ Traducció no trobada.";
}

void setup() {
    Serial.begin(115200);
    display.begin();  // 👈 Inicializa LCD

    display.showMessage("Iniciant microfon...");
    mic.begin();
    display.showMessage("Microfon llest!");

    pinMode(BUTTON_PIN, INPUT_PULLUP);
    display.showMessage("Prem el boto...");

    while (digitalRead(BUTTON_PIN) == HIGH) delay(10);
    delay(100);
    display.showMessage("Parla en 2s...");
    delay(2000);

    const size_t samples = 16000;
    const size_t pcmSize = samples * sizeof(int16_t);
    const size_t totalSize = 44 + pcmSize;

    int16_t* audioBuffer = (int16_t*) malloc(samples * sizeof(int16_t));
    if (!audioBuffer) {
        display.showMessage("Error memòria");
        return;
    }

    display.showMessage("Gravant àudio...");
    mic.read(audioBuffer, samples);

    uint8_t* wavData = (uint8_t*) malloc(totalSize);
    if (!wavData) {
        free(audioBuffer);
        display.showMessage("Error WAV");
        return;
    }

    generateWavHeader(wavData, pcmSize);
    memcpy(wavData + 44, audioBuffer, pcmSize);
    free(audioBuffer);

    display.showMessage("Codificant...");
    String base64Audio = encodeToBase64((int16_t*)wavData, totalSize / 2);
    free(wavData);

    if (base64Audio.length() < 100) {
        display.showMessage("Error Base64");
        return;
    }

    connectToWiFi();

    display.showMessage("Enviant a STT...");
    WiFiClientSecure client;
    client.setInsecure();

    HTTPClient https;
    String url = String(GOOGLE_SPEECH_API) + API_KEY;
    https.begin(client, url);
    https.addHeader("Content-Type", "application/json");

    String payload = "{"
        "\"config\": {"
            "\"encoding\": \"LINEAR16\","
            "\"sampleRateHertz\": 16000,"
            "\"languageCode\": \"ca-ES\""
        "},"
        "\"audio\": {"
            "\"content\": \"" + base64Audio + "\""
        "}"
    "}";

    int httpCode = https.POST(payload);
    String response = https.getString();
    https.end();

    Serial.println("📬 Resposta de Google Speech:");
    Serial.println(response);

    int transcriptIndex = response.indexOf("\"transcript\":");
    if (transcriptIndex != -1) {
        int start = response.indexOf("\"", transcriptIndex + 13) + 1;
        int end = response.indexOf("\"", start);
        String transcription = response.substring(start, end);
        Serial.print("📝 Transcripció: ");
        Serial.println(transcription);

        display.showLines("Transcripcio:", transcription);

        String translated = translateText(transcription);
        Serial.print("🔁 Traduccio (en): ");
        Serial.println(translated);

        display.showLines("Traduccio:", translated);
    } else {
        display.showMessage("❌ Sense transcripcio");
    }

    WiFi.disconnect();
}

void loop() {}
