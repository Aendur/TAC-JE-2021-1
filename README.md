# TAC-JE-2021-1

Repositório do trabalho 1 da discipline de TAC - turma JE - 2021/1 da UnB

Autor: Diogo César Ferreira - 11/0027931

O projeto pode ser compilado utilizando o Makefile existente no repositório, ou pela linha de comando utilizando:

```g++ -std=c++17 -m64 -I"<SDL headers path>" -o bin/game.exe src/main.cpp src/Music.cpp src/Sprite.cpp src/State.cpp src/Game.cpp -L"<SDL library path>" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer```

  
**Atenção:** se for utilizar o Makefile, editar as variáveis LIBPATH e LNKPATH conforme a configuração do SDL no seu sistema
- LIBPATH = *diretório contendo os headers do SDL*
- LNKPATH = *diretório contendo as bibliotecas do SDL*

O projeto foi desenvolvido utilizando as bibliotecas do SDL mingw 64 bits, com o compilador TDM-GCC (tdm64-1) 10.3.0

Para previnir o aparecimento do console, utilizar a flag -mwindows ao final da linha de comando.
