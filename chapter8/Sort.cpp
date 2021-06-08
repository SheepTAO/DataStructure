//
// Created by archtao on 2021/6/7.
//
// 因为要C++面向对象考试，所以用类实现一下基本的插入排序算法
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

template<class T>
class Arr {
public:
    Arr();                                                                              // 默认构造函数
    Arr(const T*, int);                                                                 // 初始化数组构造函数
    Arr(const Arr<T>&);                                                                 // 拷贝构造函数
    ~Arr();                                                                             // 析构函数
    Arr<T>& operator=(const Arr<T>&);                                                   // 重载复制函数
    T& operator[](int);                                                                 // 提供索引访问
    const T& operator[](int) const;                                                     // 提供const索引访问
    explicit operator T*();                                                             // 指针转换重载
    explicit operator const T*() const;                                                 // 指针转换const
    int GetLength() const;                                                              // 获取数组长度
// --------------------------------------- 插入排序
    void DISort();                                                                      // 直接插入排序
    void HISort();                                                                      // 折半插入排序
    void ShellSort();                                                                   // 希尔排序
// --------------------------------------- 交换排序
    void BubbleSort();                                                                  // 冒泡排序
    void QuickSort() { QSInner(1, length - 1); }                                // 快排接口
protected:
    int Partition(int, int);
    void QSInner(int, int);                                                             // 快速排序
private:
    T* arr;                                                                             // 数组指针
    int length;                                                                         // 数组长度
};

template<class T>
Arr<T>::Arr() {
    this->arr = nullptr;
    this->length = 0;
}

template<class T>
Arr<T>::Arr(const T* arr, int length) {
    this->length = length + 1;                                                              // 加入“哨兵或暂存空间”元素
    this->arr = new T[this->length];
    for (int i = 0; i < length; ++i)
        this->arr[i + 1] = arr[i];
}

template<class T>
Arr<T>::Arr(const Arr<T>& it) {
    this->length = it.length;
    this->arr = new T[this->length];
    for (int i = 0; i < it.length; ++i)
        this->arr[i] = it.arr[i];
}

template<class T>
Arr<T>::~Arr() {
    delete[] arr;
}

template<class T>
Arr<T>& Arr<T>::operator=(const Arr<T>& it) {
    if (this != &it) {                                                                      // 非自己本身
        if (this->length != it.length) {                                                    // 数组长度不一致
            this->length = it.length;
            this->arr = new T[this->length];
        }
        for (int i = 0; i < it.length; ++i)                                                 // 复制数据
            this->arr[i] = it.arr[i];
    }
    return *this;
}

template<class T>
T& Arr<T>::operator[](int index) {
    return arr[index];
}

template<class T>
const T& Arr<T>::operator[](int index) const {
    return arr[index];
}

template<class T>
Arr<T>::operator T*() {
    return arr;
}

template<class T>
Arr<T>::operator const T*() const {
    return arr;
}

template<class T>
int Arr<T>::GetLength() const {
    return length;
}

template<class T>
void Arr<T>::DISort() {
    int i, j;
    for (i = 2; i < length; ++i)                                                            // 依次将2～n-1插入前面已排序序列
        if (arr[i] < arr[i - 1]) {                                                          // 关键字小于前驱，加入有序表
            arr[0] = arr[i];                                                                // “哨兵”
            for (j = i - 1; arr[0] < arr[j]; --j)                                           // 移动“大”的元素到后面
                arr[j + 1] = arr[j];
            arr[j + 1] = arr[0];                                                            // 插入
        }
}

template<class T>
void Arr<T>::HISort() {
    for (int i = 2; i < length; ++i) {                                                      // 依次将2～n-1插入前面已排序序列
        if (arr[i] < arr[i - 1]) {
            arr[0] = arr[i];                                                                // 暂存待插入元素
            int low = 1;                                                                    // 设置查找范围low
            int high = i - 1;                                                               // 设置查找范围high
            while (low <= high) {                                                           // 折半查找插入位置，low为最终位置
                int mid = (low + high) / 2;
                if (arr[mid] < arr[0])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
            for (int j = i - 1; j >= low; --j)                                              // 移动元素
                arr[j + 1] = arr[j];
            arr[low] = arr[0];                                                              // 插入
        }
    }
}

template<class T>
void Arr<T>::ShellSort() {
    for (int dk = (length - 1) / 2; dk >= 1; dk = dk / 2) {                                 // 步长变化
        for (int i = dk + 1; i < length; ++i) {                                             // 划分排序每一个小区间
            if (arr[i] < arr[i - dk]) {                                                     // 递增
                arr[0] = arr[i];                                                            // 暂存
                int j = i - dk;
                for (; j > 0 && arr[0] < arr[j]; j -= dk)
                    arr[j + dk] = arr[j];
                arr[j + dk] = arr[0];                                                       // 插入
            } //if
        } //for
    } //for
}

template<class T>
void Arr<T>::BubbleSort() {
    for (int i = 1; i < length - 1; ++i) {
        arr[0] = 0;                                                                         // 排序标志位
        for (int j = length - 1; j > i; --j)                                                // 一趟冒泡
            if (arr[j] < arr[j - 1]) {                                                      // 交换
                T temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
                arr[0] = 1;
            }
        if (!arr[0])                                                                        // 本趟遍历后面没有发生交换，说明表已有序
            break;
    }
}

template<class T>
int Arr<T>::Partition(int low, int high) {                                                  // 一次划分
    arr[0] = arr[low];                                                                      // 第一个元素设为枢轴，对表进行划分
    while (low < high) {
        while (low < high && arr[high] >= arr[0])
            --high;
        arr[low] = arr[high];                                                               // 将比枢轴小的元素放到枢轴左边
        while (low < high && arr[low] <= arr[0])
            ++low;
        arr[high] = arr[low];                                                               // 将比枢轴大元素放到枢轴右边
    }
    arr[low] = arr[0];                                                                      // 将枢轴元素放入枢轴（最终位置）
    return low;
}

template<class T>
void Arr<T>::QSInner(int low, int high) {
    if (low < high) {
        int pivotPos = Partition(low, high);
        QSInner(low, pivotPos - 1);
        QSInner(pivotPos + 1, high);
    }
}

// 纯粹自己作非要写这个。。。
template<class ElemType>
ostream& operator<<(ostream& os, Arr<ElemType>& arr) {
    for (int i = 1; i < arr.GetLength(); ++i)
        os << arr[i] << '\t';
    return os;
}

// 测试宏
#define TEST_FUN(object, fun) do { \
    cout << "-----" << #object << '/' << #fun << "-----" << endl; \
    cout << "Before:\t" << (object) << endl; \
    (object).fun();                    \
    cout << "After:\t" << (object) << endl;  \
} while (0)

int main()
{
    int a[] = { 49,38,65,97,76,13,27,49,55,4 };
    int length = sizeof(a)/sizeof(a[0]);
    Arr<int> arr1(a, length);
    Arr<int> arr2(arr1);
    Arr<int> arr3;
    arr3 = arr2;

    TEST_FUN(arr1, HISort);
    TEST_FUN(arr2, ShellSort);
    TEST_FUN(arr3, QuickSort);

    return 0;
}

