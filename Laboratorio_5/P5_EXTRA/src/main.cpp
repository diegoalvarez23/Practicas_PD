#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h>

// Definir los buses I2C
TwoWire I2C_AHT10 = TwoWire(0);  // Bus I2C #1 para AHT10
TwoWire I2C_SSD1306 = TwoWire(1); // Bus I2C #2 para SSD1306

// Configuración de pines
#define SDA_AHT10 6
#define SCL_AHT10 7
#define SDA_SSD1306 8
#define SCL_SSD1306 9

// Inicializar dispositivos
Adafruit_AHTX0 aht;
Adafruit_SSD1306 display(128, 64, &I2C_SSD1306);

void setup() {
    Serial.begin(115200);
    
    // Iniciar buses I2C
    I2C_AHT10.begin(SDA_AHT10, SCL_AHT10, 100000);
    I2C_SSD1306.begin(SDA_SSD1306, SCL_SSD1306, 100000);
    
    // Inicializar el sensor AHT10
    if (!aht.begin(&I2C_AHT10)) {
        Serial.println("Error: No se encontró el sensor AHT10");
        while (1);
    }
    Serial.println("AHT10 inicializado correctamente");
    
    // Inicializar la pantalla OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("Error: No se encontró la pantalla SSD1306");
        while (1);
    }
    Serial.println("Pantalla SSD1306 inicializada correctamente");
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.print("Inicializando...");
    display.display();
    delay(2000);
}

void loop() {
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);  // Obtener datos del AHT10
    
    // Mostrar valores en pantalla
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.print("Temp: ");
    display.print(temp.temperature);
    display.print(" C");
    
    display.setCursor(0, 20);
    display.print("Humedad: ");
    display.print(humidity.relative_humidity);
    display.print(" %");
    
    display.display();
    delay(2000);  // Actualizar cada 2 segundos
}