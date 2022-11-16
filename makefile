# Defining constants.
CC = gcc
CFLAG = -I ./include -Wall -Wextra -Wno-unused-value -g -fcompare-debug-second
CMD = $(CC) $(CFLAG)
OUT = build

SRC = $(wildcard ./src/*.c)
_OBJ = $(subst ./src/,$(OUT)/objects/,$(SRC))
OBJ = $(_OBJ:.c=.o)
DIR_GUARD=@mkdir -p $(@D)

all: $(OBJ)	
	$(DIR_GUARD)

	$(info creating shared object)
	@$(CMD) -shared -o $(OUT)/libcpy.so $(OBJ)
	
	$(info creating static library)
	@ar rcs $(OUT)/libcpy.a $(OBJ)


$(OUT)/objects/%.o: ./src/%.c
	$(DIR_GUARD)

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
	@$(CMD) -static -L $(OUT) -o $(OUT)/a.out $(file) -lcpy
endif
	$(info running script)
	@LD_LIBRARY_PATH=$(OUT) $(OUT)/a.out


clean:
	@rm $(OBJ)
	@rm $(OUT)/libcpy.a
	@rm $(OUT)/libcpy.so
	@rmdir $(OUT)/objects
	@rmdir $(OUT)
	$(info cleaned up)

.PHONY: clean
