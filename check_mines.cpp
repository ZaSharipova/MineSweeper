#include "check_mines.h"

#include <iostream>
#include <cassert>

#include "main_logics.h"
#include "utils.h"

namespace CheckMines {

static bool OpenSquare(Square ***field, size_t x, size_t y, size_t *opened) {
    assert(field);
    assert(opened);

    if (field[x][y]->is_open) {
        return false;
    }
    field[x][y]->is_open = true;
    (*opened)++;

    return true;
}

void ConditionalOpenSquare(Square ***field, size_t x, size_t y, size_t *opened_neighbours) {
    assert(field);
    assert(opened_neighbours);

    if (!OpenSquare(field, x, y, opened_neighbours)) {
        return;
    }

    if (field[x][y]->number_of_neighbours == 0) {
        OpenNeighbours(field, x, y, opened_neighbours);
    }
}

void OpenNeighbours(Square ***field, size_t x, size_t y, size_t *number_of_opened_neighbours) {
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

LogicsExitCodes CheckMines(Square ***field, size_t x, size_t y, size_t *number_of_opened_neighbours) {
    assert(field);
    assert(number_of_opened_neighbours);

    field[x][y]->is_open = true;

    if (field[x][y]->is_mine) {
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
