//
// Created by Adam Dovciak on 08/09/2024.
//

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#ifndef SIGNALHANDLERS_H
#define SIGNALHANDLERS_H

typedef enum {
    INT = SIGINT,
    TERM = SIGTERM
} SIGNALS;

#define SIG_ACTION_INIT(handler, flags) (struct sigaction) { \
.sa_handler = handler,             \
.sa_flags = flags,                 \
.sa_mask = 0                       \
}

struct sigaction currentSIGAction;

struct sigaction replacmentSIGAction;

int init();

void sigintHandlerUSB(int signum);

#endif //SIGNALHANDLERS_H
