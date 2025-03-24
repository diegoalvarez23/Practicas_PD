#include <Arduino.h>

void anotherTask(void *parameter);

void setup() 
{ 
    Serial.begin(115200); 

    /* Creamos una nueva tarea */
    xTaskCreate(
        anotherTask,      /* Función de la tarea */
        "anotherTask",    /* Nombre de la tarea */
        10000,            /* Tamaño del stack */
        NULL,             /* Parámetro de la tarea */
        1,                /* Prioridad de la tarea */
        NULL              /* Manejador de la tarea */
    ); 
} 

/* loop() es invocado por loopTask de Arduino ESP32 */
void loop() 
{ 
    Serial.println("Esto es la tarea principal (ESP32 Task)"); 
    delay(1000); 
} 

/* Función de la tarea adicional */
void anotherTask(void *parameter) 
{ 
    for (;;) 
    { 
        Serial.println("Esto es otra tarea"); 
        vTaskDelay(pdMS_TO_TICKS(1000)); // Mejor práctica en FreeRTOS
    } 

    /* Eliminar la tarea (nunca se ejecutará porque es un bucle infinito) */
    vTaskDelete(NULL); 
}
