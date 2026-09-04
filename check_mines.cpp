#include "check_mines.h"

#include <iostream>
#include <cassert>

#include "main_logics.h"
#include "utils.h"

namespace CheckMines {

static bool OpenSquare(Field *field, size_t x, size_t y, size_t *opened) {
    assert(field);
    assert(opened);

    if (field->At(x, y).is_open) {
        return false;
    }
    field->At(x, y).is_open = true;
    (*opened)++;

    return true;
}

void ConditionalOpenSquare(Field *field, size_t x, size_t y, size_t *opened_neighbours) {
    assert(field);
    assert(opened_neighbours);

    if (!OpenSquare(field, x, y, opened_neighbours)) {
        return;
    }

    if (field->At(x, y).number_of_neighbours == 0) {
        OpenNeighbours(field, x, y, opened_neighbours);
    }
}

void OpenNeighbours(Field *field, size_t x, size_t y, size_t *number_of_opened_neighbours) {
    assert(field);
    assert(number_of_opened_neighbours);

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) {
                continue;
            }

            long n_x = (long)x + dx;
            long n_y = (long)y + dy;
            if (n_x < 0 || n_x >= (long)X_COORD) {
                continue;
            }
            if (n_y < 0 || n_y >= (long)Y_COORD) {
                continue;
            }

            ConditionalOpenSquare(field, (size_t)n_x, (size_t)n_y, number_of_opened_neighbours);
        }
    }
}

LogicsExitCodes CheckMines(Field *field, size_t x, size_t y, size_t *number_of_opened_neighbours) {
    assert(field);
    assert(number_of_opened_neighbours);

    field->At(x, y).is_open = true;

    if (field->At(x, y).is_mine) {
        std::cout << "Mine opened. You failed :(\n";
        return kFail;
    }

    ConditionalOpenSquare(field, x, y, number_of_opened_neighbours);

    if (*number_of_opened_neighbours == X_COORD * Y_COORD) {
        return kSuccessWin;
    }

    return kSuccessContinue;
}

} // CheckMines
