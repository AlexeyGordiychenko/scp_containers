MY_FILES 	= *.cc *.h ./tests/*.cc ./tests/*.h ./s21_containers/*.cc ./s21_containers/*.h ./s21_containersplus/*.cc ./s21_containersplus/*.h
GTEST_EXTRA_FLAGS = --gtest_brief=1

OS 			:= $(shell uname)

#===MAIN===============================================
all: test

%: %.cc force
	rm -f $@ || true
	$(CC) $(CPPFLAGS) $< -o $@
	./$@

test:
	cmake -S . -B build -DCMAKE_CXX_COMPILER=g++
	cmake --build build
	cd build && ./tests/all_containers_test $(GTEST_EXTRA_FLAGS)

%Test:
	cmake -S . -B build -DCMAKE_CXX_COMPILER=g++
	cmake --build build --target matrixplus_test
	cd build && ./tests/matrixplus_test $(GTEST_EXTRA_FLAGS) --gtest_filter=$@.*

#======================================================
#===EXTRA==============================================
gcov_report:
	cmake -S . -B build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=PROFILE
	cmake --build build --target matrixplus_test
	cd build && ./tests/matrixplus_test $(GTEST_EXTRA_FLAGS)
	lcov -t "test" -o test.info -c -d ./build/CMakeFiles/matrixplus_lib.dir
	genhtml -o report test.info

open:
ifeq ($(OS),Darwin)
	open -a "Google Chrome" report/src/index.html
else
	xdg-open report/src/index.html
endif

leak: test
ifeq ($(OS),Darwin)
	CK_FORK=no leaks -atExit -- ./build/tests/matrixplus_test
else
	CK_FORK=no valgrind --leak-check=full -s --track-origins=yes --log-file=leak.log ./build/tests/matrixplus_test $(GTEST_EXTRA_FLAGS)
	cat leak.log
endif

cppcheck:
	cppcheck -q --language=c++ --std=c++17 --enable=all --suppress=missingInclude --template=gcc $(MY_FILES)

clang:
	clang-format -n -style=google $(MY_FILES)

clangI:
	clang-format -i -style=google $(MY_FILES)

.PHONY: all clean gcov_report cppcheck clang clangI leak
#======================================================
