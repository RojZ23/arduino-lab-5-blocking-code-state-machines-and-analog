const int ledPin = 9;       // PWM pin
const int brightenButton = 7;
const int dimButton = 8;

int brightness = 0;
const int brightnessStep = 26; // 10 presses reaches about 255

bool lastBrightenState = LOW;
bool lastDimState = LOW;

unsigned long lastBrightenPress = 0;
unsigned long lastDimPress = 0;

const unsigned long debounceTime = 200;

void setup() {
  pinMode(ledPin, OUTPUT);

  pinMode(brightenButton, INPUT);
  pinMode(dimButton, INPUT);

  analogWrite(ledPin, brightness);
}

void loop() {
  bool brightenState = digitalRead(brightenButton);
  bool dimState = digitalRead(dimButton);

  unsigned long now = millis();

  // Detect a new brighten-button press
  if (brightenState == HIGH &&
      lastBrightenState == LOW &&
      now - lastBrightenPress > debounceTime) {

    brightness = brightness + brightnessStep;

    if (brightness > 255) {
      brightness = 255;
    }

    analogWrite(ledPin, brightness);
    lastBrightenPress = now;
  }

  // Detect a new dim-button press
  if (dimState == HIGH &&
      lastDimState == LOW &&
      now - lastDimPress > debounceTime) {

    brightness = brightness - brightnessStep;

    if (brightness < 0) {
      brightness = 0;
    }

    analogWrite(ledPin, brightness);
    lastDimPress = now;
  }

  lastBrightenState = brightenState;
  lastDimState = dimState;
}