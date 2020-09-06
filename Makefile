PROGS:=$(patsubst %.c,%,$(wildcard *.c))

.PHONY: all
all: $(PROGS)
	@:

%: %.c
	gcc -Werror -Wformat -Og -pedantic -std=c17 -o $@ $<

.PHONY: clean
clean:
	@rm -f *.o $(PROGS) *~
