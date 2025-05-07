# Informe de Práctica 4: Sistemas Operativos en Tiempo Real

Nombre: Diego Alvarez i Pere Villaronga
Fecha: 10-03-2025
Asignatura: Processadors Digitals

## Objetivos:

- Comprender el funcionamiento de un sistema operativo en tiempo real
- Implementar multitarea en ESP32 utilizando FreeRTOS
- Crear y gestionar tareas concurrentes
- Sincronizar tareas mediante semáforos

## Materiales y Herramientas

- Placa ESP32
- Entorno de desarrollo Arduino IDE
- LED
- Cableado necesario
- Biblioteca FreeRTOS

## Introducción Teórica

FreeRTOS es un sistema operativo en tiempo real que permite la ejecución de múltiples tareas en microcontroladores. En el ESP32, que tiene dos núcleos, FreeRTOS permite asignar tareas a núcleos específicos y gestionar su prioridad. Los semáforos son mecanismos de sincronización que permiten coordinar la ejecución de tareas y el acceso a recursos compartidos.


### Ejercicio Práctico 1: Tareas Concurrentes

Explicación del funcionamiento del código:

1. Se crean dos tareas: la principal (loop) y "anotherTask"
2. Ambas tareas tienen la misma prioridad (1)
3. FreeRTOS alterna la ejecución entre ambas tareas cada segundo
4. vTaskDelay permite que el planificador ejecute otras tareas durante el tiempo de espera
5. El uso de pdMS_TO_TICKS es la forma recomendada de especificar retardos en FreeRTOS


### Ejercicio Práctico 2: Sincronización con Semáforos-

_Resultados y Análisis_
Comportamiento observado:

- El LED se enciende y muestra "LED ENCENDIDO"
- Después de 1 segundo, aparece "ESPERANDO..."
- Tras 0.5 segundos, el LED se apaga y muestra "LED APAGADO"
- Después de 1 segundo apagado, el ciclo se repite

Explicación del funcionamiento:

Se crean tres semáforos binarios para sincronizar las tareas
Cada tarea espera su semáforo correspondiente (xSemaphoreTake)
Al completar su acción, cada tarea libera el semáforo para la siguiente (xSemaphoreGive)

La secuencia queda así:

turnOnLED → waitTask → turnOffLED → turnOnLED...

**Todas las tareas tienen igual prioridad, pero los semáforos aseguran el orden de ejecución**

## Conclusiones

FreeRTOS permite implementar multitarea efectiva en el ESP32
Los semáforos son mecanismos eficaces para sincronizar tareas
El uso de vTaskDelay es preferible a delay en entornos RTOS
La prioridad de tareas permite gestionar la importancia relativa de cada proceso
La práctica demostró cómo coordinar acciones secuenciales mediante semáforos

## Referencias

    Documentación oficial de FreeRTOS [Google](https://www.freertos.org/)
    Repositorio ESP32 FreeRTOS [Google](https://github.com/uagaviria/ESP32_FreeRtos)
    Tutorial de semáforos en FreeRTOS [Google](https://circuitdigest.com/microcontroller-projects/arduino-freertos-tutorial-using-semaphore-and-mutex-in-freertos-with-arduino)
    Ejemplos de semáforos contadores [Google](https://techtutorialsx.com/2017/05/11/esp32-freertos-counting-semaphores/)