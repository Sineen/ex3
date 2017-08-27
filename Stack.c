//
// Created by sineen on 8/27/17.
//

#include <stdio.h>
#include "Stack.h"

//void initStack(stack s)
//{
//	s.stk; // maloc??
//	s.top = -1;
//}

/*  Function to add an element to the stack */
void push (stack s, pNode num)
{
	if (s.top == (MAXSIZE - 1))
	{
//		fprintf ("Stack is Full\n");
	}
	else
	{
//	push  the element to the stack  ");
		s.top = s.top + 1;
		s.stk[s.top] = num;
	}
}

/*  Function to delete an element from the stack */
pNode pop (stack s)
{
	if (s.top == - 1)
	{
//		printf ("Stack is Empty\n");
		return (NULL);
	}
	else
	{
		s.top = s.top - 1;
		return(s.stk[s.top]);
//		"poped element is = %dn", s.stk[s.top]);

	}
}
///*  Function to display the status of the stack */
//void display ()
//{
//	int i;
//	if (s.top == -1)
//	{
////		printf ("Stack is empty\n");
//		return;
//	}
//	else
//	{
////		printf ("\n The status of the stack is \n");
//		for (i = s.top; i >= 0; i--)
//		{
//			printf ("%d\n", s.stk[i]);
//		}
//	}
//	printf ("\n");
//}
