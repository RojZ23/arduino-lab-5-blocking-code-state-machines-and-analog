const int blinkLED = 6;      // First LED
const int buttonLED = 5;     // Second LED
const int buttonPin = 10;    // Button input

unsigned long previousBlinkTime = 0;
const unsigned long blinkInterval = 1000; // 1 second

bool blinkState = LOW;

void setup() {
  pinMode(blinkLED, OUTPUT);
  pinMode(buttonLED, OUTPUT);
  pinMode(buttonPin, INPUT);   // External 10k pulldown resistor is used
}

void loop() {
  unsigned long currentTime = millis();

  // Blink LED 1 every second without stopping the program
  if (currentTime - previousBlinkTime >= blinkInterval) {
    previousBlinkTime = currentTime;
    blinkState = !blinkState;
    digitalWrite(blinkLED, blinkState);
  }

  // LED 2 immediately follows the button state
  if (digitalRead(buttonPin) == HIGH) {
    digitalWrite(buttonLED, HIGH);
  } else {
    digitalWrite(buttonLED, LOW);
  }
}