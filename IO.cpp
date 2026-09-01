#include "IO.h"
#include "utils.h"

namespace IO {

void ClearBuffer() {
    while (getchar() != '\n') {}
}

Logics::LogicsOptions GetOption(void) {
    int option_index = 0;

    printf("Введите, вы хотите открыть ячейку(o) или выйти(e):\n"
        "(o/e)\n");

    //ClearBuffer();
    option_index = getchar();
    printf("debug: [%c]\n", option_index);
    ClearBuffer();

    if (option_index == 'o') {
        return Logics::kOpen;
    }
    if (option_index == 'e') {
        return Logics::kStop;
    }

    return Logics::kStop;
}

void AskForCoords(size_t *x, size_t *y) {
    int scanf_counter = 0;
    do {
        printf("Введите координаты по x, y через пробел:\n");
        scanf_counter = scanf("%zu %zu", x, y);
        ClearBuffer();
    } while (scanf_counter != 2);
}

} // IO
