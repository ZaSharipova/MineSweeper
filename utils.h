#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>

enum PoolState {
    kClosed,
    kOpenedByUser,
    kOpenedByRecursion,
};

enum LogicsExitCodes {
    kSuccessStop,
    kSuccessContinue,
    kSuccessWin,
    kFail,
};

struct Square {
    size_t number_of_neighbours;
    bool is_mine;
    bool is_open;
    bool opened_by_user; // used only when already opened
};

class Field {
public:
    //... for coords

    Field();
    ~Field();

    Field(const Field&) = delete;
    Field &operator=(const Field &) = delete;

    void Dump() const;

    Square &At(size_t x, size_t y);
    const Square &At(size_t x, size_t y) const;

private:
    Square ***field_;
};

#define X_COORD 10
#define Y_COORD 10
#define number_of_mines 5

// Square ***CreateField(void);
// void DeleteField(Square ***field);
// void DumpPool(Square ***field);

#endif // UTILS_H_
