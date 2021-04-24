#include "stdio.h"
#include "stdlib.h"

#define MaxVertexNum 100 //最大顶点数设为100
#define INFINITY 65535  //∞设为双字节无符号整数的最大值65535

typedef int Vertex;     //用顶点下表顶点
typedef int WeightType; //边的权值

typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2;  //有向边
    WeightType Weight; //权重
};
typedef PtrToENode Edge;

//图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv;
    int Ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGNode MGraph;

MGraph CreateGraph( int VertexNum)
{
    Vertex V, W;
    MGraph Graph;

    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (V=0; V < Graph->Nv; V++)
        for (W=0; W < Graph->Nv; W++)
            Graph->G[V][W] = INFINITY;

    return Graph;
}

void InsertEdge (MGraph Graph, Edge E)
{
    //插入边
    Graph->G[E->V1][E->V2] = E->Weight;
    //若是无向图，还要插入边<V2, V1>
    Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    int Nv, i;
    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    scanf("%d", &(Graph->Ne));
    if( Graph->Ne != 0)//如果有边
    {
        E = (Edge)malloc(sizeof(struct ENode)); //建立边结点
        //读入边，格式为“起点 终点 权重”，插入邻接矩阵
        for(i=0; i< Graph->Ne; i++)
        {
            scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
            E->V1--;
            E->V2--;
            InsertEdge( Graph, E );
        }
    }
    return Graph;
}

void Floyd( MGraph Graph, WeightType D[][MaxVertexNum])
{
    Vertex i,j,k;
    //初始化
    for(i=0; i < Graph->Nv; i++)
        for( j=0; j < Graph->Nv; j++)
            D[i][j] = Graph->G[i][j];
    for( k=0; k<Graph->Nv; k++)
        for( i=0; i < Graph->Nv; i++)
            for( j=0; j < Graph->Nv; j++)
                if( D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                }
}

WeightType FindMaxDist( WeightType D[][MaxVertexNum], Vertex i, int N )
{
    WeightType MaxDist;
    Vertex j;

    MaxDist = 0;
    for( j=0; j < N; j++)
    {
        if( i!=j && D[i][j] > MaxDist )
            MaxDist = D[i][j];
    }
    return MaxDist;
}
void FindAnimal( MGraph Graph)
{
    WeightType D[MaxVertexNum][MaxVertexNum], MaxDist, MinDist;
    Vertex Animal, i;

    Floyd( Graph, D );
    
    MinDist = INFINITY;
    for( i=0; i < Graph->Nv; i++)
    {
        MaxDist = FindMaxDist(D, i, Graph->Nv);
        if( MaxDist == INFINITY )
        {
            printf("0\n");
            return;
        }
        if( MinDist > MaxDist)
        {
            MinDist = MaxDist;
            Animal = i + 1;
        }
    }
    printf("%d %d\n", Animal, MinDist);
}

int main()
{
    MGraph G = BuildGraph();
    FindAnimal(G);
    return 0;
}