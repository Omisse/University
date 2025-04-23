TEST := test

OBJDIR := objects

TSRCDIR := .

TESTS_SOURCES := $(wildcard $(TSRCDIR)/*.c)
TESTS_OBJECTS := $(patsubst $(TSRCDIR)%,$(OBJDIR)%,$(patsubst %.c,%.o,$(TESTS_SOURCES)))

CC := gcc
CCFLAGS := -Wall -Werror -Wextra -std=c11

RUN := ./


all: $(TEST)

clean:
	@ echo Removing all that we were building for so long...
	@ rm -rf $(OBJDIR)
	@ rm -rf $(TEST)
	@ echo All built files commited sudoku.

$(TEST): $(TESTS_OBJECTS) .FORCE
	@ echo Building $@
	@ $(CC) $(CCFLAGS) $(TESTS_OBJECTS) -o $@
	@ echo Running tests...
	@ $(RUN)$@

$(OBJDIR)/%.o: $(TSRCDIR)/%.c
	@ mkdir -p $(OBJDIR)
	@ $(CC) $(CCFLAGS) -c $< -o $@

.PHONY: clean all format-all .FORCE