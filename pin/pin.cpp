#include "pico/stdlib.h"
#include "pin.hpp"

pin::pin(uint pin){
    this->pinNumber = pin;
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

void pin::turnOn(){
    gpio_put(this->pinNumber, 1);
}

void pin::turnOff(){
    gpio_put(this->pinNumber, 0);
}
