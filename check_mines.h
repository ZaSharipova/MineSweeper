#ifndef CHECK_MINES_H_
#define CHECK_MINES_H_

#include <iostream>
#include "main_logics.h"
#include "utils.h"

namespace CheckMines {
    typedef enum StatesForOpen {
        kOpenedClean,
        kOpenedMine,
        kClosed,
    } StatesForOpen;

    void OpenNeighbours(Field *field, size_t x, size_t y, size_t *number_of_opened_neighbours);
    LogicsExitCodes CheckMines(Field *field, size_t x, size_t y, size_t *number_of_opened_neighbours);
} // CheckMines

#endif // CHECK_MINES_H_
