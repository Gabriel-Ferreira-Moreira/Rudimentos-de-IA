@echo off
gcc src/main2.c src/Primeiro_Jogador.c src/Segundo_Jogador.c src/Texture.c ^
-IC:\Jogo-da-Velha\inc ^
-LC:\libs\SDL2\SDL2\i686-w64-mingw32\lib ^
-LC:\libs\SDL2\SDL2_image\i686-w64-mingw32\lib ^
-LC:\libs\SDL2\SDL2_ttf\i686-w64-mingw32\lib ^
-o build\JogodaVelha.exe ^
-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf
