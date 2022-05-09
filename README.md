# TAC-JE-2021-1

Repositório do trabalho da discipline de TAC - turma JE - 2021/1 da UnB
<br>*Este branch é referente à **(Parte 7)** do trabalho.*

Autor: Diogo César Ferreira - 11/0027931

**Desde a parte 5, o projeto passou a utilizar o compilador MSVC do Windows.**

As ferramentas necessárias para compilar o projeto podem ser obtidas na [página de downloads do Visual Studio](https://visualstudio.microsoft.com/downloads/).
Não é necessário realizar a instalação completa do Visual Studio, apenas das [Build tools](https://aka.ms/vs/17/release/vs_BuildTools.exe), a partir das
quais o ambiente de desenvolvimento no Windows poderá ser acessado através do Prompt de Comando do Desenvolvedor (Developer Command Prompt).


O projeto pode ser compilado utilizando o Makefile existente no repositório, através do comando `nmake`.<br>
**Atenção:** editar as variáveis `SDL_INCLUDE_PATH` e `SDL_LIB_PATH` conforme a configuração do SDL no seu sistema
- `SDL_INCLUDE_PATH` = *diretório contendo os headers do SDL*
- `SDL_LIB_PATH` = *diretório contendo as bibliotecas do SDL*

*Para exibir o console, substituir a flag `/SUBSYSTEM:WINDOWS` por `/SUBSYSTEM:CONSOLE` na linha 23 do Makefile*

Ao compilar, será criado um arquivo `game.exe` na pasta `bin/`, a qual deve conter os DLLs necessários para a execução do programa (64 bits), caso o sistema não esteja configurado para localizá-los automaticamente.

O projeto foi desenvolvido utilizando:
- SDL 2.0.16 (MSVC 64-bit)
- SDL Image 2.0.5 (MSVC 64-bit)
- SDL Mixer 2.0.4 (MSVC 64-bit)
- Compilador: MSVC 19.31.31107 (x64)
- Sistema operacional Windows 10+

