//
// Created by sin_een on 8/23/17.
//

#ifndef EX3_SUDOKUTREE_H
#define EX3_SUDOKUTREE_H

typedef struct pNode
{
	unsigned int value;
	struct pNode* rightChild;
	struct pNode* leftChild;
	struct pNode* upChild;
	struct pNode* downChild;
	int row; // which inner square does it belong to
	int colume; // which inner square does it belong to
	int empty;
}pNode;
/**
 * getChildren A function that gets a node and a pointer to array of nodes.
 * the function allocates memory for an array of all the children of the node, and
 * returns the number of the children.
 * (the array might be initialized, but the function can't know how many children
 * the node has)
 * @return
 */
int getNodeChildrenFunc(pNode, pNode** /*for the result*/);


/**
 * getVal A function that gets a node and returns its value, as int
 * @return
 */

unsigned int getNodeValFunc(pNode);

/**
 * freeNode A function that frees node from memory.
 * this function will be called for each Node returns by getChilds.
 */
void freeNodeFunc(pNode);
/**
 * copy A function that do deep copy of Node.
 * @return
 */
pNode copyNodeFunc(pNode);

#endif //EX3_SUDOKUTREE_H
