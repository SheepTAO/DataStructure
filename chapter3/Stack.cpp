//栈(Last in first out, LIFO)
//top始终指向栈顶元素
#include <iostream>
using namespace std;

template<class ElemType>
class Stack{
private:
    const static int MaxSize = 50;
    ElemType data[MaxSize];
    int top;
public:
    Stack();                            //初始化栈
    bool Pop();                         //出栈
    bool Push(ElemType);                //入栈
    bool IsEmpty() {
        return top == -1;
    }
    bool IsFull() {
        return top == MaxSize - 1;
    }
    ElemType GetTop() const;
    friend ostream& operator<<(ostream& os, const Stack<ElemType>& stack) {
        int innerTop = stack.top;
        while (innerTop != -1) {
            os << "Data[" << innerTop+1 << "] = " << stack.data[innerTop] << endl;
            --innerTop;
        }
        return os;
    }
    ~Stack();
};

template<class ElemType>
Stack<ElemType>::Stack()
{
    top = -1;
}

template<class ElemType>
bool Stack<ElemType>::Pop()
{
    if (IsEmpty()) {
        return false;
    } else {
        cout << data[top] << " has been pop." << endl;
        --top;
        return true;
    }
}

template<class ElemType>
bool Stack<ElemType>::Push(ElemType elemData)
{
    if (IsFull()) {
        return false;
    } else {
        ++top;
        this->data[top] = elemData;
        return true;
    }
}

template<class ElemType>
ElemType Stack<ElemType>::GetTop() const
{
    return this->data[top];
}

template<class ElemType>
Stack<ElemType>::~Stack()
{
    top = -1;
}

int main()
{
    Stack<int> stack;
    int data;
    char choice;

    cout << "------Stack Menu------" << endl
    << "1-Push,2-Pop,3-Display,4-GetTop,0-exit:";
    cin >> choice;
    while (choice != '0') {
        switch (choice) {
            case '1':
                cout << "Input push data:";
                cin >> data;
                if (stack.Push(data)) {
                    cout << "Done!" << endl;
                } else {
                    cout << "Error!" << endl;
                }
                break;
            case '2':
                if (stack.Pop()) {
                    cout << "Done!" << endl;
                } else {
                    cout << "Error!" << endl;
                }
                break;
            case '3':
                cout << stack << endl;
                break;
            case '4':
                cout << "Top data is " << stack.GetTop() << endl;
                break;
            default:
                cout << "Error!" << endl;
                break;
        }
        cout << "Continue or not:";
        cin >> choice;
    }

    return 0;
}

