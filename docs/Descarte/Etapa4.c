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

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erro SDL: %s\n", SDL_GetError());
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
        printf("Erro IMG_Init: %s\n", IMG_GetError());
        return 1;
    }
    if (TTF_Init() == -1) {
        printf("Erro TTF: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Jogo da Velha",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SIZE, SIZE + 50, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface* boardSurf = IMG_Load("../Image/Jogo_Da_Velha.jpg");
    SDL_Surface* xSurf = IMG_Load("../Image/Jogador_1.png");
    SDL_Surface* oSurf = IMG_Load("../Image/Jogador_2.png");
    if (!boardSurf || !xSurf || !oSurf) {
        printf("Erro ao carregar imagens: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Texture* boardTex = SDL_CreateTextureFromSurface(renderer, boardSurf);
    SDL_Texture* xTex = SDL_CreateTextureFromSurface(renderer, xSurf);
    SDL_Texture* oTex = SDL_CreateTextureFromSurface(renderer, oSurf);
    SDL_FreeSurface(boardSurf);
    SDL_FreeSurface(xSurf);
    SDL_FreeSurface(oSurf);

    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 28);
    if (!font) {
        printf("Erro ao abrir fonte: %s\n", TTF_GetError());
        return 1;
    }

    int M[3][3] = {0};
    int jogadorAtual = 1; // 1 = O, 2 = X
    int vencedor = 0, jogadas = 0;
    bool quit = false;

    SDL_Event e;
    renderiza(renderer, boardTex, xTex, oTex, M);

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;

            if (!vencedor && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int cellSize = SIZE / CELLS;
                int col = e.button.x / cellSize;
                int row = e.button.y / cellSize;
                if (row < 3 && col < 3 && M[row][col] == 0) {
                    M[row][col] = jogadorAtual;
                    jogadas++;
                    vencedor = verifica(M);
                    jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
                }
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                for (int r = 0; r < 3; r++)
                    for (int c = 0; c < 3; c++)
                        M[r][c] = 0;
                vencedor = 0;
                jogadas = 0;
                jogadorAtual = 1;
            }
        }

        renderiza(renderer, boardTex, xTex, oTex, M);

        if (vencedor || jogadas == 9) {
            char msg[64];
            if (vencedor) {
                snprintf(msg, sizeof(msg), "Jogador %d venceu! [ESPACO=Reiniciar]", vencedor);
            } else {
                snprintf(msg, sizeof(msg), "Empate! [ESPACO=Reiniciar]");
            }
            SDL_Color color = {255, 0, 0, 255};
            SDL_Surface* surf = TTF_RenderText_Solid(font, msg, color);
            SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
            int tw, th;
            SDL_QueryTexture(tex, NULL, NULL, &tw, &th);
            SDL_Rect rect = {(SIZE - tw) / 2, SIZE - th - 10, tw, th};
            SDL_RenderCopy(renderer, tex, NULL, &rect);
            SDL_RenderPresent(renderer);
            SDL_FreeSurface(surf);
            SDL_DestroyTexture(tex);
        }

        SDL_Delay(16); // ~60 FPS
    }

    TTF_CloseFont(font);
    SDL_DestroyTexture(boardTex);
    SDL_DestroyTexture(xTex);
    SDL_DestroyTexture(oTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
