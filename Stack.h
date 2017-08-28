//
// Created by sineen on 8/27/17.
//

#ifndef EX3_STACK_H
#define EX3_STACK_H

#include "GenericDFS.h"

#define MAXSIZE 500

typedef struct stack
{
	pNode stk[MAXSIZE];
	int top;
}stack;


void push(stack, pNode);
pNode pop(stack);
stack* stackNew();
void freeStack(stack*);


#endif //EX3_STACK_H
