// USB MIDI receive example, Note on/off -> LED on/off
// contributed by Alessandro Fasan

//int ledPin = 13;

void OnNoteOn(byte channel, byte note, byte velocity) {
//  digitalWrite(ledPin, HIGH); // Any Note-On turns on LED
}

void OnNoteOff(byte channel, byte note, byte velocity) {
//  digitalWrite(ledPin, LOW);  // Any Note-Off turns off LED
}

void setup() {
  pinMode(ledPin, OUTPUT);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn) ;
//  digitalWrite(ledPin, HIGH);
//  delay(400);                 // Blink LED once at startup
//  digitalWrite(ledPin, LOW);
}

void loop() {
  usbMIDI.read();
}
