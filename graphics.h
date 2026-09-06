#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "utils.h"

constexpr int kCell = 40;
constexpr int kWinW = Y_COORD * kCell;
constexpr int kWinH = X_COORD * kCell;

enum class GameStates {
    kPlaying,
    kWon,
    kLost,
};

void Render(SDL_Renderer *renderer, TTF_Font *font, const Field &field, GameStates state);
bool HandleEvent(Field *field, size_t *opened, GameStates *state);

#endif // GRAPHICS_H_
