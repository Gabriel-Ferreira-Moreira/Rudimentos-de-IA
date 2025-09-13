#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define SIZE 600
#define CELLS 3

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
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SIZE, SIZE, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface* boardSurf = IMG_Load("Image/Jogo_Da_Velha.jpg");
    SDL_Surface* xSurf = IMG_Load("Image/Jogador_1.png");
    SDL_Surface* oSurf = IMG_Load("Image/Jogador_2.png");
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

    // Carrega uma fonte (use qualquer TTF disponível)
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 24);
    if (!font) {
        printf("Erro ao abrir fonte: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Color textColor = {255, 0, 0, 255}; // Vermelho
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Pressione ESPACO para reiniciar", textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    int board[CELLS][CELLS] = {0};
    int currentPlayer = 1;

    SDL_Event e;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = 0;

            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int cellSize = SIZE / CELLS;
                int col = e.button.x / cellSize;
                int row = e.button.y / cellSize;
                if (board[row][col] == 0) {
                    board[row][col] = currentPlayer;
                    currentPlayer = (currentPlayer == 1) ? 2 : 1;
                }
            }

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                for (int r = 0; r < CELLS; r++)
                    for (int c = 0; c < CELLS; c++)
                        board[r][c] = 0;
                currentPlayer = 1;
            }
        }

        SDL_RenderClear(renderer);

        // Desenha o tabuleiro
        SDL_Rect dstBoard = {0, 0, SIZE, SIZE};
        SDL_RenderCopy(renderer, boardTex, NULL, &dstBoard);

        // Desenha X e O
        int cellSize = SIZE / CELLS;
        for (int r = 0; r < CELLS; r++) {
            for (int c = 0; c < CELLS; c++) {
                if (board[r][c] == 1) {
                    SDL_Rect pos = {c * cellSize, r * cellSize, cellSize, cellSize};
                    SDL_RenderCopy(renderer, xTex, NULL, &pos);
                } else if (board[r][c] == 2) {
                    SDL_Rect pos = {c * cellSize, r * cellSize, cellSize, cellSize};
                    SDL_RenderCopy(renderer, oTex, NULL, &pos);
                }
            }
        }

        // Desenha o texto na parte inferior
        int texW = 0, texH = 0;
        SDL_QueryTexture(textTexture, NULL, NULL, &texW, &texH);
        SDL_Rect textRect = {(SIZE - texW) / 2, SIZE - texH - 10, texW, texH};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(boardTex);
    SDL_DestroyTexture(xTex);
    SDL_DestroyTexture(oTex);
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
    return 0;
}
