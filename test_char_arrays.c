#include <stdlib.h>
#include <stdio.h>

#define MESSAGE_SIZE 100

typedef char PlayerMessage[MESSAGE_SIZE];

void main () {
	PlayerMessage msgs[3] = { "ad", "b", "c" };
	//char *explore = (char *)msgs[0];
	printf("test: %s\n",msgs[0]);
	
	
}
