CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17 -fmax-errors=1 -g
LDFLAGS=-lgtest -pthread

GCOVFLAGS=--coverage
GCOV_DIR=gcov

TEST_DIR=tests
SRC_DIR=.
OBJ_DIR=obj
OBJ_DIR_GCOV=obj/$(GCOV_DIR)
OBJ_DIR_TEST=obj/$(TEST_DIR)

SRCS=$(wildcard $(SRC_DIR)/s21_*.cc)
SRCS_TEST=$(wildcard $(TEST_DIR)/s21_*.cc)
OBJS=$(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR)/%.o,$(SRCS))
OBJS_TEST=$(patsubst $(TEST_DIR)/%.cc,$(OBJ_DIR_TEST)/%.o,$(SRCS_TEST))
OBJS_GCOV=$(patsubst $(SRC_DIR)/%.cc,$(OBJ_DIR_GCOV)/%.o,$(SRCS))

TEST=test
TEST_BUILD=test_build

.PHONY: force all $(TEST) $(TEST_BUILD) gcov_report clean clean_gcda rebuild clang_n clang_i valgrind valgrind_mac

all: $(TEST)

#===MAIN===============================================
all: test

%: %.cc force
	rm -f $@ || true
	$(CC) $(CFLAGS) $< -o $@

$(TEST_BUILD): $(OBJS_GCOV) $(OBJS_TEST)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(GCOVFLAGS) -o $(TEST)

$(TEST): $(TEST_BUILD)
	$(MAKE) clean_gcda
	./$@ || true

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_TEST)/%.o: $(TEST_DIR)/%.cc
	@mkdir -p $(OBJ_DIR_TEST)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_GCOV)/%.o: $(SRC_DIR)/%.cc
	@mkdir -p $(OBJ_DIR_GCOV)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

gcov_report: $(TEST)
	mkdir -p $(GCOV_DIR)
	gcovr --html-details -o $(GCOV_DIR)/index.html --filter "$(CURDIR)/*"
	open $(GCOV_DIR)/index.html

lcov_report: $(TEST)
	mkdir -p $(GCOV_DIR)
	lcov --capture --directory $(SRC_DIR) --output-file $(GCOV_DIR)/coverage.info --no-external
	genhtml -o $(GCOV_DIR) $(GCOV_DIR)/coverage.info 
	open $(GCOV_DIR)/index.html

clean:
	rm -rf $(OBJ_DIR) $(GCOV_DIR) $(TEST)

clean_gcda:
	rm -rf $(OBJ_DIR_GCOV)/*.gcda

rebuild: clean all

clang_n:
	clang-format -n --style=Google $(SRC_DIR)/*.h $(TEST_DIR)/*.h
	clang-format -n --style=Google $(SRC_DIR)/*.cc $(TEST_DIR)/*.cc

clang_i:
	clang-format -i --style=Google $(SRC_DIR)/*.h $(TEST_DIR)/*.h
	clang-format -i --style=Google $(SRC_DIR)/*.cc $(TEST_DIR)/*.cc

valgrind: $(TEST_BUILD)
	valgrind --tool=memcheck --leak-check=yes ./$(TEST)

valgrind_mac: $(TEST_BUILD)
	leaks -atExit -- ./$(TEST) | grep LEAK:
