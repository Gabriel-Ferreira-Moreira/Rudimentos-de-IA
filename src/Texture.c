#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
//#include "../inc/Texture.h"
#include "Texture.h"
#include <stdbool.h>
#include <stdio.h>

#define CELLS 3

#ifdef SIZE
#undef SIZE
#endif
#define SIZE 600


SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* boardTex = NULL;
SDL_Texture* xTex = NULL;
SDL_Texture* oTex = NULL;
TTF_Font* font = NULL;


// Estrutura para representar retângulos clicáveis
typedef struct {
    SDL_Rect rect;
    int opcao;
} Botao;


// Função para exibir menu e capturar escolha
int mostraMenu(SDL_Renderer* renderer) {
    SDL_Surface* menuSurf = IMG_Load("../../Image/Menu.png");
    if (!menuSurf) { printf("Erro carregando menu: %s\n", IMG_GetError()); exit(1); }
    SDL_Texture* menuTex = SDL_CreateTextureFromSurface(renderer, menuSurf);
    SDL_FreeSurface(menuSurf);

    // Definir áreas clicáveis (ajuste conforme a imagem)
    Botao botoes[5] = {
        {{110, 170, 380, 70}, 1}, 
        {{110, 265, 380, 70}, 2}, 
        {{110, 357, 380, 70}, 3}, 
        {{110, 449, 380, 70}, 4},
        {{110, 540, 380, 70}, 5}  
    };

    int escolha = 0;
    SDL_Event e;

    while (!escolha) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, menuTex, NULL, NULL);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) exit(0);
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int mx = e.button.x;
                int my = e.button.y;
                for (int i = 0; i < 5; i++) {
                    if (mx >= botoes[i].rect.x && mx <= botoes[i].rect.x + botoes[i].rect.w &&
                        my >= botoes[i].rect.y && my <= botoes[i].rect.y + botoes[i].rect.h) {
                        escolha = botoes[i].opcao;
                        break;
                    }
                }
            }
        }
          // Renderizar a tela de dificuldade
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, menuTex, NULL, NULL);

        // Opcional: desenhar bordas de debug dos botões
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int i = 0; i < 5; i++) {
            SDL_RenderDrawRect(renderer, &botoes[i].rect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(menuTex);
    return escolha;
}

void renderiza() {
    int cell = SIZE / CELLS;
    SDL_RenderClear(renderer);

    // Desenha o tabuleiro apenas na área quadrada de 600x600
    SDL_Rect dst = {0, 0, SIZE, SIZE};
    SDL_RenderCopy(renderer, boardTex, NULL, &dst);

    // Desenha os X e O nas posições corretas
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
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

int MenuDificuldade(SDL_Renderer* renderer) {
    SDL_Surface* menuSurf = IMG_Load("../Image/Dificuldade.png");
    if (!menuSurf) {
        printf("Erro carregando Dificuldade: %s\n", IMG_GetError());
        exit(1);
    }
    SDL_Texture* menuTex = SDL_CreateTextureFromSurface(renderer, menuSurf);
    SDL_FreeSurface(menuSurf);

    // Definir áreas clicáveis
    Botao botoes[4] = {
        {{110, 290, 380, 70}, 1}, // Fácil
        {{110, 380, 380, 70}, 2}, // Médio
        {{110, 475, 380, 70}, 3}, // Impossível
        {{110, 570, 380, 70}, 4}  // Voltar
    };


    int escolha = 0;
    bool selecionando = true;
    SDL_Event e;

    while (selecionando) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                escolha = 4; // Voltar se fechar a janela
                selecionando = false;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x;
                int y = e.button.y;

                // Verifica se o clique está em algum botão
                for (int i = 0; i < 4; i++) {
                    SDL_Rect r = botoes[i].rect;
                    if (x >= r.x && x <= r.x + r.w &&
                        y >= r.y && y <= r.y + r.h) {
                        escolha = botoes[i].opcao;
                        selecionando = false;
                        break;
                    }
                }
            }
        }

        // Renderizar a tela de dificuldade
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, menuTex, NULL, NULL);

        // Opcional: desenhar bordas de debug dos botões
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (int i = 0; i < 4; i++) {
            SDL_RenderDrawRect(renderer, &botoes[i].rect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(menuTex);
    return escolha;
}
