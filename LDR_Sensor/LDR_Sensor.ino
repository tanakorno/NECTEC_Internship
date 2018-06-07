#define sensorPin A0
#define ledPin 9
#define threshold 900

int sensorValue = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);

  if (sensorValue < threshold) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  //analogWrite(ledPin, sensorValue);
}

