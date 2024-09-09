//
// Created by Adam Dovciak on 08/09/2024.
//

#include "SignalHandlers.h"

void sigintHandlerBasicHandler(const int signum) {
    signal(signum, SIG_DFL);
    if (signum == INTERRUPT) {
        printf("Handler 1: Caught SIGINT (signal %d)\n", signum);
    } else if (signum == TERMINATION) {
        printf("Handler 1: Caught SIGTERM (signal %d)\n", signum);
    }
    exit(1);
}

int initWithHandler() {
    trap(INTERRUPT, currentSIGInterruptAction, sigintHandlerBasicHandler);
    trap(TERMINATION, currentSIGTerminationAction, sigintHandlerBasicHandler);

    return 0;
}

void trap(int signals, struct sigaction sa, void (Handler)(int)) {
    sigemptyset(&sa.sa_mask);
    sa = SIG_ACTION_INIT(Handler, sa.sa_mask);
    const SIGNAL_STATE state = checkSignalHandler(signals, sa);
    if (state != USED) {
        if (sigaction(signals, &sa, NULL) == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }

        if (signals == INTERRUPT) {
            currentSIGInterruptAction = sa;
        } else {
            currentSIGTerminationAction = sa;
        }
    } else if (signals == INTERRUPT) {
        if (sigaction(signals, &sa, &currentSIGInterruptAction) == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
    } else if (signals == TERMINATION) {
        if (sigaction(signals, &sa, &currentSIGTerminationAction) == -1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
    }
}

SIGNAL_STATE checkSignalHandler(const int signal, struct sigaction sa) {
    if (sigaction(signal, NULL, &sa) == -1) {
        perror("sigaction");
        return ERROR;
    }

    if (sa.sa_handler == SIG_DFL) {
        printf("Signal %d handler is set to default action.\n", signal);
        return DEFAULT;
    }

    if (sa.sa_handler == SIG_IGN) {
        printf("Signal %d handler is set to ignore.\n", signal);
        return IGNORED;
    }

    printf("Signal %d handler is set to a custom handler.\n", signal);
    return USED;
}
