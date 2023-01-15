int modeButtonValue = 0;

long lastDebounceTime = 0;
long debounceDelay = 150;

void setupModeSelector() {
  pinMode(encodeModeLedPin, OUTPUT);
  pinMode(decodeModeLedPin, OUTPUT);
  pinMode(modeButtonPin, INPUT);
  digitalWrite(encodeModeLedPin, HIGH);
  digitalWrite(decodeModeLedPin, LOW);
}

void prepareSerial(bool mode)
{
  if(mode == 0)
    Serial.write("\nPrepared to transmit Morse message\n");
  else
    Serial.write("Prepared to receive Morse message\n");
}

bool updateMode(bool mode) {
  modeButtonValue = digitalRead(modeButtonPin);
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (modeButtonValue == HIGH) {
      mode = !mode;
      Serial.flush();
      prepareSerial(mode);
      digitalWrite(encodeModeLedPin, (mode ? LOW : HIGH));
      digitalWrite(decodeModeLedPin, (mode ? HIGH : LOW));
    }
    lastDebounceTime = millis();
  }
  return mode;
}
