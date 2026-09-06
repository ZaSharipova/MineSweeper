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

enum class Mark : uint8_t {
    kNone,
    kFlag,
    kQuestion,
};

struct Square {
    size_t number_of_neighbours = 0;
    bool is_mine = false;
    bool is_open = false;
    bool opened_by_user = false; // used only when already opened
    Mark mark = Mark::kNone;
};

#define X_COORD 10
#define Y_COORD 10
#define number_of_mines 5

class Field {
public:
    //... for coords

    Field();
    ~Field() = default;

    Field(const Field&) = delete;
    Field &operator=(const Field &) = delete;

    void Dump() const;

    Square &At(size_t x, size_t y);
    const Square &At(size_t x, size_t y) const;

private:
    std::vector<std::vector<Square>> field_;

    size_t Index(size_t x, size_t y) { // NOTE it is unused!!!! Have to do smth with it
        return x * Y_COORD + y;
    }
};

void CycleMark(Square &sq);

// Square ***CreateField(void);
// void DeleteField(Square ***field);
// void DumpPool(Square ***field);

#endif // UTILS_H_
