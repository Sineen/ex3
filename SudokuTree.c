//
// Created by sin_een on 8/23/17.
//


#include "SudokuTree.h"
#define MAXSIZE (100)

#define EMPTY 0
int fillPos(Node* node, pBoard board);
Node* emptyNode(pBoard board);
int* nodesInSameColum(Node node, pBoard board);
int* nodesInSameRow(Node node, pBoard board);
int* nodesInSameSquare(Node node, pBoard board);
Node* getNodeFromBoard(int row, int colume, pBoard board);
Node* copyNode(Node* node);
void freeNode(Node* node);

Node* emptyNode(pBoard board)
{
	static int i;
	static int j;
	int size = board->size;
	for (i = 0; i < size ; ++i)
	{
		for (j = 0; j < size ; ++j)
		{
			if (getNodeFromBoard(i, j, board)->value == 0)
			{
				return getNodeFromBoard(i, j, board);
			}
		}
	}
	return NULL;
}

int getNodeChildrenFunc1(pNode board, pNode ** board1/*for the result*/)
{
	pBoard node = (pBoard) board;
	pBoard** pNode1 = (pBoard**) board1;
	int retuval = 0;
	Node* empNode = emptyNode(node);
	pBoard copy;
	if( empNode == NULL )
	{
		retuval = fillPos(empNode, **pNode1);
		for (int i = 0; i < retuval; ++i)
		{
			copy = copyNodeFunc1(node);
			copy->sBoard[empNode->row * empNode->size + empNode->colume]->value = (unsigned int) empNode->possible[i];
			pNode1[i] = &copy;
		}
	}
	return retuval;

}

int* nodesInSameRow(Node node, pBoard board)
{
	int index = 0;
	size_t size = (size_t) node.size;
	int* row = (int*) malloc(size);
	for (int i = 0; i < size; i++)
	{
		if (getNodeFromBoard(node.row, i,board)->value  != EMPTY )
		{
			row[index] = (getNodeFromBoard(node.row, i, board))->value;
			++index;
		}
	}
	return row;
}


int* nodesInSameColum(Node node, pBoard board)
{
	int index = 0;
	size_t size = (size_t) node.size;
	int* cul = (int*) malloc(size);
	for (int i = 0; i < size ; i++)
	{
		if (getNodeFromBoard(i, node.colume, board)->value  != EMPTY )
		{
			cul[index] = (getNodeFromBoard(i, node.colume, board))->value;
			++index;
		}
	}
	return cul;
}

int* nodesInSameSquare(Node node, pBoard board)
{
	size_t size = (size_t) node.size;

	int* square = (int*) malloc(size);
	int index = 0;
//	assert(sizeof(sqrt(size)) == sizeof(int));
	int root = (int) sqrt(size);// already checked
	int indexi = node.row - ((node.row) % root); // this is to see which square we ar eadn changes teh index
	int indexj = node.colume - (node.colume % root);
	for (int i = indexi; i < root ; ++i)
	{
		for (int j = indexj; j < root ; ++j)
		{
			if (getNodeFromBoard(i, j ,  board)->value  != EMPTY )
			{
				square[index] = (getNodeFromBoard(i, node.colume, board))->value;
				++index;
			}
		}
	}
	return square;
}

int fillPos(Node* node, pBoard board)
{
	int size = node->size;
	int* possiableC = nodesInSameColum(*node, board);
	int* possiableR = nodesInSameRow(*node, board);
	int* possiableS = nodesInSameSquare(*node, board);
	int* val = (int*) malloc((size_t)node->size);
	for (int i = 0; i < sqrt(size); ++i)
	{
		val[possiableC[i]] = 1;
		val[possiableR[i]] = 1;
		val[possiableS[i]] = 1;
	}
	free(possiableC);
	free(possiableR);
	free(possiableS);
	int count = 0;
	for (int j = 0; j < size ; ++j)
	{
		if(val[j] == 0 )
		{
			node->possible[count] = j;
			++count;
		}
	}
	free(val);
	return count;
}





Node* getNodeFromBoard(int row, int colume, pBoard board)
{
	//int offset = i * cols + j;
// now mat[offset] corresponds to m(i, j)
	//for row-major ordering and
	//int offset = i + rows * j;
	return board->sBoard[row + board->size * colume];
}

Node* copyNode(Node* node)
{
	Node* newcopy = createNode(node->size);
	newcopy->value = node->value;
	newcopy->row = node->row;
	newcopy->colume = node->colume;

	size_t temp = sizeof(node->possible);
	for (int i = 0; i <  temp ; ++i)
	{
		newcopy->possible[i] = node->possible[i];
	}
	return (newcopy);
}

void freeNodeFunc1(pNode node)
{
	pBoard board = (pBoard) node;
	int size = board->size;
	for (int i = 0; i < size ; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			freeNode(getNodeFromBoard(i, j, board));
		}
	}
	free(board->sBoard);// ? do i want to do that ?
	free(board); // ? do i want to do that ?
}

/**
 * getVal A function that gets a node and returns its value, as int
 * @return  number of cells that are already full in teh board
 */

unsigned int getNodeValFunc1(pNode node)
{
	pBoard board = (pBoard) node;
	int size = board->size;
	unsigned int counter = 0;
	for (int i = 0; i < size ; ++i)
	{
		for (int j = 0; j < size ; ++j)
		{
			if (getNodeFromBoard(i, j, board)->value != EMPTY)
			{
				++counter;
			}
		}
	}
	return counter;
}

void freeNode(Node* node)
{
	free(node->possible);
	free(node);
}
/**
 * freeNode A function that frees node from memory.
 * this function will be called for each Node returns by getChilds.
 */

/**
 * copy A function that do deep copy of Node.
 * @return
 */

pNode copyNodeFunc1(pNode board)
{
	pBoard node = (pBoard) board;
	pBoard newboard = createSudoBoard(node->size);
	newboard->size = node->size;
	for (int i = 0; i < sizeof(node->sBoard) ; ++i)
	{
		newboard->sBoard[i] = copyNode((node->sBoard[i]));
	}
	return newboard;
}

