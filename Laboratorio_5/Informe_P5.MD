# Informe de Práctica 5: Buses de Comunicación I (I2C)

Nombre: Diego Alvarez i Pere Villaronga
Fecha: 17-03-2025
Asignatura: Processadors Digitals

## Objetivos

    ·Comprender el funcionamiento del bus I2C
    ·Implementar comunicación con dispositivos I2C
    ·Controlar una pantalla OLED mediante I2C
    ·Utilizar múltiples dispositivos en el mismo bus I2C
    ·Implementar un sistema con dos buses I2C independientes

## Materiales y Herramientas

- Placa ESP32
- Pantalla OLED SSD1306 (128x32 o 128x64)
- Sensor AHT10 (temperatura y humedad)
- Cableado 
- Entorno de desarrollo Arduino IDE
- Bibliotecas: Wire, Adafruit_GFX, Adafruit_SSD1306, Adafruit_AHTX0

## Introducción Teórica

El bus I2C (Inter-Integrated Circuit) es un protocolo de comunicación serial sincrónico que utiliza solo dos líneas:
- SDA (Serial Data): Línea de datos bidireccional
- SCL (Serial Clock): Línea de reloj para sincronización

## Características principales

- Velocidades estándar: 100kHz (modo estándar), 400kHz (modo rápido)
- Arquitectura maestro-esclavo
- Direccionamiento de 7 bits (hasta 112 dispositivos)
- Mecanismos de acknowledge para verificar recepción
- Soporte para múltiples maestros (arbitraje)


## Ejercicio Práctico 1: Comunicación con Pantalla OLED

### Resultados y Análisis
Salida por puerto serie:

**(Pantalla OLED encontrada y lista)**

Funcionamiento:

1. Se inicializa la comunicación I2C con la pantalla OLED
2. Se configura el texto a mostrar ("Hola I2C!")
3. La pantalla muestra el mensaje correctamente
4. La dirección I2C por defecto es 0x3C para esta pantalla

*Conexión física:*

ESP32     OLED
GPIO21  → SDA
GPIO22  → SCL
3.3V    → VCC
GND     → GND


##  Ejercicio Práctico 2: Sistema con Dos Buses I2C Independientes

### Resultados y Análisis
Salida por puerto serie:

*AHT10 inicializado correctamente*
*Pantalla SSD1306 inicializada correctamente*

Funcionamiento:

1. Se utilizan dos buses I2C independientes:
2. Bus 0: Para el sensor AHT10 (pines 6 y 7)
3. Bus 1: Para la pantalla OLED (pines 8 y 9)
4. El sensor AHT10 mide temperatura y humedad
5. Los datos se muestran en la pantalla OLED cada 2 segundos
6. La separación en buses independientes evita conflictos de direcciones

Conexión física:

- Bus I2C #1 (AHT10):
ESP32/AHT10
GPIO6   → SDA
GPIO7   → SCL
3.3V    → VCC
GND     → GND

- Bus I2C #2 (OLED):
ESP32/OLED
GPIO8   → SDA
GPIO9   → SCL
3.3V    → VCC
GND     → GND


## Ejercicio de Subida de Nota: Monitor de Salud con OLED y MAX30102

Implementación Propuesta
### Parte 1 - Mostrar datos en OLED:

- Código similar al anterior pero integrando el sensor MAX30102
- Mostraría frecuencia cardíaca y oxígeno en sangre en la pantalla

### Parte 2 - Servidor Web:

Implementar un servidor web con ESP32 que muestre:
- Frecuencia cardíaca actual
- Nivel de oxígeno en sangre
- Gráficos históricos
- Alertas si los valores están fuera de rango


## Conclusiones

- El bus I2C es eficiente para conectar múltiples dispositivos con pocos cables
- La dirección I2C es fundamental para identificar cada dispositivo
- En casos de conflictos de direcciones, se pueden usar buses I2C independientes
- Las resistencias pull-up son esenciales para una comunicación fiable
- La velocidad estándar (100kHz) es suficiente para la mayoría de aplicaciones con sensores

## Referencias

    Documentación oficial de FreeRTOS [Google](https://www.freertos.org/)
    Tutorial I2C con ESP32 [Google](https://randomnerdtutorials.com/esp32-i2c-communication-arduino-ide/)
    Biblioteca Adafruit SSD1306 [Google](https://github.com/adafruit/Adafruit_SSD1306)
    Documentación del sensor AHT10 [Google](https://learn.adafruit.com/adafruit-aht20)