#include "utils.h"

#include <iostream>
#include <cassert>

// namespace Utils {

Square ***CreateField(void) {
    Square ***field = (Square ***) calloc (X_COORD, sizeof(Square **));

    for (size_t x = 0; x < X_COORD; x++) {
        field[x] = (Square **) calloc (Y_COORD, sizeof(Square *));

        for (size_t y = 0; y < Y_COORD; y++) {
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

    for (size_t x = 0; x < X_COORD; x++) {
        for (size_t y = 0; y < Y_COORD; y++) {
            free(field[x][y]);
        }

        free(field[x]);
    }

    free(field);
}

#define RESET  "\033[0m"
#define RED    "\033[1;31m"
#define YELLOW "\033[1;33m"
#define WHITE  "\033[1;37m"

void DumpPool(Square ***field) {
    for (size_t x = 0; x < X_COORD; x++) {
        for (size_t y = 0; y < Y_COORD; y++) {
            Square *field_pos = field[x][y];
            if (field_pos->is_open) {
                //if (field_pos->opened_by_user) {
                    if (field_pos->is_mine) {
                        printf(RED "X" RESET);
                    } else {
                        if (field_pos->number_of_neighbours > 0) printf(YELLOW "%zu" RESET, field[x][y]->number_of_neighbours);
                        else printf(" ");
                    }
                // } else {
                //     printf(" ");
                // }
            } else {
                printf("○");
            }
            // if (y % 2 == 1) {
            //     std::cout << "..";
            // } else {
            //     std::cout << "|";
            // }
        }
        std::cout << "\n";
    }
}

//void UpdateBuffer()

// } // Utils

// TODO dump logics (has to look perfect)
// TODO buffer which will be only partially changed
