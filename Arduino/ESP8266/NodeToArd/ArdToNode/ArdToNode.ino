#include <ArduinoJson.h>

void setup() {
  Serial.begin(9600); // Start the serial communication with the baud rate of 9600 for debugging
  Serial1.begin(9600); // Start the serial communication with the baud rate of 9600 for NodeMCU
}

void loop() {
  if (Serial1.available()) { // If data is available to read from NodeMCU,
    String data = Serial1.readString(); // read it and store it in 'data'
  
    // Create a StaticJsonDocument with a capacity of 4096 bytes
    StaticJsonDocument<4096> doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, data);

    // Test if parsing succeeds.
    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    // Get the values from the JSON document
    const char* message = doc["message"]; // "Data fetched successfully"
    JsonArray gameData = doc["gameData"];

    for(JsonVariant v : gameData) {
      const char* _id = v["_id"]; // "662370b448ed5025aa3fd82c"
      const char* game = v["game"]; // "tableTennis"
      JsonObject gamedata = v["gamedata"];
      JsonObject teamA = gamedata["teamA"];
      int scoreA = teamA["score"]; // 4
      int setA = teamA["set"]; // 1
      JsonObject teamB = gamedata["teamB"];
      int scoreB = teamB["score"]; // 2
      int setB = teamB["set"]; // 0
      const char* updatedAt = v["updatedAt"]; // "2024-04-20T07:37:24.482Z"
      int __v = v["__v"]; // 0

      // Print the values
      Serial.println(message);
      Serial.println(_id);
      Serial.println(game);
      Serial.println(scoreA);
      Serial.println(setA);
      Serial.println(scoreB);
      Serial.println(setB);
      Serial.println(updatedAt);
      Serial.println(__v);
    }

    const char* dateTime = doc["dateTime"]; // "2024-04-27T19:00:26.237Z"
    Serial.println(dateTime);
  }
}