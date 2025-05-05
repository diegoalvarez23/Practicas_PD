#include <SPI.h>
#include <SD.h>

#define CS_PIN 5  // Prueba con 5 o cambia a otro pin si es necesario

void setup() {
    Serial.begin(115200);
    Serial.println("Iniciando SD ...");

    SPI.begin(18, 20, 35, CS_PIN);  // SCK, MISO, MOSI, CS
    if (!SD.begin(CS_PIN, SPI, 4000000)) { // Reduce la velocidad SPI
        Serial.println("No se pudo inicializar la tarjeta SD.");
        return;
    }

    Serial.println("Tarjeta SD inicializada correctamente.");

    // Escribir en archivo.txt
    File myFile = SD.open("/archivo.txt", FILE_WRITE);
    if (myFile) {
        Serial.println("Escribiendo en archivo.txt...");
        myFile.println("Soy el mejor del mundo");
        myFile.close();
        Serial.println("Escritura completada.");
    } else {
        Serial.println("Error al abrir archivo.txt para escritura.");
    }

    // Leer archivo.txt
    myFile = SD.open("/archivo.txt");
    if (myFile) {
        Serial.println("Contenido de archivo.txt:");
        while (myFile.available()) {
            Serial.write(myFile.read());
        }
        myFile.close();
    } else {
        Serial.println("Error al abrir archivo.txt para lectura.");
    }
}

void loop() {
    // No hacemos nada en loop()
}


