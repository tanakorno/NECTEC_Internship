#define LEDPIN LED_BUILTIN
#define BTNPIN 3

void setup() {
  pinMode(LEDPIN, OUTPUT);
  pinMode(BTNPIN, INPUT);  
}

void loop() {
  digitalWrite(LEDPIN, digitalRead(BTNPIN));
  delay(100);
}

