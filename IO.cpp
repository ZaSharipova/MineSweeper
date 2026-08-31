#include "IO.h"

namespace IO {

void ClearBuffer() {
    while (getchar() != '\n') {}
}

Logics::LogicsOptions GetOption(void) {
    int option_index = 0;

    printf("Введите, вы хотите открыть ячейку(o) или выйти(e):\n"
        "(o/e)\n");

    option_index = getchar();
    ClearBuffer();

    if (option_index == 'o') {
        return Logics::kOpen;
    }
    if (option_index == 'e') {
        return Logics::kStop;
    }

    return Logics::kStop;
}

} // IO
