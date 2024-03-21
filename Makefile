CC?=gcc

CFLAGS ?=
LIBS ?= 

LIBS += -lncurses `sdl2-config --libs`
CFLAGS += -I. `sdl2-config --cflags`

telegraph: telegraph.o morse_tree.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

.PHONY: clean
clean:
	rm -f *.o telegraph
