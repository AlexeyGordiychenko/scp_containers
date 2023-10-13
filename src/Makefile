CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17 -fmax-errors=1
OFLAGS=-O2
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
	rm -rf $(OBJ_DIR) $(GCOV_DIR) $(TEST) $(TEST_GCOV)

clean_gcda:
	rm -rf $(OBJ_DIR)/*.gcda

rebuild: clean all

clang_n:
	clang-format -n --style=Google $(SRC_DIR)/*.h $(TEST_DIR)/*.cc

clang_i:
	clang-format -i --style=Google $(SRC_DIR)/*.h $(TEST_DIR)/*.cc

valgrind: $(TEST_BUILD)
	valgrind --tool=memcheck --leak-check=yes ./$(TEST)

valgrind_mac: $(TEST_BUILD)
	leaks -atExit -- ./$(TEST) | grep LEAK:
