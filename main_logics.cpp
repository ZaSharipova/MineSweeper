#include "main_logics.h"

#include <iostream>
#include <cassert>

#include "IO.h"
#include "check_mines.h"
#include "utils.h"

namespace Logics {

LogicsExitCodes HandleLogics(Square ***field) {
    assert(field);

    //static size_t counter_of_mines_opened = 0;
    static size_t field_size = x_coord * y_coord;
    static size_t number_of_opened_squares = 0;

    if (number_of_opened_squares + number_of_mines == field_size) {
        return kSuccessWin;
    }

    LogicsOptions option = IO::GetOption();

    switch(option) {
        case kOpen: {
            size_t x = 0, y = 0;
            scanf("%zu %zu", &x, &y);
            LogicsExitCodes error_status = CheckMines::CheckMines(field, x, y, &number_of_opened_squares);
            if (error_status == kFail) return kFail;
            return HandleLogics(field);
        }

        case kStop:
            return kSuccessStop;

        default:
            return kFail;
    }
}
}
