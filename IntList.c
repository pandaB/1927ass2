// IntList.c - Lists of integers
// Written by John Shepherd, July 2008

#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "IntList.h"

#define TRUE 1
#define FALSE 0
// data structures representing IntList

struct IntListNode {
	int player;
	int data;
	struct IntListNode *next;
	            // pointer to node containing next element
};

struct IntListRep {
	int  size;  // number of elements in list
	struct IntListNode *first;
	            // node containing first value
	struct IntListNode *last;
	            // node containing last value
};

// create a new empty IntList
IntList newIntList()
{
	struct IntListRep *L;

	L = malloc(sizeof (struct IntListRep));
	assert (L != NULL);
	L->size = 0;
	L->first = NULL;
	L->last = NULL;
	return L;
}

// free up all space associated with list
void freeIntList(IntList L)
{
	// does nothing ...
}

void showList(IntList L)
{
	struct IntListNode *curr;
	curr = L->first;
	printf("L->");

	assert(L != NULL);
	if (L->size == 0) {
	} else if (L->size == 1){
		printf("[%d,%d]->",curr->data,curr->player);
	// scan list, looking for out-of-order pair
	} else {
		for (curr = L->first; curr != NULL; curr = curr->next) {
			printf("[%d,%d]->",curr->data,curr->player);
		}
	}
	
	printf("x\n");
}

int getFirstPlayer(IntList L)
{
	return L->first->player;
}

int playerPos(IntList L, int player)
{
	struct IntListNode *curr;
	curr = L->first;

	assert(L != NULL);
	int count = 0;
	for (curr = L->first; curr != NULL; curr = curr->next) {
		if(curr->player == player) {
			break;
		}
		count++;
	}
	return count;
}

// create a new IntListNode with value v, for player w
// (this function is local to this ADT)
static struct IntListNode *newIntListNode(int v, int w)
{
	struct IntListNode *n;

	n = malloc(sizeof (struct IntListNode));
	assert(n != NULL);
	n->data = v;
	n->player = w;
	n->next = NULL;
	
	return n;
}

// apppend one integer to the end of a list
void IntListInsert(IntList L, int v, int w)
{
	struct IntListNode *n;

	assert(L != NULL);
	n = newIntListNode(v,w);
	if (L->first == NULL)
		L->first = L->last = n;
	else {
		L->last->next = n;
		L->last = n;
	}
	L->size++;
}

// insert an integer into correct place in a sorted list
void IntListInsertInOrder(IntList L, int v, int w)
{

	assert(L != NULL);
	
	struct IntListNode *curr;
	struct IntListNode *val = newIntListNode(v,w);

	int inserted = FALSE;

	if (L->size == 0) {
		L->first = val;
		L->last = val;
	} else if(L->size == 1) {
		if(val->data < L->first->data) {
			val->next = L->first;
			L->first = val;
		} else {
			L->last->next = val;
			L->last = val;
		}
	} else {
		if(val->data < L->first->data) {
			val->next = L->first;
			L->first = val;
			inserted = TRUE;
		}
		
		if (!inserted) {
			for (curr = L->first; curr->next != NULL; curr = curr->next) {
				if (curr->next->data > v) {
					inserted = TRUE;
					val->next = curr->next;
					curr->next = val;
					break;
				}
			}
		}
		
		if(!inserted) {
			L->last->next = val;
			L->last = val;
		}	
	}
	L->size++;
}

// delete first occurrence of v from a list
// if v does not occur in List, no effect
void IntListDelete(IntList L, int v)
{
	struct IntListNode *curr, *prev;

	assert(L != NULL);

	// find where v occurs in list
	prev = NULL; curr = L->first;
	while (curr != NULL && curr->data != v) {
		prev = curr;
		curr = curr->next;
	}
	// not found; give up
	if (curr == NULL) return;
	// unlink curr
	if (prev == NULL)
		L->first = curr->next;
	else
		prev->next = curr->next;
	if (L->last == curr)
		L->last = prev;
	L->size--;
	// remove curr
	free(curr);
}

// return number of elements in a list
int IntListLength(IntList L)
{
	assert(L != NULL);
	return L->size;
}

// make a physical copy of a list
// new list looks identical to original list
IntList IntListCopy(IntList L)
{
	struct IntListRep *Lnew;
	struct IntListNode *curr;

	Lnew = newIntList();
	for (curr = L->first; curr != NULL; curr = curr->next)
		IntListInsert(Lnew, curr->data, curr->player);
	return Lnew;
}

// make a sorted physical copy of a list
IntList IntListSortedCopy(IntList L)
{
	struct IntListRep *Lnew;
	struct IntListNode *curr;

	Lnew = newIntList();
	for (curr = L->first; curr != NULL; curr = curr->next)
		IntListInsertInOrder(Lnew, curr->data, curr->player);
	return Lnew;
}

// check whether a list is sorted in ascending order
// returns 0 if list is not sorted, returns non-zero if it is
int IntListIsSorted(IntList L)
{
	struct IntListNode *curr;

	assert(L != NULL);
	// trivial cases, 0 or 1 items
	if (L->size < 2)
		return 1;
	// scan list, looking for out-of-order pair
	for (curr = L->first; curr->next != NULL; curr = curr->next) {
		if (curr->next->data < curr->data)
			return 0;
	}
	// nothing out-of-order, must be sorted
	return 1;
}

// check sanity of an IntList (for debugging)
int IntListOK(IntList L)
{
	struct IntListNode *p;
	int count;

	if (L == NULL)
		return 1;
	if (L->size == 0)
		return (L->first == NULL && L->last == NULL);

	// scan to (but not past) last node
	count = 1; // at least one node
	for (p = L->first; p->next != NULL; p = p->next)
		count++;

	return (count == L->size && p == L->last);
}








