#include <stdbool.h>
#include <string.h>
//For letters
char* letters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",    // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",  // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."          // S-Z
};
const int letterNo = 26;
// ".-.-.-" = break line
//For digits
char* digits[] = {
  "-----", ".----", "..---", "...--", "....-", ".....",
  "-....", "--...", "---..", "----."
};
const int digitNo = 10;

int encodeModeLedPin = 11;
int decodeModeLedPin = 12;
int modeButtonPin = 9;
int encoderOutputLedPin = 2;
bool modeState = 0;  //0 = encode, 1 = decode

void setup() {
  setupModeSelector();
  setupEncoder();
  setupDecoder();
  Serial.begin(9600);
}

void loop() {
  modeState = updateMode(modeState);
  if(modeState == 0)
  {
    updateEncoder();
  }
  else
    updateDecoder();
}
