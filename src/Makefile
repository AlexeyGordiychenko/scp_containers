GTEST_FLAGS = --gtest_brief=1
BALD 				= '\033[1m\033[4m'
NORMAL 			= '\033[0m'

OS 					:= $(shell uname)
MY_FILES 		:= $(shell find . -name "*.cc" -o -name "*.h")

#===MAIN===============================================
all: test

%: %.cc force
	rm -f $@ || true
	$(CC) $(CPPFLAGS) $< -o $@
	./$@

test:
	cmake -S . -B build -DCMAKE_CXX_COMPILER=g++
	cmake --build build
	cd build && ./tests/all_containers_test $(GTEST_FLAGS)

%Test:
	cmake -S . -B build -DCMAKE_CXX_COMPILER=g++
	cmake --build build
	cd build && ./tests/all_containers_test $(GTEST_FLAGS) --gtest_filter=$@.*

#======================================================
#===EXTRA==============================================
gcov_report:
	cmake -S . -B build -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=PROFILE
	cmake --build build
	cd build && ./tests/all_containers_test $(GTEST_FLAGS)
	lcov -t "test" -o test.info -c -d ./build/s21_containers/CMakeFiles/containers_lib.dir -d ./build/s21_containersplus/CMakeFiles/containersplus_lib.dir
	genhtml -o report test.info

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
	CK_FORK=no valgrind --leak-check=full -s --track-origins=yes --log-file=leak.log ./build/tests/all_containers_test $(GTEST_FLAGS)
	cat leak.log
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
