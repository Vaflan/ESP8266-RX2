#if defined(ESP8266)

#include <Arduino.h>
#include <RX2.h>



RX2::RX2(int pin)
{
    _pin = pin;
    digitalWrite(_pin, LOW);
    pinMode(_pin, OUTPUT);
}

void RX2::hardPulse(int pulse)
{
    // start code sequence handshake
    for (int hs = 0; hs < 4; hs++) {
        digitalWrite(_pin, HIGH);
        delayMicroseconds(1500);
        digitalWrite(_pin, LOW);
        delayMicroseconds(500);
    }
    // function code sequence pulse
    for (int pl = 0; pl < pulse; pl++) {
        digitalWrite(_pin, HIGH);
        delayMicroseconds(500);
        digitalWrite(_pin, LOW);
        delayMicroseconds(500);
    }
}

void RX2::write(int pulse)
{
    if(_step > 0 || !(pulse > 0)) {
        return;
    }
    _pulse = pulse;
    _micros = 0;
    _step = 1;
}

void RX2::next(int pulse)
{
    if(pulse > 0) {
        _nextPulse = pulse;
    }
}

void RX2::update()
{
    if(_micros > micros()) {
        return;
    }
 
    _micros = micros();
    switch(_step) {
        case 0:
            _micros += RX2_SLEEP;
            break;
        case 1:
            _micros += RX2_HANDSHAKE;
            analogWriteFreq(RX2_FREQ_2MS);
            analogWrite(_pin, RX2_PWM_3QUARTERS);
            _step = 2;
            break;
        case 2:
            _micros += _pulse * RX2_ONE_PULSE;
            analogWriteFreq(RX2_FREQ_1MS);
            analogWrite(_pin, RX2_PWM_HALF);
            _step = 3;
            break;
        case 3:
            digitalWrite(_pin, LOW);
            _step = 0;
            if (_nextPulse > 0) {
                _pulse = _nextPulse;
                _nextPulse = 0;
                _step = 1;
            }
            break;
    }
}

#endif