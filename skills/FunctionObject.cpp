/*
************************************************
***Author: SheepTAO
***File description: 函数对象-函数传参时传递参数
************************************************
*/
#include <iostream>
#include <functional>

using std::cout;
using std::endl;

typedef int(*pf)(int, int);                 // 第一种方式：定义一个函数指针类型，函数名就是指针
typedef int FuncType(int, int);             // 第二种方式：定义一个FuncType这种函数数据类型

int func1(pf func, int a, int b) {
    return func(a, b);
}

int func2(FuncType func, int a, int b) {
    return func(a, b);
}

int func3(int func(int, int), int a, int b) {        // 第三种方式：定义一个函数实例
    return func(a, b);
}

int add(int a, int b) {
    return a + b;
}

int main()
{
    int(*func4)(int, int) = add;                     // 第四种方式

    cout << "Func1:" << func1(add, 1, 2) << endl;
    cout << "Func2:" << func2(add, 1, 2) << endl;
    cout << "Func3:" << func3(add, 1, 2) << endl;
    cout << "Func4:" << func4(1, 2) << endl;

    return 0;
}