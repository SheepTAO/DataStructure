/*
************************************************
***Author: SheepTAO
***File description: 二叉树的基本操作
************************************************
*/

#include <iostream>
#include <queue>

using std::cout;
using std::endl;
using std::queue;
using ElemType = int;

// 基本二叉树
typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lChild, *rChild;
}BiTNode;

// 线索二叉树
typedef struct ThreadNode {
    ElemType data;
    struct ThreadNode *lChild, *rChild;
    int lTag, rTag;
}ThreadNode;

void InsertNode(BiTNode*&, ElemType);                                   // 插入节点
void PreOrder(const BiTNode*);                                          // 先序遍历
void InOrder(const BiTNode*);                                           // 中序遍历
void PostOrder(const BiTNode*);                                         // 后序遍历
void LevelOrder(BiTNode*);                                              // 层次遍历
void InsertThread(ThreadNode*&, ElemType);                              // 插入线索二叉树
void InThread(const BiTNode*, ThreadNode*&);
ThreadNode* CreateInThread(const BiTNode*);                      // 生成中序线索二叉树

int main()
{
    BiTNode* tree = nullptr;
    int dataArr[] = {42, 63, 15, 78, 23, 99, 65, 30, 73, 88, 12};
    size_t size = sizeof(dataArr)/sizeof(dataArr[0]);

    for (size_t i = 0; i < size; ++i) {
        InsertNode(tree, dataArr[i]);
    }
    cout << "PreOrder:\t"; InOrder(tree);  cout << endl;
    cout << "LevelOrder:\t"; LevelOrder(tree);   cout << endl;

    return 0;
}

void InsertNode(BiTNode*& node, ElemType data) {
    if (!node) {
        node = new BiTNode;
        node->data = data;
        node->lChild = nullptr;
        node->rChild = nullptr;
    } else {
        if (data < node->data)
            InsertNode(node->lChild, data);
        else 
            InsertNode(node->rChild, data);
    }
}

void PreOrder(const BiTNode *node) {
    if (node) {
        cout << node->data << '\t';
        PreOrder(node->lChild);
        PreOrder(node->rChild);
    }
}

void InOrder(const BiTNode *node) {
    if (node) {
        InOrder(node->lChild);
        cout << node->data << '\t';
        InOrder(node->rChild);
    }
}

void PostOrder(const BiTNode *node) {
    if (node) {
        PostOrder(node->lChild);
        PostOrder(node->rChild);
        cout << node->data << '\t';
    }
}

void LevelOrder(BiTNode *node) {
    if (node) {
        queue<BiTNode*> q;
        q.push(node);
        while(!q.empty()) {
            cout << q.front()->data << '\t';
            if (q.front()->lChild)                          // 左子树不为空，则左子树根节点入队
                q.push(q.front()->lChild);
            if (q.front()->rChild)                          // 右子树不为空，则右子树根节点入队
                q.push(q.front()->rChild);
            q.pop();
        }
    } else {
        cout << "Empty!!!" << endl;
    }
}

void 

ThreadNode* CreateInThread(const BiTNode *bNode) {
    ThreadNode *pre = nullptr;
    if (!bNode) {
        InThread(bNode, pre);

    }
}