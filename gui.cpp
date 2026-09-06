#include "graphics.h"

#include <string>
#include <cassert>

#include "check_mines.h"
#include "lay_mines.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window *window = SDL_CreateWindow("MineSweeper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kWinW, kWinH, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    TTF_Font *font = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 22); // сорри потом будет кроссплатформенность
    if (!font) {
        SDL_Log("Не удалось отобразить шрифт %s", SDL_GetError());
        return 1;
    }

    Field field {};
    for (size_t counter = 0; counter < number_of_mines; counter++) {
        Mines::LayMines(&field);
    }

    Mines::CountMines(&field);

    size_t opened = 0;
    GameStates state = GameStates::kPlaying;

    bool running = true;
    while (running) {
        running = HandleEvent(&field, &opened, &state);
        Render(renderer, font, field, state);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
