//
// Created by Adam Dovciak on 08/09/2024.
//

#ifndef HELPERS_H
#define HELPERS_H

typedef void (* DeallocateDoublePointer)( \
    int ** intDoublePointer \
);

void destroyDoublePointersTypes(DeallocateDoublePointer callback);

#endif //HELPERS_H
