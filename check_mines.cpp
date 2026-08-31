#include "check_mines.h"

#include <iostream>
#include <cassert>

#include "main_logics.h"
#include "utils.h"

namespace CheckMines {

int ConditionalOpenSquare(Square ***field, size_t x, size_t y, size_t *number_of_opened_neighbours) {
    bool state_open = field[x][y]->is_open;
    size_t number_of_neighbours = field[x][y]->number_of_neighbours;

    if (state_open) {
        return 0;
    }

    if (number_of_neighbours == 0) {
        return OpenNeighbours(field, x, y, number_of_opened_neighbours);
    }

    return 0;
}

LogicsExitCodes OpenNeighbours(Square ***field, size_t x, size_t y, size_t *number_of_opened_neighbours) {
    assert(field);
    assert(number_of_opened_neighbours);

    field[x][y]->is_open = true;

    (*number_of_opened_neighbours)++;
    if (*number_of_opened_neighbours == x_coord * y_coord) return kSuccessWin;

    if (x > 0) *number_of_opened_neighbours += ConditionalOpenSquare(field, x - 1, y, number_of_opened_neighbours);
    if (x + 1 < x_coord) *number_of_opened_neighbours += ConditionalOpenSquare(field, x + 1, y, number_of_opened_neighbours);
    if (y > 0) *number_of_opened_neighbours += ConditionalOpenSquare(field, x, y - 1, number_of_opened_neighbours);
    if (y + 1 < y_coord) *number_of_opened_neighbours += ConditionalOpenSquare(field, x, y + 1, number_of_opened_neighbours);

    return kSuccessWin;
}

LogicsExitCodes CheckMines(Square ***field, size_t x, size_t y, size_t *number_of_opened_neighbours) {
    if (field[x][y]->is_mine) {
        std::cout << "Mine opened. You failed :(\n";
        return kFail;
    }

    return OpenNeighbours(field, x, y, number_of_opened_neighbours);
}

} // CheckMines
