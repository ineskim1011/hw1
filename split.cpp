/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef>

void split(Node*& in, Node*& odds, Node*& evens)
{
	// returns if there is nothing stored in "in" list 
  if (!in) {
    return;
  }
  
	// head recursion 
	// passes in address of next element in list as well 
	// as current positions in evens and odds lists
  split(in->next, odds, evens);

	// CASE #1: current element in list is even 
  if (in->value % 2 == 0) {
    // set next item in list equal to current evens address
		in->next = evens;
		// set current evens address equal to current item in list 
    evens = in;
		// set current item in list pointer equal to NULL
    in = NULL;
  }
	// CASE #2: current element in list is odd 
  else {
		// set next item in list equal to current odds address
    in->next = odds;
		// set current odds address equal to current item in list 
    odds = in;
		// set current item in list pointer equal to NULL
    in = NULL;
    
  }
}