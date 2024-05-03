add_library(
    pin
    pin.hpp
    pin.cpp
)

target_link_libraries(
    pin
    pico_stdlib
)