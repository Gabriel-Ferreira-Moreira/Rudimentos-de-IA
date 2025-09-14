#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../inc/Texture.h"

#define SIZE 600
#define CELLS 3

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* boardTex = NULL;
SDL_Texture* xTex = NULL;
SDL_Texture* oTex = NULL;
TTF_Font* font = NULL;


void renderiza(){
    int cell = SIZE / CELLS;
    SDL_RenderClear(renderer);

    SDL_Rect dst = {0,0,SIZE,SIZE};
    SDL_RenderCopy(renderer, boardTex, NULL, &dst);

    for (int r=0;r<3;r++){
        for (int c=0;c<3;c++){
            if (M[r][c] == 1){
                SDL_Rect pos={c*cell,r*cell,cell,cell};
                SDL_RenderCopy(renderer, oTex, NULL, &pos);
            } else if (M[r][c] == 2){
                SDL_Rect pos={c*cell,r*cell,cell,cell};
                SDL_RenderCopy(renderer, xTex, NULL, &pos);
            }
        }
    }
    SDL_RenderPresent(renderer);
}