#include <Arduino.h>
#include "driver/gpio.h"


#define LED_PIN 48  // Canvia al pin correcte si cal
#define DELAY_TIME 500 // Temps en mil·lisegons


void setup() {
    Serial.begin(115200);
    gpio_pad_select_gpio((gpio_num_t)LED_PIN); // Configura el pin com a GPIO
    gpio_set_direction((gpio_num_t)LED_PIN, GPIO_MODE_OUTPUT); // Configura com a sortida
    Serial.println("ESP32-S3 iniciat, LED parpellejant...");
}


void loop() {
    uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG; // Punter al registre de sortida
    *gpio_out |= (1 << LED_PIN); // Encén el LED
    Serial.println("LED ENCÈS!");
    delay(DELAY_TIME);


    *gpio_out &= ~(1 << LED_PIN); // Apaga el LED
    Serial.println("LED APAGAT!");
    delay(DELAY_TIME);
}
