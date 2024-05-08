add_library(
    lcd1602
    lcd1602.hpp
    lcd1602.cpp
)

target_link_libraries(
    lcd1602
    pico_stdlib
	hardware_i2c
)