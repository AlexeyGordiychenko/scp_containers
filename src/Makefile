CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17 -fmax-errors=1 -g
LDFLAGS=-lgtest -pthread

GCOVFLAGS=--coverage
GCOV_DIR=gcov

TEST_DIR=tests
SRC_DIR=.
OBJ_DIR=obj
OBJ_DIR_GCOV=$(OBJ_DIR)/$(GCOV_DIR)
OBJ_DIR_TEST=$(OBJ_DIR)/$(TEST_DIR)

SRCS=$(wildcard $(SRC_DIR)/s21_*.h)
SRCS_TEST=$(wildcard $(TEST_DIR)/s21_*.cc)
OBJS_TEST=$(patsubst $(TEST_DIR)/%.cc,$(OBJ_DIR_TEST)/%.o,$(SRCS_TEST))
OBJS_GCOV=$(patsubst $(TEST_DIR)/%.cc,$(OBJ_DIR_GCOV)/%.o,$(SRCS_TEST))

TEST=test
TEST_GCOV=$(TEST)_gcov
TEST_BUILD=$(TEST)_build
TEST_BUILD_GCOV=$(TEST_BUILD)_gcov

.PHONY: force all $(TEST) $(TEST_BUILD) $(TEST_GCOV) $(TEST_BUILD_GCOV) gcov_report clean clean_gcda rebuild clang_n clang_i valgrind valgrind_mac

all: $(TEST)

#===MAIN===============================================
all: test

%: %.cc force
	rm -f $@ || true
	$(CC) $(CFLAGS) $< $(LDFLAGS) -o $@

$(TEST): $(TEST_BUILD)
	./$@ || true

$(TEST_BUILD): $(OBJS_TEST)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $(TEST)

$(OBJ_DIR_TEST)/%.o: $(TEST_DIR)/%.cc
	@mkdir -p $(OBJ_DIR_TEST)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_GCOV): $(TEST_BUILD_GCOV)
	$(MAKE) clean_gcda
	./$@ || true

$(TEST_BUILD_GCOV): $(OBJS_GCOV)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(GCOVFLAGS) -o $(TEST_GCOV)

$(OBJ_DIR_GCOV)/%.o: $(TEST_DIR)/%.cc
	@mkdir -p $(OBJ_DIR_GCOV)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

gcov_report: $(TEST_GCOV)
	mkdir -p $(GCOV_DIR)
	gcovr --html-details  -o $(GCOV_DIR)/index.html --filter s21_\.\*.h
	open $(GCOV_DIR)/index.html

lcov_report: $(TEST_GCOV)
	mkdir -p $(GCOV_DIR)
	lcov --capture --directory $(SRC_DIR) --output-file $(GCOV_DIR)/coverage.info --no-external
	genhtml -o $(GCOV_DIR) $(GCOV_DIR)/coverage.info 
	open $(GCOV_DIR)/index.html

clean:
	rm -rf *.o *.a *.out *.info *.log *.html *.gc* test gcov_report report build*

test:
	cmake -S . -B build -DCMAKE_CXX_COMPILER=g++
	cmake --build build
	cd build && ./tests/all_containers_test $(GTEST_FLAGS)

%Test:
	cmake -S . -B build -DCMAKE_CXX_COMPILER=g++
	cmake --build build
	cd build && ./tests/all_containers_test --gtest_filter=$@.*

#======================================================
#===EXTRA==============================================
gcov_report:
	cmake -S . -B build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=PROFILE
	cmake --build build
	lcov --no-external -c -i --directory . --output-file pre_test.info
	cd build && ./tests/all_containers_test $(GTEST_FLAGS)
	lcov --no-external -c --directory . --output-file test.info
	lcov -a pre_test.info -a test.info -o full_test.info
	lcov --remove test.info '*gtest*' '*googletest*' -o filtered_test.info
	genhtml filtered_test.info -o report 

open:
ifeq ($(OS),Darwin)
	open -a "Google Chrome" report/index.html
else
	xdg-open report/index.html
endif

leak: test
ifeq ($(OS),Darwin)
	CK_FORK=no leaks -atExit -- ./build/tests/all_containers_test $(GTEST_FLAGS)
else
	CK_FORK=no valgrind --leak-check=full -s --track-origins=yes --log-file=./build/leak.log ./build/tests/all_containers_test $(GTEST_FLAGS)
	cat ./build/leak.log
endif

cppcheck:
	@echo "-===Checking code...===-"
	cppcheck -q --language=c++ --std=c++17 --enable=all --suppress=missingInclude --template=gcc $(MY_FILES)
	@echo "-===Done===-"

clang:
	@echo "-===Checking style...===-"
	clang-format -n -style=google $(MY_FILES)
	@echo "-===Done===-"

clangI:
	@echo "-===Correcting style...===-"
	clang-format -i -style=google $(MY_FILES)
	@echo "-===Done===-"

help:
	@echo "-===Main project targets:===-"
	@echo $(BALD)"\tmake test (or make, or make all)"$(NORMAL)" - run all tests"
	@echo $(BALD)"\tmake clean"$(NORMAL)" - clean unnecessary files and uninstall the app"

	@echo "-===Extra project targets:===-"
	@echo $(BALD)"\tmake SuiteNameTest"$(NORMAL)" - run all tests in 'SuiteName' test suite"
	@echo $(BALD)"\tmake gcov_report"$(NORMAL)" - create test coverage HTML-report"
	@echo $(BALD)"\tmake open"$(NORMAL)" - open test coverage HTML-report"
	@echo $(BALD)"\tmake leak"$(NORMAL)" - check for memory leaks with Valgrind (Linux) or Leaks (MACOS)"
	@echo $(BALD)"\tmake cppcheck"$(NORMAL)" - analyse code with static code analyser"
	@echo $(BALD)"\tmake clang"$(NORMAL)" - analyse code for Google Style"
	@echo $(BALD)"\tmake clangI"$(NORMAL)" - analyse code for Google Style and correct style mistakes"
	@echo $(BALD)"\tmake help"$(NORMAL)" - show helpful information for the project"

.PHONY: all clean gcov_report cppcheck clang clangI leak help

.SILENT: help clang clangI cppcheck
#======================================================
