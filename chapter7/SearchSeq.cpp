/*
************************************************
***Author: SheepTAO
***File description: 顺序查找的基本操作
************************************************
*/

#include <iostream>

using std::cout;
using std::endl;
using ElemType = int;

typedef struct {
    ElemType *data;
    size_t tableLen;
}SSTable;

void InitSSTable(SSTable&, ElemType*);                                  // 初始化顺序表
void DisplaySSTable(const SSTable&);                                    // 打印顺序表 
size_t SearchSeq(const SSTable&, const ElemType, size_t);                       // 顺序查找元素
void Clear(SSTable&);                                                   // 回收工作            

int main()
{
    ElemType data[] = {15, 36, 78, 45, 12, 46, 82, 64, 19, 35, 28, 67};
    SSTable ss;

    InitSSTable(ss, data, sizeof(data)/sizeof(data[0]));
    DisplaySSTable(ss);     cout << endl;

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

void DisplaySSTable(const SSTable& table) {
    for (size_t i = 1; i < table.tableLen; ++i) {
        cout << table.data[i] << '\t';
    }
}

size_t SearchSeq(const SSTable& table, const ElemType key) {
    table.data[0] = key;                            // “哨兵”
    size_t i = table.tableLen;

    for (; table.data[i] != key; --i);              // 从后网前查找
    
    return i;
}

void Clear(SSTable& table) {
    delete table.data;
}