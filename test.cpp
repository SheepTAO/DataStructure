//
// Created by archtao on 2021/5/10.
//
#include <iostream>
using namespace std;

int main()
{
    int arr[]{1, 2, 3, 4, 5};

    for (int i: arr) {
        cout << "#" << i-1 << "::" << arr[i-1] << endl;
    }

    return 0;
}

