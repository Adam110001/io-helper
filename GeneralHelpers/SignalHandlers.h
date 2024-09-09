//
// Created by Adam Dovciak on 08/09/2024.
//

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#ifndef SIGNALHANDLERS_H
#define SIGNALHANDLERS_H

typedef enum {
    INTERRUPT = SIGINT,
    TERMINATION = SIGTERM
} SIGNALS;

#define SIG_ACTION_INIT(handler, flags) (struct sigaction) { \
.sa_handler = handler, \
.sa_flags = flags, \
.sa_mask = 0 \
}

struct sigaction currentSIGInterruptAction;

struct sigaction currentSIGTerminationAction;

struct sigaction replacmentSIGAction;

int initWithHandler();

void sigintHandlerUSB(int signum);

typedef void (* DeallocateDoublePointer)( \
    int ** intDoublePointer \
);

void trap(int signals, struct sigaction sa, void (Handler)(int));

typedef enum {
    ERROR = -1,
    DEFAULT = 0,
    IGNORED = 1,
    USED = 2
} SIGNAL_STATE;

SIGNAL_STATE checkSignalHandler(const int signal, struct sigaction sa);

#endif //SIGNALHANDLERS_H
