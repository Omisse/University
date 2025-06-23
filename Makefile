all: filler task

clean:
	@ rm -f liblist.a
	@ rm -f list.o
	@ rm -f task
	@ rm -f filler

liblist.a: list.c list.h
	@ gcc list.c -c -o list.o
	@ ar rcs liblist.a list.o

filler: list_fill.c
	@ gcc list_fill.c -o filler

task: task.c liblist.a
	@ gcc task.c liblist.a -o task

fill: filler
	@ ./filler

run: task
	@ ./task