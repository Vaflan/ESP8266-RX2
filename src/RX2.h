// W1 - Fixed durations as per RX2B datasheet see http://www.datasheetdir.com/RX-2B+download

#ifndef RX2_h
#define RX2_h

#define RX2_ENDCODE          4
#define RX2_FORWARD         10
#define RX2_FORWARD_TURBO   16
#define RX2_TURBO           22
#define RX2_FORWARD_LEFT    28
#define RX2_FORWARD_RIGHT   34
#define RX2_BACKWARD        40
#define RX2_BACKWARD_RIGHT  46
#define RX2_BACKWARD_LEFT   52
#define RX2_LEFT            58
#define RX2_RIGHT           64

#define RX2_SLEEP          10L
#define RX2_HANDSHAKE    7900L // Some bug with micros()
#define RX2_ONE_PULSE    1000L

#define RX2_PWM_HALF       511
#define RX2_PWM_3QUARTERS  767

#define RX2_FREQ_2MS       500
#define RX2_FREQ_1MS      1000

#if !defined(ESP8266)
#error "This library only supports esp8266 boards."
#endif

class RX2
{
public:
    RX2(int pin);
    void hardPulse(int pulse);
    void write(int pulse);
    void next(int pulse);
    void update();

private:
    volatile unsigned long _micros = 0L;
    volatile int _step = 0;
    int _nextPulse = 0;
    int _pulse = 0;
    int _pin;
};

#endif