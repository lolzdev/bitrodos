include config.mk

SRC:=src/main.c \
	 src/log.c \
	 src/window.c \
	 src/math/linear.c
OBJ:=$(SRC:.c=.o)
OBJ_TEST:=$(OBJ:main.o=test.o)

test: ${BIN_DIR} ${OBJ_TEST}
	@${CC} ${CFLAGS_DEBUG} ${OPENGL_LIBS} ${GLFW_LIBS_DYNAMIC} ${OBJ_TEST} -o ${BIN_DIR}/bitrodos_test
	@${BIN_DIR}/bitrodos_test

all: ${BIN_DIR} $(OBJ)
	${CC} ${CFLAGS_DEBUG} ${OPENGL_LIBS} ${GLFW_LIBS_DYNAMIC} ${OBJ} -o ${BIN_DIR}/bitrodos

%.o: %.c
	${CC} ${CFLAGS_DEBUG} -c $< -o $@

${BIN_DIR}:
	@mkdir -v ${BIN_DIR}

.PHONY: clean
clean:
	@rm -rfv ${BIN_DIR}
	@rm -rfv ${OBJ}
