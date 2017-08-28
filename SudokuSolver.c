//
// Created by sin_een on 8/23/17.
//

#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <memory.h>
#include "SudokuTree.h"
#include "GenericDFS.h"
#include <limits.h>

#define NOT_ROOT (-1)
#define MISSING_NUMBER (-2)
#define NEGATIVE_NUMBER (-3)
#define BIGGER (-4)
#define LETTERS (-5)
#define FILE_ERROR (-6)
#define EXTRA_ARGUMENTS (-7)
#define FEW_ARGUMENTS (-8)
#define NOT_IN_RANG (-10)
#define NOT_DIGIT (-9)
#define ZERO (0)
#define MAXSIZE (100)
#define BASE (10)
#define DELIM ("\n ")


char* fileName;
void checkRange(int num, int size);
int strToInt(char* string);
void readFile(FILE* in);
void checkIfNotDigit(const char* string);
void checkIfPositive(int num);
void errors(int errorNumber);
pBoard solveSudo(pBoard board);
void printBoard(pNode node);




void checkRoot(int size)
{
	int temp = (int) sqrt(size);
	if(temp*temp != size) errors(NOT_ROOT);
}


void checkIfPositive(int num)
{
	if(num < ZERO ) errors(NEGATIVE_NUMBER);
}

void checkIfNotDigit(const char *string)
{
	if (isalpha(string)) {
		errors(LETTERS);
	} else if (isdigit(string)) {
		return;
	} else {
		errors(NOT_DIGIT);
	}
}



void checkRange(int num, int size)
{
	// checks if the number is in range 0 < num < size
	checkIfPositive(num);
	if ( num == size )
	{
		if ( size > MAXSIZE ) errors(NOT_IN_RANG);
	}
	else if (num > size)
	{
		errors(NOT_IN_RANG);
	}
}

int strToInt(char *string)
{
	checkIfNotDigit(string);
	char *ptr;
	long ret;
	ret = strtol(string, &ptr, BASE);
	if(ptr[0] == '\n') errors(LETTERS);
	return (int)ret;
}

void readFile(FILE *in)
{
	if (in == NULL)
	{
		errors(FILE_ERROR);
	}
	char* sSize = NULL;
	if (fgets(sSize, MAXSIZE , NULL) == NULL)
	{
		errors(MISSING_NUMBER);
	}
	int size = strToInt(sSize);
	checkRoot(size);
	checkIfPositive(size);
	checkRange(size, size);
	int i, j, numOfCul, value;
	pBoard sudokuBoard = createSudoBoard(size);
	char * line = NULL;
	char* token = NULL;
	Node* node;

//	char* lines[size];
	for (i = 0; i < size; i++) // goes through rows
	{
		if (fgets(line, size , NULL) == NULL)
		{
			errors(MISSING_NUMBER);
		}
		numOfCul = 0 ;
		for ( j = 0; j < size; j++) //  goes through colums
		{
			token = strtok(line, DELIM);
			if (token == NULL)
			{
				break;
			}
			++numOfCul;
			;
			checkIfNotDigit(token);
			value = strToInt(token);
			checkRange(value, size);
			node = createNode(size);
			node->value = (unsigned int) value;
			node->colume = j;
			node->row = i;
			sudokuBoard->sBoard[i + size * j] = node;
		}
		if( numOfCul != size) errors(MISSING_NUMBER);
	}
	pBoard solved = solveSudo(sudokuBoard);
	if (solved == NULL) fprintf(stdout," no solution");
	else
	{
		printBoard(solved);
	}
}


void errors(int errorNumber)
{
	switch (errorNumber)
	{
		case FILE_ERROR:
			fprintf(stderr, "%s:no such file\n" , fileName);
			break;
		case NOT_ROOT:
			fprintf(stderr, "%s:not a valid sudoku file\n" , fileName);
			break;
		case EXTRA_ARGUMENTS:
			fprintf(stderr, " Wrong input too many arguments\n");
			break;
		case MISSING_NUMBER:
			fprintf(stderr, "%s:not a valid sudoku file\n" , fileName);
			break;
		case FEW_ARGUMENTS:
			fprintf(stderr, " Wrong input  arguments missing \n");
			break;
		case LETTERS:
			fprintf(stderr, "%s:not a valid sudoku file\n" , fileName);
			break;
		case BIGGER:
			fprintf(stderr, "%s:not a valid sudoku file\n" , fileName);
			break;
		case NEGATIVE_NUMBER:
			fprintf(stderr, "%s:not a valid sudoku file\n" , fileName);
			break;
		default:
			fprintf(stderr, "NO ERROR \n");
	}
}

pBoard solveSudo(pBoard board)
{
	unsigned int size = INT_MAX;
	{
		//pNode getBest(pNode head, getNodeChildrenFunc getChildren,
		//getNodeValFunc getVal, freeNodeFunc freeNode, copyNodeFunc copy, unsigned int best)

		return (getBest(board,getNodeChildrenFunc1, getNodeValFunc1, freeNodeFunc1, copyNodeFunc1, size));
	}
}

void printBoard(pNode node)
{
	pBoard board = (pBoard) node;
	int counter = 0;
	fprintf(stdout, "%d\n", board->size);
	for (int i = 0; i < sizeof(board->sBoard) ; ++i)
	{
		if (counter == sqrt(board->size))
		{
			fprintf(stdout,"\n");
		}
		fprintf(stdout, "%d\n", board->sBoard[i]->value);
	}
}


int main(int argc, char *argv[])
{
	if(argc > 2)
	{
		errors(EXTRA_ARGUMENTS);
	}
	else if ( argc < 2)
	{
		errors(FEW_ARGUMENTS);
	}
	else
	{
		fileName = argv[0];
		FILE* inputFile = fopen(argv[1], "r");
		readFile(inputFile);
		fclose(inputFile);

	}
}