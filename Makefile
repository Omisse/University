TARGET := s2l1.a
TEST := test

SRCDIR := core
HDIR := core
OBJDIR := objects

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
HEADERS := $(wildcard $(HDIR)/*.hpp)
OBJECTS := $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(patsubst %.cpp,%.o,$(SOURCES)))

TSRCDIR := main
THDIR := main

TESTS_SOURCES := $(wildcard $(TSRCDIR)/*.cpp)
TESTS_HEADERS := $(wildcard $(THDIR)/*.hpp)
TESTS_OBJECTS := $(patsubst $(TSRCDIR)%,$(OBJDIR)%,$(patsubst %.cpp,%.o,$(TESTS_SOURCES)))

CC := g++
CCFLAGS := -Wall -Werror -Wextra -std=c++20

RUN := ./


all: $(TEST)

clean:
	@ echo Removing all that we were building for so long...
	@ rm -rf $(OBJDIR)
	@ rm -rf $(TARGET)
	@ rm -rf $(TEST)
	@ echo All built files commited sudoku.

$(TARGET): $(OBJECTS)
	@ echo Building $@
	@ ar rcs $@ $(OBJECTS)
	
$(TEST): $(TARGET) $(TESTS_OBJECTS)
	@ echo Building $@
	@ $(CC) $(CCFLAGS) $(TESTS_OBJECTS) -o $@ $< $(LINK)
	@ echo Running tests...
	@ $(RUN)$@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@ mkdir -p $(OBJDIR)
	@ $(CC) $(CCFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TSRCDIR)/%.cpp
	@ mkdir -p $(OBJDIR)
	@ $(CC) $(CCFLAGS) -c $< -o $@


format-all: $(SOURCES) $(TESTS_SOURCES) $(HEADERS) $(TESTS_HEADERS)
	@ echo Starting format...
	@ clang-format --style=Google -n $^
	@ clang-format --style=Google -i $^
	@ echo Formatting done.

.PHONY: clean all format-all