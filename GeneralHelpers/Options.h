//
// Created by Adam Dovciak on 01/09/2024.
//

#ifndef OPTIONS_H
#define OPTIONS_H

#include <stdbool.h>

struct KnownOptions {
    bool help;
    bool usbDetection;
} options;

void sortOptions(int numberOfOptions, char * stringOptionsPassed[]);

void helpOutput();

#endif //OPTIONS_H
