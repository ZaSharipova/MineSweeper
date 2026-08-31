#include "lay_mines.h"

#include <iostream>
#include <random>

#include "utils.h"

namespace Mines {
void LayMines(Square ***field) {
    int x = rand() % x_coord, y = rand() % y_coord;
    do {
        x = rand() % x_coord;
        y = rand() % y_coord;
    } while (field[x][y]->is_mine);

    field[x][y]->is_mine = true;
}

void CountMines(Square ***field) {
    for (size_t x = 0; x < x_coord; x++) {
        for (size_t y = 0; y < y_coord; y++) {
            if (x > 0) field[x][y]->number_of_neighbours += field[x - 1][y]->is_mine;
            if (x + 1 < x_coord) field[x][y]->number_of_neighbours += field[x + 1][y]->is_mine;
            if (y > 0) field[x][y]->number_of_neighbours += field[x][y - 1]->is_mine;
            if (y + 1 < y_coord) field[x][y]->number_of_neighbours += field[x][y + 1]->is_mine;
        }
    }
}

} // Mines
