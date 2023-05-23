#include "GA1A12S202.h"

GA1A12S202 lux(A0);

void setup() {
    Serial.begin(115200);
    delay(5000);
}

void loop() {
    Serial.print("Raw = ");
    Serial.print(lux.getRaw());
    Serial.print(", Lux = ");
    Serial.println(lux.getLux(true));
    delay(1000);
}
