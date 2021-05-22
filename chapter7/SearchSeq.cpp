/*
************************************************
***Author: SheepTAO
***File description: 顺序查找的基本操作
************************************************
*/

#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using ElemType = int;

typedef struct {
    ElemType *data;
    size_t tableLen;
}SSTable;

void InitSSTable(SSTable&, ElemType*, size_t);                          // 初始化顺序表
void BubbleSort(SSTable&);                                              // 冒泡排序 
void DisplaySSTable(const SSTable&);                                    // 打印顺序表
size_t SearchSeq(const SSTable&, const ElemType);                       // 顺序查找元素
void Clear(SSTable&);                                                   // 回收工作            

int main()
{
    ElemType data[] = {15, 36, 78, 45, 12, 46, 82, 64, 19, 35, 28, 67};
    SSTable ss;
    ElemType key;

    InitSSTable(ss, data, sizeof(data)/sizeof(data[0]));

    cout << "Before sort:" << endl;
    DisplaySSTable(ss);
    cout << endl;

    cout << "After sort:" << endl;
    BubbleSort(ss);
    DisplaySSTable(ss);
    cout << endl;
    // cout << "Search Num:";
    // cin >> key;
    // if (SearchSeq(ss, key))
    //     cout << "Find!" << endl;
    // else
    //     cout << "Error!" << endl;

    Clear(ss);
    return 0;
}

void InitSSTable(SSTable& table, ElemType* data, size_t size) {
    size = size + 1;

    table.data = new ElemType[size];
    for (size_t i = 1; i < size; ++i) {
        table.data[i] = data[i-1];
    }
    table.tableLen = size;
}

void BubbleSort(SSTable& table) {
    ElemType temp;

    for (size_t i = 2; i < table.tableLen; ++i) {
        for (size_t j = 1; j < i; ++j) {
            if (table.data[j] > table.data[i]) {
                temp = table.data[j];
                table.data[j] = table.data[i];
                table.data[i] = temp;
            }
        }
    }
}

void DisplaySSTable(const SSTable& table) {
    for (size_t i = 1; i < table.tableLen; ++i) {
        cout << table.data[i] << '\t';
    }
}

size_t SearchSeq(const SSTable& table, const ElemType key) {
    table.data[0] = key;                            // “哨兵”
    size_t i = table.tableLen;

    for (; table.data[i] != key; --i);              // 从后往前查找
    
    return i;
}

void Clear(SSTable& table) {
    delete table.data;
}