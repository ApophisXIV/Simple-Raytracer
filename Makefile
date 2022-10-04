INC_PATH = ./inc
SRC_PATH = ./src
BUILD_PATH = ./build
OBJ_PATH = $(BUILD_PATH)/obj

PROGRAM = raytracer
PROGRAM_IMG_DIMENSIONS = 640 480
RECURSION_DEPTH = 5
PROGRAM_OUTPUT_IMAGE_PPM = imagen.ppm
PROGRAM_OUTPUT_IMAGE_BMP = imagen.bmp
CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -Werror -g -O0 -I $(INC_PATH)
LDFLAGS = -lm

SRC_FILES = $(shell find $(SRC_PATH) -name '*.c')
OBJ_FILES = $(subst $(SRC_PATH),$(OBJ_PATH),$(SRC_FILES:.c=.o))
DEP_FILES = $(subst $(SRC_PATH),$(OBJ_PATH),$(SRC_FILES:.c=.d))

# Lista de directorios donde buscar los archivos .c y .o (https://www.gnu.org/software/make/manual/html_node/General-Search.html)
vpath %.c $(SRC_PATH):$(SRC_PATH)/core:$(SRC_PATH)/core/formats:$(SRC_PATH)/core/scene:$(SRC_PATH)/core/shapes:$(SRC_PATH)/core/utils
vpath %.o $(OBJ_PATH):$(OBJ_PATH)/core:$(OBJ_PATH)/core/formats:$(OBJ_PATH)/core/scene:$(OBJ_PATH)/core/shapes:$(OBJ_PATH)/core/utils

#Patterns Rules (https://www.gnu.org/software/make/manual/html_node/Pattern-Rules.html)
%.o: %.c
	@echo -e '\033[1;33m=============================================================================\033[0m'
	@echo -e '\033[1;41m --> \033[0;1;34m Compilando: \033[0m \033[1;33m $< \033[0m\033[0m'
	@echo -e '\033[1;33m=============================================================================\033[0m'
	@mkdir -p $(dir $(OBJ_FILES))
	$(CC) $(CFLAGS) -c $< -o $(subst $(SRC_PATH),$(OBJ_PATH),$(dir $<))$@
	@echo -e '\033[0;1;36m -> Generando dependencias: \033[0m'
	$(CC) $(CFLAGS) -MM $< > $(subst $(SRC_PATH),$(OBJ_PATH),$(dir $<))$(@:.o=.d)
	@echo -e '\033[1;33m=============================================================================\n\033[0m'

$(PROGRAM): $(notdir $(OBJ_FILES))
	@echo -e '\033[1;33m=============================================================================\033[0m'
	@echo -e '\033[1;41m --> \033[0;1;34m Linkeando: \033[0m \033[1;33m $@ \033[0m\033[0m'
	@echo -e '\033[1;33m=============================================================================\033[0m'
	$(CC) $(OBJ_FILES) -o $(PROGRAM) $(LDFLAGS)
	@echo -e '\033[1;33m=============================================================================\n\033[0m'

clean:
	@echo -e '\033[1;33m=============================================================================\033[0m'
	@echo -e '\033[1;41m --> \033[0;1;34m Limpiando el directorio... \033[0m'
	@echo -e '\033[1;33m=============================================================================\033[0m'
	@echo -e '\033[1;41m Borrando archivos \033[0m'
	rm -f $(OBJ_FILES)
	rm -f $(DEP_FILES)
	rm -f $(PROGRAM)
	@echo -e '\033[1;33m=============================================================================\n\033[0m'

run_ppm: $(PROGRAM)
	@echo -e '\033[1;36m=============================================================================\033[0m'
	@echo -e '\033[1;41m --> \033[0;1;34m Ejecutando: \033[0m \033[1;35m $(PROGRAM) \033[0m\033[0m'
	@echo -e '\033[1;36m=============================================================================\033[0m'
	./$(PROGRAM) $(PROGRAM_IMG_DIMENSIONS) $(RECURSION_DEPTH) $(PROGRAM_OUTPUT_IMAGE_PPM)
	@echo -e '\n\033[1;36m=============================================================================\033[0m'
	@echo -e '\033[1;41m --> \033[0;1;34m Abriendo resultado: \033[0m \033[1;35m $(PROGRAM_OUTPUT_IMAGE_PPM) \033[0m\033[0m'
	@echo -e '\033[1;36m=============================================================================\n\033[0m'
	eog $(PROGRAM_OUTPUT_IMAGE_PPM)

run_bmp: $(PROGRAM)
	@echo -e '\033[1;36m=============================================================================\033[0m'
	@echo -e '\033[1;41m --> \033[0;1;34m Ejecutando: \033[0m \033[1;35m $(PROGRAM) \033[0m\033[0m'
	@echo -e '\033[1;36m=============================================================================\033[0m'
	./$(PROGRAM) $(PROGRAM_IMG_DIMENSIONS) $(RECURSION_DEPTH) $(PROGRAM_OUTPUT_IMAGE_BMP)
	@echo -e '\n\033[1;36m=============================================================================\033[0m'
	@echo -e '\033[1;41m --> \033[0;1;34m Abriendo resultado: \033[0m \033[1;35m $(PROGRAM_OUTPUT_IMAGE_BMP) \033[0m\033[0m'
	@echo -e '\033[1;36m=============================================================================\n\033[0m'
	eog $(PROGRAM_OUTPUT_IMAGE_BMP)

leak-test: $(PROGRAM)
	@echo -e '\033[1;36m=============================================================================\033[0m'
	@echo -e '\033[1;41m --> \033[0;1;34m Ejecutando: \033[0m \033[1;35m $(notdir $<) \033[0m\033[0m'
	@echo -e '\033[1;36m=============================================================================\033[0m'
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(PROGRAM) $(PROGRAM_IMG_DIMENSIONS) 0 $(PROGRAM_OUTPUT_IMAGE_PPM) 2> valgrind.log
	@echo -e '\n\033[1;36m=============================================================================\033[0m'
	@echo -e '\033[1;41m --> \033[0;1;34m Verificando leaks: \033[0m'
	@echo -e '\033[1;36m=============================================================================\033[0m'
	@if grep -q -c "ERROR SUMMARY: 0 errors" valgrind.log; then \
		echo '\033[1;41m --> \033[0;1;34m No hay leaks! \033[0m'; \
		echo '\033[1;36m=============================================================================\033[0m'; \
	else \
		echo '\033[0;1;31m Hay leaks! \033[0m'; \
		echo '\033[0;1;34m Verificar: \033[0m \033[1;35m valgrind.log \033[0m\033[0m'; \
		echo '\033[1;36m=============================================================================\033[0m'; \
	fi

debug: $(PROGRAM)
	@echo -e '\033[1;36m=============================================================================\033[0m'
	@echo -e '\033[1;41m --> \033[0;1;34m Ejecutando debug: \033[0m \033[1;35m $(notdir $<) \033[0m\033[0m'
	@echo -e '\033[1;36m=============================================================================\033[0m'
	gdb --args ./$(PROGRAM) $(PROGRAM_IMG_DIMENSIONS) $(RECURSION_DEPTH) $(PROGRAM_OUTPUT_IMAGE_PPM)
	@echo -e '\033[1;36m=============================================================================\n\033[0m'

test_no_reflex: $(PROGRAM)
	@echo -e '\033[1;36m=============================================================================\033[0m'
	@echo -e '\033[1;41m --> \033[0;1;34m Ejecutando prueba sin reflejos: \033[0m \033[1;35m $(notdir $<) \033[0m\033[0m'
	@echo -e '\033[1;36m=============================================================================\033[0m'
	./$(PROGRAM) $(PROGRAM_IMG_DIMENSIONS) 0 $(PROGRAM_OUTPUT_IMAGE_PPM)
	@echo -e '\033[1;36m=============================================================================\n\033[0m'

info:
	@echo -e '\033[1;33m=============================================================================\033[0m'
	@echo -e '\033[1;41m --> \033[0;1;34m Variables: \033[0m'
	@echo -e '\033[1;33m=============================================================================\033[0m'
	@echo -e '\033[4;32m'SRC_PATH:'\033[0m ' $(SRC_PATH)
	@echo -e '\033[4;32m'INC_PATH:'\033[0m ' $(INC_PATH)
	@echo -e '\033[4;32m'BUILD_PATH:'\033[0m ' $(BUILD_PATH)
	@echo -e '\033[4;32m'OBJ_PATH:'\033[0m ' $(OBJ_PATH)
	@echo -e '\033[4;32m'SRC_FILES:'\033[0m ' $(SRC_FILES)
	@echo -e '\033[4;32m'OBJ_FILES:'\033[0m ' $(OBJ_FILES)
	@echo -e '\033[4;32m'DEP_FILES:'\033[0m ' $(DEP_FILES)
	@echo -e '\033[4;32m'PROGRAM:'\033[0m ' $(PROGRAM)
	@echo -e '\n\033[1;33m=============================================================================\033[0m'
