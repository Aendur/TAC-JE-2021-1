# SDL_INCLUDE_PATH and SDL_LIB_PATH must be set according to where SDL is located in your system
#SDL_INCLUDE_PATH=
#SDL_LIB_PATH=

#####
SRCDIR=src
HEADIR=include
OBJDIR=obj
MAIN=src\main.cpp
PROJ_LIBS= Alien Bullet Camera CameraFollower Collider Game GameObject InputManager Minion Music PenguinBody PenguinCannon Rect Resources Sound Sprite State TileMap TileSet Vec2
LIBS=$(patsubst %,obj\\%.obj,$(PROJ_LIBS))
CFLAGS=/W4 /EHsc /std:c++20 /I$(HEADIR) /I$(SDL_INCLUDE_PATH) /utf-8 /nologo
SDL_LIBS=SDL2main SDL2 SDL2_image SDL2_mixer

# /SUBSYSTEM:WINDOWS hides the console, /SUBSYSTEM:CONSOLE shows it
#LINKFLAGS=/link /SUBSYSTEM:WINDOWS /LIBPATH:$(OBJDIR) /LIBPATH:$(SDL_LIB_PATH) $(PROJ_LIBS) $(patsubst %,%.lib,$(SDL_LIBS)) shell32.lib
LINKFLAGS=/link /SUBSYSTEM:CONSOLE /LIBPATH:$(OBJDIR) /LIBPATH:$(SDL_LIB_PATH) $(PROJ_LIBS) $(patsubst %,%.lib,$(SDL_LIBS)) shell32.lib

bin\main.exe: dirs $(MAIN) $(LIBS)
	cl $(CFLAGS) /Fo:obj\ /Fe:bin\game.exe $(MAIN) $(LINKFLAGS)

{src\}.cpp{obj\}.obj:
	cl $(CFLAGS) /c /Fo:obj\ $<

remake: clean bin\main.exe

dirs:
	(IF NOT EXIST obj (MKDIR obj))
.PHONY: dirs

clean:
	FOR %I IN (obj\*) DO @((echo Removing file %I) & (del %I))
	IF EXIST obj (rmdir obj)
.PHONY: clean

