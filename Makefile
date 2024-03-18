CC?=gcc

CFLAGS ?=
LDFLAGS ?=

CFLAGS += -I.

telegraph: telegraph.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f *.o telegraph
