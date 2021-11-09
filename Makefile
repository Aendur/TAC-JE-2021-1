# LIBPATH and LNKPATH must be set according to where SDL is located in your system
LIBPATH = D:/SDL/include
LNKPATH = D:/SDL/mingw/lib/x64

#####
CFLAGS = -std=c++17 -m64 -Wall -Wextra -Wpedantic
LIBS = $(patsubst src/%.cpp,obj/%.o,$(filter-out src/main.cpp,$(wildcard src/*.cpp)))
SDLLFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

#-mwindows = noconsole
main: $(LIBS)
	g++ $(CFLAGS) -I$(LIBPATH) -Iinclude -obin/game.exe src/main.cpp $(LIBS) -L$(LNKPATH) $(SDLLFLAGS)

obj/%.o: src/%.cpp include/%.h
	g++ $(CFLAGS) -I$(LIBPATH) -Iinclude -c -o$@ $<

unittest_tilemap: CFLAGS += -DUNITTEST -DUNITTEST_TILEMAP
unittest_tilemap: obj/TileMap.o obj/GameObject.o obj/Rect.o
	g++ -I$(LIBPATH) -o tests/test.exe $^ -L$(LNKPATH) $(SDLLFLAGS)

.PHONY: clean
clean:
	for /F %%i in ('dir /b obj') do (echo removing file %%i && del obj\%%i)

