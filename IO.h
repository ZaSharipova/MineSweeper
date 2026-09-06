#ifndef IO_H_
#define IO_H_

#include "main_logics.h"

namespace IO {

Logics::LogicsOptions GetOption(void);
void ClearBuffer();
void AskForCoords(size_t *x, size_t *y);
void PrintSeparator();

} // IO

#endif //IO_H_
