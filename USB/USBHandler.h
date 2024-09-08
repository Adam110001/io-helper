//
// Created by Adam Dovciak on 01/09/2024.
//

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/usb/IOUSBLib.h>
#include <IOKit/IOCFPlugin.h>
#include <IOKit/IOBSD.h>

#include <mach/mach_port.h>

#ifndef USBHANDLER_H
#define USBHANDLER_H

static io_iterator_t usbAddedIter;
static io_iterator_t usbRemovedIter;

typedef enum USBType {
    USBA,
    USBC,
    Thunderbolt
} USBType;

struct USBDefinition {
    USBType usbType;
};

int detectUSB();

void usbDeviceAdded(void *refCon, io_iterator_t iterator);

io_service_t usbDevice;

kern_return_t kr;

IOCFPlugInInterface **plugInInterface;

SInt32 score;

#define MACH_PORT_SUCCESS KERN_SUCCESS

#define DEALLOCATE_PORT(task, name) mach_port_deallocate(task, name)

kern_return_t mach_port_deallocate(ipc_space_t task, mach_port_name_t name);

#endif //USBHANDLER_H
