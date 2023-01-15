int keyerButtonPin = 8;
int decoderLedPin = 3;
unsigned long signalLength = 0, pressTime = 0, releaseTime = 0, oldPressTime = 0;
char code[7];
char ch;
int codeLength = 0;
int cutoffTime = 300;
int noiseThreshold = 50;

char convertSignal() {
  if (noiseThreshold < signalLength && signalLength < cutoffTime)
    return '.';
  else if (signalLength >= cutoffTime)
    return '-';
}

void emptyCode() {
  strcpy(code, "");
  codeLength = 0;
}

char convertCode() {
  if (strcmp(code, ".-.-.-") == 0) {
    emptyCode();
    return '\n';
  } else if (strcmp(code, ".-.-") == 0) {
    emptyCode();
    return ' ';
  } else {
    for (int i = 0; i < letterNo; i++)
      if (strcmp(code, letters[i]) == 0) {
        emptyCode();
        return char('A' + i);
      }
    for (int i = 0; i < digitNo; i++)
      if (strcmp(code, digits[i]) == 0) {
        emptyCode();
        return char('0' + i);
      }
    emptyCode();
    return '\0';
  }
}

void setupDecoder() {
  pinMode(keyerButtonPin, INPUT_PULLUP);
  pinMode(decoderLedPin, OUTPUT);
}

void updateDecoder() {
NextChar:
  while (digitalRead(keyerButtonPin) == LOW) {
    modeState = updateMode(modeState);
    if (modeState == 0)
      return;
  }
  oldPressTime = releaseTime;
  pressTime = millis();
  digitalWrite(decoderLedPin, HIGH);
  while (digitalRead(keyerButtonPin) == HIGH) {}
  releaseTime = millis();
  digitalWrite(decoderLedPin, LOW);
  signalLength = releaseTime - pressTime;
  if (signalLength > noiseThreshold) {
    code[codeLength++] = convertSignal();
  }
  while (millis() - releaseTime < cutoffTime + (cutoffTime / 2)) {
    if (digitalRead(keyerButtonPin) == HIGH)
      goto NextChar;
  }
  code[codeLength] = '\0';
  ch = convertCode();
  if (ch != '\0')
    Serial.print(ch);
  else
    Serial.print("Unknown character encountered!\n");
}