#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1  // Reset pin (se puede dejar en -1 si no se usa)
#define SCREEN_ADDRESS 0x3C  // Dirección I2C del OLED (0x3D en algunos modelos)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);

  // Inicializar la pantalla OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("Error: No se encontró la pantalla OLED"));
    while (1);
  }

  Serial.println(F("Pantalla OLED encontrada y lista"));

  display.clearDisplay();
  display.setTextSize(2); // Tamaño del texto
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 10);
  display.println("Hola I2C!");
  display.display(); // Mostrar en pantalla
}

void loop() {
}