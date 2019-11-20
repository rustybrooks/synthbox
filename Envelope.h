
class Envelope {
public:
  Envelope(double attack, double decay, double sustain, double release, uint32_t start_micros) 
    : _attack(attack)
    , _decay(decay)
    , _sustain(sustain)
    , _release(release)
    , _release_from(release)
    , _last(0)
    , _start_micros(start_micros)
    , _releasing(false)
  {
  }

  void set_start(uint32_t current_micros) {
    _releasing = false;
    _start_micros = current_micros;
    _release_from = 0;
    _last = 0;
  }
  
  void set_release(uint32_t current_micros) {
    _releasing = true;
    _start_micros = current_micros;
    _release_from = _last;
  }

  uint16_t value(uint32_t current_micros) {
    double offset = (current_micros - _start_micros)/65535.0;
    if (_releasing) {
      if (offset > _release) { return 0; }
      _last = (1 - offset/_release) * _release_from;
    } else {
      if (offset < _attack) {
          _last = offset/_attack;
      } else if (offset < _attack + _decay) {
          _last = _sustain + (offset-_attack)/_decay*(1-_sustain);
      } else {
        return _last;
      }
    }

    return int(_last*65535);
  }
private:
   double _attack, _decay, _sustain, _release, _release_from, _last;
   uint32_t _start_micros;
   bool _releasing;
};
