//
// Created by Adam Dovciak on 01/09/2024.
//

#include "USBHandler.h"

int detectUSB() {
    CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
    if (!matchingDict) {
        printf("Error: kIOUSBDeviceClassName");
        exit(-2);
    } else {
        CFRetain(matchingDict);
    }

    IONotificationPortRef notificationPort = IONotificationPortCreate(kIOMainPortDefault);

    if (notificationPort == NULL) {
        printf("Failed to create IONotificationPortRef\n");
        exit(-3);
    }

    CFRunLoopSourceRef runLoopSource = IONotificationPortGetRunLoopSource(notificationPort);

    if (runLoopSource == NULL) {
        printf("Failed to get CFRunLoopSourceRef\n");
        exit(-4);
    }

    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopDefaultMode);

    kr = IOServiceAddMatchingNotification(notificationPort,
                                          kIOTerminatedNotification, matchingDict,
                                          usbDeviceAdded, NULL, &usbAddedIter);

    usbDeviceAdded(NULL, usbAddedIter);

    CFRunLoopRun();

    return 0;
}

void usbDeviceAdded(void *refCon, io_iterator_t iterator) {
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


