//
// Created by archtao on 2021/6/12.
//
// 归并排序 - 突然看到我这函数声明我自己都傻了。。。哈哈哈， 这玩意我自己都看不懂用的啥参数
// I try to tell you, but you don't listen.
#include <iostream>

using std::endl;
using std::cout;

void Merge(int*, int, int, int);                                                // 归并
void MergeSort(int[], int, int);                                                // 归并排序
void ShowData(int[], int);                                                      // 打印数据

int main()
{
    int arr[] = { 49, 38, 65, 97, 76, 13, 27 };
    int len = sizeof(arr) / sizeof(arr[0]);

    cout << "Before:\t"; ShowData(arr, len); cout << endl;
    MergeSort(arr, 0, len - 1);
    cout << "After:\t"; ShowData(arr, len); cout << endl;

    return 0;
}

void Merge(int list[], int low, int mid, int high) {
    int assistList[high - low + 1];
    int i, j, k;
    for (k = low; k <= high; ++k)
        assistList[k] = list[k];
    for (i = low, j = mid + 1, k = i; i <= mid && j <= high; ++k) {
        if (assistList[i] <= assistList[j])
            list[k] = assistList[i++];
        else
            list[k] = assistList[j++];
    }
//    检查为遍历完全的表
    while (i <= mid)
        list[k++] = assistList[i++];
    while (j <= high)
        list[k++] = assistList[j++];
}

void MergeSort(int list[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        MergeSort(list, low, mid);
        MergeSort(list, mid + 1, high);
        Merge(list, low, mid, high);
    }
}

void ShowData(int* list, int len) {
    for (int i = 0; i < len; ++i)
        cout << list[i] << '\t';
}

