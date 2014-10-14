// useIntList.c - testing IntList data type

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "IntList.h"

int main(int argc, char *argv[])
{
	IntList l = newIntList();

	//myList = getIntList(stdin);
	//showIntList(myList);
	//assert(IntListOK(myList));

	//myOtherList = IntListSortedCopy(myList);
	//printf("Sorted:\n");
	//showIntList(myOtherList);
	//assert(IntListOK(myOtherList));
	//assert(IntListIsSorted(myOtherList));

	printf("begin insert\n");
	showList(l);
	IntListInsertInOrder(l, 100, 1);
	showList(l);
	IntListInsertInOrder(l, 110, 2);
	showList(l);
	IntListInsertInOrder(l, 90, 3);
	showList(l);
	IntListInsertInOrder(l, 105, 4);
	
	int p = playerPos(l,3);
	
	printf("p is %d\n",p);
	
	showList(l);

	return 0;
	
	
}
