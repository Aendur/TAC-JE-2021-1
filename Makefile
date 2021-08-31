LIBPATH = D:/SDL/include
LNKPATH = D:/SDL/mingw/lib/x64
CFLAGS = -std=c++17 -m64 -Wall -Wextra -Wpedantic

#-mwindows = noconsole
main: obj/Music.o obj/Sprite.o obj/State.o obj/Game.o
	g++ $(CFLAGS) -I$(LIBPATH) -obin/a.exe src/main.cpp obj/Music.o obj/Sprite.o obj/State.o obj/Game.o -L$(LNKPATH) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

obj/Music.o: src/Music.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/Music.o src/Music.cpp

obj/Sprite.o: src/Sprite.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/Sprite.o src/Sprite.cpp

obj/State.o: src/State.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/State.o src/State.cpp

obj/Game.o: src/Game.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/Game.o src/Game.cpp

clean:
	del /q obj\*