//
// Created by sin_een on 8/23/17.
//

#include <stddef.h>
#include <assert.h>
#include "Stack.h"
#define EMPTY (-1)

#define visitedd 1
#define unVisited 0
//#include <obstack.h>

typedef void* pNode;

typedef int getNodeChildrenFunc(pNode, pNode** /*for the result*/);

typedef unsigned int getNodeValFunc(pNode);

typedef void freeNodeFunc(pNode);

typedef pNode copyNodeFunc(pNode);

int wasVisted (pNode arr[], pNode* u);
void addToVisited(pNode arr[], pNode* u , copyNodeFunc copy);


/**
 * @brief getBest This function returns the best valued node in a tree using
 * DFS algorithm.
 * @param head The head of the tree
 * @param getChildren A function that gets a node and a pointer to array of nodes.
 * the function allocates memory for an array of all the children of the node, and
 * returns the number of the children.
 * (the array might be initialized, but the function can't know how many children
 * the node has)
 * @param getVal A function that gets a node and returns its value, as int
 * @param freeNode A function that frees node from memory.
 * this function will be called for each Node returns by getChilds.
 * @param best The best available value for a node, when the function encounters
 * a node with that value it stops looking and returns it.
 * If the best value can't be determined, pass UINT_MAX (defined in limits.h)
 * for that param.
 * @param copy A function that do deep copy of Node.
 * @return The best valued node in the tree
 * In case of an error, or when all the nodes in the tree valued zero the returns
 * Node is NULL.
 * If some nodes shares the best valued, the function returns the first one it encounters.
 */
pNode getBest(pNode head, getNodeChildrenFunc getChildren,
			  getNodeValFunc getVal, freeNodeFunc freeNode, copyNodeFunc copy, unsigned int best)
{
//	DFS(G,v)   ( v is the vertex where the search starts )
//	Stack S := {};   ( start with an empty stack )
//	for each vertex u, set visited[u] := false;
//	push S, v;
//	while (S is not empty) do
//		u := pop S;
//	if (not visited[u]) then
//				visited[u] := true;
//	for each unvisited neighbour w of u
//	push S, w;
//	end if
//		end while
//		END DFS()
	stack* stack1 = stackNew();


	pNode visited[MAXSIZE] = {NULL};
	int j; // number of node we are on;
	unsigned int val = getVal(head);
	if (val == best){
		return head;
	}
	push(*stack1, head);
	while (stack1->top != EMPTY)
	{
		pNode u = copy(pop(*stack1));
		val = getVal(u);
		if (val == best){
			return u;
		}
		if ( wasVisted(visited, &u) == unVisited)
		{
			addToVisited(visited, &u, copy);
		}


		pNode** children1 = NULL;  // a pointer to an array of all the children of the node.
		int number_of_kids = getChildren(u, children1); // already allocated memory to children
		for (j = 0; j < number_of_kids; j++)
		{
			if( wasVisted(visited, *(children1+j)) == unVisited) // if nto visted
			{
				push(*stack1,*(children1+j));
			}

		}
		freeNode(children1);
		freeStack(stack1);
	}
	return NULL;
}



int wasVisted(pNode *arr, pNode *u)
{
	int wasVisited = unVisited;
	int i;
	for(i = 0; i < MAXSIZE ; i++ )
	{
		if (arr[i] == u)
		{
			wasVisited = visitedd;
		}
	}

	return wasVisited;
}

void addToVisited(pNode *arr, pNode *u, copyNodeFunc copy)
{
	int i = 0;
	while ( arr[i] != NULL)
	{
		i++;
	}
	assert( arr[i] == NULL);
	arr[i] = copy(u);
}



