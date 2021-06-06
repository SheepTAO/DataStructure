//
// Created by archtao on 2021/6/2.
//
// 邻接表实现图的基本操作 -仅学习算法而无实际使用意义
#include <iostream>
#include <queue>
#define MaxVertexNum 100

using std::cout;
using std::endl;

typedef struct ArcNode {                                                                // 边表结点
    int adjVex;                                                                         // 该弧所指向顶点位置
    struct ArcNode* next;                                                               // 指向下一条弧的指针
}ArcNode;

