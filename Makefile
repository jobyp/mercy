PROGS:=$(patsubst %.c,%,$(wildcard *.c))

.PHONY: all
all: $(PROGS)
	@:

%: %.c
	gcc -Werror -Og -pedantic -std=c17 -o $@ $<

.PHONY: clean
clean:
	@rm -f *.o $(PROGS) *~
