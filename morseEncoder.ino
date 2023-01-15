int dotDelay = 200;
int dashDelay = 3 * dotDelay;

void setupEncoder() {
  pinMode(encoderOutputLedPin, OUTPUT);
  prepareSerial(modeState);
}

void updateEncoder() {
  char ch;
  if (Serial.available()) {
    ch = Serial.read();  // read a single letter if (ch >= 'a' && ch <= 'z')
    if (ch >= 'a' && ch <= 'z') {
      flashSequence(letters[ch - 'a']);
    } else if (ch >= 'A' && ch <= 'Z') {
      flashSequence(letters[ch - 'A']);
    } else if (ch >= '0' && ch <= '9') {
      flashSequence(digits[ch - '0']);
    } else if (ch == ' ') {
      delay(dotDelay * 4);
    } else if (ch == '\n') {
      Serial.write("Message Delivered!\n");
    }
  }
}

void flashSequence(char* sequence) {
  int i = 0;
  while (sequence[i] != NULL) {
    flashDotOrDash(sequence[i]);
    i++;
  }
  delay(dotDelay * 3);
}


void flashDotOrDash(char dotOrDash) {
  digitalWrite(encoderOutputLedPin, HIGH);
  if (dotOrDash == '.') {
    delay(dotDelay);
  } else  // must be a -
  {
    delay(dashDelay);
  }
  digitalWrite(encoderOutputLedPin, LOW);
  delay(dotDelay);
}