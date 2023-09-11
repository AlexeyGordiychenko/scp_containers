CC=g++
CPPFLAGS=-Wall -Wextra -Werror -std=c++17 -g -fmax-errors=1

.PHONY: rbtree

rbtree:
	rm -f $@ || true
	$(CC) $(CPPFLAGS) $@.cc -o $@
	./$@