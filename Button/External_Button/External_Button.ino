#define LEDPIN 2
#define BTNPIN 5

const int LEDPIN = 2;
const int BTNPIN = 5;

void setup() {
  pinMode(LEDPIN, OUTPUT);
  pinMode(BTNPIN, INPUT);  
}

void loop() {
  digitalWrite(LED_BUILTIN, digitalRead(BTNPIN));
  delay(100);
}

