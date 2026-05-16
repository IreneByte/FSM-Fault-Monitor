int redPin = 6;
int greenPin = 5;
int bluePin = 3;
int buttonPin = 8;
int buzzerPin = 2;
int faultPin = 7;

enum State {
  IDLE,
  RUNNING, 
  FAULT,
  RESET_REQUIRED
};

State currentState = IDLE;
int lastButtonReading = HIGH;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(faultPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int buttonReading = digitalRead(buttonPin);

  if (buttonReading == LOW && lastButtonReading == HIGH) {
    if (currentState == IDLE) {
      currentState = RUNNING;
    } 
    else if (currentState == RESET_REQUIRED) {
      currentState = IDLE;
    }
  }

  if (currentState == RUNNING && digitalRead(faultPin) == LOW) {
    currentState = FAULT;
  }

  if (currentState == FAULT && digitalRead(buttonPin) == LOW) {
    currentState = RESET_REQUIRED;
  }

  if (currentState == IDLE) {
    setColor(0, 0, 0); // Off
    digitalWrite(buzzerPin, LOW);
  } 
  else if (currentState == RUNNING) {
    setColor(0, 255, 0); // Green
    digitalWrite(buzzerPin, LOW);
  }
  else if (currentState == FAULT) {
    setColor(255, 0, 0); // Red
    digitalWrite(buzzerPin, HIGH);
  }
  else if (currentState == RESET_REQUIRED) {
    setColor(255, 165, 0); // Yellow
    digitalWrite(buzzerPin, LOW);
  }

  lastButtonReading = buttonReading;
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
