//
// Created by Adam Dovciak on 01/09/2024.
//

#include "Options.h"

#include <stdio.h>
#include <string.h>

void sortOptions(const int numberOfOptions, char * stringOptionsPassed[]) {
    int result = -1;
    for (int i = 1; i < numberOfOptions; i++) {
        result = strcmp(stringOptionsPassed[i], "--help");
        if (result == 0) {
            options.help = true;
            break;
        }

        result = strcmp(stringOptionsPassed[i], "--usb");
        if (result == 0) {
            options.usbDetection = true;
            break;
        }
    }
}

void helpOutput() {
    printf("Welcone! Thos service helps to making your experience with IOKIT so much easier.\n"
           "Current options:\n"
           "--help: Shows all the options\n"
           "--usb: Helps to detect usb devices plugged into the PC\n");
}
