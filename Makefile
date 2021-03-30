CFLAGS := -Wall -Werror -lm -fsanitize=undefined -fsanitize=address
INCLUDE:= -I./include
SRC  := ./source
BIN  := ./include
SRCS := $(wildcard $(SRC)/*.cpp)
OBJ  := $(SRCS:.cpp=.o)
EXEC := bin/main
.PHONY: all clean
.SUFFIXES: .cpp .o
all: $(EXEC) bin
	
bin:
	mkdir bin
	
$(EXEC): $(OBJ)
	g++ $(CFLAGS) $(INCLUDE) $(OBJ) -o $@
	
.cpp.o:
	g++ -c $(CFLAGS) $(INCLUDE) $< -o $@
	
clean:
	rm -r bin
