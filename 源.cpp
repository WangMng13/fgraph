#include <iostream>
#include<iostream>
using namespace std;
#define MAX_COST 100/* 最大权重,应由用户定义 */
#define MAXVEX 20/* 最大顶点数,应由用户定义 */
typedef char VertexType; /* 顶点类型应由用户定义 */
typedef int EdgeType; /* 边上的权值类型应由用户定义 */

typedef struct EdgeNode/* 边结点  */
{
    int adjvex;/* 邻接点域,存储该顶点对应的下标 */
    EdgeType weight;/* 用于存储权值,对于非网图可以不需要 */
    struct EdgeNode* next;/* 链域,指向下一个邻接点 */
}EdgeNode;

typedef struct VextexNode/* 顶点表结点 */
{
    VertexType data;/* 顶点域,存储顶点信息 */
    EdgeNode* firstedge;/* 边表头指针 */
}VextexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numNodes, numEdges;/* 图中当前顶点数和边数 */
}GraphAdjList;


void CreateALGraph(GraphAdjList* Gp)  //创建有向图
{
    int i, j, k;
    EdgeNode* pe;
    cout << "输入顶点数和边数(空格分隔）:" << endl;
    cin >> Gp->numNodes >> Gp->numEdges;

    for (i = 1; i < Gp->numNodes; i++)    //数组中下标为0不用。
    {
        Gp->adjList[i].data = i;
        Gp->adjList[i].firstedge = NULL;/* 将边表置为空表 */
    }
    cout << "请逐行输入边(vi,vj)的顶点序号i,j和权重（空格分隔）:" << endl;
    for (k = 1; k < Gp->numEdges; k++)/* 建立边表 */
    {

        cin >> i >> j;
        pe = (EdgeNode*)malloc(sizeof(EdgeNode));
        cin >> pe->weight;
        pe->next = Gp->adjList[i].firstedge;//每次插入新的表节点时都是插在第一个位置
        Gp->adjList[i].firstedge = pe;
        pe->adjvex = j;/* 邻接序号为j */

    }
}

void FGraph(GraphAdjList* G, int cost[], int pre[]) { //求多段图
    int i;
    EdgeNode* p;
    p = (EdgeNode*)malloc(sizeof(EdgeNode));
    for (i = G->numEdges; i > 0; i--) {
        p = G->adjList[i].firstedge;//第一个Next结点
        while (p)
        {    //定位顶点表结点为i的所有next结点，从中找出最小的cost,并记录前驱。
            if (cost[p->adjvex] + p->weight < cost[i])
            {
                cost[i] = cost[p->adjvex] + p->weight;
                pre[i] = p->adjvex;
            }
            p = p->next;
        }
    }
}

void getWay(GraphAdjList* G, int pre[])  //获取路径
{
    int i = 1;
    cout << 1;  //以1为路径的起点！
    while (i < G->numNodes)
    {
        cout << "->" << pre[i];
        i = pre[i];
    }
}

int main()
{
    int cost[MAXVEX], pre[MAXVEX];
    int i;
    for (i = 0; i < MAXVEX; i++) {//初始化pre和cost
        pre[i] = -1;
        cost[i] = MAX_COST;
    }
    GraphAdjList* G;
    G = (GraphAdjList*)malloc(sizeof(GraphAdjList));
    CreateALGraph(G);
    cost[G->numNodes] = 0;
    FGraph(G, cost, pre);
    cout << endl;
    cout << "\nAll cost is " << cost[1] << endl;
    cout << "最小成本路径为：";
    getWay(G, pre);
    cout << endl;

    return 0;
}
