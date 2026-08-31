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

#define x_coord 30
#define y_coord 16
#define number_of_mines 3

Square ***CreateField(void);
void DeleteField(Square ***field);
void DumpPool();

enum LogicsExitCodes {
    kSuccessStop,
    kSuccessWin,
    kFail,
};

#endif // UTILS_H_
