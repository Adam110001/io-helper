cmake_minimum_required(VERSION 3.28)
project(io-helper C)

set(CMAKE_C_STANDARD 11)

find_library(COREFOUNDATION_FRAMEWORK CoreFoundation)
find_library(IOKIT_FRAMEWORK IOKit)

add_executable(io-helper main.c
        USB/USBHandler.c
        USB/USBHandler.h
        GeneralHelpers/Options.c
        GeneralHelpers/Options.h
        GeneralHelpers/SignalHandlers.c
        GeneralHelpers/SignalHandlers.h
        GeneralHelpers/Helpers.c
        GeneralHelpers/Helpers.h)

target_link_libraries(
        io-helper
        ${COREFOUNDATION_FRAMEWORK}
        ${IOKIT_FRAMEWORK}
)