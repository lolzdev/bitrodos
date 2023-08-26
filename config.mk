# Compiler settings
CC:=cc
CFLAGS:=-Wall -Wextra -pedantic -O3 -std=c99 -I./src
CFLAGS_DEBUG:=-Wall -Wextra -pedantic -g -std=c99 -I./src

# Generic libs
LIBS=-lm -lpthread -lrt
# Linker settings
OPENGL_LIBS=-lGL
## Static
GLFW_LIBS=-lglfw -ldl -lX11 -lxcb -lXau -lXdmcp
## Dynamic
GLFW_LIBS_DYNAMIC=-lglfw
# Lua library
LUA_LIBS=-llua

BIN_DIR:=bin
