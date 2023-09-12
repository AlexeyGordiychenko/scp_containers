CC=g++
CPPFLAGS=-Wall -Wextra -Werror -std=c++17 -g -fmax-errors=1

.PHONY: force

force:

%: %.cc force
	rm -f $@ || true
	$(CC) $(CPPFLAGS) $< -o $@
	./$@