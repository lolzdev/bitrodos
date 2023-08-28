include config.mk

TESTS-IN:=$(wildcard tests/*.c)
TESTS:=$(TESTS-IN:.c=.test)
SRC:=src/main.c \
	 src/log.c \
	 src/window.c \
	 src/gl.c \
	 src/assets.c \
	 src/camera.c \
	 src/input.c \
	 src/hash.c \
	 src/mods.c \
	 src/registry.c \
	 src/math/linear.c \
	 src/rendering/renderer.c \
	 src/rendering/lua.c \
	 src/rendering/text.c \

OBJ:=$(SRC:.c=.o)
OBJ_TEST:=$(OBJ:src/main.o=)


all: ${BIN_DIR} $(OBJ)
	${CC} ${CFLAGS_DEBUG} ${LIBS} ${LUA_LIBS} ${OPENGL_LIBS} ${GLFW_LIBS_DYNAMIC} ${OBJ} -o ${BIN_DIR}/bitrodos

test: ${BIN_DIR} ${OBJ_TEST} ${TESTS}

%.o: %.c
	${CC} ${CFLAGS_DEBUG} -c $< -o $@

%.test: %.c
	@echo "running test $@..."
	@${CC} ${CFLAGS_DEBUG} ${LIBS} ${LUA_LIBS} ${OPENGL_LIBS} ${GLFW_LIBS_DYNAMIC} ${OBJ_TEST} $< -o ${BIN_DIR}/$@
	@${BIN_DIR}/$@ || (echo "failed"; exit 1)
	@echo OK

${BIN_DIR}:
	@mkdir -v ${BIN_DIR}
	@mkdir -v ${BIN_DIR}/tests

.PHONY: clean
clean:
	@rm -rfv ${BIN_DIR}
	@rm -rfv ${OBJ}
