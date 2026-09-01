#include "lay_mines.h"

#include <iostream>
#include <random>

#include "utils.h"

namespace Mines {
void LayMines(Square ***field) {
    int x = rand() % X_COORD, y = rand() % Y_COORD;
    do {
        x = rand() % X_COORD;
        y = rand() % Y_COORD;
    } while (field[x][y]->is_mine);

    field[x][y]->is_mine = true;
}

void CountMines(Square ***field) {
    for (size_t x = 0; x < X_COORD; x++) {
        for (size_t y = 0; y < Y_COORD; y++) {
            if (field[x][y]->is_mine) {
                continue;
            }
            int count = 0;
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

                    count += field[n_x][n_y]->is_mine ? 1 : 0;
                }
            }
            field[x][y]->number_of_neighbours = count;
        }
    }
}

} // Mines
