#include <stdint.h>

#include "lcd1602.hpp"

/* Quick helper function for single byte transfers */
void lcd1602::write_byte(uint8_t val) {
#ifdef i2c_default
    i2c_write_blocking(i2c_default, addr, &val, 1, false);
#endif
}

void lcd1602::toggle_enable(uint8_t val) {
    // Toggle enable pin on LCD display
    // We cannot do this too quickly or things don't work
#define DELAY_US 600
    sleep_us(DELAY_US);
    i2c_write_byte(val | lcd1602::ENABLE_BIT);
    sleep_us(DELAY_US);
    i2c_write_byte(val & ~lcd1602::ENABLE_BIT);
    sleep_us(DELAY_US);
}

// The display is sent a byte as two separate nibble transfers
void lcd1602::send_byte(uint8_t val, int mode) {
	uint8_t high = mode | (val & 0xF0) | lcd1602::BACKLIGHT;
	uint8_t low = mode | ((val << 4) & 0xF0) | lcd1602::BACKLIGHT;

	this->write_byte(high);
	this->toggle_enable(high);
	this->write_byte(low);
	this->toggle_enable(low);
}

void lcd1602::clear(void) {
    this->send_byte(lcd1602::CLEARDISPLAY, lcd1602::COMMAND);
}

// go to location on LCD
void lcd1602::set_cursor(int line, int position) {
    int val = (line == 0) ? 0x80 + position : 0xC0 + position;
    this->send_byte(val, lcd1602::COMMAND);
}

void lcd1602::send_char(char val) {
    this->send_byte(val, lcd1602::CHARACTER);
}

void lcd1602::send_string(const char *s) {
    while (*s) {
        this->send_char(*s++);
    }
}

lcd1602::lcd1602() {
	// This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
	i2c_init(i2c_default, 100 * 1000);
	gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
	gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
	gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
	gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
	// Make the I2C pins available to picotool
	bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

	
	this->send_byte(0x03, lcd1602::COMMAND);
	sleep_ms(5); # need to wait 5 ms after first reset
	this->send_byte(0x03, lcd1602::COMMAND);
	sleep_ms(1);
	this->send_byte(0x03, lcd1602::COMMAND);
	sleep_ms(1);
	this->send_byte(0x02, lcd1602::COMMAND);

	this->send_byte(lcd1602::ENTRYMODESET | lcd1602::ENTRYLEFT, lcd1602::COMMAND);
	this->send_byte(lcd1602::FUNCTIONSET | lcd1602::2LINE, lcd1602::COMMAND);
	this->send_byte(lcd1602::DISPLAYCONTROL | lcd1602::DISPLAYON, lcd1602::COMMAND);
	this->clear();
}

