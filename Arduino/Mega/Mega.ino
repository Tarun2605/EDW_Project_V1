#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <Keypad.h>
#include <ArduinoJson.h>


#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4


MCUFRIEND_kbv tft;


const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {23, 25, 27, 29}; // Rows 1 to 4 connected to R1, R2, R3, R4 pins
byte colPins[COLS] = {31,33,35,37}; // Columns 1 to 4 connected to C1, C2, C3, C4 pins


/* byte rowPins[ROWS] = {22,24,26,28}; // Rows 1 to 4 connected to R1, R2, R3, R4 pins
byte colPins[COLS] = {30,32,34,36}; // Columns 1 to 4 connected to C1, C2, C3, C4 pins */


Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


int selectedGame = 0;
bool inGameScreen = false;
bool tableTennisActive = false;
bool HockeyActive = false;
bool BadmintonActive = false;
bool AddGameActive = false;


int tabletennisTeamA = 0;  // Score for Team A in Tennis
int tabletennisTeamB = 0;  // Score for Team B in Tennis
int HockeyTeamA = 0;   // Score for Team A in Tennis
int HockeyTeamB = 0;   // Score for Team B in Tennis
int BadmintonTeamA = 0;    // Score for Team A in Tennis
int BadmintonTeamB = 0;    // Score for Team B in Tennis


int setScoreA = 0;           // Set score for Team A
int setScoreB = 0;           // Set score for Team B
int BadmintonsetScoreA = 0;  // Set score for Team A
int BadmintonsetScoreB = 0;  // Set score for Team B


bool isPaused = true;
unsigned long previousMillis = 0;
unsigned long interval = 1000; // 1 second interval
int minutes = 0;
int seconds = 10;
int quarter = 1; // Hockey Quarter


bool lastpoint = true;  //true means player 1


bool player1Serving = true;  //Player 1 is serving


                  /*






                  ADD GAME Variables
       
       
       
                  */
enum GameType {
  TIMED,
  NON_TIMED,
};


GameType selectedGameType;


//For Timed Sports


int inputMinutes = 0;
int inputMinutesCopy = 0;
int inputSeconds = 0;


int inputNumIntervals=0;
int intervalno=1;


bool customisPaused = true;
unsigned long custompreviousMillis = 0;
unsigned long custominterval = 1000; // 1 second interval


//For non timed sports
int winningScore;
int numGames;
int numSets;


int customTeamA = 0;  
int customTeamB = 0;  
int customGameScoreA = 0;          
int customGameScoreB = 0;          
int customSetScoreA = 0;          
int customSetScoreB = 0;          


int choice=0;
bool gameAdded=false;


/////////////////////////////////////////////////////////////




const int NUM_GAMES = 4;


String games[NUM_GAMES] = { "Table Tennis", "Badminton", "Hockey", "ADD GAME" };


const uint16_t gameColors[NUM_GAMES] = { 0x7E0, 0xFF00, 0xF800, 0x001F };


void setData(String data) {
  if (data.startsWith("SetData")) {
    data = data.substring(7);
  }
  Serial.println(data);
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
    Serial.println(scoreA);
    int setA = teamA["set"]; // 1
    JsonObject teamB = gamedata["teamB"];
    int scoreB = teamB["score"]; // 2
    int setB = teamB["set"]; // 0
    const char* updatedAt = v["updatedAt"]; // "2024-04-20T07:37:24.482Z"
    int _v = v["_v"]; // 0


    // Update the global variables based on the game
    if (strcmp(game, "tableTennis") == 0) {
      tabletennisTeamA = scoreA;
      tabletennisTeamB = scoreB;
      setScoreA = setA;
      setScoreB = setB;
      Serial.println("Table tennis is set");
    } else if (strcmp(game, "hockey") == 0) {
      HockeyTeamA = scoreA;
      HockeyTeamB = scoreB;
      quarter=gamedata["quarter"];
      Serial.println("Hockey is set");
    } else if (strcmp(game, "badminton") == 0) {
      BadmintonTeamA = scoreA;
      BadmintonTeamB = scoreB;
      BadmintonsetScoreA = setA;
      BadmintonsetScoreB = setB;
      Serial.println("Badminton is set");
    }
  }


  // const char* dateTime = doc["dateTime"]; // "2024-04-27T19:00:26.237Z"
  // Serial.println(dateTime);
}




void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);


  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(0x0000);
  tft.setTextSize(2);


  if (!inGameScreen) {
    displayMenu();
  }
}


void loop() {
if (Serial1.available()){
    String data = Serial1.readString(); // read it and store it in 'data'
    if (data.startsWith("{")) {
        setData(data);
    }
  }


  char key = keypad.getKey();


  if (key != NO_KEY) {
    switch (key) {


      case 'A':
        // Handle navigation key 'A' press (up)
        if(!inGameScreen) {
          selectedGame--;
          if (selectedGame < 0) {
            selectedGame = NUM_GAMES - 1;
          }
        }
        if (inGameScreen) {
     //////////////
        } else {
          displayMenu();
        }
        break;


      case 'B':
        // Handle navigation key 'B' press (down)
        if(!inGameScreen) {
          selectedGame++;
          if (selectedGame >= NUM_GAMES) {
            selectedGame = 0;
          }
        }
       
        if (inGameScreen) {
         /////////////////
        } else {
          displayMenu();
        }
        break;


      case 'C':
        // Handle navigation key 'C' press (select)
        switch (selectedGame) {
          case 0:
            displayTennisScoreScreen();
            tableTennisActive = true;
            break;
          case 1:
            displayBadmintonScoreScreen();
            BadmintonActive = true;
            break;
          case 2:
            displayHockeyScoreScreen();
            HockeyActive = true;
            break;
          case 3:
            if(!gameAdded){
              displayAddGameMenu();
            }
            else{
              if(selectedGameType == TIMED){
                displayCustomScoreScreen_Timed();
              }
              else if(selectedGameType == NON_TIMED){
                displayCustomScoreScreen_NonTimed();
              }
            }
            AddGameActive=true;
            break;
          default:
            break;
        }
        break;
      case 'D':
        // Handle navigation key 'D' press (back)
        tft.setTextSize(2);
        inGameScreen = false;
        tableTennisActive = false;
        BadmintonActive = false;
        HockeyActive = false;
        AddGameActive =false;
        displayMenu();
        break;


      case '*':
        resetfinalTTScore();
        resetfinalBadmintonScore();
        resetfinalHockeyScore();
        resetfinalCustomScore_Timed();
        resetfinalCustomScore_NonTimed();
        switch (selectedGame) {
          case 0:
            displayTennisScoreScreen();
            tableTennisActive = true;
            break;
          case 1:
            displayBadmintonScoreScreen();
            BadmintonActive = true;
            break;
          case 2:
            displayHockeyScoreScreen();
            HockeyActive = true;
            break;
          case 3:
          if(gameAdded){
              if(selectedGameType == TIMED){
                displayCustomScoreScreen_Timed();
              }
              else if(selectedGameType == NON_TIMED){
                displayCustomScoreScreen_NonTimed();
              }
          }
              break;
          default:
              break;
        }
        break;
      default:
        // Handle other keys if needed
        break;
    }
  }


  if(HockeyActive){
    unsigned long currentMillis = millis();
    if (key=='#') {
         isPaused = !isPaused;
        Serial.println("Button pressed");
        Serial1.println("HockeyChangeQuarter");
      delay(50); // Debounce delay
      }
   


    if (!isPaused && currentMillis - previousMillis >= interval) {
      // Update timer every second
      previousMillis = currentMillis;


      if (seconds == 0) {
        if (minutes == 0) {
          // Timer reached 0
         
          quarter++;
          Serial.println("arduino is channging quarter");
          // Serial1.println("HockeyChangeQuarter");


          resetTimer();
          //displayHockeyScoreScreen();
          if(quarter>4){
            quarter=1;
          }
          return; // Exit loop
        } else {
          minutes--;
          seconds = 59;
        }
      } else {
        seconds--;
      }
      displayTimer();
    }
    if(isPaused){
      displayStaticTimer();
    }
  }


  if(AddGameActive && selectedGameType == TIMED){
    unsigned long currentMillis = millis();
    if (key=='#') {
        customisPaused = !customisPaused;
        Serial.println("Button pressed");
        delay(50); // Debounce delay
      }
   


    if (!customisPaused && currentMillis - custompreviousMillis >= custominterval) {
      // Update timer every second
      custompreviousMillis = currentMillis;


      if (inputSeconds == 0) {
        if (inputMinutes == 0) {
          // Timer reached 0
          intervalno++;
          resetCustomTimer();
          if(intervalno>inputNumIntervals){
            intervalno=1;
          }
          return; // Exit loop
        } else {
          inputMinutes--;
          inputSeconds = 59;
        }
      } else {
        inputSeconds--;
      }
      displayCustomTimer();
    }
    if(customisPaused){
      displayCustomStaticTimer();
    }
  }
 
  if (tableTennisActive) {
    // Increment score for Team A in Tennis
    if (key == 'A') {
      delay(50);  // Debounce delay
        tabletennisTeamA++;
        Serial1.println("TableTennisTeamAInc");
        updateTennisScore();
    }


    // Increment score for Team B in Tennis
    if (key == 'B') {
      delay(50);  // Debounce delay
        tabletennisTeamB++;
         Serial1.println("TableTennisTeamBInc");
        updateTennisScore();
    }
  }


  else if (BadmintonActive) {
    // Increment score for Team A in Tennis
    if (key == 'A') {
      delay(50);  // Debounce delay
        BadmintonTeamA++;
        Serial1.println("BadmintonTeamAInc");
        lastpoint=true;
        updateBadmintonScore();
    }


    // Increment score for Team B in Tennis
    if (key == 'B') {
      delay(50);  // Debounce delay
        BadmintonTeamB++;
        Serial1.println("BadmintonTeamBInc");
        lastpoint= false;
        updateBadmintonScore();
    }
  }
  else if (HockeyActive) {
    // Increment score for Team A in Hockey
    if (key == 'A') {
      delay(50);  // Debounce delay
      if (minutes + seconds>0 && !isPaused) {
        Serial1.println("HockeyTeamAInc");
        HockeyTeamA++;
        updateHockeyScore();
      }
    }


    // Increment score for Team B in Tennis
    if (key=='B') {
      delay(50);  // Debounce delay
      if (minutes + seconds>0 && !isPaused) {
        Serial1.println("HockeyTeamBInc");
        HockeyTeamB++;
        updateHockeyScore();
      }
    }
    if(minutes+seconds == 0){
      updateHockeyScore();
    }


  }
  else if(AddGameActive){
    if(!gameAdded){
      char key = keypad.getKey();


      if (key != NO_KEY) {
        addGameMenuHandler(key); // Handle key presses
      }  
    }
    else{
      if(selectedGameType == TIMED){
        if (key == 'A') {
          delay(50);  // Debounce delay
          if (inputMinutes + inputSeconds>0 && ! customisPaused) {
            customTeamA++;
            updateCustomScore_Timed();
          }
        }


        // Increment score for Team B in Tennis
        if (key=='B') {
          delay(50);  // Debounce delay
          if (inputMinutes + inputSeconds>0 && ! customisPaused) {
            customTeamB++;
            updateCustomScore_Timed();
          }
        }
        if(inputMinutes + inputSeconds == 0){
          updateCustomScore_Timed();
        }


      }
      else if(selectedGameType == NON_TIMED){
        if (key == 'A') {
          delay(50);  // Debounce delay
            customTeamA++;
            updateCustomScore_NonTimed();
        }


        // Increment score for Team B in Tennis
        if (key == 'B') {
          delay(50);  // Debounce delay
            customTeamB++;
            updateCustomScore_NonTimed();
        }


      }
    }
  }  
}


// Function to display the menu
void displayMenu() {
  tft.setTextSize(2);
  tft.fillScreen(0x0000);


  int menuWidth = 220;
  int menuHeight = NUM_GAMES * 30 + 20;
  int menuX = (tft.width() - menuWidth) / 2;
  int menuY = (tft.height() - menuHeight) / 2;


  int borderColor = 0xFFFF;
  tft.drawRect(menuX, menuY, menuWidth, menuHeight, borderColor);


  for (int i = 0; i < NUM_GAMES; i++) {
    if (selectedGame == i && !inGameScreen) {
      tft.setTextColor(gameColors[i]);
    } else {
      tft.setTextColor(0xFFFF);
    }
    tft.setCursor(menuX + 10, menuY + 10 + i * 30);
    tft.println(games[i]);
  }
}


        /*ADD GAME MENU FUNCTIONS*/


void displayAddGameMenu() {
  tft.setTextSize(2);
  tft.fillScreen(0x0000);


  int menuWidth = 280;
  int menuHeight = 200;
  int menuX = (tft.width() - menuWidth) / 2;
  int menuY = (tft.height() - menuHeight) / 2 ;


  int borderColor = 0xFFFF;
  tft.drawRect(menuX, menuY, menuWidth, menuHeight, borderColor);
  tft.setTextColor(0xFFFF);


  // Prompt for game type selection
  tft.setCursor(menuX+10,menuY+20);
  tft.println("Select game type:");
  tft.setCursor(menuX+10,menuY+40);
  tft.println("1. Timed");
  tft.setCursor(menuX+10,menuY+60);
  tft.println("2. Non-timed");
}




void displayTimedGameConfigMenu() {
  tft.fillScreen(0x0000); // Clear the screen


  tft.setTextColor(0xFFFF); // White text color
  tft.setTextSize(2);


  // Prompt for game duration
  tft.setCursor(10, 20);
  tft.println("Enter game duration(min) :");


  inputMinutes = getIntegerInput();
  inputMinutesCopy= inputMinutes;


  // Prompt for number of intervals (if applicable)
  tft.setCursor(10, 100);
  tft.println("Enter number of intervals:");


  inputNumIntervals = getIntegerInput();


  displayConfirmationScreen();


  choice = getYesNoInput();


  if(choice==1){
    gameAdded=true;
    games[3]="Custom Game";
    displayMenu();
  }
  else if(choice == 2){
    tft.fillScreen(0x0000);
    tft.print("Tu likhega iska code?");
  }
 
}


void displayNonTimedGameConfigMenu() {
 
  tft.fillScreen(0x0000); // Clear the screen


  tft.setTextColor(0xFFFF); // White text color
  tft.setTextSize(2);


  // Prompt for game duration
  tft.setCursor(10, 20);
  tft.println("Enter number of points in a Game: ");


  winningScore = getIntegerInput();


  // Prompt for number of intervals (if applicable)
  tft.setCursor(10, 100);
  tft.println("Enter the number of Games in a Set: ");
 
  numGames = getIntegerInput();


  tft.setCursor(10, 180);
  tft.println("Sets required to win: ");
 
  numSets = getIntegerInput();
 
  displayConfirmationScreen();


  choice = getYesNoInput();


  if(choice==1){
    gameAdded =true;
    games[3]="Custom Game";
    displayMenu();
  }
  else if(choice == 2){
    tft.fillScreen(0x0000);
    tft.print("Tu likhega iska code?");
  }
}


int getIntegerInput() {
  String input = "";
  char key;
  do {
    key = keypad.getKey();
    if (key >= '0' && key <= '9') {
      input += key;
      tft.print(key);
    }
  } while (key != '#'); // Assume # key signifies end of input


  return input.toInt();
}


int getYesNoInput() {
  String input = "";
  char key;
  do {
    key = keypad.getKey();
    if (key == '1' || key == '2') {
      input += key;
      tft.print(key);
    }
  } while (key != '#'); // Assume # key signifies end of input


  return input.toInt();
}




void addGameMenuHandler(char key) {
  switch (key) {
    case '1':
      selectedGameType = TIMED;
      displayTimedGameConfigMenu();
      break;
    case '2':
      selectedGameType = NON_TIMED;
      displayNonTimedGameConfigMenu();
      break;
    case 'A':
      // Return to main menu or perform other actions
      break;
    case 'B':
      // Cancel operation or return to main menu
      break;
    default:
      // Handle other keys if needed
      break;
  }
}


void displayConfirmationScreen(){


  tft.fillScreen(0x0000);
  tft.setTextColor(0xFFFF);
  tft.setTextSize(2);
  tft.setCursor(10,20);


  tft.println("Please Confirm Game Details(Yes(1) / No(2)) : ");


  if(selectedGameType == TIMED){
    tft.setCursor(10,60);
    tft.print("Game Type: TIMED");
       
    tft.setCursor(10,100);
    tft.print("Duration: ");
    tft.print(inputMinutes);
   
    tft.setCursor(10,140);
    tft.print("Intervals: ");
    tft.print(inputNumIntervals);
   
  }
  else{
    tft.setCursor(10,60);
    tft.print("Game Type: NON_TIMED");
   
    tft.setCursor(10,100);
    tft.print("Winning Points: ");
    tft.print(winningScore);
   
    tft.setCursor(10,140);
    tft.print("Games: ");
    tft.print(numGames);


    tft.setCursor(10,180);
    tft.print("Sets: ");
    tft.print(numSets);


  }


}


//Scoring Functions


// Function to display the tennis score screen
void displayTennisScoreScreen() {
  int screenWidth = tft.width();
  int screenHeight = tft.height();


  int teamAWidth = screenWidth / 2;
  int teamAX = 0;
  int teamAY = 20;
  int teamAHeight = screenHeight - teamAY;


  int teamBWidth = screenWidth / 2;
  int teamBX = screenWidth / 2;
  int teamBY = 20;
  int teamBHeight = screenHeight - teamBY;
  inGameScreen = true;
  uint16_t teamAColor = 0xFFFF;  // White
  uint16_t teamBColor = 0xFFFF;  // White
  if (player1Serving) {
    teamAColor = 0x00FF;
  } else {
    teamBColor = 0x00FF;
  }
  uint16_t backgroundColor = 0x0000;  // Black
  uint16_t borderColor = 0x0000;      // Black


  tft.fillRect(0, 0, screenWidth, screenHeight, backgroundColor);


  tft.fillRect(teamAX, teamAY, teamAWidth, teamAHeight, teamAColor);
  tft.setTextColor(0x0000);  // Black
  tft.setTextSize(3);
  tft.setCursor(teamAX + 10, teamAY + 20);
  tft.println("Team A");
  tft.setTextSize(2);
  tft.setCursor(teamAX + 10, teamAY + 60);
  tft.println("Score: " + String(tabletennisTeamA));
  tft.setCursor(teamAX + 10, teamAY + 120);
  tft.println("Set: " + String(setScoreA));


  tft.fillRect(teamBX, teamBY, teamBWidth, teamBHeight, teamBColor);
  tft.setTextColor(0x0000);  // Black
  tft.setTextSize(3);
  tft.setCursor(teamBX + 10, teamBY + 20);
  tft.println("Team B");
  tft.setTextSize(2);
  tft.setCursor(teamBX + 10, teamBY + 60);
  tft.println("Score: " + String(tabletennisTeamB));
  tft.setCursor(teamBX + 10, teamBY + 120);
  tft.println("Set: " + String(setScoreB));


  tft.fillRect(screenWidth / 2 - 2, 0, 4, screenHeight, borderColor);
}


void updateTennisScore() {
  int screenWidth = tft.width();
  int screenHeight = tft.height();
  if (tabletennisTeamA
        >= 11
      && tabletennisTeamA
             - tabletennisTeamB
           >= 2) {
    setScoreA++;
    resetTennisScore();
  } else if (tabletennisTeamB >= 11 && tabletennisTeamB - tabletennisTeamA >= 2) {
    setScoreB++;
    resetTennisScore();
  } else {


    if ((tabletennisTeamA
         + tabletennisTeamB)
        < 20) {
      if ((tabletennisTeamA
           + tabletennisTeamB)
              % 2
            == 0
          && (tabletennisTeamA
              + tabletennisTeamB)
               != 0) {
        player1Serving = !player1Serving;
      }
    } else {
      player1Serving = !player1Serving;
    }
  }
  if (setScoreA == 2) {


    tft.fillRect(0, 0, screenWidth, screenHeight, 0x0000);
    tft.setTextColor(0x07E0);  // Green
    tft.setTextSize(3);
    tft.setCursor(50, 100);
    tft.println("Team A Wins!");
    tft.setTextSize(2);
    tft.setCursor(50, 140);
    tft.println("Game Over");
    delay(2000);
   resetfinalTTScore();
    // displayMenu();
  } else if (setScoreB == 2) {
    tft.fillRect(0, 0, screenWidth, screenHeight, 0x0000);
    tft.setTextColor(0x07E0);  // Green
    tft.setTextSize(3);
    tft.setCursor(50, 100);
    tft.println("Team B Wins!");
    tft.setTextSize(2);
    tft.setCursor(50, 140);
    tft.println("Game Over");
    delay(2000);
   resetfinalTTScore();
    // displayMenu();
  } else {
      displayTennisScoreScreen();
  }
}


// Function to display the badminton score screen
void displayBadmintonScoreScreen() {
  int screenWidth = tft.width();
  int screenHeight = tft.height();


  int teamAWidth = screenWidth / 2;
  int teamAX = 0;
  int teamAY = 20;
  int teamAHeight = screenHeight - teamAY;


  int teamBWidth = screenWidth / 2;
  int teamBX = screenWidth / 2;
  int teamBY = 20;
  int teamBHeight = screenHeight - teamBY;
  inGameScreen = true;
  uint16_t teamAColor = 0xFFFF;  // White
  uint16_t teamBColor = 0xFFFF;  // White
  if (player1Serving) {
    teamAColor = 0x00FF;
  } else {
    teamBColor = 0x00FF;
  }
  uint16_t backgroundColor = 0x0000;  // Black
  uint16_t borderColor = 0x0000;      // Black


  tft.fillRect(0, 0, screenWidth, screenHeight, backgroundColor);


  tft.fillRect(teamAX, teamAY, teamAWidth, teamAHeight, teamAColor);
  tft.setTextColor(0x0000);  // Black
  tft.setTextSize(3);
  tft.setCursor(teamAX + 10, teamAY + 20);
  tft.println("Team A");
  tft.setTextSize(2);
  tft.setCursor(teamAX + 10, teamAY + 60);
  tft.println("Score: " + String(BadmintonTeamA));
  tft.setCursor(teamAX + 10, teamAY + 120);
  tft.println("Set: " + String(BadmintonsetScoreA));


  tft.fillRect(teamBX, teamBY, teamBWidth, teamBHeight, teamBColor);
  tft.setTextColor(0x0000);  // Black
  tft.setTextSize(3);
  tft.setCursor(teamBX + 10, teamBY + 20);
  tft.println("Team B");
  tft.setTextSize(2);
  tft.setCursor(teamBX + 10, teamBY + 60);
  tft.println("Score: " + String(BadmintonTeamB));
  tft.setCursor(teamBX + 10, teamBY + 120);
  tft.println("Set: " + String(BadmintonsetScoreB));


  tft.fillRect(screenWidth / 2 - 2, 0, 4, screenHeight, borderColor);
}


void updateBadmintonScore() {
  int screenWidth = tft.width();
  int screenHeight = tft.height();
  if (BadmintonTeamA >= 21 && BadmintonTeamA - BadmintonTeamB >= 2) {
    BadmintonsetScoreA++;
    resetBadmintonScore();
  } else if (BadmintonTeamB >= 21 && BadmintonTeamB - BadmintonTeamA >= 2) {
    BadmintonsetScoreB++;
    resetBadmintonScore();
  } else {
      if(lastpoint){
        player1Serving=true;
      }
      else{
        player1Serving=false;
      }


  }
  if (BadmintonsetScoreA == 2) {


    tft.fillRect(0, 0, screenWidth, screenHeight, 0x0000);
    tft.setTextColor(0x07E0);  // Green
    tft.setTextSize(3);
    tft.setCursor(50, 100);
    tft.println("Team A Wins!");
    tft.setTextSize(2);
    tft.setCursor(50, 140);
    tft.println("Game Over");
    delay(2000);
   resetfinalBadmintonScore();
    // displayMenu();
  } else if (BadmintonsetScoreB == 2) {
    tft.fillRect(0, 0, screenWidth, screenHeight, 0x0000);
    tft.setTextColor(0x07E0);  // Green
    tft.setTextSize(3);
    tft.setCursor(50, 100);
    tft.println("Team B Wins!");
    tft.setTextSize(2);
    tft.setCursor(50, 140);
    tft.println("Game Over");
    delay(2000);
    resetfinalBadmintonScore();
    // displayMenu();
  } else {
      displayBadmintonScoreScreen();
  }
}


// Function to display the hockey score screen
  void displayHockeyScoreScreen() {
  int screenWidth = tft.width();
  int screenHeight = tft.height();


  int teamAWidth = screenWidth / 2;
  int teamAX = 0;
  int teamAY = 120;
  int teamAHeight = screenHeight - teamAY;


  int teamBWidth = screenWidth / 2;
  int teamBX = screenWidth / 2;
  int teamBY = 120;
  int teamBHeight = screenHeight - teamBY;


  int timerWidth = screenWidth;
  int timerX=0;
  int timerY=0;
  int timerHeight = screenHeight - timerY;


  inGameScreen = true;
  uint16_t teamAColor = 0xFFFF;  // White
  uint16_t teamBColor = 0xFFFF;  // White
  uint16_t timerColor = 0xFF00;  // Yellow
  uint16_t backgroundColor = 0x0000;  // Black
  uint16_t borderColor = 0x0000;      // Black
  tft.fillRect(timerX, timerY, timerWidth, 120, timerColor);
  tft.setTextColor(0x0000);  // Black
  tft.setTextSize(3);
  tft.setCursor(timerX + 10, timerY + 20);
  tft.println("Time: ");


  tft.setTextSize(2);
  tft.setCursor(timerX+10, timerY+70);
  tft.println("Quarter: ");


  tft.fillRect(0, 120, screenWidth, 4, borderColor);


  tft.fillRect(0, 120, screenWidth, screenHeight/2, backgroundColor);


  tft.fillRect(teamAX, teamAY, teamAWidth, teamAHeight, teamAColor);
  tft.setTextColor(0x0000);  // Black
  tft.setTextSize(3);
  tft.setCursor(teamAX + 10, teamAY + 20);
  tft.println("Team A");
  tft.setTextSize(2);
  tft.setCursor(teamAX + 10, teamAY + 60);
  tft.println("Score: " + String(HockeyTeamA));
 


  tft.fillRect(teamBX, teamBY, teamBWidth, teamBHeight, teamBColor);
  tft.setTextColor(0x0000);  // Black
  tft.setTextSize(3);
  tft.setCursor(teamBX + 10, teamBY + 20);
  tft.println("Team B");
  tft.setTextSize(2);
  tft.setCursor(teamBX + 10, teamBY + 60);
  tft.println("Score: " + String(HockeyTeamB));


  tft.fillRect(screenWidth / 2 - 2, 120, 4, screenHeight, borderColor);


  tft.setTextSize(4);
}


void updateHockeyScore() {


  int screenWidth = tft.width();
  int screenHeight = tft.height();
 
  if(minutes+seconds==0 && quarter==4){
    if(HockeyTeamA > HockeyTeamB){
      tft.fillRect(0, 0, screenWidth, screenHeight, 0x0000);
      tft.setTextColor(0x07E0);  // Green
      tft.setTextSize(3);
      tft.setCursor(50, 100);
      tft.println("Team A Wins!");
      tft.setTextSize(2);
      tft.setCursor(50, 140);
      tft.println("Game Over");
      delay(2000);
      resetfinalHockeyScore();
    }
    else if(HockeyTeamB > HockeyTeamA){
      tft.fillRect(0, 0, screenWidth, screenHeight, 0x0000);
      tft.setTextColor(0x07E0);  // Green
      tft.setTextSize(3);
      tft.setCursor(50, 100);
      tft.println("Team B Wins!");
      tft.setTextSize(2);
      tft.setCursor(50, 140);
      tft.println("Game Over");
      delay(2000);
      resetfinalHockeyScore();
    }
    else if(HockeyTeamB == HockeyTeamA){
      tft.fillRect(0, 0, screenWidth, screenHeight, 0x0000);
      tft.setTextColor(0x07E0);  // Green
      tft.setTextSize(3);
      tft.setCursor(50, 100);
      tft.println("DRAW !!");
      tft.setTextSize(2);
      tft.setCursor(50, 140);
      tft.println("Game Over");
      delay(2000);
      resetfinalHockeyScore();
    }
  }
  else{
    displayHockeyScoreScreen();
  }
 
}


//Table Tennis Resetting
void resetTennisScore() {
  tabletennisTeamA = 0;
  tabletennisTeamB = 0;
}




void resetfinalTTScore() {
  resetTennisScore();
  setScoreA = 0;
  setScoreB = 0;
  player1Serving = true;
}


//Badminton Resetting
void resetBadmintonScore() {
  BadmintonTeamA = 0;
  BadmintonTeamB = 0;
}




void resetfinalBadmintonScore() {
  resetBadmintonScore();
  BadmintonsetScoreA = 0;
  BadmintonsetScoreB = 0;
  player1Serving = true;
}




void resetfinalHockeyScore() {
  HockeyTeamA = 0;
  HockeyTeamB = 0;
  resetTimer();
  quarter=1;
}


void resetfinalCustomScore_Timed() {
  customTeamA = 0;
  customTeamB = 0;
  resetCustomTimer();
  intervalno=1;
}


void resetCustomTimer(){
  inputMinutes=inputMinutesCopy;
  inputSeconds = 0;
  customisPaused= true;
}


void resetTimer(){
  minutes=0;
  seconds=10;
  isPaused=true;
}


void resetCustomScore_NonTimed() {
  customTeamA = 0;
  customTeamB = 0;
}


void resetfinalCustomScore_NonTimed() {
  resetTennisScore();
  customSetScoreA = 0;
  customSetScoreB = 0;
}


// Function to display the timer
void displayTimer() {
  int screenWidth = tft.width();
  int screenHeight = tft.height();
   tft.fillRect(115,10,200,115, 0xFF00); //yellow
    tft.setCursor(120, 15);
    tft.setTextColor(0x0000);
    if(minutes<10){
      tft.print("0");
    }
    tft.print(minutes);
    tft.print(":");
    if (seconds < 10) {
        tft.print("0");  
    }
    tft.print(seconds);


    tft.setTextSize(2);
    tft.setCursor(120,70);
    tft.print(quarter);
    tft.setTextSize(4);
}


void displayStaticTimer(){


  int screenWidth = tft.width();
  int screenHeight = tft.height();
    tft.setCursor(120, 15);
    tft.setTextColor(0x0000);
    if(minutes<10){
      tft.print("0");
    }
    tft.print(minutes);
    tft.print(":");
    if (seconds < 10) {
        tft.print("0");  
    }
    tft.print(seconds);
    tft.setTextSize(2);
    tft.setCursor(120,70);
    tft.print(quarter);
    tft.setTextSize(4);
}


 void displayCustomScoreScreen_Timed() {
  int screenWidth = tft.width();
  int screenHeight = tft.height();


  int teamAWidth = screenWidth / 2;
  int teamAX = 0;
  int teamAY = 120;
  int teamAHeight = screenHeight - teamAY;


  int teamBWidth = screenWidth / 2;
  int teamBX = screenWidth / 2;
  int teamBY = 120;
  int teamBHeight = screenHeight - teamBY;


  int timerWidth = screenWidth;
  int timerX=0;
  int timerY=0;
  int timerHeight = screenHeight - timerY;


  inGameScreen = true;
  uint16_t teamAColor = 0xFFFF;  // White
  uint16_t teamBColor = 0xFFFF;  // White
  uint16_t timerColor = 0x7E00;  // green
  uint16_t backgroundColor = 0x0000;  // Black
  uint16_t borderColor = 0x0000;      // Black
  tft.fillRect(timerX, timerY, timerWidth, 120, timerColor);
  tft.setTextColor(0x0000);  // Black
  tft.setTextSize(3);
  tft.setCursor(timerX + 10, timerY + 20);
  tft.println("Time: ");


  tft.setTextSize(2);
  tft.setCursor(timerX+10, timerY+70);
  tft.println("Interval: ");


  tft.fillRect(0, 120, screenWidth, 4, borderColor);


  tft.fillRect(0, 120, screenWidth, screenHeight/2, backgroundColor);


  tft.fillRect(teamAX, teamAY, teamAWidth, teamAHeight, teamAColor);
  tft.setTextColor(0x0000);  // Black
  tft.setTextSize(3);
  tft.setCursor(teamAX + 10, teamAY + 20);
  tft.println("Team A");
  tft.setTextSize(2);
  tft.setCursor(teamAX + 10, teamAY + 60);
  tft.println("Score: " + String(customTeamA));
 


  tft.fillRect(teamBX, teamBY, teamBWidth, teamBHeight, teamBColor);
  tft.setTextColor(0x0000);  // Black
  tft.setTextSize(3);
  tft.setCursor(teamBX + 10, teamBY + 20);
  tft.println("Team B");
  tft.setTextSize(2);
  tft.setCursor(teamBX + 10, teamBY + 60);
  tft.println("Score: " + String(customTeamB));


  tft.fillRect(screenWidth / 2 - 2, 120, 4, screenHeight, borderColor);


}


void updateCustomScore_Timed() {


  int screenWidth = tft.width();
  int screenHeight = tft.height();
 
  if(inputMinutes + inputSeconds==0 && intervalno ==inputNumIntervals){
    if(customTeamA > customTeamB){
      tft.fillRect(0, 0, screenWidth, screenHeight, 0x0000);
      tft.setTextColor(0x07E0);  // Green
      tft.setTextSize(3);
      tft.setCursor(50, 100);
      tft.println("Team A Wins!");
      tft.setTextSize(2);
      tft.setCursor(50, 140);
      tft.println("Game Over");
      delay(2000);
      resetfinalCustomScore_Timed();
    }
    else if(customTeamB > customTeamA){
      tft.fillRect(0, 0, screenWidth, screenHeight, 0x0000);
      tft.setTextColor(0x07E0);  // Green
      tft.setTextSize(3);
      tft.setCursor(50, 100);
      tft.println("Team B Wins!");
      tft.setTextSize(2);
      tft.setCursor(50, 140);
      tft.println("Game Over");
      delay(2000);
      resetfinalCustomScore_Timed();
    }
    else if(customTeamB == customTeamA){
      tft.fillRect(0, 0, screenWidth, screenHeight, 0x0000);
      tft.setTextColor(0x07E0);  // Green
      tft.setTextSize(3);
      tft.setCursor(50, 100);
      tft.println("DRAW !!");
      tft.setTextSize(2);
      tft.setCursor(50, 140);
      tft.println("Game Over");
      delay(2000);
      resetfinalCustomScore_Timed();
    }
  }
  else{
  displayCustomScoreScreen_Timed();
  }
}


void displayCustomTimer() {
  int screenWidth = tft.width();
  int screenHeight = tft.height();
   tft.fillRect(115,10, 200, 50, 0x7E00); //yellow
    tft.setCursor(120, 15);
    tft.setTextColor(0x0000);
    tft.setTextSize(4);
    if(inputMinutes<10){
      tft.print("0");
    }
    tft.print(inputMinutes);
    tft.print(":");
    if (inputSeconds < 10) {
        tft.print("0");  
    }
    tft.print(inputSeconds);


    tft.setTextSize(2);
    tft.setCursor(120,70);
    tft.print(intervalno);
    tft.setTextSize(4);
}


void displayCustomStaticTimer(){


  tft.setTextSize(4);
  int screenWidth = tft.width();
  int screenHeight = tft.height();
    tft.setCursor(120, 15);
    tft.setTextColor(0x0000);
    if(inputMinutes<10){
      tft.print("0");
    }
    tft.print(inputMinutes);
    tft.print(":");
    if (inputSeconds < 10) {
        tft.print("0");  
    }
    tft.print(inputSeconds);
    tft.setTextSize(2);
    tft.setCursor(120,70);
    tft.print(intervalno);
}


void displayCustomScoreScreen_NonTimed() {
  int screenWidth = tft.width();
  int screenHeight = tft.height();


  int teamAWidth = screenWidth / 2;
  int teamAX = 0;
  int teamAY = 20;
  int teamAHeight = screenHeight - teamAY;


  int teamBWidth = screenWidth / 2;
  int teamBX = screenWidth / 2;
  int teamBY = 20;
  int teamBHeight = screenHeight - teamBY;
  inGameScreen = true;
  uint16_t teamAColor = 0xFFFF;  // White
  uint16_t teamBColor = 0xFFFF;  // White


  uint16_t backgroundColor = 0x0000;  // Black
  uint16_t borderColor = 0x0000;      // Black


  tft.fillRect(0, 0, screenWidth, screenHeight, backgroundColor);


  tft.fillRect(teamAX, teamAY, teamAWidth, teamAHeight, teamAColor);
  tft.setTextColor(0x0000);  // Black
  tft.setTextSize(3);
  tft.setCursor(teamAX + 10, teamAY + 20);
  tft.println("Team A");
  tft.setTextSize(2);
  tft.setCursor(teamAX + 10, teamAY + 60);
  tft.println("Score: " + String(customTeamA));
  tft.setCursor(teamAX + 10, teamAY + 120);
  tft.println("Set: " + String(customSetScoreA));


  tft.fillRect(teamBX, teamBY, teamBWidth, teamBHeight, teamBColor);
  tft.setTextColor(0x0000);  // Black
  tft.setTextSize(3);
  tft.setCursor(teamBX + 10, teamBY + 20);
  tft.println("Team B");
  tft.setTextSize(2);
  tft.setCursor(teamBX + 10, teamBY + 60);
  tft.println("Score: " + String(customTeamB));
  tft.setCursor(teamBX + 10, teamBY + 120);
  tft.println("Set: " + String(customSetScoreB));


  tft.fillRect(screenWidth / 2 - 2, 0, 4, screenHeight, borderColor);
}


void updateCustomScore_NonTimed() {
  int screenWidth = tft.width();
  int screenHeight = tft.height();
  if (customTeamA
        >= winningScore
      && customTeamA
             - customTeamB
           >= 2) {
    customSetScoreA++;
    resetCustomScore_NonTimed();
  } else if (customTeamB >= winningScore && customTeamB - customTeamA >= 2) {
    customSetScoreB++;
    resetCustomScore_NonTimed();
  }
  if (customSetScoreA == numSets) {


    tft.fillRect(0, 0, screenWidth, screenHeight, 0x0000);
    tft.setTextColor(0x07E0);  // Green
    tft.setTextSize(3);
    tft.setCursor(50, 100);
    tft.println("Team A Wins!");
    tft.setTextSize(2);
    tft.setCursor(50, 140);
    tft.println("Game Over");
    delay(2000);
    resetfinalCustomScore_NonTimed();
    // displayMenu();
  } else if (customSetScoreB == 2) {
    tft.fillRect(0, 0, screenWidth, screenHeight, 0x0000);
    tft.setTextColor(0x07E0);  // Green
    tft.setTextSize(3);
    tft.setCursor(50, 100);
    tft.println("Team B Wins!");
    tft.setTextSize(2);
    tft.setCursor(50, 140);
    tft.println("Game Over");
    delay(2000);
    resetfinalCustomScore_NonTimed();
    // displayMenu();
  } else {
    displayCustomScoreScreen_NonTimed();
  }
}







