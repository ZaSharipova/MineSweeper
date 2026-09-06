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

Field::Field() : field_(X_COORD, std::vector<Square>(Y_COORD)) {}

Square &Field::At(size_t x, size_t y) {
    return field_[x][y];
}

const Square &Field::At(size_t x, size_t y) const {
    return field_[x][y];
}

void Field::Dump() const {
    for (size_t x = 0; x < X_COORD; x++) {
        for (size_t y = 0; y < Y_COORD; y++) {

            const Square &sq = At(x, y);
            if (sq.is_open) {
                if (sq.is_mine) {
                    std::cout << kRed << "X" << kReset;
                } else if (sq.number_of_neighbours > 0) {
                    std::cout << kYellow << At(x, y).number_of_neighbours << kReset;
                } else std::cout << " ";

            } else if (sq.mark == Mark::kFlag) {
                std::cout << kRed << "F" << kReset;

            } else {
                std::cout << "○";
            }
        }

        std::cout << "\n";
    }
}

void CycleMark(Square &sq) {
    if (sq.is_mine) {
        return;
    }

    switch (sq.mark) {
        case Mark::kNone:
            sq.mark = Mark::kFlag;
            break;

        case Mark::kFlag:
            sq.mark = Mark::kQuestion;
            break;

        case Mark::kQuestion:
            sq.mark = Mark::kNone;
            break;

        default:
            break;
    }
}

// TODO dump logics (has to look perfect)
// TODO buffer which will be only partially changed
