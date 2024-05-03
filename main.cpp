#include "pin/pin.hpp"
#include "pico/stdlib.h"


int main() {
    pin led_pin = pin(27);
    while (true) {
        led_pin.turnOn();
        sleep_ms(250);
        led_pin.turnOff();
        sleep_ms(250);
    }
}

