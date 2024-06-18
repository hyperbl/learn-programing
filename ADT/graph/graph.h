/*graph.h -- 图ADT*/
#ifndef GRAPH_H_
#define GRAPH_H_
#include "../element.h"

typedef enum {DIGRAPH, UNDIGRAPH} GraphKind;   // 图的种类类型：有向图/无向图

#ifdef USE_ADJMAT          // 邻接矩阵表示法

typedef ElementType Vertex;   // 定义顶点类型
typedef Vertex * AdjMat;      // 定义弧类型

typedef struct graph   
{
    GraphKind kind;
    int vexNum;     // 顶点数
    int arcNum;     // 弧数
    Vertex * vexs;   // 顶点组
    AdjMat * arcs;    // 邻接矩阵，对于无权图，用1或0表示相邻否；对于带权图，则表示该弧的权值。
} * Graph;

#define Graph_init Graph_init_mat
#define Graph_free Graph_free_mat

#else
#ifdef USE_ADJLIST

typedef ElementType VertexType;

typedef struct VNode
{
    VertexType data;
    struct VNode * firstArc;
} VNode;

typedef VNode * AdjList;

typedef struct graph
{
    GraphKind kind;
    int vexNum;
    int arcNum;
    AdjList * vertices;
} * Graph;

#define Graph_init Graph_init_list
#define Graph_free Graph_free_list

#else
#error Unknown USE_Type
#endif

#endif

// 以下是图的一些函数的原型

// 初始化图
Graph Graph_init(GraphKind kind, int vexNum, int arcNum);

// 删除图
void Graph_free(Graph G);

#endif