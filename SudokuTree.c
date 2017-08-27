//
// Created by sin_een on 8/23/17.
//

#include <malloc.h>
#include <memory.h>
#include "SudokuTree.h"
int getNodeChildrenFunc(pNode node, pNode** pNode1/*for the result*/)
{
	int counter = 0;
	if (node.downChild != NULL)
	{
		++counter;
		pNode1[counter] = node.downChild;

	}
	if (node.leftChild != NULL)
	{
		++counter;
		pNode1[counter] = node.leftChild;
	}
	if (node.upChild != NULL)
	{
		++counter;
		pNode1[counter] = node.upChild;
	}
	if (node.rightChild != NULL)
	{
		++counter;
		pNode1[counter] = (node.rightChild);
	}
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
	free(node.rightChild);
	free(node.leftChild);// ? do i want to do that ?
	free(node.upChild);// ? do i want to do that ?
	free(node.downChild);// ? do i want to do that ?
}
/**
 * copy A function that do deep copy of Node.
 * @return
 */
pNode copyNodeFunc(pNode node)
{
	pNode newcopy;
	newcopy.visited = node.visited;
	newcopy.value = node.value;
	size_t sizep = sizeof(node.downChild);
	memcpy(newcopy.leftChild,node.leftChild, sizep);
	memcpy(newcopy.rightChild,node.rightChild, sizep);
	memcpy(newcopy.upChild,node.upChild, sizep);
	memcpy(newcopy.downChild,node.downChild, sizep);
	return (newcopy);
}