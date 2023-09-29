lcov -t "$1.cpp" -o $1.info -c -d . --exclude '/usr/*' 
genhtml -o report $1.info
@$(OPEN) ./report/index.html
