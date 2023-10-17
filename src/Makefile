BALD 				= '\033[1m\033[4m'
NORMAL 			= '\033[0m'

BUILD_FLAGS := -DCMAKE_CXX_COMPILER=g++
GTEST_FLAGS := --gtest_brief=1
OS 					:= $(shell uname)
MY_FILES 		:= $(shell find . -name "*.cc" -o -name "*.h")

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

# temporary rules for testing/debugging standalone .cc files {
force:

%: %.cc force
	rm -f $@ || true
	$(CC) $(CFLAGS) -g $< $(LDFLAGS) -o $@
#}

$(TEST): $(TEST_BUILD)
	./$@ || true

$(TEST_BUILD): $(OBJS_TEST)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(OFLAGS) -o $(TEST)

$(OBJ_DIR_TEST)/%.o: $(TEST_DIR)/%.cc
	@mkdir -p $(OBJ_DIR_TEST)
	$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@

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
	lcov --capture --directory $(SRC_DIR) --exclude "$(CURDIR)/tests/*" --output-file $(GCOV_DIR)/coverage.info --no-external
	genhtml -o $(GCOV_DIR) $(GCOV_DIR)/coverage.info 
	open $(GCOV_DIR)/index.html

clean:
	rm -rf *.o *.a *.out *.info *.log *.html *.gc* test gcov_report report build*

test: BUILD_FLAGS := $(BUILD_FLAGS) -DCMAKE_BUILD_TYPE=RELEASE
test: _build _run

%Test:
	@make test GTEST_FLAGS=--gtest_filter=$@.*

test_no_optimization: clean _build _run

#======================================================
#===INTERNAL===========================================
_build:
	cmake -S . -B build $(BUILD_FLAGS)
	cmake --build build

_run:
	cd build && ./tests/all_containers_test $(GTEST_FLAGS)

#======================================================
#===EXTRA==============================================
gcov_report: BUILD_FLAGS := $(BUILD_FLAGS) -DCMAKE_BUILD_TYPE=PROFILE
gcov_report: _build
	lcov --no-external -c -i --directory . --output-file build/pre_test.info
	@make _run
	lcov --no-external -c --directory . --output-file build/test.info
	lcov -a build/pre_test.info -a build/test.info -o build/full_test.info
	lcov --remove build/full_test.info '*gtest*' '*googletest*' '*tests*' -o build/filtered_test.info
	genhtml build/filtered_test.info -o report 

leaks: BUILD_FLAGS := $(BUILD_FLAGS) -DCMAKE_BUILD_TYPE=RELEASE
leaks: _build
ifeq ($(OS),Darwin)
	CK_FORK=no leaks -atExit -- ./build/tests/all_containers_test $(GTEST_FLAGS)
else
	CK_FORK=no valgrind --leak-check=full -s --track-origins=yes --log-file=./build/leak.log ./build/tests/all_containers_test $(GTEST_FLAGS)
	cat ./build/leak.log
endif

open:
ifeq ($(OS),Darwin)
	open -a "Google Chrome" report/index.html
else
	xdg-open report/index.html
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
	@echo $(BALD)"\tmake leaks"$(NORMAL)" - check for memory leaks with Valgrind (Linux) or Leaks (MACOS)"
	@echo $(BALD)"\tmake cppcheck"$(NORMAL)" - analyse code with static code analyser"
	@echo $(BALD)"\tmake clang"$(NORMAL)" - analyse code for Google Style"
	@echo $(BALD)"\tmake clangI"$(NORMAL)" - analyse code for Google Style and correct style mistakes"
	@echo $(BALD)"\tmake help"$(NORMAL)" - show helpful information for the project"

.PHONY: all clean gcov_report cppcheck clang clangI leaks help

.SILENT: help clang clangI cppcheck
#======================================================
