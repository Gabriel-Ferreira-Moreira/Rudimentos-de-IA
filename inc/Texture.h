#ifndef JOGO_DA_VELHA_H
#define JOGO_DA_VELHA_H

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define SIZE 600
#define CELLS 3

// Variáveis globais
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* boardTex;
extern SDL_Texture* xTex;
extern SDL_Texture* oTex;
extern TTF_Font* font;

// Matriz do tabuleiro
extern int M[CELLS][CELLS];

// Funções
void renderiza();

#endif // JOGO_DA_VELHA_H
