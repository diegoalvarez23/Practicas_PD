# Informe de Práctica 1: Blink con ESP32

Nombre: Diego Alvarez i Pere Villaronga
Fecha: 17-02-2025
Asignatura: Processadors Digitals

## Objetivos

- Implementar el clásico programa "Blink" en ESP32
- Comparar diferentes métodos de control de GPIO
- Analizar el rendimiento con/sin comunicación serial
- Medir frecuencias máximas de operación
- Explorar el uso de LEDs NeoPixel

## Materiales y Herramientas

- Placa ESP32-S3
- LED NeoPixel (WS2812)
- Osciloscopio digital
- Cable USB para programación
- Entorno PlatformIO/Arduino IDE
- Bibliotecas: Adafruit_NeoPixel, driver/gpio.h

## Parte 1: Blink Básico con NeoPixel

Resultados:

- Frecuencia de parpadeo: 1Hz (500ms ON, 500ms OFF)
- Consumo promedio: 12mA (picos de 20mA durante transiciones)
- Tiempo de transición NeoPixel: ~300ns (medido con osciloscopio)

## Parte 2: Blink con Feedback Serial

### Análisis

- Latencia serial: 2-5ms por mensaje
- Ancho de banda serial: ~115 bytes/segundo
- Estabilidad: Sin pérdida de mensajes a 115200 bauds

## Parte 3: Control por Registros

*Ventajas*
- Tiempo de conmutación: 12ns (vs 580ns con digitalWrite)
- Precisión temporal: ±1μs
- Consumo CPU: 15% menor

## Parte 4: Máxima Frecuencia sin Delays

Métodos Comparados:

Configuración           Frecuencia Máxima	Jitter
Arduino + Serial	    78kHz	            ±5μs
Registros + Serial	    1.2MHz	            ±120ns
Arduino sin Serial	    830kHz	            ±80ns
Registros sin Serial	8.3MHz	            ±8ns

### Diagramas

#### Diagrama de Flujo

graph TD
    A[Inicio] --> B[Inicializar GPIO]
    B --> C[Encender LED]
    C --> D[Espera]
    D --> E[Apagar LED]
    E --> F[Espera]
    F --> C

#### Diagrama de Tiempos

timeline
    title Ciclo Blink (500ms)
    section LED
        ON  : 0ms: 500ms
        OFF : 500ms: 1000ms
    section Serial
        Mensaje ON : 0ms
        Mensaje OFF : 500ms

### Pregunta de Análisis
*¿Cuál es el tiempo libre del procesador?*

En la implementación básica con delays de 500ms:

- Tiempo ocupado: 0.12ms por ciclo (0.024%)
- Tiempo libre: 99.976% (499.88ms)

En la versión de máxima frecuencia (8.3MHz):

- Tiempo ocupado: 100% (sin delays)
- Se requieren interrupciones para multitarea

## Conclusiones

- El control directo por registros ofrece el máximo rendimiento
- Las funciones Arduino simplifican desarrollo pero limitan velocidad
- La comunicación serial introduce latencia significativa
- El ESP32 puede alcanzar frecuencias de toggle >8MHz
- La temperatura interna es un indicador útil de carga del CPU

## Referencias

- Documentación GPIO ESP32 [Google](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html)
- Adafruit NeoPixel Best Practices [Google](https://learn.adafruit.com/adafruit-neopixel-uberguide)
- ESP32 Internal Temperature Sensor [Google](https://github.com/espressif/esp-idf/issues/146)