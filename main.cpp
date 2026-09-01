#include <iostream>

#include "lay_mines.h"
#include "main_logics.h"
#include "utils.h"

int main() {
    Square ***field = CreateField();
    for (size_t counter = 0; counter < number_of_mines; counter ++) {
        Mines::LayMines(field);
    }

    Mines::CountMines(field);

    LogicsExitCodes error_status = Logics::HandleLogics(field);

    //DumpPool(field);
    DeleteField(field);

    return error_status;
}
