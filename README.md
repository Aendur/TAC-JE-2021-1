# TAC-JE-2021-1

Repositório do trabalho da discipline de TAC - turma JE - 2021/1 da UnB
<br>*Este branch é referente ao **Trabalho 4**.*

Autor: Diogo César Ferreira - 11/0027931

O projeto pode ser compilado utilizando o Makefile existente no repositório.<br>
**Atenção:** editar as variáveis LIBPATH e LNKPATH conforme a configuração do SDL no seu sistema
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

