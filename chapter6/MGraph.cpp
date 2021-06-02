//
// Created by archtao on 2021/6/1.
//
// 邻接矩阵实现图的基本操作 - 仅为算法实现考虑不考虑实际使用
#include <iostream>
#include <queue>
#define MaxVertexNum 100                                                            // 顶点数目最大值

using std::cout;
using std::endl;
using std::queue;
using VertexType = int;                                                             // 顶点的数据类型
using EdgeType = bool;                                                              // 带权图中边上权值的数据类型

typedef struct MGraph {
    VertexType vex[MaxVertexNum];                                                   // 顶点表
    EdgeType edge[MaxVertexNum][MaxVertexNum];                                      // 邻接矩阵，边表
    int vexNum, arcNum;                                                             // 图当前顶点数和弧数
}MGraph;
bool visited[MaxVertexNum];                                                         // 访问标记数组

// --------------------------------------------
void InitNonDirection(MGraph&);                                                      // 初始化无向图的邻接矩阵
bool Adjacent(const MGraph&, VertexType, VertexType);                                // 判断图是否存在边(x, y)
int FirstNeighbor(const MGraph&, VertexType);                                        // 返回图中第一个邻接点
int NextNeighbor(const MGraph&, VertexType, VertexType);                             // 返回图中当前结点的下一个结点
void ResetVisited();                                                                 // 重置访问数组
void BFSTraverse(const MGraph&);                                                     // 广度遍历图中每一个结点
void BFS(const MGraph&, VertexType);                                                 // 广度优先遍历
void DFSTraverse(const MGraph&);                                                     // 深度遍历图中每一个结点
void DFS(const MGraph&, VertexType);                                                 // 深度优先遍历
// --------------------------------------------
#define VISIT(fun) do { \
    ResetVisited();     \
    std::cout << #fun << ":\t";\
    fun;                \
    std::cout << std::endl;    \
} while(0)
// --------------------------------------------

int main()
{
    MGraph g;

    InitNonDirection(g);
    VISIT(BFS(g, 1));
    VISIT(DFS(g, 1));

    return 0;
}

// 生成一个自己定义的图见Graph.png
void InitNonDirection(MGraph& g) {
    for (int i = 0; i < 8; ++i) {
        g.vex[i] = i;
    }

    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            g.edge[i][j] = false;

    g.edge[0][1] = g.edge[1][0] = true;
    g.edge[0][4] = g.edge[4][0] = true;
    g.edge[1][5] = g.edge[5][1] = true;
    g.edge[2][5] = g.edge[5][2] = true;
    g.edge[2][6] = g.edge[6][2] = true;
    g.edge[2][3] = g.edge[3][2] = true;
    g.edge[3][6] = g.edge[6][3] = true;
    g.edge[3][7] = g.edge[7][3] = true;
    g.edge[5][6] = g.edge[6][5] = true;
    g.edge[6][7] = g.edge[7][6] = true;
    g.vexNum = 8;
    g.arcNum = 10;
}

// 判断是否存在边(x, y) 存在返回true 不存在返回false
bool Adjacent(const MGraph& g, VertexType x, VertexType y) {
    return g.edge[x][y];
}

// 求图g中顶点x的第一个邻接点，若有则返回顶点号，若没有或不存在x则返回-1
int FirstNeighbor(const MGraph& g, VertexType x) {
    if (x < 0 || x > g.vexNum)
        return -1;

    for (int i = 0; i < g.vexNum; ++i) {
        if (g.edge[x][i])
            return i;
    }
    return -1;
}

// 返回图g中y结点（x中的邻接点）的下一个邻接点，若y是最后一个则返回-1
int NextNeighbor(const MGraph& g, VertexType x, VertexType y) {
    for (int i = y + 1; i < g.vexNum; ++i) {
        if (g.edge[x][i])
            return i;
    }
    return -1;
}

void ResetVisited() {
    for (bool & i : visited)
        i = false;
}

// 用于遍历非连通图
void BFSTraverse(const MGraph& g) {
    for (int i = 0; i < g.vexNum; ++i)
        visited[i] = false;
    for (int i = 0; i < g.vexNum; ++i)
        if (!visited[i])
            BFS(g, i);
}

// 广度优先遍历类似于二叉树层序遍历法 -要借助队列和访问数组
void BFS(const MGraph& g, VertexType v) {
    queue<VertexType> q;
    cout << g.vex[v] << "\t";
    visited[v] = true;
    q.push(v);
    while (!q.empty()) {
        v = q.front();
        q.pop();
        for (VertexType w = FirstNeighbor(g, v); w >= 0; w = NextNeighbor(g, v, w))
            if (!visited[w]) {
                cout << g.vex[w] << "\t";
                visited[w] = true;
                q.push(w);
            }
    }
}

// 深度优先遍历类似于树的先根遍历法 -要借助递归栈和访问数组
void DFS(const MGraph& g, VertexType v) {
    cout << g.vex[v] << "\t";
    visited[v] = true;
    for (VertexType w = FirstNeighbor(g, v); w >= 0; w = NextNeighbor(g, v, w))                 // 访问v的所有未访问结点
        if (!visited[w])
            DFS(g, w);
}

