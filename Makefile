CC?=gcc

CFLAGS ?=
LDFLAGS ?= -lncurses

CFLAGS += -I.

telegraph: telegraph.o morse_tree.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o telegraph
