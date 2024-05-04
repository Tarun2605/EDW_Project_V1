#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <SoftwareSerial.h>

const char* ssid = "ESP8266_AP";     // SSID for the Access Point
const char* password = "password";   // Password for the Access Point

ESP8266WebServer server(80);
char* ipp="";
const char* apiUrl = "https://edw-tfub.onrender.com/"; // Change to your API endpoint

int redPin = D0;
int greenPin = D1;
int bluePin = D2;


void setColor(int redValue, int greenValue,  int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin,  greenValue);
  analogWrite(bluePin, blueValue);
}

void handleRoot() {
  String content = "<!DOCTYPE html>\n"
                   "<html>\n"
                   "<head>\n"
                   "  <title>ESP Wi-Fi Manager</title>\n"
                   "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
                   "  <link rel=\"icon\" href=\"data:,\">\n"
                   "  <link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.7.2/css/all.css\" integrity=\"sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr\" crossorigin=\"anonymous\">\n"
                   "  <style>\n"
                   "    html {\n"
                   "    font-family: Arial, Helvetica, sans-serif; \n"
                   "    display: inline-block; \n"
                   "    text-align: center;\n"
                   "  }\n"
                   "  \n"
                   "  h1 {\n"
                   "    font-size: 1.8rem; \n"
                   "    color: white;\n"
                   "  }\n"
                   "  \n"
                   "  p { \n"
                   "    font-size: 1.4rem;\n"
                   "  }\n"
                   "  \n"
                   "  .topnav { \n"
                   "    overflow: hidden; \n"
                   "    background-color: #0A1128;\n"
                   "  }\n"
                   "  \n"
                   "  body {  \n"
                   "    margin: 0;\n"
                   "  }\n"
                   "  \n"
                   "  .content { \n"
                   "    padding: 5%;\n"
                   "  }\n"
                   "  \n"
                   "  .card-grid { \n"
                   "    max-width: 800px; \n"
                   "    margin: 0 auto; \n"
                   "    display: grid; \n"
                   "    grid-gap: 2rem; \n"
                   "    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));\n"
                   "  }\n"
                   "  \n"
                   "  .card { \n"
                   "    background-color: white; \n"
                   "    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);\n"
                   "  }\n"
                   "  \n"
                   "  .card-title { \n"
                   "    font-size: 1.2rem;\n"
                   "    font-weight: bold;\n"
                   "    color: #034078\n"
                   "  }\n"
                   "  \n"
                   "  input[type=submit] {\n"
                   "    border: none;\n"
                   "    color: #FEFCFB;\n"
                   "    background-color: #034078;\n"
                   "    padding: 15px 15px;\n"
                   "    text-align: center;\n"
                   "    text-decoration: none;\n"
                   "    display: inline-block;\n"
                   "    font-size: 16px;\n"
                   "    width: 100px;\n"
                   "    margin-right: 10px;\n"
                   "    border-radius: 4px;\n"
                   "    transition-duration: 0.4s;\n"
                   "    }\n"
                   "  \n"
                   "  input[type=submit]:hover {\n"
                   "    background-color: #1282A2;\n"
                   "  }\n"
                   "  \n"
                   "  input[type=text], input[type=number], select {\n"
                   "    width: 50%;\n"
                   "    padding: 12px 20px;\n"
                   "    margin: 18px;\n"
                   "    display: inline-block;\n"
                   "    border: 1px solid #ccc;\n"
                   "    border-radius: 4px;\n"
                   "    box-sizing: border-box;\n"
                   "  }\n"
                   "  \n"
                   "  label {\n"
                   "    font-size: 1.2rem; \n"
                   "  }\n"
                   "  .value{\n"
                   "    font-size: 1.2rem;\n"
                   "    color: #1282A2;  \n"
                   "  }\n"
                   "  .state {\n"
                   "    font-size: 1.2rem;\n"
                   "    color: #1282A2;\n"
                   "  }\n"
                   "  button {\n"
                   "    border: none;\n"
                   "    color: #FEFCFB;\n"
                   "    padding: 15px 32px;\n"
                   "    text-align: center;\n"
                   "    font-size: 16px;\n"
                   "    width: 100px;\n"
                   "    border-radius: 4px;\n"
                   "    transition-duration: 0.4s;\n"
                   "  }\n"
                   "  .button-on {\n"
                   "    background-color: #034078;\n"
                   "  }\n"
                   "  .button-on:hover {\n"
                   "    background-color: #1282A2;\n"
                   "  }\n"
                   "  .button-off {\n"
                   "    background-color: #858585;\n"
                   "  }\n"
                   "  .button-off:hover {\n"
                   "    background-color: #252524;\n"
                   "  } \n"
                   "  </style>\n"
                   "</head>\n"
                   "<body>\n"
                   "  <div class=\"topnav\">\n"
                   "    <h1>ESP Wi-Fi Manager</h1>\n"
                   "  </div>\n"
                   "  <div class=\"content\">\n";

  if (WiFi.status() == WL_CONNECTED) {
    content += "<p class=\"state\">Connected to " + String(WiFi.SSID()) + "</p>\n";
  } else {
    content += "<p class=\"state\">Not connected to Wi-Fi</p>\n";
  }

  content += "<div class=\"card-grid\">\n"
             "    <div class=\"card\">\n"
             "        <form action=\"/connect\" method=\"POST\">\n"
             "          <p>\n"
             "            <label for=\"ssid\">SSID</label>\n"
             "            <select id=\"ssid\" name=\"ssid\">\n";

  int numNetworks = WiFi.scanNetworks();
  for (int i = 0; i < numNetworks; ++i) {
    String ssid = WiFi.SSID(i);
    bool isOpen = WiFi.encryptionType(i) == ENC_TYPE_NONE;
    if (isOpen) {
      content += "<option style=\"color:green;\" value=\"" + ssid + "\">" + ssid + "</option>\n";
    } else {
      content += "<option value=\"" + ssid + "\">" + ssid + "</option>\n";
    }
  }

  content += "            </select><br>\n"
             "            <label for=\"pass\">Password</label>\n"
             "            <input type=\"text\" id =\"pass\" name=\"pass\"><br>\n"
             "            <input type =\"submit\" value =\"Connect\">\n"
             "          </p>\n"
             "        </form>\n"
             "      </div>\n"
             "    </div>\n"
             "  </div>\n"
             "</body>\n"
             "</html>";

  server.send(200, "text/html", content);
}

void handleScorePage(){
  String content="<!DOCTYPE html>\n"
                "<html>\n"
                "    <head>\n"
                "      <style>\n"
                "        html {\n"
                "        font-family: Arial, Helvetica, sans-serif;\n"
                "        display: inline-block;\n"
                "        text-align: center;\n"
                "        }\n"
                "        h1 {\n"
                "            font-size: 1.8rem;\n"
                "            color: white;\n"
                "        }\n"
                "        .topnav {\n"
                "            overflow: hidden;\n"
                "            background-color: #0A1128;\n"
                "        }\n"
                "        body {\n"
                "            margin: 0;\n"
                "        }\n"
                "        .content {\n"
                "            padding: 50px;\n"
                "        }\n"
                "        .card-grid {\n"
                "            max-width: 800px;\n"
                "            margin: 0 auto;\n"
                "            display: grid;\n"
                "            grid-gap: 2rem;\n"
                "            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));\n"
                "        }\n"
                "        .card {\n"
                "            background-color: white;\n"
                "            box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);\n"
                "        }\n"
                "        .card-title {\n"
                "            font-size: 1.2rem;\n"
                "            font-weight: bold;\n"
                "            color: #034078;\n"
                "        }\n"
                "        .reading {\n"
                "            font-size: 1.2rem;\n"
                "            color: #1282A2;\n"
                "        }\n"
                "      </style>\n"
                "        <title>ESP IOT DASHBOARD</title>\n"
                "        <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
                "        <link rel=\"icon\" type=\"image/png\" href=\"favicon.png\">\n"
                "    </head>\n"
                "    <body>\n"
                "        <div class=\"topnav\">\n"
                "            <h1>SENSOR READINGS (WEBSOCKET)</h1>\n"
                "        </div>\n"
                "        <div class=\"content\">\n"
                "            <div class=\"card-grid\">\n"
                "                <div class=\"card\">\n"
                "                    <p class=\"card-title\"> Temperature</p>\n"
                "                    <p class=\"reading\"><span id=\"temperature\"></span> &deg;C</p>\n"
                "                </div>\n"
                "                <div class=\"card\">\n"
                "                    <p class=\"card-title\"> Humidity</p>\n"
                "                    <p class=\"reading\"><span id=\"humidity\"></span> &percnt;</p>\n"
                "                </div>\n"
                "                <div class=\"card\">\n"
                "                    <p class=\"card-title\"> Pressure</p>\n"
                "                    <p class=\"reading\"><span id=\"pressure\"></span> hpa</p>\n"
                "                </div>\n"
                "            </div>\n"
                "        </div>\n"
                "        <script>\n"
                "          \n"
                "var gateway = `ws://${window.location.hostname}/ws`;\n"
                "var websocket;\n"
                "// Init web socket when the page loads\n"
                "window.addEventListener('load', onload);\n"
                "\n"
                "function onload(event) {\n"
                "    initWebSocket();\n"
                "}\n"
                "\n"
                "function getReadings(){\n"
                "    websocket.send(\"getReadings\");\n"
                "}\n"
                "\n"
                "function initWebSocket() {\n"
                "    console.log('Trying to open a WebSocket connection…');\n"
                "    websocket = new WebSocket(gateway);\n"
                "    websocket.onopen = onOpen;\n"
                "    websocket.onclose = onClose;\n"
                "    websocket.onmessage = onMessage;\n"
                "}\n"
                "\n"
                "// When websocket is established, call the getReadings() function\n"
                "function onOpen(event) {\n"
                "    console.log('Connection opened');\n"
                "    getReadings();\n"
                "}\n"
                "\n"
                "function onClose(event) {\n"
                "    console.log('Connection closed');\n"
                "    setTimeout(initWebSocket, 2000);\n"
                "}\n"
                "\n"
                "// Function that receives the message from the ESP32 with the readings\n"
                "function onMessage(event) {\n"
                "    console.log(event.data);\n"
                "    var myObj = JSON.parse(event.data);\n"
                "    var keys = Object.keys(myObj);\n"
                "\n"
                "    for (var i = 0; i < keys.length; i++){\n"
                "        var key = keys[i];\n"
                "        document.getElementById(key).innerHTML = myObj[key];\n"
                "    }\n"
                "}\n"
                "        </script>\n"
                "    </body>\n"
                "</html>";

  
  server.send(200,"text/html",content);
}

void handleConnect() {
  String ssid = server.arg("ssid");
  String pass = server.arg("pass");

  // Connect to WiFi
  WiFi.begin(ssid.c_str(), pass.c_str());

  // Wait for connection
  setColor(0, 0, 255);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Serial.println("Connected to WiFi");
  // Serial.print("IP Address: ");
  if (callAPI("https://edw-tfub.onrender.com/config/bootUp")) {
    // Serial.println(url);
    String url="https://edw-tfub.onrender.com/config/getAllData";
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

    // Ignore SSL certificate validation
    client->setInsecure();

    // Create an HTTPClient instance
    HTTPClient https;

    // Initializing an HTTPS communication using the secure client
    // Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, url)) {  // HTTPS
      // Serial.print("[HTTPS] GET...\n");
      // Start connection and send HTTP header
      int httpCode = https.GET();
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been sent and Server response header has been handled
        // Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
        // File found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          Serial.println(payload);
          https.end();
          // return true; // API call successful
        }
      } else {
        Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }
    setColor(0,0,0);
    // delay(500);
    setColor(0, 255, 0); // Green Color
  }
 IPAddress ip = WiFi.localIP();
  String ipAddress = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
  ipp = (char*) ipAddress.c_str();
  // Serial.println(ipAddress);

  // Redirect to a different page after connecting
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}
SoftwareSerial nodemcu(D3, D4);
bool callAPI(String url) {
  // Serial.println(url);
  std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

  // Ignore SSL certificate validation
  client->setInsecure();

  // Create an HTTPClient instance
  HTTPClient https;

  // Initializing an HTTPS communication using the secure client
  // Serial.print("[HTTPS] begin...\n");
  if (https.begin(*client, url)) {  // HTTPS
    // Serial.print("[HTTPS] GET...\n");
    // Start connection and send HTTP header
    int httpCode = https.GET();
    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been sent and Server response header has been handled
      // Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      // File found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String payload = https.getString();
        Serial.println(payload);
        https.end();
        return true; // API call successful
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n");
  }

  return false; // API call failed
}
void setup() {
  Serial.begin(9600);
  nodemcu.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  // Set ESP8266 as an access point
  IPAddress apIP(192, 168, 4, 1);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  // setColor(255,0,0);
  setColor(0,0,255);
  // Start the server
  server.on("/", handleRoot);
  server.on("/score", handleScorePage);
  server.on("/connect", handleConnect);
  server.begin();
  Serial.println("HTTP server started");
}


unsigned long lastAPICallTime = 0;
const unsigned long apiCallInterval = 10000; // 10 seconds interval

void loop() {
  // nodemcu.println("hiiiiiiiiiiiiii");
  server.handleClient();

  

  
    String receivedData = Serial.readStringUntil('\r'); // Read the data until newline character
    // Serial.println(receivedData);
    if (receivedData.equals("TableTennisTeamAInc")) {
      Serial.println("TableTennisTeamAIncFromNode");
      setColor(255,0,100);
      delay(500);
      if(callAPI("https://edw-tfub.onrender.com/game/tableTennis/teamA/inc")){
        setColor(0,255,0);
      }
    }
    if (receivedData.equals("TableTennisTeamBInc")) {
      Serial.println("TableTennisTeamBIncFromNode");
      setColor(255,0,100);
      delay(500);
      if(callAPI("https://edw-tfub.onrender.com/game/tableTennis/teamB/inc")){
        setColor(0,255,0);
      }
    }
    if (receivedData.equals("BadmintonTeamAInc")) {
      Serial.println("TableTennisTeamBIncFromNode");
      setColor(255,0,100);
      delay(500);
      if(callAPI("https://edw-tfub.onrender.com/game/badminton/teamA/inc")){
        setColor(0,255,0);
      }
    }
    if (receivedData.equals("BadmintonTeamBInc")) {
      Serial.println("TableTennisTeamBInc");
      callAPI("https://edw-tfub.onrender.com/game/badminton/teamB/inc");
    }
    if (receivedData.equals("HockeyChangeQuarter")) {
      // Serial.println("TableTennisTeamAInc");
      Serial.println("Changing quarter");
      setColor(255,0,100);
      if(callAPI("https://edw-tfub.onrender.com/game/hockey/changeQuarter")){
        setColor(0,255,0);
      }
    }
    if (receivedData.equals("ResetAllData")) {
      // Serial.println("TableTennisTeamAInc");
      Serial.println("Reset Data");
      setColor(255,0,100);
      if(callAPI("https://edw-tfub.onrender.com/config/resetAllData")){
        Serial.println("Done resetting");
        setColor(0,255,0);
      }
    }
    if (receivedData.equals("HockeyTeamAInc")) {
      // Serial.println("TableTennisTeamAInc");
      setColor(255,0,100);
      if(callAPI("https://edw-tfub.onrender.com/game/hockey/teamA/inc")){
        setColor(0,255,0);
      }
    }
    if (receivedData.equals("HockeyTeamBInc")) {
      // Serial.println("TableTennisTeamAInc");
      setColor(255,0,100);
      if(callAPI("https://edw-tfub.onrender.com/game/hockey/teamB/inc")){
        setColor(0,255,0);
      }
    }
    if (receivedData.equals("HockeyTimePause")) {
      // Serial.println("TableTennisTeamAInc");
      setColor(255,0,100);
      if(callAPI("https://edw-tfub.onrender.com/game/hockey/time/pause")){
        setColor(0,255,0);
      }
    }
    if (receivedData.equals("HockeyTimeResume")) {
      // Serial.println("TableTennisTeamAInc");
      setColor(255,0,100);
      if(callAPI("https://edw-tfub.onrender.com/game/hockey/time/resume")){
        setColor(0,255,0);
      }
    }
}


// Function to send data back to Arduino
void sendToArduino(String data) {
  Serial.println(data); // Send data over serial communication to Arduino
}