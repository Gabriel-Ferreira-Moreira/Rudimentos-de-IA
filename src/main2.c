#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/Texture.h"

#ifdef _WIN32
    #include <windows.h>
    #include "C:\\Jogo-da-Velha\\inc\\Primeiro_Jogador.h"
    #include "C:\\Jogo-da-Velha\\inc\\Segundo_Jogador.h"
    void wait(int s) { Sleep(s * 1000); }
#else
    #include <unistd.h>
    #include "../inc/Primeiro_Jogador.h"
    #include "../inc/Segundo_Jogador.h"
    void wait(int s) { sleep(s); }
#endif

int M[3][3], vencedor = 0, numJogadas = 0;
int a,b;
char menu, Primeiro;

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
        if (Primeiro=='2'){
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
            Primeiro_Jogador(&i,&j,numJogadas,M,a,b,chance);
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
        if (Primeiro=='1'){
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
            Segundo_Jogador(&i,&j,numJogadas,M,a,b,chance);
            wait(1);
            if (M[i-1][j-1]==0){ M[i-1][j-1]=2; feito=true; }
        }
        renderiza();
    } while(!feito);
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    printf("Quem comeca jogando?\n1 - BOT\n2 - JOGADOR\n");
    scanf(" %c",&Primeiro);

    // SDL Init
    if (SDL_Init(SDL_INIT_VIDEO)!=0){ printf("Erro SDL:%s\n",SDL_GetError()); return 1; }
    if (!(IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG)&(IMG_INIT_PNG|IMG_INIT_JPG))){ printf("Erro IMG:%s\n",IMG_GetError()); return 1;}
    if (TTF_Init()==-1){ printf("Erro TTF:%s\n",TTF_GetError()); return 1; }

    window = SDL_CreateWindow("Jogo da Velha",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SIZE,SIZE,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface* boardSurf=IMG_Load("../Image/Jogo_Da_Velha.jpg");
    SDL_Surface* xSurf=IMG_Load("../Image/Jogador_1.png");
    SDL_Surface* oSurf=IMG_Load("../Image/Jogador_2.png");
    boardTex=SDL_CreateTextureFromSurface(renderer,boardSurf);
    xTex=SDL_CreateTextureFromSurface(renderer,xSurf);
    oTex=SDL_CreateTextureFromSurface(renderer,oSurf);
    SDL_FreeSurface(boardSurf); SDL_FreeSurface(xSurf); SDL_FreeSurface(oSurf);

    font=TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",28);

    inicializa_Jogo();
    renderiza();

    vencedor=verifica();

    while(vencedor==0){
        numJogadas++;
        joga1();
        vencedor=verifica();
        if(vencedor==1) break;
        if(numJogadas==9) break;

        numJogadas++;
        joga2();
        vencedor=verifica();
        if(vencedor==2) break;
    }

    // Exibir mensagem de fim
    char msg[64];
    if(vencedor==1 && Primeiro=='1') snprintf(msg,sizeof(msg),"BOT vence!");
    else if(vencedor==1 && Primeiro=='2') snprintf(msg,sizeof(msg),"Jogador vence!");
    else if(vencedor==2 && Primeiro=='1') snprintf(msg,sizeof(msg),"Jogador vence!");
    else if(vencedor==2 && Primeiro=='2') snprintf(msg,sizeof(msg),"BOT vence!");
    else snprintf(msg,sizeof(msg),"Empate!");
    SDL_Color color={255,0,0,255};
    SDL_Surface* surf=TTF_RenderText_Solid(font,msg,color);
    SDL_Texture* tex=SDL_CreateTextureFromSurface(renderer,surf);
    int tw,th; SDL_QueryTexture(tex,NULL,NULL,&tw,&th);
    SDL_Rect rect={(SIZE-tw)/2,(SIZE-th)/2,tw,th};
    SDL_RenderCopy(renderer,tex,NULL,&rect);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(surf); SDL_DestroyTexture(tex);

    // Espera espaço para sair
    SDL_Event e;
    bool esperar=true;
    while(esperar){
        while(SDL_PollEvent(&e)){
            if(e.type==SDL_QUIT) esperar=false;
            if(e.type==SDL_KEYDOWN && e.key.keysym.sym==SDLK_SPACE) esperar=false;
        }
    }

    // SDL Cleanup
    TTF_CloseFont(font);
    SDL_DestroyTexture(boardTex);
    SDL_DestroyTexture(xTex);
    SDL_DestroyTexture(oTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit(); IMG_Quit(); SDL_Quit();
    return 0;
}
