MY_FILES 	= *.cc *.h ./tests/*.cc ./tests/*.h ./s21_containers/*.cc ./s21_containers/*.h ./s21_containersplus/*.cc ./s21_containersplus/*.h
GTEST_EXTRA_FLAGS = --gtest_brief=1

OS 			:= $(shell uname)

#===MAIN===============================================
all: test

%: %.cc force
	rm -f $@ || true
	$(CC) $(CPPFLAGS) $< -o $@
	./$@

val:
	valgrind --tool=memcheck --leak-check=yes ./rbtree