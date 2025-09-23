@echo off
gcc src/main2.c src/Primeiro_Jogador.c src/Segundo_Jogador.c src/Texture.c Icone/icon.o ^
-IC:\Jogo-da-Velha\inc ^
-IC:\Jogo-da-Velha\inc\SDL ^
-LC:\Jogo-da-Velha\build\lib ^
-o build\bin\Jogo-da-Velha.exe ^
-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

:: Criar atalho para o executável na Área de Trabalho
powershell -command "$desktop = [Environment]::GetFolderPath('Desktop'); $s=(New-Object -COM WScript.Shell).CreateShortcut(\"$desktop\Jogo-da-Velha.lnk\"); $s.TargetPath='C:\Jogo-da-Velha\build\bin\Jogo-da-Velha.exe'; $s.WorkingDirectory='C:\Jogo-da-Velha\build'; $s.IconLocation='C:\Jogo-da-Velha\Image\JV.ico'; $s.Save()"
