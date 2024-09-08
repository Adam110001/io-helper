#include <stdio.h>
#include "GeneralHelpers/Options.h"
#include "GeneralHelpers/SignalHandlers.h"
#include "USB/USBHandler.h"

int main(const int argc, char * argv[]) {
    int setUPSIGHandler = init();
    if (setUPSIGHandler != 0) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    sortOptions(argc, argv);

    if (options.help) {
        helpOutput();
    } else if (options.usbDetection) {
        int result = detectUSB();
    }

    return 0;
}
