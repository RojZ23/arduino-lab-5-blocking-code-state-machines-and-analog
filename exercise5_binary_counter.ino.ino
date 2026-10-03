const int binaryLEDs[4] = {2, 3, 4, 5};

const int upButton = 8;
const int downButton = 9;
const int resetButton = 10;

int countValue = 0;

bool lastUpState = LOW;
bool lastDownState = LOW;
bool lastResetState = LOW;

unsigned long lastUpPress = 0;
unsigned long lastDownPress = 0;
unsigned long lastResetPress = 0;

const unsigned long debounceTime = 180;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(binaryLEDs[i], OUTPUT);
  }

  pinMode(upButton, INPUT);
  pinMode(downButton, INPUT);
  pinMode(resetButton, INPUT);

  displayBinary();
}

void loop() {
  bool upState = digitalRead(upButton);
  bool downState = digitalRead(downButton);
  bool resetState = digitalRead(resetButton);

  unsigned long now = millis();

  // Count up
  if (upState == HIGH &&
      lastUpState == LOW &&
      now - lastUpPress > debounceTime) {

    countValue++;

    if (countValue > 15) {
      countValue = 0;
    }

    displayBinary();
    lastUpPress = now;
  }

  // Count down
  if (downState == HIGH &&
      lastDownState == LOW &&
      now - lastDownPress > debounceTime) {

    countValue--;

    if (countValue < 0) {
      countValue = 15;
    }

    displayBinary();
    lastDownPress = now;
  }

  // Reset counter to zero
  if (resetState == HIGH &&
      lastResetState == LOW &&
      now - lastResetPress > debounceTime) {

    countValue = 0;
    displayBinary();

    lastResetPress = now;
  }

  lastUpState = upState;
  lastDownState = downState;
  lastResetState = resetState;
}

void displayBinary() {
  for (int bit = 0; bit < 4; bit++) {
    bool bitValue = bitRead(countValue, bit);
    digitalWrite(binaryLEDs[bit], bitValue);
  }
}