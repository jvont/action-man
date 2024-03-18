CC?=gcc

CFLAGS ?=
LDFLAGS ?=

CFLAGS += -I. -Ihttp-parser
# LDFLAGS += -Lhttp-parser -lhttp_parser

telegraph: telegraph.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f *.o telegraph
