
#include "Envelope.h"
#include "wavetables.h"

const int pin_dac1 = A21; 
const int pin_dac2 = A20;

const int samples = 1024;

uint16_t wavetable_zero[samples];

uint16_t *wave_ptr1 = wavetable_sin;
uint16_t *wave_ptr2 = wavetable_zero;


elapsedMicros last_wave = 0;
// elapsedMicros last_write = 0;
int accumulator = 0;
double frequency = 5;
double mix = 0.5;


void OnControlChange(byte channel, byte control, byte value) {
  if (control == 0) {
    // frequency = sqrt((value+1));
    frequency = pow(2, value/12.0)/10;
    Serial.print("Received freq CC "); Serial.print(value);
    Serial.print(" freq = "); Serial.print(frequency);
    Serial.println();
  } else {
    mix = value/127.0;  
    Serial.print("Received mix CC "); Serial.print(value);
    Serial.print(" mix = "); Serial.print(mix);
    Serial.println();
  }
}

void OnProgramChange(byte channel, byte program) {
  Serial.print("Received PC "); Serial.print(program);
  Serial.println();

  switch(program) {
    case 0:
      wave_ptr1 = wavetable_sin;
      wave_ptr2 = wavetable_zero;
      break;
    case 1:
      wave_ptr1 = wavetable_sin;
      wave_ptr2 = wavetable_tri;
      break;
    case 2:
      wave_ptr1 = wavetable_tri;
      wave_ptr2 = wavetable_zero;
      break;
    case 3:
      wave_ptr1 = wavetable_tri;
      wave_ptr2 = wavetable_square;
      break;
    case 4:
      wave_ptr1 = wavetable_square;
      wave_ptr2 = wavetable_zero;
      break;
    case 5:
      wave_ptr1 = wavetable_square;
      wave_ptr2 = wavetable_saw_up;
      break;
    case 6:
      wave_ptr1 = wavetable_saw_up;
      wave_ptr2 = wavetable_zero;
      break;
    case 7:
      wave_ptr1 = wavetable_saw_up;
      wave_ptr2 = wavetable_saw_down;
      break;
    case 8:
      wave_ptr1 = wavetable_saw_down;
      wave_ptr2 = wavetable_zero;
      break;
    default:
      wave_ptr1 = wavetable_sin;
      wave_ptr2 = wavetable_zero;
  }
}


void setup() {
  for (int i=0; i<samples; i++) {
    wavetable_zero[i] = 0;
  }

  usbMIDI.setHandleControlChange(OnControlChange);
  usbMIDI.setHandleProgramChange(OnProgramChange);

  analogWriteResolution(16);
}

void loop() {
  usbMIDI.read();
  int table_pos = int(last_wave/1e6*1024*frequency) % 1024;

  analogWrite(pin_dac1, wave_ptr1[table_pos]*(1-mix) + wave_ptr2[table_pos]*mix);

  delayMicroseconds(100);
}
