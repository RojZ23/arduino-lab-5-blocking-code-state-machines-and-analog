const int buttonPin = 10;

const int redLED = 3;
const int yellowLED = 5;
const int greenLED = 6;

const unsigned long longPressLength = 1000;  // 1 second
const unsigned long doubleClickGap = 400;    // 0.4 second
const unsigned long debounceDelay = 50;

bool lastButtonState = LOW;
bool buttonState = LOW;

unsigned long buttonDownTime = 0;
unsigned long lastButtonChange = 0;
unsigned long firstClickTime = 0;

int numberOfClicks = 0;

bool stoplightMode = false;
bool discoMode = false;

unsigned long lightTimer = 0;
int stoplightStep = 0;
int discoStep = 0;

void setup() {
  pinMode(buttonPin, INPUT);

  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  allLightsOff();
}

void loop() {
  checkButton();
  updateLights();
}

void checkButton() {
  bool reading = digitalRead(buttonPin);
  unsigned long currentTime = millis();

  // Debounce: ignore fast electrical noise from the button
  if (reading != lastButtonState) {
    lastButtonChange = currentTime;
  }

  if (currentTime - lastButtonChange > debounceDelay) {

    // Detect a real state change
    if (reading != buttonState) {
      buttonState = reading;

      // Button has just been pressed
      if (buttonState == HIGH) {
        buttonDownTime = currentTime;
      }

      // Button has just been released
      if (buttonState == LOW) {
        unsigned long pressTime = currentTime - buttonDownTime;

        // Long press: 1 second or longer
        if (pressTime >= longPressLength) {
          longPress();
          numberOfClicks = 0;
        }

        // Short press: less than 1 second
        else {
          numberOfClicks++;

          // First click: start waiting for a possible second click
          if (numberOfClicks == 1) {
            firstClickTime = currentTime;
          }

          // Second click: double press
          else if (numberOfClicks == 2) {
            doublePress();
            numberOfClicks = 0;
          }
        }
      }
    }
  }

  // If only one click occurred and the double-click time expires,
  // treat it as a short press.
  if (numberOfClicks == 1 &&
      currentTime - firstClickTime > doubleClickGap) {

    shortPress();
    numberOfClicks = 0;
  }

  lastButtonState = reading;
}

void shortPress() {
  // Short press starts stoplight mode
  stoplightMode = true;
  discoMode = false;

  stoplightStep = 0;
  lightTimer = millis();
}

void doublePress() {
  // Double press starts disco mode
  discoMode = true;
  stoplightMode = false;

  discoStep = 0;
  lightTimer = millis();
}

void longPress() {
  // Long press turns every LED off
  stoplightMode = false;
  discoMode = false;

  allLightsOff();
}

void updateLights() {
  if (stoplightMode == true) {
    runStoplight();
  }

  if (discoMode == true) {
    runDisco();
  }
}

void runStoplight() {
  unsigned long currentTime = millis();

  // Red for 3 seconds
  if (stoplightStep == 0) {
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);

    if (currentTime - lightTimer >= 3000) {
      stoplightStep = 1;
      lightTimer = currentTime;
    }
  }

  // Yellow for 1 second
  else if (stoplightStep == 1) {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, LOW);

    if (currentTime - lightTimer >= 1000) {
      stoplightStep = 2;
      lightTimer = currentTime;
    }
  }

  // Green for 3 seconds
  else if (stoplightStep == 2) {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, HIGH);

    if (currentTime - lightTimer >= 3000) {
      stoplightStep = 0;
      lightTimer = currentTime;
    }
  }
}

void runDisco() {
  unsigned long currentTime = millis();

  // Change to a new LED every 150 milliseconds
  if (currentTime - lightTimer >= 150) {
    lightTimer = currentTime;

    allLightsOff();

    if (discoStep == 0) {
      digitalWrite(redLED, HIGH);
    }

    else if (discoStep == 1) {
      digitalWrite(yellowLED, HIGH);
    }

    else if (discoStep == 2) {
      digitalWrite(greenLED, HIGH);
    }

    discoStep++;

    if (discoStep > 2) {
      discoStep = 0;
    }
  }
}

void allLightsOff() {
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(greenLED, LOW);
}