#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\DEV\PC\c++\libraries\SFML-2.5.1_mingw_32bit\include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\DEV\PC\c++\libraries\SFML-2.5.1_mingw_32bit\lib

DEFINES = -DSFML_STATIC

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -O3 -std=c++11 -static -static-libgcc -static-libstdc++

LIBRARIES =	-l sfml-graphics-s\
				-l sfml-window-s\
				-l sfml-audio-s\
				-l sfml-network-s\
				-l sfml-system-s\
				-l winmm\
				-l ws2_32\
				-l ogg\
				-l vorbis\
				-l vorbisfile\
				-l vorbisenc\
				-l flac\
				-l openal32\
				-l gdi32\
				-l freetype\
				-l opengl32\
#This is the target that compiles our executable

default: build

build:
	g++ *.cpp -o app.exe $(DEFINES) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LIBRARIES)
