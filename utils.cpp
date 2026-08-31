#include "utils.h"

#include <iostream>
#include <cassert>

// namespace Utils {

Square ***CreateField(void) {
    Square ***field = (Square ***) calloc (x_coord, sizeof(Square **));

    for (size_t x = 0; x < x_coord; x++) {
        field[x] = (Square **) calloc (y_coord, sizeof(Square *));
        for (size_t y = 0; y < y_coord; y++) {
            Square *sq = (Square *) calloc (1, sizeof(Square));
            sq->is_mine = false;
            sq->is_open = false;
            sq->opened_by_user = false;
            sq->number_of_neighbours = 0;
            field[x][y] = sq;
        }
    }

    return field;
}

void DeleteField(Square ***field) {
    assert(field);

    for (size_t x = 0; x < x_coord; x++) {
        for (size_t y = 0; y < y_coord; y++) {
            free(field[x][y]);
        }

        free(field[x]);
    }

    free(field);
}

void DumpPool() {
    for (size_t x = 0; x < x_coord; x++) {
        for (size_t y = 0; y < y_coord; y++) {
            if (y % 2 == 1) {
                std::cout << "..";
            } else {
                std::cout << "|";
            }
        }
        std::cout << "\n";
    }
}

//void UpdateBuffer()

// } // Utils

// TODO dump logics (has to look perfect)
// TODO buffer which will be only partially changed
