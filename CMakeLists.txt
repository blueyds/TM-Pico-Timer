cmake_minimum_required(VERSION 3.12)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(tmpicotimer C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(ADDED_LIBS "")

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
	message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()


# Initialize the SDK
pico_sdk_init()

option(PIN "Use basic GPIO pin class" ON)
option(LCD1602 "Use lcd1602 driver class" OFF)

if(PIN)
	add_subdirectory(pin)
	list(APPEND ADDED_LIBS "pin")
endif()

if(LCD1602)
	add_subdirectory(lcd1602)
	list(APPEND ADDED_LIBS "lcd1602")
endif()

add_compile_options(-Wall
	-Wno-format 
	# int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
	
	-Wno-unused-function 
	# we have some for the docs that aren't called
	)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
	add_compile_options(-Wno-maybe-uninitialized)
endif()

add_executable(tmpicotimer main.cpp )

# pull in common dependencies and additional i2c hardware support
target_link_libraries(tmpicotimer 
	pico_stdlib
	ADDED_LIBS
)

# create map/bin/hex file etc.
pico_add_extra_outputs(tmpicotimer)
