/*
************************************************
***Author: SheepTAO
***File description: 中缀表达式转后缀表达式
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