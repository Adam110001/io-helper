//
// Created by Adam Dovciak on 08/09/2024.
//

#include "SignalHandlers.h"

void sigintHandlerUSB(int signum) {
    printf("Handler 1: Caught SIGINT (signal %d)\n", signum);
    exit(1);
}

int init() {
    sigemptyset(&currentSIGAction.sa_mask);
    currentSIGAction = SIG_ACTION_INIT(sigintHandlerUSB, currentSIGAction.sa_mask);

    if (sigaction(SIGINT, &currentSIGAction, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    return 0;
}