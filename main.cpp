#include "pico/stdlib.h"
#include "pin/pin.hpp"
#include "lcd1602/lcd1602.hpp"

int main() {
    pin led_pin = pin(27);
	lcd1602 display = lcd1602();
	display.send_string("POWERED ON");
    while (true) {
        led_pin.turnOn();
        sleep_ms(250);
        led_pin.turnOff();
        sleep_ms(250);
    }
}

