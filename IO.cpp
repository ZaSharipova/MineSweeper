#include "IO.h"
#include "main_logics.h"
#include "utils.h"

namespace IO {

void ClearBuffer() {
    while (getchar() != '\n') {}
}

Logics::LogicsOptions GetOption(void) {

    printf("Введите, вы хотите открыть ячейку(o), пометить ее(f) или выйти(e):\n"
        "(o/e/f)\n");

    //ClearBuffer();
    int option_index = 0;
    option_index = getchar();
    ClearBuffer();

    switch (option_index) {
        case 'o':
            return Logics::kOpen;

        case 'e':
            return Logics::kStop;

        case 'f':
            return Logics::kFlag;

        default:
            return Logics::kStop;
    }
}

void AskForCoords(size_t *x, size_t *y) {
    int scanf_counter = 0;
    do {
        printf("Введите координаты по x, y через пробел:\n");
        scanf_counter = scanf("%zu %zu", x, y);
        ClearBuffer();
    } while (scanf_counter != 2);
}

void PrintSeparator() {
    std::cout << "------------------\n";
}

} // IO
