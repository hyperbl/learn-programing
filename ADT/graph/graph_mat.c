/* graph_mat.c -- 以邻接矩阵表示*/
#define USE_ADJMAT
#ifdef USE_ADJLIST
#undef USE_ADJLIST
#endif
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

Graph Graph_init_mat(GraphKind kind, int vexNum, int arcNum)
{
    Graph G = (Graph) malloc(sizeof (struct graph));
    G->kind = kind;
    G->vexNum = vexNum;
    G->arcNum = arcNum;
    G->vexs = (Vertex *) calloc(vexNum, sizeof (Vertex));
    G->arcs = (AdjMat *) calloc(vexNum, sizeof (AdjMat));
    for (int i = 0; i < vexNum; i++)
        G->arcs[i] = (AdjMat) calloc(vexNum, sizeof (Vertex));
    return G;
}

void Graph_free_mat(Graph G)
{
    for (int i = 0; i < G->vexNum; i++)
        free(G->arcs[i]);
    free(G->arcs);
    free(G->vexs);
}