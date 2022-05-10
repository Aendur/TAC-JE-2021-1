# TAC-JE-2021-1

Repositório do trabalho 1 da disciplina de TAC - turma JE - 2021/1 da UnB

Autor: Diogo César Ferreira - 11/0027931

O projeto pode ser compilado utilizando o Makefile existente no repositório, ou pela linha de comando utilizando:

```g++ -std=c++17 -m64 -I"<SDL headers path>" -o bin/game.exe src/main.cpp src/Music.cpp src/Sprite.cpp src/State.cpp src/Game.cpp -L"<SDL library path>" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer```

**Atenção:** se for utilizar o Makefile, editar as variáveis LIBPATH e LNKPATH conforme a configuração do SDL no seu sistema
- `LIBPATH` = *diretório contendo os headers do SDL*
- `LNKPATH` = *diretório contendo as bibliotecas do SDL*

*Para previnir o aparecimento do console, utilizar a flag `-mwindows` ao final da linha de comando.*

Ao compilar, será criado um arquivo `game.exe` na pasta `bin/`, a qual deve conter os DLLs necessários para a execução do programa (64 bits), caso o sistema não esteja configurado para localizá-los automaticamente.

O projeto foi desenvolvido utilizando:
- SDL 2.0.16 (mingw 64-bit)
- SDL Image 2.0.5 (mingw 64-bit)
- SDL Mixer 2.0.4 (mingw 64-bit)
- Compilador: TDM-GCC (tdm64-1) 10.3.0
- Sistema operacional Windows 10

As outras fases do trabalho podem ser acessadas através dos links a seguir, ou verificando-se os seus respectivos *branches* T1 a T7.
- [Parte 7 (última)](https://github.com/Aendur/TAC-JE-2021-1/tree/T7)
- [Parte 6](https://github.com/Aendur/TAC-JE-2021-1/tree/T6)
- [Parte 5](https://github.com/Aendur/TAC-JE-2021-1/tree/T5)
- [Parte 4](https://github.com/Aendur/TAC-JE-2021-1/tree/T4)
- [Parte 3](https://github.com/Aendur/TAC-JE-2021-1/tree/T3)
- [Parte 2](https://github.com/Aendur/TAC-JE-2021-1/tree/T2)
- [Parte 1](https://github.com/Aendur/TAC-JE-2021-1/tree/T1)


