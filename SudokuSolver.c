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
//#include <libGenericDFS.a>
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
#define EMPTY 0

char* fileName;
void checkRange(int num, int size);
int strToInt(char* string);
void readFile(FILE* in);
void checkIfNotDigit(const char* string);
void checkIfPositive(int num);
void errors(int errorNumber);

pNode** createSudoBoard(const int* size)
{
	pNode** board = (pNode**)malloc((*size) * (*size) * sizeof(int));
	return board;
}

void freeboard(int* board)
{
	free(board);
}
pNode getNodeFromBoard(int row, int colume, int size , pNode* board)
{
	//int offset = i * cols + j;
// now mat[offset] corresponds to m(i, j)
	//for row-major ordering and
	//int offset = i + rows * j;
	return board[row + size * colume];
}

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


pNode* nodesInSameRow(pNode node, pNode** board, int size)
{
	int index = 0;
	pNode* row = (pNode*) malloc(MAXSIZE);
	for (int i = 0; i < size; i++)
	{
		if (getNodeFromBoard(node.row, i, size, *board).value  != EMPTY )
		{
			row[index] = copyNodeFunc(getNodeFromBoard(node.row, i, size, *board));
		}
	}
	return row;
}


pNode* nodesInSameColum(pNode node, pNode** board, int size)
{
	int index = 0;
	pNode* cul = (pNode*) malloc(MAXSIZE);
	for (int i = 0; i < size ; i++)
	{
		if (getNodeFromBoard(i, node.colume, size, *board).value  != EMPTY )
		{
			cul[index] = copyNodeFunc(getNodeFromBoard(i, node.colume, size, *board));
		}
	}
	return cul;
}

pNode* nodesInSameSquare(pNode node, pNode** board, int size)
{
	assert(sqrt(size) == )
	int root = sqrt(size);
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
	pNode** sudokuBoard = createSudoBoard(&size);
	char * line = NULL;
	char* token = NULL;
	pNode* node;

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
			node = createNode();
			node->value = (unsigned int) value;
			node->colume = j;
			node->row = i;
			if (node->value == EMPTY) node->empty = EMPTY;
			sudokuBoard[i + size * j] = node;
		}
		if( numOfCul != size) errors(MISSING_NUMBER);
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

	}
}