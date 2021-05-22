/*
************************************************
***Author: SheepTAO
***File description: 二叉树的基本操作包括线索二叉树
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
// --------------------------------------
void InsertThread(ThreadNode*&, ElemType);                              // 插入线索二叉树
void LinkThread(ThreadNode*&, ThreadNode*&);                            // 链接线索
void InThread(ThreadNode*&, ThreadNode*&);                              // 中序遍历二叉树线索化
void CreateInThread(ThreadNode*&);                                      // 创建中序线索二叉树
ThreadNode* FirstNode(ThreadNode*);                                     // 寻找中序线索二叉树中中序序列下的第一个结点
ThreadNode* NextNode(ThreadNode*);                                      // 寻找下一个结点
void InThreadOrder(ThreadNode*);                                        // 遍历中序线索树
// --------------------------------------
BiTNode* SearchNext(BiTNode*);                                  // 寻找后继结点前驱指针
void SearchNode(BiTNode*&, BiTNode*&, ElemType);                        // 寻找匹配结点并返回此指针和前驱指针
bool DelNode(BiTNode*&, ElemType);                                      // 删除二叉排序树中的结点

int main()
{
    BiTNode* normalTree = nullptr;
    ThreadNode* threadTree = nullptr;
    int dataArr[] = {42, 63, 15, 78, 23, 99, 65, 30, 73, 88, 12, 111};
    size_t size = sizeof(dataArr)/sizeof(dataArr[0]);

    for (size_t i = 0; i < size; ++i) {
        InsertNode(normalTree, dataArr[i]);
    }
    for (size_t i = 0; i < size; ++i) {
        InsertThread(threadTree, dataArr[i]);
    }
    CreateInThread(threadTree);
    cout << "InOrder:\t"; InOrder(normalTree);  cout << endl;
    cout << "LevelOrder:\t"; LevelOrder(normalTree);   cout << endl;
    cout << "InThreadOrder:\t"; InThreadOrder(threadTree);  cout << endl;

    if(DelNode(normalTree, 78)) {
        cout << "Delete Finished." << endl;
        cout << "Now inOrder:\t"; InOrder(normalTree);  cout << endl;
    } else {
        cout << "Delete Failed!" << endl;
    }

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

void PreOrder(const BiTNode* node) {
    if (node) {
        cout << node->data << '\t';
        PreOrder(node->lChild);
        PreOrder(node->rChild);
    }
}

void InOrder(const BiTNode* node) {
    if (node) {
        InOrder(node->lChild);
        cout << node->data << '\t';
        InOrder(node->rChild);
    }
}

void PostOrder(const BiTNode* node) {
    if (node) {
        PostOrder(node->lChild);
        PostOrder(node->rChild);
        cout << node->data << '\t';
    }
}

void LevelOrder(BiTNode* node) {
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

void InsertThread(ThreadNode*& node, ElemType data) {
    if (!node) {
        node = new ThreadNode;
        node->data = data;
        node->lChild = nullptr;
        node->rChild = nullptr;
        node->lTag = -1;
        node->rTag = -1;
    } else {
        if (data < node->data) {
            InsertThread(node->lChild, data);
            node->lTag = 0;                                 // 左孩子存在
        } else {
            InsertThread(node->rChild, data);
            node->rTag = 0;                                 // 右孩子存在
        }
    }
}

void LinkThread(ThreadNode*& p, ThreadNode*& pre) {
    if (!p->lChild) {
        p->lChild = pre;                                    // 左子树为空，建立前驱线索
        p->lTag = 1;
    }
    if (pre && !pre->rChild) {
        pre->rChild = p;                                    // 建立前驱结点的后继线索
        pre->rTag = 1;
    }
    pre = p;                                                // 标记当前结点成为刚刚访问过的结点
}

void InThread(ThreadNode*& p, ThreadNode*& pre) {
    if (p) {
        InThread(p->lChild, pre);
        LinkThread(p, pre);
        InThread(p->rChild, pre);
    }
}

void CreateInThread(ThreadNode*& node) {
    ThreadNode* pre = nullptr;
    if (node) {                                             // 非空二叉树，线索化
        InThread(node, pre);                                // 线索化二叉树
        pre->rChild = nullptr;                              // 处理遍历的最后一个结点
        pre->rTag = 1;
    }
}

ThreadNode* FirstNode(ThreadNode* node) {
    while (node->lTag == 0) {
        node = node->lChild;
    }

    return node;
}

ThreadNode* NextNode(ThreadNode* node) {
    if (node->rTag == 0) 
        return FirstNode(node->rChild);                     // 寻找此结点的直接后继，右子树的最左下角的结点
    else
        return node->rChild;                                // rTag = 1 直接返回后继线索
}

void InThreadOrder(ThreadNode* node) {
    for (ThreadNode* p = FirstNode(node); p != nullptr; p = NextNode(p)) {
        if (p->lTag == 1)
            cout << '\'';
        cout << p->data;
        if (p->rTag == 1)
            cout << '\'';
        cout << '\t';
    }
}

// 中序遍历的直接后继
BiTNode* SearchNext(BiTNode* node) {
    while (node->lChild)
        node = node->lChild;
    return node;
}

// p指向当前结点，pre指向父结点
void SearchNode(BiTNode*& p, BiTNode*& pre, ElemType data) {
    if (p && p->data != data) {
        pre = p;
        if (data < p->data) {
            p = p->lChild;
            SearchNode(p, pre, data);                       // 向左孩子搜索
        }
        else {
            p = p->rChild;
            SearchNode(p, pre, data);                       // 向右孩子搜索
        }
    }
}

bool DelNode(BiTNode*& node, ElemType data) {
    BiTNode* p, *pre;
    pre = nullptr;
    p = node;
    bool LR = false;                                                // 0-左，1-右

    if (!node) {
        return false;                                               // 空树
    } else {
        SearchNode(p, pre, data);
        LR = pre->lChild == p ? 1 : 0;                              // 确定删除是左子树还是右子树
        if (p) {
            if (!p->lChild && !p->rChild) {                         // 删除叶子结点
                if (LR) 
                    pre->lChild = nullptr;
                else
                    pre->rChild = nullptr;
                delete p;
            } else if (p->lChild && !p->rChild) {                   // 只有左孩子
                if (LR)
                    pre->lChild = p->lChild;
                else
                    pre->rChild = p->lChild;
                delete p;
            } else if (p->rChild && !p->lChild) {                   // 只有右孩子
                if (LR)
                    pre->lChild = p->rChild;
                else
                    pre->rChild = p->rChild;
                delete p;
            } else {                                                // 左孩子非空且右孩子非空
                BiTNode* del = SearchNext(p->rChild);
                ElemType newData = del->data;
                DelNode(p, del->data);                              // 回归前三种删除方式
                p->data = newData;
            }
            return true;
        } else {
            return false;                                           // 没有找到该元素
        }
    }
}