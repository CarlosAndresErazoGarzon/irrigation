#include "GA1A12S202.h"

GA1A12S202::GA1A12S202(int pin) {
    _pin = pin;
}


GA1A12S202::GA1A12S202(int pin, float logRange) {
    _pin = pin;
    _logRange = logRange;
}


void GA1A12S202::begin(void) {
    pinMode(_pin, INPUT);
}


int GA1A12S202::getRaw() {
    return getRaw(false);
}


int GA1A12S202::getRaw(bool smooth=false) {
    delay(1);
    
    if(smooth==true) {
        int total = 0;
        
        for(int i=0; i<100; i++) {
            total += analogRead(_pin);
            delay(1);
        }
        
        return(total/100);
    } else
        return analogRead(_pin);
}


float GA1A12S202::getLux() {
    return getLux(false);
}


float GA1A12S202::getLux(bool smooth=false) {
    int raw = getRaw(smooth);
    float logLux = raw * _logRange / _rawRange;
    
    return pow(10, logLux);
}
