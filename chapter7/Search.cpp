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

void InitSSTable(SSTable&, const ElemType*, size_t);                    // 初始化顺序表
void BubbleSort(SSTable&);                                              // 冒泡排序 
void DisplaySSTable(const SSTable&);                                    // 打印顺序表
size_t SearchSeq(const SSTable&, ElemType);                             // 顺序查找元素
size_t BinarySearch(const SSTable&, ElemType);                          // 二分查找
size_t BSRecursion(const SSTable&, size_t, size_t, ElemType);           // 递归实现二分查找
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

    cout << "Input search num:";
    cin >> key;
    size_t at = BSRecursion(ss, 1, ss.tableLen-1, key);
    if (at)
        cout << "Find! AT:" << at << endl;
    else
        cout << "Not find!" << endl;

    Clear(ss);
    return 0;
}

void InitSSTable(SSTable& table, const ElemType* data, size_t size) {
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

// 顺序查找
size_t SearchSeq(const SSTable& table, const ElemType key) {
    table.data[0] = key;                            // “哨兵”
    size_t i = table.tableLen;

    for (; table.data[i] != key; --i);              // 从后往前查找
    
    return i;                                       // 查找失败返回0，成功返回数组下标
}

// 二分查找 -要求是顺序表且有序
size_t BinarySearch(const SSTable& table, const ElemType key) {
    size_t low = 1;
    size_t high = table.tableLen - 1;

    while (low <= high) {
        size_t mid = (low + high) / 2;
//        cout << mid << '-' << table.data[mid] << endl;
        if (table.data[mid] == key)
            return mid;                             // 查找成功返回数组下标
        else if (key < table.data[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    return 0;                                       // 查找失败返回0
}

// 递归实现二分查找
size_t BSRecursion(const SSTable& table, size_t low, size_t high, const ElemType key) {
    if (low <= high) {
        size_t mid = (low + high) / 2;
        if (table.data[mid] == key)
            return mid;
        else if (key < table.data[mid])
            return BSRecursion(table, low, mid - 1, key);
        else
            return BSRecursion(table, mid + 1, high, key);
    }
    return 0;
}

void Clear(SSTable& table) {
    delete table.data;
}