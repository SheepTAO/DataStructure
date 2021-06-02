//
// Created by archtao on 2021/5/31.
//

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void GetNext(string, int*);                                                     // 获取next数组
void GetNextVal(string, int*);                                                  // next数组优化
int IndexKMP(string, string, const int*);                                       // KMP算法

int main()
{
    string s = "$abaacaabcabaabc";
    string t = "$abaabc";
    int next[t.length()];
    GetNext(t, next);
    for (int i = 1; i < t.length(); ++i) {
        cout << next[i] << "\t";
    }
    cout << endl;
    cout << "Position: " << IndexKMP(s, t, next) << endl;

    return 0;
}

void GetNext(string t, int* next) {
    int i = 1, j = 0;
    next[1] = 0;
    while (i < t.length()) {
        if (0 == j || t[i] == t[j]) {
            ++i;
            ++j;
            next[i] = j;
        } else {
            j = next[j];
        }
    }
}

int IndexKMP(string s, string t, const int* next) {
    int i = 1, j = 1;
    while (i <= s.length() && j <= t.length()) {
        if (0 == j || s[i] == t[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }
    if (j > t.length())
        return i - t.length();
    else
        return 0;
}

