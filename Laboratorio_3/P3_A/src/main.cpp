#include <WiFi.h>
#include <WebServer.h>
#include <Arduino.h>


// SSID & Password
const char* ssid = "Xiaomi_11T_Pro";  // Ingresa tu SSID
const char* password = "12345678"; // Ingresa tu contraseña


WebServer server(80); // Objeto del servidor HTTP


// Declaración anticipada de la función handle_root
void handle_root();


void setup() {
    Serial.begin(115200);
    Serial.println("Intentando conectar a:");
    Serial.println(ssid);


    WiFi.begin(ssid, password);
   
    int intentos = 0;
    while (WiFi.status() != WL_CONNECTED && intentos < 20) {
        delay(1000);
        Serial.print(".");
        intentos++;
    }


    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi conectado exitosamente");
        Serial.print("IP asignada: ");
        Serial.println(WiFi.localIP()); // Muestra la IP asignada al ESP32-S3
    } else {
        Serial.println("\nError: No se pudo conectar al WiFi");
    }


    server.on("/", handle_root);
    server.begin();
    Serial.println("Servidor HTTP iniciado");
}


void loop() {
    server.handleClient();
}


// Manejo de la ruta raíz "/"
void handle_root() {
  String HTML = R"rawliteral(
  <!DOCTYPE html>
  <html lang="ca">
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Lamine Yamal - Promesa del Futbol</title>
  </head>
  <body>
      <h1>Lamine Yamal - Promesa del Futbol</h1>
      <img src="Lamine_Yamal.jpg" alt="Lamine Yamal celebrant un gol" width="400" />
      <p>Lamine Yamal és considerat una de les majors promeses del futbol mundial. Amb només 16 anys, aquest talentós jugador ha captat l'atenció de milions d'aficionats pel seu estil de joc únic i la seva visió.</p>
      <hr />
      <h2>Informació Bàsica</h2>
      <ul>
          <li><strong>Nom complet:</strong> Lamine Yamal Nasraoui Ebana</li>
          <li><strong>Data de naixement:</strong> 13 de juliol de 2007</li>
          <li><strong>País:</strong> Espanya</li>
          <li><strong>Club:</strong> FC Barcelona</li>
          <li><strong>Posició:</strong> Extrem</li>
      </ul>
      <h2>Carrera Professional</h2>
      <p>Lamine Yamal ha debutat a les categories inferiors del FC Barcelona i ja ha tingut aparicions amb el primer equip. El seu talent natural, combinat amb el suport d'una gran acadèmia com La Masia, el fa un jugador excepcional.</p>
      <h3>Moments destacats</h3>
      <ul>
          <li><em>Debut amb el primer equip del FC Barcelona:</em> abril de 2023</li>
          <li><em>Primer gol a La Liga:</em> setembre de 2023</li>
          <li><em>Primera convocatòria amb la selecció espanyola absoluta:</em> octubre de 2023</li>
      </ul>
      <h2>Estadístiques</h2>
      <p><strong>Última temporada (2023/2024):</strong></p>
      <ul>
          <li>Gols: 10</li>
          <li>Assistències: 7</li>
          <li>Partits jugats: 30</li>
      </ul>
      <hr />
      <h2>Galeria d'imatges</h2>
      <p>Una selecció de moments destacats de Lamine Yamal:</p>
      <img src="lamine1.jpg" alt="Lamine Yamal celebrant un gol" width="300"/>
      <br />
      <img src="lamine2.jpg" alt="Lamine Yamal en acció durant un partit" width="300"/>
      <hr />
      <h2>Contacte</h2>
      <p>Per a més informació, podeu visitar:</p>
      <ul>
          <li><a href="https://www.fcbarcelona.com">Pàgina oficial del FC Barcelona</a></li>
          <li><a href="https://www.laliga.com">Pàgina oficial de La Liga</a></li>
      </ul>
      <hr />
      <p>Aquesta pàgina ha estat creada com a exemple d'HTML per a un projecte web.</p>
  </body>
  </html>
  )rawliteral";


  server.send(200, "text/html", HTML);
}

