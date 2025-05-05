#include <Arduino.h>

#define RXD2 16
#define TXD2 17

String inputBuffer = "";   // Lo que el usuario escribe
String echoBuffer = "";    // Lo que regresa de UART2
bool waitingEcho = false;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Escribe un mensaje y presiona Enter para enviarlo.");
}

void loop() {
  // Mientras escribes, mostrar en pantalla y almacenar
  while (Serial.available()) {
    char c = Serial.read();
    Serial.print(c);           // Mostrar en tiempo real
    inputBuffer += c;

    // Si presionas Enter
    if (c == '\n') {
      Serial2.print(inputBuffer); // Enviar todo a UART2
      waitingEcho = true;         // Activar lectura de eco
      echoBuffer = "";            // Limpiar buffer de eco
      inputBuffer = "";           // Limpiar entrada
    }
  }

  // Leer eco de UART2
  while (waitingEcho && Serial2.available()) {
    char c = Serial2.read();
    echoBuffer += c;

    // Si detectamos que terminó el eco (por \n)
    if (c == '\n') {
      Serial.print("[ECO] ");
      Serial.print(echoBuffer); // Mostrar todo junto
      waitingEcho = false;
    }
  }
}




