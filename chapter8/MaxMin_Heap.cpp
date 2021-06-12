//
// Created by archtao on 2021/6/10.
//
// 堆排序 - 大根堆 - 排序 - 递增序列
// 时间复杂度： 建堆O(n),排序O(nlog(2)n)
#include <iostream>

using std::cout;
using std::endl;

#define MAXSIZE 100

typedef struct Heap {
    int list[MAXSIZE];
    int length;
}Heap;

void InitHeap(Heap&, const int*, int);                                              // 初始化堆
void MaxHeapAdjust(Heap&, int, int);                                                // 将以k为根的子树调整为大根堆
void BuildMaxHeap(Heap&);                                                           // 建立大根堆
void SortMaxHeap(Heap&);                                                            // 对大根堆进行排序
void DelElement(Heap&, int);                                                        // 删除一个位置元素
void InsertElement(Heap&, int);                                                     // 插入一个元素
void ShowData(const Heap&);                                                         // 打印数据

int main()
{
    int list[] = { 53, 17, 78, 9, 45, 65, 87, 32 };
    int len = sizeof(list) / sizeof(list[0]);
    Heap heap;

    InitHeap(heap, list, len);
    BuildMaxHeap(heap);
    cout << "Build:\t"; ShowData(heap); cout << endl;
    InsertElement(heap, 63);
    cout << "Ins 63:\t"; ShowData(heap); cout << endl;
    InsertElement(heap, 91);
    cout << "Ins 91:\t"; ShowData(heap); cout << endl;
    DelElement(heap, 3);
    cout << "Del 3:\t"; ShowData(heap); cout << endl;
    DelElement(heap, 1);
    cout << "Del 1:\t"; ShowData(heap); cout << endl;
    SortMaxHeap(heap);
    cout << "Sort:\t"; ShowData(heap); cout << endl;

    return 0;
}

void InitHeap(Heap& heap, const int* l, int len) {
    heap.length = len;
    for (int i = 0; i < len; ++i)                                                   // 下标从1开始
        heap.list[i + 1] = l[i];
}

void BuildMaxHeap(Heap& heap) {
    for (int i = heap.length / 2; i > 0; --i)                                       // 从后往前调整所有非终端结点
        MaxHeapAdjust(heap, i, heap.length);
}

void MaxHeapAdjust(Heap& heap, int k, int len) {
    heap.list[0] = heap.list[k];                                                    // 暂存子树的根结点
    for (int i = 2 * k; i <= len; i *= 2) {                                         // 沿k较大的子结点向下筛选
        if (i < len && heap.list[i] < heap.list[i + 1])                             // 确定较大的元素值最大的子结点
            ++i;
        if (heap.list[0] >= heap.list[i])
            break;                                                                  // 筛选结束
        else {
            heap.list[k] = heap.list[i];                                            // 将list[i]调整到双亲结点上
            k = i;                                                                  // 修改k值，以便继续向下筛选
        }
    }
    heap.list[k] =  heap.list[0];                                                   // 被筛选结点的值放入最终位置
}

void SortMaxHeap(Heap& heap) {
    for (int i = heap.length; i > 1; --i) {                                         // n-1趟的交换和建堆过程
        heap.list[0] = heap.list[1];                                                // 堆顶和堆底元素互换
        heap.list[1] = heap.list[i];
        heap.list[i] = heap.list[0];
        MaxHeapAdjust(heap, 1, i - 1);                                      // 把剩余元素重新整理成大根堆
    }
}

void DelElement(Heap& heap, int k) {
    heap.list[0] = heap.list[k];                                                    // 让当前元素与表底元素互换
    heap.list[k] = heap.list[heap.length];
    heap.list[heap.length] = heap.list[0];

    MaxHeapAdjust(heap, k, --heap.length);                                       // 调整堆，让替换后的元素“下坠”
}

void InsertElement(Heap& heap, int data) {
    if (heap.length > MAXSIZE - 2) {
        cout << "Full Error!" << endl;
        return;
    }
    int i, k;
    heap.list[++heap.length] = data;                                                // 将新元素插入尾部
    heap.list[0] = heap.list[heap.length];                                          // 暂存待插入元素
    for (i = heap.length / 2, k = heap.length; i >= 1; i /= 2) {                    // 插入元素后使其“上升”
        if (heap.list[i] >= heap.list[0])
            break;
        heap.list[k] = heap.list[i];
        k = i;
    }
    heap.list[k] = heap.list[0];                                                    // 插入其对应位置
}

void ShowData(const Heap& heap) {
    for (int i = 1; i <= heap.length; ++i)
        cout << heap.list[i] << "\t";
}
