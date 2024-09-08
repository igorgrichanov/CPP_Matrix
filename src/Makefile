CC=g++
CFLAGS=--std=c++17 -pedantic -O2 -Wall -Wextra -Werror
LIB_NAME=matrix_oop.a
TEST_FLAGS=-lgtest -lgtest_main -pthread
VALGRIND_FLAGS=--tool=memcheck --track-origins=yes

all: $(LIB_NAME)

$(LIB_NAME): *.cpp
	$(CC) $(CFLAGS) -c $^
	ar rc $@ *.o
	ranlib $@

test: *.cpp
	$(CC) $(CFLAGS) -o matrix_oop tests/main.cpp $^ $(TEST_FLAGS)
	./matrix_oop

format:
	@cp ../materials/linters/.clang-format ./
	@clang-format -i *.cpp *.h tests/*.cpp
	@clang-format -n *.cpp *.h tests/*.cpp
	@rm .clang-format

valgrind:
	$(CC) $(CFLAGS) -o matrix_oop tests/main.cpp -g -O0 *.cpp $(TEST_FLAGS)
	valgrind $(VALGRIND_FLAGS) ./matrix_oop

clean:
	rm matrix_oop
	rm -f *.gcda *.gcno *.gcov *.o *.a

rebuild: clean all