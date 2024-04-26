#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncWebSocket.h> // Include the AsyncWebSocket header file

const char* ssid = "ESP8266_AP";     // SSID for the Access Point
const char* password = "password";   // Password for the Access Point

AsyncWebServer server(80);
AsyncWebSocket webSocket("/ws");

float temperature = 0.0;
float humidity = 0.0;
float pressure = 0.0;

void handleWebSocketMessage(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {}

void updateSensorValues() {
  // Update sensor values here
  temperature += 0.1;
  humidity += 0.5;
  pressure += 1.0;
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>ESP IOT DASHBOARD</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    html {
      font-family: Arial, Helvetica, sans-serif;
      display: inline-block;
      text-align: center;
    }
    h1 {
      font-size: 1.8rem;
      color: white;
    }
    .topnav {
      overflow: hidden;
      background-color: #0A1128;
    }
    body {
      margin: 0;
    }
    .content {
      padding: 50px;
    }
    .card-grid {
      max-width: 800px;
      margin: 0 auto;
      display: grid;
      grid-gap: 2rem;
      grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
    }
    .card {
      background-color: white;
      box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    }
    .card-title {
      font-size: 1.2rem;
      font-weight: bold;
      color: #034078;
    }
    .reading {
      font-size: 1.2rem;
      color: #1282A2;
    }
  </style>
</head>
<body>
  <div class="topnav">
    <h1>SENSOR READINGS (WEBSOCKET)</h1>
  </div>
  <div class="content">
    <div class="card-grid">
      <div class="card">
        <p class="card-title">Temperature</p>
        <p class="reading"><span id="temperature"></span> &deg;C</p>
      </div>
      <div class="card">
        <p class="card-title">Humidity</p>
        <p class="reading"><span id="humidity"></span> &percnt;</p>
      </div>
      <div class="card">
        <p class="card-title">Pressure</p>
        <p class="reading"><span id="pressure"></span> hPa</p>
      </div>
    </div>
    <div class="console-cont">
      <div class="console">
        <p>Console:</p>
        <div id="console"></div>
      </div>
    </div>
  </div>
  <script>
    var gateway = `ws://${window.location.hostname}/ws`;
    var websocket;

    window.addEventListener('load', onload);

    function onload(event) {
      initWebSocket();
    }

    function getReadings() {
      websocket.send("getReadings");
    }

    function logToConsole(message) {
      const consoleElement = document.getElementById('console');
      const p = document.createElement('p');
      p.textContent = message;
      consoleElement.appendChild(p);
    }

    function initWebSocket() {
      try {
        logToConsole('Connecting to ' + gateway);
        websocket = new WebSocket(gateway);
        websocket.onopen = onOpen;
        websocket.onclose = onClose;
        websocket.onmessage = onMessage;
      } catch (error) {
        console.error(error);
        logToConsole('Websocket error: ' + error);
      }
    }

    function onOpen(event) {
      logToConsole('Connection opened');
      getReadings();
    }

    function onClose(event) {
      console.log('Connection closed');
      setTimeout(initWebSocket, 2000);
    }

    function onMessage(event) {
      console.log(event.data);
      var myObj = JSON.parse(event.data);
      var keys = Object.keys(myObj);

      for (var i = 0; i < keys.length; i++) {
        var key = keys[i];
        document.getElementById(key).innerHTML = myObj[key];
      }
    }
  </script>
</body>
</html>
)rawliteral";

void handleRoot(AsyncWebServerRequest *request) {
  request->send_P(200, "text/html", index_html);
}

void setup() {
  Serial.begin(115200);
  delay(10);

  // Set ESP8266 as an access point
  WiFi.softAPConfig(IPAddress(192, 168, 4, 1), IPAddress(192, 168, 4, 1), IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Route for root / web page
  server.on("/", HTTP_GET, handleRoot);

  // Route for WebSocket
  webSocket.onEvent(handleWebSocketMessage);

  // Start server
  server.begin();
  Serial.println("HTTP server started");

  // Setup sensor values
  temperature = 20.0;
  humidity = 50.0;
  pressure = 1013.25;
}

void loop() {
  delay(1000); // Adjust delay according to your requirements

  // Update sensor values
  updateSensorValues();

  // Broadcast sensor values over WebSocket
  String sensorData = "{\"temperature\": " + String(temperature, 2) + ", \"humidity\": " + String(humidity, 2) + ", \"pressure\": " + String(pressure, 2) + "}";
  webSocket.textAll(sensorData);

  // Handle WebSocket events
  webSocket.cleanupClients();
}
