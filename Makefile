SRC    = $(wildcard *.c)
OBJ    = $(SRC:%.c=%.o)
BIN    = sheep

CC     = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

.PHONY: all clean format

all: $(BIN)

clean:
	rm -f $(BIN) $(OBJ)

format:
	find . -name "*.[ch]" | xargs clang-format -i -style=file

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -lncursesw -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $<

