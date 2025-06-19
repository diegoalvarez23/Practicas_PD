#include "WiFiConnection.h"
#include <WiFi.h>

void WiFiConnection::begin(const char* ssid, const char* password) {
    Serial.println("Conectando a WiFi...");

    IPAddress dns(8, 8, 8, 8);  // DNS de Google
    WiFi.disconnect(true);      // Força reconexió neta
    WiFi.config(INADDR_NONE, INADDR_NONE, dns); // Assigna DNS

    WiFi.begin(ssid, password);

    unsigned long startAttemptTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 15000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\n✅ Conectado a WiFi!");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\n❌ No s'ha pogut connectar.");
    }

    // ⚠️ Esperar per estabilitzar DNS
    Serial.println("🌐 Esperant per estabilitzar la connexió DNS...");
    delay(2000);
}

bool WiFiConnection::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}
