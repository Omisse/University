all: main
	./test

main:
	gcc main.cpp student_data.cpp student_data_budget.cpp student_data_debt.cpp -lstdc++ -o test

clean:
	@ echo Removing all that we were building for so long...
	@ rm test &2>/dev/null
	@ rm data.bin &2>/dev/null
	@ rm data.txt &2>/dev/null
	@ echo All built files commited sudoku.

valgrind: main
	valgrind --leak-check=full --show-leak-kinds=all ./test