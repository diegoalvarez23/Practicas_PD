# **Informe de Práctica 8: Buses de Comunicación IV (UART)**

Nombre: Diego Alvarez i Pere Villaronga

Asignatura: Processadors Digitals

## **Objetivos**

* Comprender el funcionamiento de la comunicación serie asíncrona mediante UART.

* Implementar un bucle de comunicación usando los puertos UART0 y UART2 del ESP32.

* Observar el eco de datos enviados a través de UART2 redirigidos al terminal serie.

## **Materiales y Herramientas**

* Placa de desarrollo ESP32

* Entorno de desarrollo Arduino IDE

* Monitor serie

* Conexión USB

## **Introducción Teórica**

UART (Universal Asynchronous Receiver-Transmitter) es un protocolo de comunicación serie **asíncrono**. A diferencia de protocolos síncronos como SPI o I2C, UART no utiliza señal de reloj compartida, por lo que ambos dispositivos deben estar configurados con los mismos parámetros de baudios, paridad, bits de parada y tamaño de datos.

ESP32 dispone de tres interfaces UART (UART0, UART1 y UART2), cuyos pines pueden reasignarse libremente. Para esta práctica, se empleó UART0 para comunicación con el PC y UART2 para redirigir y recibir datos.

   

## **Funcionamiento**

1. El usuario escribe un mensaje en el monitor serie (UART0).

2. Al presionar Enter (`\n`), el mensaje completo se envía a través de UART2.

3. UART2 debe estar conectado físicamente en bucle (TXD2 conectado a RXD2).

4. Lo recibido por UART2 se muestra de nuevo en el monitor con el prefijo `[ECO]`.

## **Resultados y Análisis**

**Entradas y salidas del monitor serie:**

Esto demuestra que la comunicación por UART2 está funcionando correctamente y que los datos se redirigen y retornan en eco, como se esperaba.

## **Conclusiones**

* La comunicación UART asíncrona permite una transmisión y recepción eficiente sin necesidad de señal de reloj externa.

* Es fundamental configurar ambos extremos con los mismos parámetros para evitar errores.

* Este ejercicio práctico demostró cómo trabajar con múltiples UART en ESP32 y cómo monitorear la comunicación en tiempo real.

