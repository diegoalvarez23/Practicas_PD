# Informe de Práctica 7: Buses de Comunicación III (I2S)

Nombre: \[Tu nombre\] Fecha: \[Fecha de realización\] Asignatura: Sistemas Embebidos

## Objetivos

- Comprender el funcionamiento del bus I2S  
- Implementar comunicación I2S para reproducción de audio  
- Generar tonos de audio directamente desde el ESP32  
- Reproducir archivos de audio desde tarjeta SD  
- Configurar un sistema de audio completo con amplificador I2S

## Materiales y Herramientas

- Placa ESP32  
- Módulo amplificador MAX98357 I2S  
- Altavoz o auriculares (4-8Ω)  
- Tarjeta microSD y adaptador  
- Cableado  
- Entorno de desarrollo Arduino IDE  
- Bibliotecas: ESP8266Audio, driver/i2s.h

## Introducción Teórica

El bus I2S (Inter-IC Sound) es un estándar de comunicación serial para transmisión de audio digital que utiliza tres líneas:

- SCK/BCLK (Serial Clock/Bit Clock): Sincronización de bits  
- WS/LRCLK (Word Select/Left-Right Clock): Selección de canal (L/R)  
- SD/DIN (Serial Data/Data In): Datos de audio

## Características principales

- Especializado para audio digital  
- Soporte para 16-32 bits por muestra  
- Frecuencias de muestreo típicas: 8kHz a 96kHz  
- Configuraciones maestro/esclavo  
- Formato de datos MSB-first

## Ejercicio Práctico 1: Generación de Tono 440Hz

### Resultados y Análisis

Salida por puerto serie:

*Generant to de 440 Hz per I2S...*

### Funcionamiento:

1. Configura el periférico I2S del ESP32 como maestro  
2. Genera un tono sinusoidal de 440Hz (La4)  
3. Muestra de audio a 44.1kHz con resolución de 16 bits  
4. Utiliza DMA para transferencia eficiente de datos  
5. El búfer circular permite reproducción continua

### Conexión física (ESP32 \+ MAX98357):

ESP32     MAX98357 GPIO18  → BCLK GPIO15  → LRCLK GPIO21  → DIN GND     → GND 3.3V    → Vin

## Ejercicio Práctico 2: Reproducción desde Tarjeta SD

### Resultados y Análisis

Salida por puerto serie (ejemplo):

*Reproduciendo audio...* *info: Iniciando decodificador WAV* *info: Tasa de muestreo: 44100, canales: 2* *ID3: Título: Ejemplo* *Fin archivo: Reproducción completada*

### Funcionamiento:

1. Lee archivos WAV/MP3 desde tarjeta SD  
2. Soporta múltiples formatos de audio  
3. Proporciona feedback sobre el estado de reproducción  
4. Permite control de volumen digital

### Conexión física adicional:

ESP32/SD Module GPIO18  → SCK GPIO19  → MISO GPIO23  → MOSI GPIO5   → CS

### Configuración del Sistema Completo

Para un sistema de audio completo con ESP32:

#### Señal I2S:

1. Configurar pines BCLK, LRCLK y DIN  
2. Establecer frecuencia de muestreo (44.1kHz recomendado)  
3. Definir resolución (16/24/32 bits)

#### Amplificador MAX98357:

1. Conexión directa a salida I2S  
2. Configuración mono/estéreo mediante jumpers  
3. Ajuste de ganancia (3-15dB)

#### Almacenamiento:

1. Tarjeta SD formateada en FAT16/32  
2. Archivos de audio en formato WAV (PCM) o MP3  
3. Estructura de directorios simple

## Conclusiones

- El protocolo I2S es ideal para aplicaciones de audio digital  
- El ESP32 tiene capacidades avanzadas de procesamiento de audio  
- La combinación con amplificadores como el MAX98357 simplifica el diseño  
- Es posible implementar sistemas de audio completos con almacenamiento externo  
- La biblioteca ESP8266Audio proporciona funcionalidades avanzadas

## Referencias

- Documentación oficial I2S de ESP32 ([Google](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/i2s.html))  
- Biblioteca ESP8266Audio [Google](https://github.com/earlephilhower/ESP8266Audio)  
- Hoja de datos MAX98357 [Google](https://www.analog.com/media/en/technical-documentation/data-sheets/MAX98357.pdf)  
- Guía completa de audio con ESP32 [Google](https://www.luisllamas.es/esp32-audio-i2s/)

