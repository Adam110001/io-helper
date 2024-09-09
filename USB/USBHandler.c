//
// Created by Adam Dovciak on 01/09/2024.
//

#include "USBHandler.h"

#include "../GeneralHelpers/SignalHandlers.h"

void sigintHandlerUSB(const int signum) {
    signal(signum, SIG_DFL);
    if (signum == SIGINT) {
        printf("Handler 2: Caught SIGINT (signal %d)\n", signum);
    } else if (signum == SIGTERM) {
        printf("Handler 2: Caught SIGTERM (signal %d)\n", signum);
    }
    exit(1);
}

int detectUSB() {
    const CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
    if (matchingDict == NULL) {
        printf("Error: kIOUSBDeviceClassName");
        exit(-2);
    }
    CFRetain(matchingDict);

    const IONotificationPortRef notificationPort = IONotificationPortCreate(kIOMainPortDefault);
    if (notificationPort == NULL) {
        free(matchingDict);
        printf("Failed to create IONotificationPortRef\n");
        exit(-3);
    }

    const CFRunLoopSourceRef runLoopSource = IONotificationPortGetRunLoopSource(notificationPort);
    if (runLoopSource == NULL) {
        free(matchingDict);
        free(notificationPort);
        printf("Failed to get CFRunLoopSourceRef\n");
        exit(-4);
    }

    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopDefaultMode);

    kr = IOServiceAddMatchingNotification(notificationPort,
                                          kIOTerminatedNotification, matchingDict,
                                          usbDeviceAdded, NULL, &usbAddedIter);

    if (kr != kIOReturnSuccess) {
        free(matchingDict);
        free(notificationPort);
        free(runLoopSource);
        printf("Failed to get IOServiceAddMatchingNotification\n");
        exit(-4);
    }

    usbDeviceAdded(NULL, usbAddedIter);

    trap(INTERRUPT, currentUSBSIGInterruptAction, sigintHandlerUSB);
    trap(TERMINATION, currentUSBSIGTerminationAction, sigintHandlerUSB);

    CFRunLoopRun();

    return 0;
}

void usbDeviceAdded(void *refCon, const io_iterator_t iterator) {
    while((usbDevice = IOIteratorNext(iterator))) {
        printf("Information:\n");
        io_name_t name;
        IORegistryEntryGetName(usbDevice, name);
        printf("\tName:\t\t%s\n", (char *)name);

        const CFNumberRef idProduct = (CFNumberRef)IORegistryEntrySearchCFProperty(usbDevice, kIOServicePlane, CFSTR(kUSBProductID), kCFAllocatorDefault, 0);
        if (idProduct) {
            uint16_t PID;
            CFNumberGetValue(idProduct, kCFNumberSInt16Type, (void *)&PID);
            printf("\tidProduct:\t0x%x\n", PID);
        }
        CFRelease(idProduct);

        const CFNumberRef vendorID = (CFNumberRef)IORegistryEntrySearchCFProperty(usbDevice, kIOServicePlane,  CFSTR(kUSBVendorID), kCFAllocatorDefault, 0);
        if (vendorID) {
            uint16_t VID;
            CFNumberGetValue(vendorID, kCFNumberSInt16Type, (void *)&VID);
            printf("\tvendorID:\t0x%x\n", VID);
        }
        CFRelease(vendorID);
    }
}


