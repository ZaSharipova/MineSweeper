#include <iostream>

#include "lay_mines.h"
#include "main_logics.h"
#include "utils.h"

int main() {
    Field field {};
    for (size_t counter = 0; counter < number_of_mines; counter++) {
        Mines::LayMines(&field);
    }

    Mines::CountMines(&field);

   return Logics::HandleLogics(&field);
}
