#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600); // Start the serial communication with the baud rate of 9600
}

void loop() {
  // Create a StaticJsonDocument with a capacity of 4096 bytes
  StaticJsonDocument<4096> doc;

  // Set the values in the document
  doc["message"] = "Data fetched successfully";
  JsonArray gameData = doc.createNestedArray("gameData");

  JsonObject game1 = gameData.createNestedObject();
  game1["_id"] = "662370b448ed5025aa3fd82c";
  game1["game"] = "tableTennis";
  JsonObject gamedata1 = game1.createNestedObject("gamedata");
  JsonObject teamA1 = gamedata1.createNestedObject("teamA");
  teamA1["score"] = 4;
  teamA1["set"] = 1;
  JsonObject teamB1 = gamedata1.createNestedObject("teamB");
  teamB1["score"] = 2;
  teamB1["set"] = 0;
  game1["updatedAt"] = "2024-04-20T07:37:24.482Z";
  game1["__v"] = 0;

  // Add more games as needed...

  doc["dateTime"] = "2024-04-27T19:00:26.237Z";

  // Serialize JSON document to string
  String data;
  serializeJson(doc, data);

  // Send the data
  Serial.println(data);

  delay(3000); // Wait for a second
}