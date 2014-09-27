// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
Edge mkEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	Edge new = {v,w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = wt;
		g->edges[w][v] = wt;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	
	int i = 0;
	int j = 0;
	
	GraphRep *new = malloc(sizeof(GraphRep));
	new->nV = nV;
	new->nE = 0;
	new->edges = malloc(nV*sizeof(int));
	
	for (i = 0; i < nV; i++) {
		new->edges[i] = malloc(nV*sizeof(int));
	}

	printf("check_020\n");
	
	for(i=0;i<nV;i++) {
		for(j=0;j<nV;j++) {
			new->edges[i][j]=0;
		}
	}
	
	return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
	assert(g != NULL);
	// not needed for this lab
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
	assert(g != NULL);
	printf("#vertices=%d, #edges=%d\n\n",g->nV,g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf("%d %s\n",v,names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf("\t%s (%d)\n",names[w],g->edges[v][w]);
			}
		}
		printf("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert(g != NULL && validV(g,src) && validV(g,dest));
	
	int len = 0;
	int i = 0;
	
	int seen[MAXCITIES];
	
	Queue cities = newQueue();
	
	Edge curr;
	curr.v = src;
	
	int** tempPath;
	
	tempPath = malloc(); 
	
	
	while () {
		
		i = 0;
		while (i<g->nV) {
			if(g->edges[curr.v][i] < max)	{
				if(i == dest) {
					
					break;
				}
				curr.w = i;
				QueueJoin(cities,curr);
			}
			i++;
		}
		curr.v = QueueLeave(cities)
	}




	return len;  // dummy ... always claims there is no path

}











