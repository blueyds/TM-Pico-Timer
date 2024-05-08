#ifndef lcd1602_hpp_7483920
#define lcd1602_hpp_7483920
#include <stdint.h>
/*
   NOTE: The panel must be capable of being driven at 3.3v NOT 5v. The Pico
   GPIO (and therefor I2C) cannot be used at 5v.

   You will need to use a level shifter on the I2C lines if you want to run the
   board at 5v.

   Connections on Raspberry Pi Pico board, other boards may vary.

   GPIO 4 (pin 6)-> SDA on LCD bridge board
   GPIO 5 (pin 7)-> SCL on LCD bridge board
   3.3v (pin 36) -> VCC on LCD bridge board
   GND (pin 38)  -> GND on LCD bridge board
*/
class lcd1602{
	public:
		void write_byte(uint8_t val);
		void toggle_enable(uint8_t val);
		void send_byte(uint8_t val, int mode);
		void clear(void);
		void set_cursor(int line, int position);
		void send_char(char val);
		void send_string(const char *s);
		void send_command(int cmd);
		lcd1602();
		
	private:
		// By default these LCD display drivers are on bus address 0x27
		int addr = 0x27;
		
		static const uint8_t CLEARDISPLAY = 0x01;
		static const uint8_t RETURNHOME = 0x02;
		static const uint8_t RESET = 0x03;
		static const uint8_t ENTRYMODESET = 0x04;
		static const uint8_t DISPLAYCONTROL = 0x08;
		static const uint8_t CURSORSHIFT = 0x10;
		static const uint8_t FUNCTIONSET = 0x20;
		static const uint8_t SETCGRAMADDR = 0x40;
		static const uint8_t SETDDRAMADDR = 0x80;
		
		// flags for display entry mode
		static const uint8_t ENTRYSHIFTINCREMENT = 0x01;
		static const uint8_t ENTRYLEFT = 0x02;
		
		// flags for display and cursor control
		static const uint8_t BLINKON = 0x01;
		static const uint8_t CURSORON = 0x02;
		static const uint8_t DISPLAYON = 0x04;
		
		// flags for display and cursor shift
		static const uint8_t MOVERIGHT = 0x04;
		static const uint8_t DISPLAYMOVE = 0x08;
		
		// flags for function set
		static const uint8_t DOTS5x10 = 0x04;
		static const uint8_t LINES2 = 0x08;
		static const uint8_t BITMODE8 = 0x10;
		
		// flag for backlight control
		static const uint8_t BACKLIGHT = 0x08;
		
		static const uint8_t ENABLE_BIT = 0x04;
		
		// Modes for lcd_send_byte
		static const uint8_t CHARACTER = 1;
		static const uint8_t COMMAND = 0;
		
		static const int MAX_LINES = 2;
		static const int MAX_CHARS = 16;
};
#endif