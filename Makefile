CC = gcc
CPPFLAGS = -DNDEBUG
CFLAGS = -g -Wall -Wvla -Wextra -std=c99
LDFLAGS = -g
LDLIBS = -L. -lGenericDFS -lm

VAL = valgrind
VALFLAGS = --leak-check=full --show-possibly-lost=yes --show-reachable=yes --undef-value-errors=yes --log-file=

.PHONY: clean all val tar

all: SudokuSolver libGenericDFS.a

SudokuSolver: SudokuSolver.o SudokuTree.o libGenericDFS.a
	$(CC) $(LDFLAGS) SudokuSolver.o SudokuTree.o -o $@ $(LDLIBS)

lib%.a: %.o
	ar -rcs $@ $^

# Implicit rule
# %.o: %.c
# 	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@
GenericDFS.o: GenericDFS.c Stack.h GenericDFS.h
Stack.o: Stack.c Stack.h GenericDFS.h
SudokuSolver.o: SudokuSolver.c SudokuTree.h GenericDFS.h
SudokuTree.o: SudokuTree.c SudokuTree.h GenericDFS.h


val: valdbg_SudokuSolver
valdbg_SudokuSolver: SudokuSolver
	$(VAL) $(VALFLAGS)"$@" $< basic.in

tar: ex3.tar
ex3.tar: Makefile SudokuTree.c SudokuTree.h Stack.c Stack.h GenericDFS.c SudokuSolver.c
	tar -cvf $@ $^ extension.pdf

clean:
	rm -f *.o *.a SudokuSolver valdbg_* ex3.tar