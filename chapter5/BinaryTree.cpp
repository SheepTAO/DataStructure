/*
************************************************
***Author: SheepTAO
***File description: 二叉树的基本操作包括线索二叉树
************************************************
*/

#include <iostream>
#include <queue>
#include <stack>

using std::cout;
using std::endl;
using std::queue;
using std::stack;
using ElemType = int;

#define MaxSize 100

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

// --------------------------------------
void InsertNode(BiTNode*&, ElemType);                                   // 插入节点
void PreOrder(const BiTNode*);                                          // 先序遍历
void PreOrderNonRecursive(BiTNode*);                                    // 先序遍历非递归
void InOrder(const BiTNode*);                                           // 中序遍历
void InOrderNonRecursive(BiTNode*);                                     // 中序遍历非递归
void PostOrder(const BiTNode*);                                         // 后序遍历
void PostOrderNonRecursive(BiTNode*);                                   // 后序遍历非递归
void LevelOrder(BiTNode*);                                              // 层次遍历
BiTNode* SearchSeq(BiTNode*, ElemType);                                 // 有序表的顺序查找
int DepthTree(const BiTNode*);                                          // 获取树的深度
int BTDepth(BiTNode*);                                                  // 非递归算法获取树的深度
int BTWidth(BiTNode*);                                                  // 统计二叉树宽度(具有结点数目最多那一层结点的个数)
int LeavesCounts(const BiTNode*);                                       // 获取叶子结点的个数
bool IsComplete(BiTNode*);                                              // 判断是否是完全二叉树
// --------------------------------------
void InsertThread(ThreadNode*&, ElemType);                              // 插入线索二叉树
void LinkThread(ThreadNode*&, ThreadNode*&);                            // 链接线索
void InThread(ThreadNode*&, ThreadNode*&);                              // 中序遍历二叉树线索化
void CreateInThread(ThreadNode*&);                                      // 创建中序线索二叉树
ThreadNode* FirstNode(ThreadNode*);                                     // 寻找中序线索二叉树中中序序列下的第一个结点
ThreadNode* NextNode(ThreadNode*);                                      // 寻找下一个结点
void InThreadOrder(ThreadNode*);                                        // 遍历中序线索树
// --------------------------------------
BiTNode* SearchNext(BiTNode*);                                          // 寻找后继结点前驱指针
void SearchNode(BiTNode*&, BiTNode*&, ElemType);                        // 寻找匹配结点并返回此指针和前驱指针
bool DelNode(BiTNode*&, ElemType);                                      // 删除二叉排序树中的结点
// --------------------------------------

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
    cout << "PreOrder:\t"; PreOrder(normalTree); cout << endl;
    cout << "PreOrderNonRecursive:\t"; PreOrderNonRecursive(normalTree); cout << endl;
    cout << "InOrder:\t"; InOrder(normalTree);  cout << endl;
    cout << "InOrderNonRecursive:\t"; InOrderNonRecursive(normalTree); cout << endl;
    cout << "PostOrder:\t"; PostOrder(normalTree); cout << endl;
    cout << "PostOrderNonRecursive:\t"; PostOrderNonRecursive(normalTree); cout << endl;
    cout << "LevelOrder:\t"; LevelOrder(normalTree);   cout << endl;
    cout << "InThreadOrder:\t"; InThreadOrder(threadTree);  cout << endl;

    cout << "Recursive TreeDepth:\t" << DepthTree(normalTree) << endl;
    cout << "Non-Recursive TreeDepth:\t" << BTDepth(normalTree) << endl;
    cout << "TreeWidth:\t" << BTWidth(normalTree) << endl;
    cout << "LeavesCounts:\t" << LeavesCounts(normalTree) << endl;
    cout << std::boolalpha << "IsComplete:\t" << IsComplete(normalTree) << endl;

    if (DelNode(normalTree, 78)) {
        cout << "Delete Finished." << endl;
        cout << "Now InOrder:\t"; InOrder(normalTree);  cout << endl;
    } else {
        cout << "Delete Failed!" << endl;
    }

    if (SearchSeq(normalTree, 99))
        cout << "Find!" << endl;
    else
        cout << "Error!" << endl;

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

// 递归先序遍历
void PreOrder(const BiTNode* node) {
    if (node) {
        cout << node->data << '\t';
        PreOrder(node->lChild);
        PreOrder(node->rChild);
    }
}

// 非递归先序遍历
void PreOrderNonRecursive(BiTNode* node) {
    stack<BiTNode*> s;

    while (node || !s.empty()) {                            // 结点非空 || 栈非空
        if (node) {                                         // 非空结点
            cout << node->data << "\t";                     // 先打印结点数据
            s.push(node);                                   // 将结点入栈
            node = node->lChild;                            // 访问该结点左孩子
        } else {                                            // 空结点
            node = s.top();
            s.pop();                                        // 栈顶结点出栈
            node = node->rChild;                            // 访问该结点右孩子
        }
    }
}

// 递归中序遍历
void InOrder(const BiTNode* node) {
    if (node) {
        InOrder(node->lChild);
        cout << node->data << '\t';
        InOrder(node->rChild);
    }
}

// 非递归中序遍历
void InOrderNonRecursive(BiTNode* node) {
    stack<BiTNode*> s;

    while (node || !s.empty()) {                            // 结点非空 || 栈非空
        if (node) {                                         // 非空结点
            s.push(node);                                   // 该结点入栈
            node = node->lChild;                            // 访问左孩子
        } else {                                            // 空结点
            node = s.top();
            s.pop();
            cout << node->data << "\t";                     // 打印结点数据
            node = node->rChild;                            // 访问右孩子
        }
    }
}

// 递归后序遍历
void PostOrder(const BiTNode* node) {
    if (node) {
        PostOrder(node->lChild);
        PostOrder(node->rChild);
        cout << node->data << '\t';
    }
}

// 非递归后序遍历
void PostOrderNonRecursive(BiTNode* node) {
    stack<BiTNode*> s;
    BiTNode* r = nullptr;

    while (node || !s.empty()) {
        if (node) {                                             // 走到最左边
            s.push(node);
            node = node->lChild;
        } else {
            node = s.top();
            if (node->rChild && node->rChild != r) {            // 如果右孩子非空且未访问过
                node = node->rChild;                            // 转向右孩子
            } else {                                            // 否则为已经访问过结点
                s.pop();                                        // 出栈
                cout << node->data << "\t";
                r = node;                                       // 标记当前结点
                node = nullptr;                                 // 每一次出栈访问完一个结点相当于遍历完以该结点为根的子树，需将node置为nullptr
            }
        } // else
    } // while
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

BiTNode* SearchSeq(BiTNode* node, ElemType data) {
    if (node && node->data != data) {
        if (node->data > data)
            return SearchSeq(node->lChild, data);
        else
            return SearchSeq(node->rChild, data);
    } else {
        return node;
    }
}

int DepthTree(const BiTNode* node) {
    if (node) {
        int hl = DepthTree(node->lChild);
        int hr = DepthTree(node->rChild);

        return hl > hr ? hl + 1 : hr + 1;
    } else {
        return 0;
    } 
}

int BTDepth(BiTNode* node) {
    if (!node) {
        return 0;
    }

    int front = -1, rear = -1;              // 队列的队首指针和队尾指针
    int last = 0, level = 0;                // 每一层的最后一个元素下标和层数
    BiTNode* queue[MaxSize];
    queue[++rear] = node;                   // 根节点入队
    while (front < rear) {
        node = queue[++front];              // 队列元素出队
        if (node->lChild)
            queue[++rear] = node->lChild;   // 左孩子入队
        if (node->rChild)
            queue[++rear] = node->rChild;   // 右孩子入队
        if (front == last) {                // 处理该层最右孩子结点
            level++;                        // 层数加一
            last = rear;                    // 获取下一层最右结点
        }
    }
    return level;
}

int BTWidth(BiTNode* node) {
    if (!node)
        return 0;

    int front = -1, rear = -1;
    int last = 0, width = 1;
    BiTNode* q[MaxSize];
    q[++rear] = node;
    while (front < rear) {
        node = q[++front];
        if (node->lChild)
            q[++rear] = node->lChild;
        if (node->rChild)
            q[++rear] = node->rChild;
        if (front == last) {
            last = rear;
            width = width < last - front ? last - front : width;
        }
    }
    return width;
}

bool IsComplete(BiTNode* node) {
    if (!node)
        return false;

    queue<BiTNode*> q;
    BiTNode* pNode;
    q.push(node);
    while (!q.empty()) {
        pNode = q.front();
        q.pop();
        if (pNode) {                        // 空结点也保存
            q.push(pNode->lChild);
            q.push(pNode->rChild);
        } else {                            // 遇到空结点
            while (!q.empty()) {
                pNode = q.front();
                q.pop();
                if (pNode)
                    return false;
            }
        }
    } // while (!q.empty())

    return true;
}

int LeavesCounts(const BiTNode* node) {
    if (!node) {
        return 0;
    } else if (!node->lChild && !node->rChild) {
        return 1;
    } else {
        return LeavesCounts(node->lChild) + LeavesCounts(node->rChild); 
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