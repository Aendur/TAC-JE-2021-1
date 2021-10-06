# LIBPATH and LNKPATH must be set according to where SDL is located in your system
LIBPATH = D:/SDL/include
LNKPATH = D:/SDL/mingw/lib/x64

#####
CFLAGS = -std=c++17 -m64 -Wall -Wextra -Wpedantic
LIBS = obj/Music.o obj/Sprite.o obj/State.o obj/Game.o obj/GameObject.o obj/Rect.o obj/Vec2.o obj/Sound.o obj/Face.o obj/TileSet.o obj/TileMap.o obj/Resources.o
SDLLFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

#-mwindows = noconsole
main: $(LIBS)
	g++ $(CFLAGS) -I$(LIBPATH) -obin/game.exe src/main.cpp $(LIBS) -L$(LNKPATH) $(SDLLFLAGS) -mwindows

obj/Music.o: src/Music.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -o$@ $<

obj/Sprite.o: src/Sprite.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -o$@ $<

obj/State.o: src/State.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -o$@ $<

obj/Game.o: src/Game.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -o$@ $<

obj/GameObject.o: src/GameObject.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -o$@ $<

obj/Rect.o: src/Rect.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -o$@ $<

obj/Vec2.o: src/Vec2.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -o$@ $<

obj/Sound.o: src/Sound.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -o$@ $<

 obj/Face.o: src/Face.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -o$@ $<

obj/TileSet.o: src/TileSet.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -o$@ $<

obj/TileMap.o: src/TileMap.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -o$@ $<

obj/Resources.o: src/Resources.cpp
	g++ $(CFLAGS) -I$(LIBPATH) -c -o$@ $<

unittest_tilemap: CFLAGS += -DUNITTEST -DUNITTEST_TILEMAP
unittest_tilemap: obj/TileMap.o obj/GameObject.o obj/Rect.o
	g++ -I$(LIBPATH) -o tests/test.exe $^ -L$(LNKPATH) $(SDLLFLAGS)

.PHONY: clean
clean:
	for /F %%i in ('dir /b obj') do (echo removing file %%i && del obj\%%i)

