LIBPATH = D:/SDL/include
LNKPATH = D:/SDL/mingw/lib/x64
CFLAGS = -std=c++17 -m64 -Wall -Wextra -Wpedantic
LIBS = obj/Music.o obj/Sprite.o obj/State.o obj/Game.o obj/GameObject.o obj/Rect.o obj/Vec2.o obj/Sound.o obj/Face.o obj/TileSet.o obj/TileMap.o obj/Resources.o

#-mwindows = noconsole
main: $(LIBS)
	g++ $(CFLAGS) -I$(LIBPATH) -obin/game.exe src/main.cpp $(LIBS) -L$(LNKPATH) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

obj/Music.o: src/Music.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/Music.o src/Music.cpp

obj/Sprite.o: src/Sprite.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/Sprite.o src/Sprite.cpp

obj/State.o: src/State.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/State.o src/State.cpp

obj/Game.o: src/Game.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/Game.o src/Game.cpp

obj/GameObject.o: src/GameObject.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/GameObject.o src/GameObject.cpp

obj/Rect.o:
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/Rect.o src/Rect.cpp

obj/Vec2.o:
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/Vec2.o src/Vec2.cpp

obj/Sound.o:
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/Sound.o src/Sound.cpp

 obj/Face.o:
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/Face.o src/Face.cpp

obj/TileSet.o:
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/TileSet.o src/TileSet.cpp

obj/TileMap.o:
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/TileMap.o src/TileMap.cpp

obj/Resources.o:
	g++ $(CFLAGS) -I$(LIBPATH) -c -oobj/Resources.o src/Resources.cpp

.PHONY: clean
clean:
	for /F %%i in ('dir /b obj') do (echo removing file %%i && del obj\%%i)
