// Item.h - String Items for use in GADTs
// Written by John Shepherd, March 2013

#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>
#include <string.h>

typedef struct _item {
	int player;
	int value;
} *Item;

#endif
