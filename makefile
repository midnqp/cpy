# Defining constants.
CC = gcc
CFLAG = -I ./include -Wall -Wextra -Wno-unused-value -g -fcompare-debug-second
CMD = $(CC) $(CFLAG)
OUT = build

SRC = $(wildcard ./src/*.c)
_OBJ = $(subst ./src/,$(OUT)/objects/,$(SRC))
OBJ = $(_OBJ:.c=.o)




all: $(OBJ)
	
	@if [ ! -d "$(OUT)" ]; then\
		mkdir -p $(OUT)/objects;\
	fi

	$(info creating shared object)
	@$(CMD) -shared -o $(OUT)/libcpy.so $(OBJ)
	
	$(info creating static library)
	@ar rcs $(OUT)/libcpy.a $(OBJ)


$(OUT)/objects/%.o: ./src/%.c
	$(info compiling $^)
	@$(CMD) -c -fpic -o $@ $^


script: all

ifeq ($(file),)
	$(info script file is empty)
	exit 1
endif

ifeq ($(link),shared)
	$(info compiling script dynamically)
	@$(CMD) -fsanitize=address -L $(OUT) -o $(OUT)/a.out $(file) -lcpy
else ifeq ($(link),static)
	$(info compiling script statically)
	@$(CMD) -static -L $(OUT) -o $(OUT)/a.out -lcpy
endif
	$(info running script)
	@LD_LIBRARY_PATH=$(OUT) $(OUT)/a.out
