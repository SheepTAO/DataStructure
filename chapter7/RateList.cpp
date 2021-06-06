//
// Created by archtao on 2021/6/6.
//
// 链表（带头结点）中的元素按访问比率从高到低排序
#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using ElemType = int;

// 因为访问概率高的将放到最前面，因为在每一次访问后有大量的元素移动，所以采用链表。
typedef struct RLTable {
    ElemType data;                                                                  // 当前结点的元素
    struct RLTable* next;                                                           // 指向下一个结点的指针
    size_t rate;                                                                    // 当前结点已被访问的次数
}RLTable;

void InitRLTable(RLTable*&);                                                        // 初始化链表
void InsertRLTable(RLTable*&, ElemType);                                            // 插入结点
RLTable* Search(RLTable*, ElemType);                                                // 查找结点数据并更新访问次数和位置
void ShowInfo(const RLTable*);                                                      // 打印数据
void ClearTable(RLTable*);                                                          // 清空链表

int main()
{
    int arr[] = { 11,22,33,44,55,66,77,88,99 };
    size_t len = sizeof(arr)/sizeof(arr[1]);
    RLTable* table;

    InitRLTable(table);
    for (size_t i = 0; i < len; ++i)
        InsertRLTable(table, arr[i]);
    ShowInfo(table);
    Search(table, 11);
    Search(table, 11);
    Search(table, 22);
    Search(table, 55);
    ShowInfo(table);

    ClearTable(table);

    return 0;
}

void InitRLTable(RLTable*& table) {
    table = new RLTable;
    table->next = nullptr;
    table->data = 0;
    table->rate = 0;
}

// 增（头插法）
void InsertRLTable(RLTable*& table, ElemType data) {
    auto temp = new RLTable;
    temp->data = data;
    temp->next = nullptr;
    temp->rate = 0;

    temp->next = table->next;
    table->next = temp;
    ++table->data;
}

// 算法描述:查找相应的元素，如果查找到则加其rate访问次数加一更将其前移到第一个小于rate的后面
//         或者移动到标头，则链表整体根据“访问比率rate”来降序排列
RLTable* Search(RLTable* table, const ElemType data) {
    RLTable* p = table->next;                                                           // 工作指针
    RLTable* pre = table;                                                               // 前驱指针

    while (p) {
        if (p->data == data)
            break;
        pre = p;                                                                        // 更新前驱指针
        p = p->next;                                                                    // 更新工作指针
    }
    if (p) {                                                                            // 查找到结点
        ++(p->rate);                                                                    // 访问次数加一
        pre->next = p->next;                                                            // 摘下工作结点等待插入
        pre = table;                                                                    // 重置pre为待插入结点的前驱指针
        while (p->rate < pre->next->rate)                                               // 寻找待插入位置的前驱
            pre = pre->next;
        p->next = pre->next;                                                            // 插入相应的位置
        pre->next = p;
    }

    return p;                                                                           // 返回查找指针
}

void ShowInfo(const RLTable* table) {
    auto ptr = table->next;
    while (ptr) {
        std::cout << "(" << ptr->data << "," << ptr->rate << ")->";
        ptr = ptr->next;
    }
    std::cout << "null" << std::endl;
}

void ClearTable(RLTable* table) {
    RLTable* del;
    while (table) {
        del = table;
        table = table->next;
        delete del;
    }
}