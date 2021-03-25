CFLAGS := -Wall -Werror -lm -fsanitize=undefined -fsanitize=address
INCLUDE:= -I./include
SRC  := ./source
BIN  := ./include
SRCS := $(wildcard $(SRC)/*.c)
EXEC := $(patsubst $(SRC)/%.c,$(BIN)/%,$(SRCS)) -- ЧТО ТО НЕ ТО
.PHONY: all clean
all: bin $(EXEC)
	
bin:
	mkdir bin
	
$(BIN)/%: $(SRC)/%.c
	@echo [Compiling]: $@
	gcc $(CFLAGS) $< $(INCLUDE) -o $@.o
	
	ЧТО ТО ДЛЯ МЭЙНА ?

clean:
	rm -r bin
