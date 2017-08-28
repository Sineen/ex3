//
// Created by sin_een on 8/23/17.
//

#ifndef EX3_SUDOKUTREE_H
#define EX3_SUDOKUTREE_H

#define MAX 99
//#include "Stack.h"
#include <malloc.h>
#include <memory.h>
#include <assert.h>
#include <math.h>
#include "GenericDFS.h"


typedef struct Node
{
	int* possible;
	unsigned int value;
	int size;
	int row; // which inner square does it belong to
	int colume; // which inner square does it belong to
}Node;

typedef struct
{
	Node** sBoard;
	int size;
} Board;

typedef Board* pBoard;

Node* createNode(int size){
	Node* node = (Node *) malloc(sizeof(Node));
	node->size = size;
	node->possible = (int *) malloc(size * sizeof(int));
	return node;
}

pBoard createSudoBoard(const int size)
{
	pBoard board = (pBoard)malloc((size) * (size) * sizeof(int));
	board->size = size;
	return board;
}


/**
 * getChildren A function that gets a node and a pointer to array of nodes.
 * the function allocates memory for an array of all the children of the node, and
 * returns the number of the children.
 * (the array might be initialized, but the function can't know how many children
 * the node has)
 * @return
 */


int getNodeChildrenFunc1(pNode , pNode ** /*for the result*/);


/**
 * getVal A function that gets a node and returns its value, as int
 * @return
 */

unsigned int getNodeValFunc1(pNode);

/**
 * freeNode A function that frees node from memory.
 * this function will be called for each Node returns by getChilds.
 */
void freeNodeFunc1(pNode);
/**
 * copy A function that do deep copy of Node.
 * @return
 */
pNode copyNodeFunc1(pNode);

#endif //EX3_SUDOKUTREE_H
