//
// Created by sin_een on 8/23/17.
//

#include <malloc.h>
#include <memory.h>
#include "SudokuTree.h"
int getNodeChildrenFunc(pNode node, pNode** pNode1/*for the result*/)
{
	int counter = 0;
	// hsoudl culculate teh children adn add them ( children is teh possiablities for that square
//	while (node.children[counter] != NULL)
//	{
//		pNode* temp = createNode();
//		*temp = copyNodeFunc(*node.children[counter]);
//		pNode1[counter] = temp;
//		++counter;
//	}

	return counter;
}


/**
 * getVal A function that gets a node and returns its value, as int
 * @return
 */

unsigned int getNodeValFunc(pNode node)
{
	return node.value;
}

/**
 * freeNode A function that frees node from memory.
 * this function will be called for each Node returns by getChilds.
 */
void freeNodeFunc(pNode node)
{
	free(node.children[1]);// ? do i want to do that ?
	free(node.parent);// ? do i want to do that ?
}
/**
 * copy A function that do deep copy of Node.
 * @return
 */

pNode copyNodeFunc(pNode node)
{
	pNode* newcopy = createNode();
	newcopy->value = node.value;
	newcopy->row = node.row;
	newcopy->colume = node.colume;
	newcopy->empty = node.empty;
	size_t temp = sizeof(node.parent);

	memcpy(newcopy->parent,node.parent,temp) ;
	temp = sizeof(node.children);
	memcpy(newcopy->children,node.children, temp);
	return (*newcopy);
}