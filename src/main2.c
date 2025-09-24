#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
//#include "Texture.h"
#include "Texture.h"

#ifdef _WIN32
    #include "BOT.h"
    void wait(int s) { SDL_Delay(s * 1000); }
#else
    #include <unistd.h>
    #include "BOT.h"
    void wait(int s) { sleep(s); }
#endif

int M[3][3], vencedor, numJogadas;
int a,b;
char menu, Primeiro, Dificuldade='0';



void inicializa_Jogo(){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            M[i][j]=0;
    vencedor = 0;
    numJogadas = 0;
}


int verifica(){
    for (int i=0;i<3;i++){
        if (M[i][0] && M[i][0]==M[i][1] && M[i][1]==M[i][2]) return M[i][0];
        if (M[0][i] && M[0][i]==M[1][i] && M[1][i]==M[2][i]) return M[0][i];
    }
    if (M[0][0] && M[0][0]==M[1][1] && M[1][1]==M[2][2]) return M[0][0];
    if (M[0][2] && M[0][2]==M[1][1] && M[1][1]==M[2][0]) return M[0][2];
    return 0;
}

void joga1(){
    int i,j;
    bool feito=false;
    do {
        if (Primeiro=='2' || Primeiro=='3'){
            // Jogador humano via clique
            SDL_Event e;
            while (SDL_WaitEvent(&e)){
                if (e.type==SDL_QUIT) exit(0);
                if (e.type==SDL_MOUSEBUTTONDOWN && e.button.button==SDL_BUTTON_LEFT){
                    int cellSize = SIZE / CELLS;
                    j = e.button.x / cellSize + 1;
                    i = e.button.y / cellSize + 1;
                    if (M[i-1][j-1]==0){ M[i-1][j-1]=1; feito=true; break; }
                }
            }
        } else {
            bool chance=false;
            Primeiro_Jogador(&i,&j,numJogadas,M,a,b,chance,Dificuldade);
            wait(1);
            if (M[i-1][j-1]==0){ M[i-1][j-1]=1; feito=true; }
            
        }
        renderiza();
    } while(!feito);
    a=i; b=j;
}

void joga2(){
    int i,j;
    bool feito=false;
    do {
        if (Primeiro=='1' || Primeiro=='3'){
            // Jogador humano via clique
            SDL_Event e;
            while (SDL_WaitEvent(&e)){
                if (e.type==SDL_QUIT) exit(0);
                if (e.type==SDL_MOUSEBUTTONDOWN && e.button.button==SDL_BUTTON_LEFT){
                    int cellSize = SIZE / CELLS;
                    j = e.button.x / cellSize + 1;
                    i = e.button.y / cellSize + 1;
                    if (M[i-1][j-1]==0){ M[i-1][j-1]=2; feito=true; break; }
                }
            }
        } else {
            bool chance=false;
            Segundo_Jogador(&i,&j,numJogadas,M,a,b,chance,Dificuldade);
            wait(1);
            if (M[i-1][j-1]==0){ M[i-1][j-1]=2; feito=true; }
        }
        renderiza();
    } while(!feito);
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    if (SDL_Init(SDL_INIT_VIDEO)!=0){ printf("Erro SDL:%s\n",SDL_GetError()); return 1; }
    if (!(IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG)&(IMG_INIT_PNG|IMG_INIT_JPG))){ printf("Erro IMG:%s\n",IMG_GetError()); return 1; }
    if (TTF_Init()==-1){ printf("Erro TTF:%s\n",TTF_GetError()); return 1; }

    window = SDL_CreateWindow("Jogo da Velha", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SIZE, SIZE+100, SDL_WINDOW_SHOWN);
    if (!window) { printf("Erro ao criar janela: %s\n", SDL_GetError()); return 1; }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) { printf("Erro ao criar renderer: %s\n", SDL_GetError()); return 1; }

    font = TTF_OpenFont("C:/Jogo-da-Velha/build/bin/DejaVuSans.ttf",28);
    //if (!font) { printf("Erro ao carregar fonte: %s\n", TTF_GetError()); return 1; }

    bool rodando = true;
    while (rodando) {
        SDL_SetWindowSize(window, SIZE, SIZE+100);
        int escolha = mostraMenu(renderer);

        switch (escolha) {
            case 1: Primeiro = '3'; break; // Jogador x Jogador
            case 2: Primeiro = '2'; break; // Jogador x Bot
            case 3: Primeiro = '1'; break; // Bot x Jogador
            case 4: { // Menu de Dificuldades
                SDL_SetWindowSize(window, SIZE, SIZE+100);
                int dif = MenuDificuldade(renderer);
                switch (dif) {
                    case 1: Dificuldade = '0'; break; // Fácil
                    case 2: Dificuldade = '1'; break; // Médio
                    case 3: Dificuldade = '2'; break; // Impossível
                    case 4: default: break; // Voltar ao menu inicial
                }
                continue; // Volta ao menu inicial sem iniciar partida
            }
            case 5: rodando = false; continue;
        }

        SDL_SetWindowSize(window, SIZE, SIZE);

        SDL_Surface* boardSurf=IMG_Load("C:/Jogo-da-Velha/Image/Jogo_Da_Velha.jpg");
        SDL_Surface* xSurf=IMG_Load("C:/Jogo-da-Velha/Image/Jogador_1.png");
        SDL_Surface* oSurf=IMG_Load("C:/Jogo-da-Velha/Image/Jogador_2.png");
        if (!boardSurf || !xSurf || !oSurf) {
            printf("Erro ao carregar imagens: %s\n", IMG_GetError());
            rodando = false; break;
        }
        boardTex=SDL_CreateTextureFromSurface(renderer,boardSurf);
        xTex=SDL_CreateTextureFromSurface(renderer,xSurf);
        oTex=SDL_CreateTextureFromSurface(renderer,oSurf);
        SDL_FreeSurface(boardSurf); SDL_FreeSurface(xSurf); SDL_FreeSurface(oSurf);

        inicializa_Jogo();
        renderiza();
        vencedor=verifica();

        while(vencedor==0){
            joga1();
            numJogadas++;
            vencedor=verifica();
            if(vencedor==1) break;
            if(numJogadas==9) break;
            numJogadas++;
            joga2();
            vencedor=verifica();
            if(vencedor==2) break;
        }

        char msg[64];
        if(vencedor==1 && Primeiro=='1') snprintf(msg,sizeof(msg),"BOT vence!");
        else if(vencedor==1 && Primeiro=='2') snprintf(msg,sizeof(msg),"Jogador vence!");
        else if(vencedor==2 && Primeiro=='1') snprintf(msg,sizeof(msg),"Jogador vence!");
        else if(vencedor==2 && Primeiro=='2') snprintf(msg,sizeof(msg),"BOT vence!");
        else if(vencedor==1 && Primeiro=='3') snprintf(msg,sizeof(msg),"Jogador 1 vence!");
        else if(vencedor==2 && Primeiro=='3') snprintf(msg,sizeof(msg),"Jogador 2 vence!");
        else snprintf(msg,sizeof(msg),"Empate!");
        SDL_Color color={255,0,0,255};
        SDL_Surface* surf=TTF_RenderText_Solid(font,msg,color);
        SDL_Texture* tex=SDL_CreateTextureFromSurface(renderer,surf);
        int tw,th; SDL_QueryTexture(tex,NULL,NULL,&tw,&th);
        SDL_Rect rect={(SIZE-tw)/2,(SIZE-th)/2,tw,th};
        SDL_RenderCopy(renderer,tex,NULL,&rect);
        SDL_RenderPresent(renderer);
        SDL_FreeSurface(surf); SDL_DestroyTexture(tex);

        SDL_Event e; bool esperar=true;
        while(esperar){
            while(SDL_PollEvent(&e)){
                if(e.type==SDL_QUIT){ rodando=false; esperar=false; }
                if(e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_SPACE) esperar=false;
            }
        }

        SDL_DestroyTexture(boardTex);
        SDL_DestroyTexture(xTex);
        SDL_DestroyTexture(oTex);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit(); IMG_Quit(); SDL_Quit();
    return 0;
}