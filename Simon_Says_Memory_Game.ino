/*
  ============================================================
              SIMON SAYS MEMORY GAME
                 Arduino UNO R4 WiFi
  ============================================================

  LEDs:
    LED 1 -> D2
    LED 2 -> D3
    LED 3 -> D4
    LED 4 -> D5

  Buttons:
    Button 1 -> D6
    Button 2 -> D7
    Button 3 -> D8
    Button 4 -> D9

  Buzzer:
    Signal -> D10
    VCC    -> 5V
    GND    -> GND

  Buttons use INPUT_PULLUP:
    Released = HIGH
    Pressed  = LOW
  ============================================================
*/


// -------------------- PIN CONFIGURATION --------------------

const int ledPins[4] = {2, 3, 4, 5};
const int buttonPins[4] = {6, 7, 8, 9};

const int buzzerPin = 10;


// -------------------- SOUND CONFIGURATION --------------------

const int notes[4] = {
  262,    // C4
  330,    // E4
  392,    // G4
  523     // C5
};


// -------------------- GAME CONFIGURATION --------------------

const int MAX_LEVEL = 50;

int gameSequence[MAX_LEVEL];

int currentLevel = 1;


// ============================================================
//                         SETUP
// ============================================================

void setup() {

  Serial.begin(9600);

  // Configure LEDs and buttons
  for (int i = 0; i < 4; i++) {

    pinMode(ledPins[i], OUTPUT);

    // Internal pull-up resistor used for buttons
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  pinMode(buzzerPin, OUTPUT);


  // Generate different random sequences after restart
  randomSeed(analogRead(A0));


  // Startup animation
  startupAnimation();


  // Generate first element of the game
  gameSequence[0] = random(0, 4);


  Serial.println();
  Serial.println("==============================");
  Serial.println("   SIMON SAYS MEMORY GAME");
  Serial.println("==============================");
  Serial.println();
  Serial.println("Watch the sequence...");
}


// ============================================================
//                       MAIN GAME LOOP
// ============================================================

void loop() {

  Serial.println();
  Serial.print("LEVEL: ");
  Serial.println(currentLevel);

  delay(800);


  // Simon displays the sequence
  showSequence();


  // Player repeats the sequence
  bool playerCorrect = getPlayerInput();


  // ---------------- CORRECT ----------------

  if (playerCorrect) {

    Serial.println("CORRECT!");

    successAnimation();

    delay(500);


    // Add a new random step
    if (currentLevel < MAX_LEVEL) {

      gameSequence[currentLevel] = random(0, 4);

      currentLevel++;
    }

    else {

      victoryAnimation();

      resetGame();
    }
  }


  // ---------------- WRONG ----------------

  else {

    gameOver();

    resetGame();
  }
}


// ============================================================
//                    DISPLAY GAME SEQUENCE
// ============================================================

void showSequence() {

  // Small pause before sequence starts
  delay(300);


  for (int i = 0; i < currentLevel; i++) {

    int selectedLED = gameSequence[i];


    // Turn LED on
    digitalWrite(ledPins[selectedLED], HIGH);


    // Play corresponding note
    tone(buzzerPin, notes[selectedLED]);


    delay(450);


    // Turn LED and sound off
    digitalWrite(ledPins[selectedLED], LOW);

    noTone(buzzerPin);


    delay(200);
  }
}


// ============================================================
//                      PLAYER INPUT
// ============================================================

bool getPlayerInput() {

  for (int position = 0; position < currentLevel; position++) {

    int pressedButton = waitForButton();


    // Check whether player's button matches Simon's sequence
    if (pressedButton != gameSequence[position]) {

      return false;
    }
  }


  return true;
}


// ============================================================
//                    WAIT FOR BUTTON PRESS
// ============================================================

int waitForButton() {

  while (true) {

    for (int i = 0; i < 4; i++) {

      // INPUT_PULLUP means LOW = pressed
      if (digitalRead(buttonPins[i]) == LOW) {


        // Give immediate visual feedback
        digitalWrite(ledPins[i], HIGH);


        // Give sound feedback
        tone(buzzerPin, notes[i]);


        // Wait until player releases button
        while (digitalRead(buttonPins[i]) == LOW) {

          delay(5);
        }


        // Turn feedback off
        digitalWrite(ledPins[i], LOW);

        noTone(buzzerPin);


        // Simple debounce delay
        delay(100);


        return i;
      }
    }
  }
}


// ============================================================
//                     STARTUP ANIMATION
// ============================================================

void startupAnimation() {

  // Run forward
  for (int i = 0; i < 4; i++) {

    digitalWrite(ledPins[i], HIGH);

    tone(buzzerPin, notes[i]);

    delay(150);

    digitalWrite(ledPins[i], LOW);

    noTone(buzzerPin);
  }


  // Run backwards
  for (int i = 3; i >= 0; i--) {

    digitalWrite(ledPins[i], HIGH);

    tone(buzzerPin, notes[i]);

    delay(100);

    digitalWrite(ledPins[i], LOW);

    noTone(buzzerPin);
  }


  delay(500);
}


// ============================================================
//                    SUCCESS ANIMATION
// ============================================================

void successAnimation() {

  // Turn all LEDs on
  setAllLEDs(HIGH);


  // Success sound
  tone(buzzerPin, 700);

  delay(120);


  tone(buzzerPin, 900);

  delay(120);


  tone(buzzerPin, 1200);

  delay(180);


  noTone(buzzerPin);


  // Turn all LEDs off
  setAllLEDs(LOW);


  delay(250);
}


// ============================================================
//                      GAME OVER
// ============================================================

void gameOver() {

  Serial.println();
  Serial.println("------------------------------");
  Serial.println("          GAME OVER!");
  Serial.println("------------------------------");

  Serial.print("FINAL SCORE: ");
  Serial.println(currentLevel - 1);

  Serial.println();


  // Flash all LEDs three times
  for (int flash = 0; flash < 3; flash++) {

    setAllLEDs(HIGH);

    tone(buzzerPin, 200);

    delay(200);


    setAllLEDs(LOW);

    noTone(buzzerPin);

    delay(150);
  }


  // Falling game-over sound
  tone(buzzerPin, 400);

  delay(200);


  tone(buzzerPin, 300);

  delay(200);


  tone(buzzerPin, 200);

  delay(400);


  noTone(buzzerPin);


  delay(1000);
}


// ============================================================
//                      VICTORY MODE
// ============================================================

void victoryAnimation() {

  Serial.println();
  Serial.println("******************************");
  Serial.println("       MAX LEVEL REACHED!");
  Serial.println("            YOU WIN!");
  Serial.println("******************************");


  for (int repeat = 0; repeat < 3; repeat++) {

    for (int i = 0; i < 4; i++) {

      digitalWrite(ledPins[i], HIGH);

      tone(buzzerPin, notes[i]);

      delay(100);

      digitalWrite(ledPins[i], LOW);
    }
  }


  tone(buzzerPin, 1000);

  delay(200);


  tone(buzzerPin, 1300);

  delay(200);


  tone(buzzerPin, 1600);

  delay(500);


  noTone(buzzerPin);


  setAllLEDs(LOW);

  delay(1500);
}


// ============================================================
//                       RESET GAME
// ============================================================

void resetGame() {

  Serial.println("Starting new game...");
  Serial.println();


  currentLevel = 1;


  // Generate a new starting sequence
  gameSequence[0] = random(0, 4);


  setAllLEDs(LOW);

  noTone(buzzerPin);


  delay(1000);
}


// ============================================================
//                   CONTROL ALL FOUR LEDs
// ============================================================

void setAllLEDs(bool state) {

  for (int i = 0; i < 4; i++) {

    digitalWrite(ledPins[i], state);
  }
}
