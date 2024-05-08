#include <stdint>
#include <string>
#include "pin/pin.hpp"
#include "lcd1602/lcd1602.hpp"

int main() {
    pin led_pin = pin(27);
	lcd lcd1602 = lcd1602();
	counter int = 0;
    while (true) {
        led_pin.turnOn();
        sleep_ms(250);
        led_pin.turnOff();
        sleep_ms(250);
    }
}

