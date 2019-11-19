#include "wavetables.h"

const int pin_dac1 = 21; // look this up

elapsedMicros last_wave = 0;
int accumulator = 0;
double frequency = .01;

void OnNoteOn(byte channel, byte note, byte velocity) {
}

void OnNoteOff(byte channel, byte note, byte velocity) {
}

void setup() {
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  analogWriteResolution(16);
}

void loop() {
  // usbMIDI.read();
  int table_pos = int(last_wave*frequency/1e6) % 256;
  Serial.print(table_pos); Serial.print(" ");
  Serial.print(wavetable_sin[table_pos]); Serial.print(" ");
  Serial.println();

  analogWrite(pin_dac1, wavetable_sin[table_pos]);
}
