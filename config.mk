# Compiler settings
CC:=cc
FREETYPE_CFLAGS:=-I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -I/usr/include/sysprof-4 -pthread
CFLAGS:=-Wall -Wextra -pedantic -O3 -std=c99 -I./src ${FREETYPE_CFLAGS}
CFLAGS_DEBUG:=-Wall -Wextra -pedantic -g -std=c99 -I./src ${FREETYPE_CFLAGS}

# Generic libs
LIBS=-lm -lpthread -lfreetype

# Linker settings
OPENGL_LIBS=-lGL
#OPENGL_LIBS=-framework OpenGL # MacOS

## Static
GLFW_LIBS=-lglfw -ldl -lX11 -lxcb -lXau -lXdmcp
## Dynamic
GLFW_LIBS_DYNAMIC=-lglfw

# Lua library
LUA_LIBS=-llua

BIN_DIR:=bin
