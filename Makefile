all: test run

test: main.cpp list_node.hpp my_list.hpp
	gcc -lstdc++ --std=c++11 main.cpp -o test

run: test
	./test

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all ./test 

clean:
	rm vgcore* &2>/dev/null
	rm test &2>/dev/null
	