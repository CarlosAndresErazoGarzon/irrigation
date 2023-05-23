// Adapted from https://learn.adafruit.com/adafruit-ga1a12s202-log-scale-analog-light-sensor/use-it
#include <math.h>
#include "application.h"

class GA1A12S202 {
    private:
        int _pin = A0;
        float _rawRange = 4096;
        float _logRange = 5.0;
    
    public:
        GA1A12S202(int pin);
        GA1A12S202(int pin, float logRange);
        void begin(void);
        int getRaw();
        int getRaw(bool smooth);
        float getLux();
        float getLux(bool smooth);
};
