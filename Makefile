PROGS:=$(patsubst %.c,%,$(wildcard *.c))

.PHONY: all
all: $(PROGS)
	@:

%: %.c
	gcc -Werror -std=c11 -o $@ $<

.PHONY: clean
clean:
	@rm -f *.o $(PROGS) *~
