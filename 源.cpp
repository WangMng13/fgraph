#include <iostream>
#include<iostream>
using namespace std;
#define MAX_COST 100/* ���Ȩ��,Ӧ���û����� */
#define MAXVEX 20/* ��󶥵���,Ӧ���û����� */
typedef char VertexType; /* ��������Ӧ���û����� */
typedef int EdgeType; /* ���ϵ�Ȩֵ����Ӧ���û����� */

typedef struct EdgeNode/* �߽��  */
{
    int adjvex;/* �ڽӵ���,�洢�ö����Ӧ���±� */
    EdgeType weight;/* ���ڴ洢Ȩֵ,���ڷ���ͼ���Բ���Ҫ */
    struct EdgeNode* next;/* ����,ָ����һ���ڽӵ� */
}EdgeNode;

typedef struct VextexNode/* ������� */
{
    VertexType data;/* ������,�洢������Ϣ */
    EdgeNode* firstedge;/* �߱�ͷָ�� */
}VextexNode, AdjList[MAXVEX];

typedef struct
{
    AdjList adjList;
    int numNodes, numEdges;/* ͼ�е�ǰ�������ͱ��� */
}GraphAdjList;


void CreateALGraph(GraphAdjList* Gp)  //��������ͼ
{
    int i, j, k;
    EdgeNode* pe;
    cout << "���붥�����ͱ���(�ո�ָ���:" << endl;
    cin >> Gp->numNodes >> Gp->numEdges;

    for (i = 1; i < Gp->numNodes; i++)    //�������±�Ϊ0���á�
    {
        Gp->adjList[i].data = i;
        Gp->adjList[i].firstedge = NULL;/* ���߱���Ϊ�ձ� */
    }
    cout << "�����������(vi,vj)�Ķ������i,j��Ȩ�أ��ո�ָ���:" << endl;
    for (k = 1; k < Gp->numEdges; k++)/* �����߱� */
    {

        cin >> i >> j;
        pe = (EdgeNode*)malloc(sizeof(EdgeNode));
        cin >> pe->weight;
        pe->next = Gp->adjList[i].firstedge;//ÿ�β����µı�ڵ�ʱ���ǲ��ڵ�һ��λ��
        Gp->adjList[i].firstedge = pe;
        pe->adjvex = j;/* �ڽ����Ϊj */

    }
}

void FGraph(GraphAdjList* G, int cost[], int pre[]) { //����ͼ
    int i;
    EdgeNode* p;
    p = (EdgeNode*)malloc(sizeof(EdgeNode));
    for (i = G->numEdges; i > 0; i--) {
        p = G->adjList[i].firstedge;//��һ��Next���
        while (p)
        {    //��λ�������Ϊi������next��㣬�����ҳ���С��cost,����¼ǰ����
            if (cost[p->adjvex] + p->weight < cost[i])
            {
                cost[i] = cost[p->adjvex] + p->weight;
                pre[i] = p->adjvex;
            }
            p = p->next;
        }
    }
}

void getWay(GraphAdjList* G, int pre[])  //��ȡ·��
{
    int i = 1;
    cout << 1;  //��1Ϊ·������㣡
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
    for (i = 0; i < MAXVEX; i++) {//��ʼ��pre��cost
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
    cout << "��С�ɱ�·��Ϊ��";
    getWay(G, pre);
    cout << endl;

    return 0;
}
