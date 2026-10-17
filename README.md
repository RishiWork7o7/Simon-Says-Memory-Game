# 🎮 Arduino Simon Says Memory Game

A classic **Simon Says Memory Game** built using an **Arduino UNO R4 WiFi**, LEDs, push buttons, and a buzzer.

The Arduino generates a random sequence of LEDs and sounds. The player must memorize the sequence and repeat it using the corresponding push buttons. Every successful round adds another step to the sequence, making the game progressively more difficult.

---

## 📌 Project Overview

This project was built to practice fundamental Arduino concepts such as:

- Digital inputs and outputs
- Push button interfacing
- Arduino `INPUT_PULLUP`
- LED control
- Buzzer tone generation
- Arrays
- Loops
- Random sequence generation
- User input handling
- Game logic
- Serial Monitor output

---

## 🧰 Components Used

| Component | Quantity |
|---|---:|
| Arduino UNO R4 WiFi | 1 |
| Breadboard | 1 |
| LEDs | 4 |
| Push Buttons | 4 |
| 220 Ω Resistors | 4 |
| 3-Pin Buzzer Module | 1 |
| Jumper Wires | As required |
| USB Cable | 1 |

No external power supply is required because the Arduino can be powered through USB.

---

## 🔌 Pin Configuration

### LEDs

| LED | Arduino Pin |
|---|---:|
| LED 1 | D2 |
| LED 2 | D3 |
| LED 3 | D4 |
| LED 4 | D5 |

Each LED is connected to GND through a **220 Ω current-limiting resistor**.

### Push Buttons

| Button | Arduino Pin |
|---|---:|
| Button 1 | D6 |
| Button 2 | D7 |
| Button 3 | D8 |
| Button 4 | D9 |

The buttons use Arduino's built-in `INPUT_PULLUP` resistors.

Therefore:

- Button released = `HIGH`
- Button pressed = `LOW`

No external pull-up or pull-down resistors are required.

### Buzzer Module

| Buzzer Pin | Connection |
|---|---|
| S (Signal) | D10 |
| + (VCC) | 5V |
| - (GND) | GND |

---

## ⚡ Circuit Connections

The four LEDs are controlled individually by digital pins D2-D5.

Each LED is connected as:

```text
Arduino Digital Pin
        |
       LED
        |
      220 Ω
        |
       GND
```

The push buttons are connected between their respective Arduino input pins and GND:

```text
Arduino Input Pin
        |
     Push Button
        |
       GND
```

The Arduino uses `INPUT_PULLUP` to keep each input HIGH until its button is pressed.

---

## 🎯 How the Game Works

When the Arduino starts:

1. A startup LED and sound animation plays.
2. The Arduino generates a random LED.
3. The LED lights up and its corresponding sound is played.
4. The player presses the matching button.
5. If the answer is correct, the game advances to the next level.
6. A new random step is added to the existing sequence.
7. The complete sequence is shown again.
8. The player must reproduce the entire sequence in the correct order.
9. The sequence continues getting longer after every successful round.
10. Pressing an incorrect button triggers the **Game Over** sequence.

After Game Over, the game resets and starts again from Level 1.

---

## 🧠 Example Gameplay

### Level 1

```text
Arduino: 🟢

Player:  🟢
```

### Level 2

```text
Arduino: 🟢 → 🔴

Player:  🟢 → 🔴
```

### Level 3

```text
Arduino: 🟢 → 🔴 → 🔵

Player:  🟢 → 🔴 → 🔵
```

The sequence continues increasing until the player makes a mistake.

---

## 🎵 Sound System

Each button/LED has a different frequency:

| Button | Frequency |
|---|---:|
| Button 1 | 262 Hz |
| Button 2 | 330 Hz |
| Button 3 | 392 Hz |
| Button 4 | 523 Hz |

This gives every game input its own recognizable sound.

The buzzer is also used for:

- Startup feedback
- Correct sequence feedback
- Game Over sound

---

## 💻 Serial Monitor

The Arduino Serial Monitor can be used to view the current level and final score.

Set the Serial Monitor baud rate to:

```text
9600
```

Example output:

```text
LEVEL: 1
LEVEL: 2
LEVEL: 3
LEVEL: 4

GAME OVER!
SCORE: 3

LEVEL: 1
```

---

## 🚀 How to Run the Project

1. Assemble the circuit on the breadboard.
2. Connect the Arduino UNO R4 WiFi to the computer using USB.
3. Open `Simon_Says_Memory_Game.ino` in Arduino IDE.
4. Select the correct Arduino board.
5. Select the correct COM/serial port.
6. Upload the program.
7. Wait for the startup animation.
8. Watch the LED sequence carefully.
9. Repeat the sequence using the push buttons.
10. Try to reach the highest level possible!

---

## 📂 Repository Structure

```text
Simon-Says-Memory-Game/
│
├── Simon_Says_Memory_Game.ino
├── README.md
│
└── images/
    └── project-photo.jpg
```

---

## 🔧 Concepts Learned

This project demonstrates several important embedded-system and Arduino concepts:

### Digital Output
Digital pins control the four LEDs.

### Digital Input
Push buttons allow the player to communicate with the Arduino.

### Internal Pull-Up Resistors
`INPUT_PULLUP` eliminates the need for external button resistors.

### Arrays
LED pins, button pins, sounds, and the generated sequence are stored efficiently using arrays.

### Random Numbers
Arduino's `random()` function generates unpredictable game sequences.

### Loops
Loops are used to display sequences, monitor buttons, and control animations.

### Functions
Different parts of the program are separated into functions such as:

```cpp
showSequence()
getPlayerInput()
waitForButton()
startupAnimation()
successAnimation()
gameOver()
```

This makes the program easier to understand and maintain.

---

## 🌟 Features

- Random memory sequences
- Increasing difficulty
- Four physical input buttons
- Four LED indicators
- Individual sound for each input
- Startup animation
- Success animation
- Game Over animation
- Score tracking
- Serial Monitor feedback
- Automatic game restart
- Maximum sequence length of 50

---

## 🔮 Future Improvements

Possible upgrades include:

- OLED/LCD score display
- High-score storage using EEPROM
- Adjustable difficulty modes
- Faster sequences at higher levels
- Dedicated Start/Reset button
- Multiplayer mode
- Custom melodies
- Better enclosure and button layout
- Wireless score monitoring using UNO R4 WiFi
- Web-based leaderboard

---

## 📷 Project Images

Add photographs of the completed circuit here.

Example:

```markdown
![Simon Says Memory Game](images/project-photo.jpg)
```

---

## 🛠️ Built With

- Arduino UNO R4 WiFi
- Arduino IDE
- C/C++
- Breadboard electronics

---

## 📜 License

This project is available under the **MIT License**.

---

## 🙌 About the Project

This project was created as a hands-on Arduino learning project to understand how multiple hardware components can be combined with software logic to create an interactive embedded system.

The project started by individually testing each LED and push button before integrating the buzzer and finally implementing the complete Simon Says game logic.

---

⭐ If you found this project useful, consider starring the repository!
