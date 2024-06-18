/* graph_list.c -- 以邻接表表示*/
#define USE_ADJLIST
#ifdef USE_ADJMAT
#undef USE_ADJMAT
#endif
#include "graph.h"
#include <stdlib.h>

Graph Graph_init_list(GraphKind kind, int vexNum, int arcNum)
{
    Graph G = (Graph) malloc(sizeof (struct graph));
    G->kind = kind;
    G->vexNum = vexNum;
    G->arcNum = arcNum;
    G->vertices = (AdjList *) calloc(vexNum, sizeof (AdjList));
    for (int i = 0; i < vexNum; i++) G->vertices[i] = NULL;
}

void Graph_free_list(Graph G)
{
    for (int i = 0; i < G->vexNum; i++) free(G->vertices[i]);
    free(G->vertices);
}