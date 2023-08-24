# Compiler settings
CC:=cc
CFLAGS:=-Wall -Wextra -pedantic -O3 -std=c99
DEBUG_CFLAGS:=-Wall -Wextra -pedantic -g -std=c99

# Linker settings
OPENGL_LIBS=-lGL
## Static
GLFW_LIBS=-lglfw -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp
## Dynamic
GLFW_LIBS_DYNAMIC=-lglfw

BIN_DIR:=bin