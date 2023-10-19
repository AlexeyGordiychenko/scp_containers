BALD 				= '\033[1m\033[4m'
NORMAL 			= '\033[0m'

OS 					:= $(shell uname)
MY_FILES 		:= $(shell find . \( -name "*.cc" -o -name "*.h" \) -not -path "./build/*")

BUILD_FLAGS := -DCMAKE_CXX_COMPILER=g++
GTEST_FLAGS := --gtest_brief=1

ifeq ($(OS),Darwin)
	LCOV_MAC_FLAG = -q --rc geninfo_unexecuted_blocks=1 --ignore-errors mismatch,mismatch,unused
else
	LCOV_MAC_FLAG = -q
endif

#===MAIN===============================================
all: test

clean:
	rm -rf *.o *.a *.out *.info *.log *.html *.gc* test gcov_report report gcovr build*

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
lcov_report: BUILD_FLAGS := $(BUILD_FLAGS) -DCMAKE_BUILD_TYPE=PROFILE
lcov_report: _build
	lcov --no-external -c -i --directory . --output-file build/pre_test.info $(LCOV_MAC_FLAG)
	@make _run
	lcov --no-external -c --directory . --output-file build/test.info $(LCOV_MAC_FLAG)
	lcov -a build/pre_test.info -a build/test.info -o build/full_test.info --ignore-errors mismatch $(LCOV_MAC_FLAG)
	lcov --remove build/full_test.info '*gtest*' '*googletest*' '*tests*' -o build/filtered_test.info --ignore-errors mismatch $(LCOV_MAC_FLAG)
	genhtml build/filtered_test.info -o report

gcov_report: BUILD_FLAGS := $(BUILD_FLAGS) -DCMAKE_BUILD_TYPE=PROFILE
gcov_report: _build
	@make _run
	mkdir -p gcovr
	gcovr --html-details -o gcovr/index.html --filter scp_\.\*.h

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

open_gcov:
ifeq ($(OS),Darwin)
	open -a "Google Chrome" gcovr/index.html
else
	xdg-open gcovr/index.html
endif

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
	@echo $(BALD)"\tmake gcov_report"$(NORMAL)" - create test coverage HTML-report with gcovr"
	@echo $(BALD)"\tmake lcov_report"$(NORMAL)" - create test coverage HTML-report with lcov"
	@echo $(BALD)"\tmake open"$(NORMAL)" - open test coverage HTML-report made by lcov"
	@echo $(BALD)"\tmake open_gcov"$(NORMAL)" - open test coverage HTML-report mady by gcovr"
	@echo $(BALD)"\tmake leaks"$(NORMAL)" - check for memory leaks with Valgrind (Linux) or Leaks (MACOS)"
	@echo $(BALD)"\tmake clang"$(NORMAL)" - analyse code for Google Style"
	@echo $(BALD)"\tmake clangI"$(NORMAL)" - analyse code for Google Style and correct style mistakes"
	@echo $(BALD)"\tmake help"$(NORMAL)" - show helpful information for the project"

.PHONY: all clean gcov_report lcov_report cppcheck clang clangI leaks help

.SILENT: help clang clangI cppcheck
#======================================================
