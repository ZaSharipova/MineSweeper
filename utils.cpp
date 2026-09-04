#include "utils.h"

#include <iostream>
#include <cassert>
#include <cstdlib>

namespace {
    constexpr const char *kReset = "\033[0m";
    constexpr const char *kRed = "\033[1;31m";
    constexpr const char *kYellow = "\033[1;33m";
    constexpr const char *kWhite = "\033[1;37m";
} // namespace

Field::Field() {
    field_ = static_cast<Square ***>(calloc (X_COORD, sizeof(Square **)));

    for (size_t x = 0; x < X_COORD; x++) {
        field_[x] = static_cast<Square **>(calloc (Y_COORD, sizeof(Square *)));

        for (size_t y = 0; y < Y_COORD; y++) {
            Square *sq = static_cast<Square *>(calloc (1, sizeof(Square)));
            sq->is_mine = false;
            sq->is_open = false;
            sq->opened_by_user = false;
            sq->number_of_neighbours = 0;
            field_[x][y] = sq;
        }
    }
}

Field::~Field() {
    assert(field_);

    for (size_t x = 0; x < X_COORD; x++) {
        for (size_t y = 0; y < Y_COORD; y++) {
            free(field_[x][y]);
        }

        free(field_[x]);
    }

    free(field_);
}

Square &Field::At(size_t x, size_t y) {
    return *field_[x][y];
}

const Square &Field::At(size_t x, size_t y) const {
    return *field_[x][y];
}

void Field::Dump() const {
    for (size_t x = 0; x < X_COORD; x++) {
        for (size_t y = 0; y < Y_COORD; y++) {
            Square *field_pos = field_[x][y];
            if (field_pos->is_open) {
                    if (field_pos->is_mine) {
                        std::cout << kRed << "X" << kReset;
                    } else {
                        if (field_pos->number_of_neighbours > 0) {
                            std::cout << kYellow << field_[x][y]->number_of_neighbours << kReset;
                        } else std::cout << " ";
                    }
            } else {
                std::cout << "○";
            }
        }
        std::cout << "\n";
    }
}

// TODO dump logics (has to look perfect)
// TODO buffer which will be only partially changed
