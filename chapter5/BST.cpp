//
// Created by archtao on 2021/5/10. Binary Search Tree
//
#include <iostream>
using namespace std;
using ElemType = int;

typedef struct Node{
    ElemType data;
    struct Node* lChild;
    struct Node* rChild;
}Node;

void Insert(Node*&, ElemType);              //插入结点
void PreOrder(Node*);                       //先序遍历
void InOrder(Node*);                        //中序遍历
void PostOrder(Node*);                      //后序遍历
int GetHeight(Node*);                       //获取树的高度
int GetMax(Node*);                          //获取最大值
Node* SearchNode(Node*, ElemType);          //搜索结点
bool DelNode(Node*&, ElemType);             //删除结点

int main()
{
    int arr[]{48, 15, 23, 32, 19, 36, 89, 75, 65};
    int data;
    Node* tree = nullptr;

    for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i) {
        Insert(tree, arr[i]);
    }
    Insert(tree, 16);
    cout << "PreOrder:\t";
    PreOrder(tree);
    cout << endl;
    cout << "InOrder:\t";
    InOrder(tree);
    cout << endl;
    cout << "PostOrder:\t";
    PostOrder(tree);
    cout << endl;

    cout << "TreeHeight:\t" << GetHeight(tree) << endl;
    cout << "The max number is: " << GetMax(tree) << endl;

    cout << "Input search number:";
    cin >> data;
    if (SearchNode(tree, data)) {
        cout << "We get it." << endl;
    } else {
        cout << "It don't exist." << endl;
    }

    return 0;
}

void Insert(Node*& tree, ElemType data)
{
    if (!tree) {
        tree = new Node;
        tree->data = data;
        tree->lChild = nullptr;
        tree->rChild = nullptr;
    } else {
        if (data < tree->data) {
            Insert(tree->lChild, data);
        } else {
            Insert(tree->rChild, data);
        }
    }
}

Node* SearchNode(Node* node, ElemType data)
{
    if (node) {
        if (data == node->data) {
            return node;
        } else if (data < node->data) {
            return SearchNode(node->lChild, data);
        } else {
            return SearchNode(node->rChild, data);
        }
    } else {
        return node;
    }
}

bool DelNode(Node*& node, ElemType data)
{
    if (node->data == data) {
        node->data = data;
    } else {
        Node* parentNode = node;
    }
}

void PreOrder(Node* node)
{
    if (node) {
        cout << node->data << "\t";
        PreOrder(node->lChild);
        PreOrder(node->rChild);
    }
}

// 中序遍历是升序形式
void InOrder(Node* node)
{
    if (node) {
        InOrder(node->lChild);
        cout << node->data << "\t";
        InOrder(node->rChild);
    }
}

void PostOrder(Node* node)
{
    if (node) {
        PostOrder(node->lChild);
        PostOrder(node->rChild);
        cout << node->data << "\t";
    }
}

int GetHeight(Node* node)
{
    int max = 0;

    if (node) {
        int lh = GetHeight(node->lChild);
        int rh = GetHeight(node->rChild);
        max = lh > rh ? lh : rh;
        return max + 1;
    } else {
        return max;
    }
}

int GetMax(Node* node)
{
    if (node) {
        int ml = GetMax(node->lChild);
        int rl = GetMax(node->rChild);
        int max = node->data;
        if (max < ml) {max = ml;}
        if (max < rl) {max = rl;}
        return max;
    } else {
        return -1;
    }
}