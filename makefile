target := app
CC := gcc
CFLAGS := -g -Wall -Wextra -Wpedantic -std=c99
src := main.c str.c
obj := main.o str.o

all: $(target)

$(target): $(obj)
	$(CC) $(obj) -o $(target)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm $(obj)

distclean: clean
	rm $(target)

run: $(target)
	@./$(target)

debug: $(target)
	@gdb $(target)
