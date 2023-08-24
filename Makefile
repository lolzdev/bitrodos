include config.mk

SRC:=src/main.c \
	 src/log.c \
	 src/window.c
OBJ:=$(SRC:.c=.o)

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
