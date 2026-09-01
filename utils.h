#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>

struct Square {
    size_t number_of_neighbours;
    bool is_mine;
    bool is_open;
    bool opened_by_user; // used only when already opened
};

enum PoolState {
    kClosed,
    kOpenedByUser,
    kOpenedByRecursion,
};

#define X_COORD 10
#define Y_COORD 10
#define number_of_mines 5

Square ***CreateField(void);
void DeleteField(Square ***field);
void DumpPool(Square ***field);

enum LogicsExitCodes {
    kSuccessStop,
    kSuccessContinue,
    kSuccessWin,
    kFail,
};

#endif // UTILS_H_
