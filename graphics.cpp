#include "graphics.h"

#include <string>
#include <cassert>

#include "check_mines.h"
#include "lay_mines.h"

static SDL_Color NumberColor(size_t number_of_neighbours) {
    switch (number_of_neighbours) {
        case 1:
            return {80, 120, 255, 255};
        case 2:
            return {60, 200, 90, 255};
        case 3:
            return {230, 70, 70, 255};
        case 4:
            return {150, 80, 220, 255};
        default:
            return {230, 210, 60, 255};
    }
}

static void DrawText(SDL_Renderer* renderer, TTF_Font *font, SDL_Rect cell, const std::string &string, SDL_Color color) {
    assert(renderer);
    if (!font) {
        return;
    }

    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, string.c_str(), color);
    if (!surface) {
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = {
        cell.x + (cell.w - surface->w) / 2,
        cell.y + (cell.h - surface->h) / 2,
        surface->w, surface->h
    };

    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Render(SDL_Renderer *renderer, TTF_Font *font, const Field &field, GameStates state) {
    assert(renderer);
    assert(font);

    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    for (size_t x = 0; x < X_COORD; x++) {
        for (size_t y = 0; y < Y_COORD; y++) {
            const Square &square = field.At(x, y);
            SDL_Rect cell = {(int)y * kCell, (int)x * kCell, kCell, kCell};

            if (square.is_open) {
                if (square.is_mine) {
                    SDL_SetRenderDrawColor(renderer, 200, 40, 40, 255);
                    SDL_RenderFillRect(renderer, &cell);
                } else {
                    SDL_SetRenderDrawColor(renderer, 60, 60, 60, 255);
                    SDL_RenderFillRect(renderer, &cell);
                    if (square.number_of_neighbours > 0) {
                        DrawText(renderer, font, cell, std::to_string(square.number_of_neighbours),
                            NumberColor(square.number_of_neighbours));
                    }
                }
            } else {
                SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
                SDL_RenderFillRect(renderer, &cell);
                if (square.mark == Mark::kFlag) {
                    DrawText(renderer, font, cell, "F", {220, 50, 50, 255});
                } else if (square.mark == Mark::kQuestion) {
                    DrawText(renderer, font, cell, "?", {230, 210, 60, 255});
                }
            }

            SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }

    if (state != GameStates::kPlaying) {
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        if (state == GameStates::kWon) {
            SDL_SetRenderDrawColor(renderer, 40, 160, 40, 110);
        } else {
            SDL_SetRenderDrawColor(renderer, 160, 40, 40, 110);
        }

        SDL_Rect full = {0, 0, kWinW, kWinH};
        SDL_RenderFillRect(renderer, &full);

        SDL_Rect banner = {0, kWinH / 2 - 20, kWinW, 40};
        DrawText(renderer, font, banner, state == GameStates::kWon ? "YOU WON" : "YOU LOSE", {255, 255, 255, 255});
    }

    SDL_RenderPresent(renderer);
}

bool HandleEvent(Field *field, size_t *opened, GameStates *state) {
    assert(field);
    assert(opened);
    assert(state);

    SDL_Event event {};
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }

        if (event.type == SDL_MOUSEBUTTONDOWN && *state == GameStates::kPlaying) {
            size_t col = event.button.x / kCell;
            size_t row = event.button.y / kCell;
            if (row >= X_COORD || col >= Y_COORD) {
                continue;
            }

            if (event.button.button == SDL_BUTTON_LEFT) {
                LogicsExitCodes result = CheckMines::CheckMines(field, row, col, opened);
                if (result == kFail) {
                    field->RevealMines();
                    *state = GameStates::kLost;
                } else if (result == kSuccessWin) {
                    *state = GameStates::kWon;
                }
            } else if (event.button.button == SDL_BUTTON_RIGHT) {
                CycleMark(field->At(row, col));
            }
        }
    }

    return true;
}
