#include <iostream>

#include "lay_mines.h"
#include "main_logics.h"
#include "utils.h"

int main() {
    Square ***field = CreateField();
    Mines::LayMines(field);
    Mines::CountMines(field);

    LogicsExitCodes error_status = Logics::HandleLogics(field);

    DeleteField(field);

    return error_status;
}
