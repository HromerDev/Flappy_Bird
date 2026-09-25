CFLAGS = -Iinclude -I/include

LDFLAGS_LINUX = -Llib -lraylib_Linux -lGL -lm -lpthread -ldl -lrt -lX11 -fsanitize=address
LDFLAGS_WINDOWS = -Llib -lraylib_Windows -lopengl32 -lgdi32 -lwinmm -lm

SRCS = src/*.c scripts/*.c

OUTPUTLINUX = builds/linux/
OUTPUTWINDOWS = builds/windows/

GAMENAME = main

default:
	gcc $(SRCS) $(CFLAGS) -o $(GAMENAME) $(LDFLAGS_LINUX)

windows:
	x86_64-w64-mingw32-gcc $(SRCS) $(CFLAGS) -o $(GAMENAME).exe $(LDFLAGS_WINDOWS)