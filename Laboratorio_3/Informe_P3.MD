# Informe de Práctica 3: WiFi y Bluetooth

Nombre: Diego Alvarez i Pere Villaronga
Fecha: 3-03-2025
Asignatura: Processadors Digitals

## Objetivos

- Implementar un servidor web en modo STA (Station) con ESP32
- Establecer comunicación Bluetooth Classic con dispositivo móvil
- Configurar un servidor BLE (Bluetooth Low Energy)
- Comparar diferentes tecnologías de comunicación inalámbrica

## Materiales y Herramientas

- Placa ESP32-S3
- Dispositivo móvil con Bluetooth
- Router WiFi
- Cable USB para programación
- Entorno de desarrollo Arduino IDE
- Bibliotecas: WiFi, WebServer, BluetoothSerial, BLEDevice

## Parte A: Servidor Web en modo STA

### Resultados y Análisis
Salida por puerto serie:

*Intentando conectar a: Xiaomi_11T_Pro*
*....*
*WiFi conectado exitosamente*
*IP asignada: 192.168.1.35*
*Servidor HTTP iniciado*

### Funcionamiento:

- El ESP32 se conecta a la red WiFi como cliente (STA)
- Crea un servidor web en el puerto 80
- Responde a peticiones HTTP con una página HTML
- La página muestra información sobre el futbolista Lamine Yamal

### Pruebas:

1. Acceso desde navegador web a la IP mostrada
2. Visualización correcta del contenido HTML
3. Tiempo de respuesta < 200ms

## Parte B: Bluetooth Classic

### Resultados y Análisis
Salida por puerto serie:

*Dispositivo Bluetooth iniciado*
*[Cuando se conecta] Device connected*
*[Cuando se envían datos] Received: Hola*

### Funcionamiento:

- Crea un dispositivo Bluetooth llamado "ESP32test"
- Establece comunicación serie bidireccional
- Usa la app "Serial Bluetooth Terminal" para pruebas
- Latencia medida: 50-100ms

### Pruebas:

1. Emparejamiento exitoso con dispositivo móvil
2. Envío/recepción de texto correctamente
3. Distancia máxima efectiva: ~10m

## Comparativa de Tecnologías

**Característica    WiFi (STA)	    Bluetooth Classic       BLE**
Consumo energético	Alto	        Medio	                Muy bajo
Ancho de banda	    Alto	        Medio	                Bajo
Alcance	            ~50m	        ~10m	                ~30m
Latencia	        Baja	        Media	                Media
Configuración	    Compleja	    Simple	                Simple
Casos de uso	    Web/IoT	        Audio/Serial	        Sensores

## Conclusiones

- WiFi es ideal para aplicaciones que requieran alto ancho de banda
- Bluetooth Classic funciona bien para comunicación serie simple
- BLE es perfecto para dispositivos con batería y transmisión ocasional
- El ESP32 permite implementar las tres tecnologías simultáneamente
- Cada protocolo tiene ventajas específicas según el caso de uso

## Referencias

Documentación oficial WiFi de ESP32 [Google](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/network/esp_wifi.html)
Guía BLE con ESP32 [Google](https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/)
Ejemplos BluetoothSerial [Google](https://github.com/espressif/arduino-esp32/tree/master/libraries/BluetoothSerial/examples)

