/*
************************************************
***Author: SheepTAO
***File description: 中缀表达式转后缀表达式
中缀表达式转换成后缀表达式算法思想
1.从左向右开始扫描中缀表达式
2.遇到数字时，加入后缀表达式
3.遇到运算符时：
    a.若为'(',入栈
    b.若为')',则一次把栈中的运算符加入后缀表达式，直到出现'('，从栈中删除'('
    c.若为除括号外的其他运算符，当其优先级高于除'('外的栈顶元素时，直接入栈。否则从栈顶开始，
      依次弹出比当前处理的运算符优先级高和优先级相等的运算符，直到一个比它优先级低的或遇到一
      个')'为之
************************************************
*/

#include <iostream>
#include <stack>
#include <string>

using std::cout;
using std::endl;
using std::string;
using std::stack;

int GetPriority(const char);
string ChangeExpression(const string);

int main()
{
    string str = "a+b-a*((c+d)/e-f)+g";

    str = ChangeExpression(str);
    cout << str << endl;

    return 0;
}

int GetPriority(const char op) {
    switch (op) {
        case '*': return 5;
        case '/': return 5;
        case '+': return 4;
        case '-': return 4;
        default : return 0;
    }
}

string ChangeExpression(const string str) {
    stack<char> s;
    string retStr;
    size_t length = str.size();

    for(size_t i = 0; i < length; ++i) {
        if ('a' <= str[i] && str[i] <= 'z') {
            retStr += str[i];
        } else {
            if (s.empty() || GetPriority(str[i]) > GetPriority(s.top()) || str[i] == '(') {
                s.push(str[i]);
            } else if (str[i] == ')') {
                while (s.top() != '(') {
                    retStr += s.top();
                    s.pop();
                }
                s.pop();
            } else {
                while (!s.empty() && GetPriority(s.top()) >= GetPriority(str[i]) && s.top() != '(') {
                    retStr += s.top();
                    s.pop();
                }
                s.push(str[i]);
            }
        }
    }
    while (!s.empty()) {
        retStr += s.top();
        s.pop();
    }
    
    return retStr;
}