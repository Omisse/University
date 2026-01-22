all: run

run: test
	./test

test: main.cpp
	gcc -lstdc++ --std=c++11 main.cpp -o test

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all ./test

clean:
	rm test 2&>/dev/null
	rm vgcore* 2&>/dev/null