#ifndef MAIN_LOGICS_H_
#define MAIN_LOGICS_H_

#include <iostream>
#include "utils.h"

namespace Logics {

enum LogicsOptions {
    kOpen,
    kStop,
};

LogicsExitCodes HandleLogics(Field *field);

} // LOGICS

#endif // MAIN_LOGICS_H_
