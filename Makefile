CC=clang++
CFLAGS=-g -Wall -std=c++20

OBJDIR=obj
SRCDIR=src
TESTDIR=tests
BINDIR=bin
ASMDIR=hex

#Wildcard find all .cpp-files
SRCS=$(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/**/*.cpp)

#Substitute all .cpp files with .obj files, from the SRCS-variable
OBJS=$(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.obj, $(SRCS))

#Get and run tests
TESTS=$(wildcard $(TESTDIR)/*.cpp)
TESTBINS=$(patsubst $(TESTDIR)/%.cpp, $(TESTDIR)/bin/%, $(TESTS))

#Create Assembly
ASMBINS=$(patsubst $(SRCDIR)/%.cpp, $(ASMDIR)/%.s, $(SRCS))

BIN = $(BINDIR)/main

all:$(BIN)

#Make release creates a more lean option
release: CFLAGS=-Wall -o2 -DNDEBUG
release: clean
release: $(BIN)

#Makes the binary
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

#Make .obj files from the .cpp files
$(OBJDIR)/%.obj: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(SRCDIR)

#Make ASM outputs
$(ASMDIR)/%.s: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -S $< -o $@

#Invoke to make ASM outputs
asm: $(ASMBINS)
	@echo "asm"

#Make the tests before running them
$(TESTDIR)/bin/%: $(TESTDIR)/%.cpp
	$(CC) $(CFLAGS) -c $< $(OBJS) -o $@

#Invoke to run tests (needs a runner)
test: $(BIN) $(TESTDIR)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

clean: 
	$(RM) -r $(OBJDIR)/* $(ASMDIR)/* $(BINDIR)/*

init:
	@mkdir $(OBJDIR) $(BINDIR) $(TESTDIR) $(SRCDIR)
	echo "DONE"

$(ASMDIR):
	mkdir $@

$(TESTDIR)/bin:
	mkdir $@

