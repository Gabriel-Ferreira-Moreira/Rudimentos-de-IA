#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdbool.h>

#define SIZE 600
#define CELLS 3

// Renderiza tabuleiro e peças
void renderiza(SDL_Renderer* renderer,
               SDL_Texture* boardTex, SDL_Texture* xTex, SDL_Texture* oTex,
               int M[3][3]) {
    int cell = SIZE / CELLS;
    SDL_RenderClear(renderer);

    SDL_Rect dst = {0, 0, SIZE, SIZE};
    SDL_RenderCopy(renderer, boardTex, NULL, &dst);

    for (int r = 0; r < CELLS; r++) {
        for (int c = 0; c < CELLS; c++) {
            if (M[r][c] == 1) {
                SDL_Rect pos = {c * cell, r * cell, cell, cell};
                SDL_RenderCopy(renderer, oTex, NULL, &pos);
            } else if (M[r][c] == 2) {
                SDL_Rect pos = {c * cell, r * cell, cell, cell};
                SDL_RenderCopy(renderer, xTex, NULL, &pos);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

// Verifica vencedor: retorna 1 (O), 2 (X) ou 0 (nenhum)
int verifica(int A[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (A[i][0] && A[i][0] == A[i][1] && A[i][1] == A[i][2]) return A[i][0];
        if (A[0][i] && A[0][i] == A[1][i] && A[1][i] == A[2][i]) return A[0][i];
    }
    if (A[0][0] && A[0][0] == A[1][1] && A[1][1] == A[2][2]) return A[0][0];
    if (A[0][2] && A[0][2] == A[1][1] && A[1][1] == A[2][0]) return A[0][2];
    return 0;
}
