// Exercise 4: 5 LED sequencer
// Right button: moves / speeds sequence to the right
// Left button: moves / speeds sequence to the left
// Reset button: returns to center LED and stops sequence

// LED pins
const int whiteLED = 2;
const int yellowLED = 3;
const int blueLED = 4;
const int redLED = 5;
const int greenLED = 6;

// Button pins
const int rightButton = 8;
const int leftButton = 9;
const int resetButton = 10;

// LED location:
// 0 = red, 1 = yellow, 2 = green, 3 = blue, 4 = white
int ledPosition = 2;

// Direction and speed:
// 0 = stopped
// Positive number = moving right
// Negative number = moving left
int speed = 0;

// Stores the time when the LED last moved
unsigned long lastMoveTime = 0;

// Stores previous button states
int oldRightButtonState = HIGH;
int oldLeftButtonState = HIGH;
int oldResetButtonState = HIGH;

// Stops accidental multiple button presses
unsigned long lastButtonPressTime = 0;
const unsigned long debounceTime = 200;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(whiteLED, OUTPUT);

  // Buttons connect to GND when pressed
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);

  // Begin with the green center LED on
  displayLED();
}

void loop() {
  readButtons();
  runSequencer();
}

void readButtons() {
  int rightButtonState = digitalRead(rightButton);
  int leftButtonState = digitalRead(leftButton);
  int resetButtonState = digitalRead(resetButton);

  unsigned long currentTime = millis();

  // RIGHT BUTTON
  // Button press is HIGH -> LOW because INPUT_PULLUP is used
  if (rightButtonState == LOW && oldRightButtonState == HIGH) {
    if (currentTime - lastButtonPressTime > debounceTime) {
      speed++;

      // Limit maximum speed to the right
      if (speed > 5) {
        speed = 5;
      }

      lastButtonPressTime = currentTime;
    }
  }

  // LEFT BUTTON
  if (leftButtonState == LOW && oldLeftButtonState == HIGH) {
    if (currentTime - lastButtonPressTime > debounceTime) {
      speed--;

      // Limit maximum speed to the left
      if (speed < -5) {
        speed = -5;
      }

      lastButtonPressTime = currentTime;
    }
  }

  // RESET BUTTON
  if (resetButtonState == LOW && oldResetButtonState == HIGH) {
    if (currentTime - lastButtonPressTime > debounceTime) {
      ledPosition = 2;  // Green center LED
      speed = 0;        // Stop movement

      displayLED();

      lastButtonPressTime = currentTime;
    }
  }

  // Save button states for the next loop
  oldRightButtonState = rightButtonState;
  oldLeftButtonState = leftButtonState;
  oldResetButtonState = resetButtonState;
}

void runSequencer() {
  // Do nothing if the sequencer is stopped
  if (speed == 0) {
    return;
  }

  int movementDelay;

  // Faster speed values use smaller delays
  if (abs(speed) == 1) {
    movementDelay = 800;
  }
  else if (abs(speed) == 2) {
    movementDelay = 600;
  }
  else if (abs(speed) == 3) {
    movementDelay = 400;
  }
  else if (abs(speed) == 4) {
    movementDelay = 250;
  }
  else {
    movementDelay = 100;
  }

  unsigned long currentTime = millis();

  // Move only after enough time has passed
  if (currentTime - lastMoveTime >= movementDelay) {
    lastMoveTime = currentTime;

    // Move to the right
    if (speed > 0) {
      ledPosition++;

      // After the white LED, return to red
      if (ledPosition > 4) {
        ledPosition = 0;
      }
    }

    // Move to the left
    if (speed < 0) {
      ledPosition--;

      // Before the red LED, return to white
      if (ledPosition < 0) {
        ledPosition = 4;
      }
    }

    displayLED();
  }
}

void displayLED() {
  // Turn all LEDs off
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(whiteLED, LOW);

  // Turn on the LED at the selected position
  if (ledPosition == 0) {
    digitalWrite(redLED, HIGH);
  }

  if (ledPosition == 1) {
    digitalWrite(yellowLED, HIGH);
  }

  if (ledPosition == 2) {
    digitalWrite(greenLED, HIGH);
  }

  if (ledPosition == 3) {
    digitalWrite(blueLED, HIGH);
  }

  if (ledPosition == 4) {
    digitalWrite(whiteLED, HIGH);
  }
}