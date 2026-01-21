all: main
	./test

main:
	gcc main.cpp student_data.cpp -lstdc++ -o test

clean:
	@ echo Removing all that we were building for so long...
	@ rm test
	@ echo All built files commited sudoku.

valgrind: main
	valgrind --leak-check=full --show-leak-kinds=all ./test