# synthbox
A teensy arduino thing to do various MIDI and CV utilities

Stuff I want:
* multiple MIDI in
* USB host for USB MIDI/mouse/KB
* single MIDI OUT?  Multiples/routable?

* CV gate ins/outs - can use digital pins?  Do we need level conversion?
* CV ins/outs - allowable levels?  DC coupling/no dc coupling?  oscope taps?

* regular button / pot / rotary encoder input support

* Utilities
  - attenuverters - can act as inputs also?  If out is connected, disconnect teensy input or duplicate?  2 outs makes attenuverted mult?
  - static CV sources (attenuverters with no inputs?)
  - mults / sums / mixers / steal ideas from Maths
  - LFOs - feedback LED, +/- outputs and or duplicate outs - params controllable by MIDI or CV, multiple mixable shapes
  - envelopes - feedback LED, +/- outs and/or dupes - params controllable by MIDI or CV
  - CV note quantizers
  - slew limiter
  - CV delay
  - clock input/out/thru?
  
  teensy 3.6 has only 2 DACs?
  are the teensy adc/dacs good enough anyway?
