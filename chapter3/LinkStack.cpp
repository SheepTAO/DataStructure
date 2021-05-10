//链式栈(暂时放弃，because new 的新的对象也有构造,析构和push,pop)
#include <iostream>
using namespace std;

template<class ElemType>
class LinkStack {
private:
    ElemType data;
    LinkStack<ElemType>* next;
public:
    LinkStack();
    bool IsEmpty();
    bool Push(const ElemType&);
    bool Pop();
    friend ostream& operator<<(ostream& os, const LinkStack<ElemType>& node) {

    }
//    ~LinkStack();
};

template<class ElemType>
LinkStack<ElemType>::LinkStack()
{
    this->data = 0;
    this->next = nullptr;
}

template<class ELemType>
bool LinkStack<ELemType>::IsEmpty()
{
    return this;
}

template<class ElemType>
bool LinkStack<ElemType>::Push(const ElemType& pushData)
{
    LinkStack<ElemType>* newNode = new LinkStack<ElemType>;
    newNode->data = pushData;
    this->next = newNode;
    return true;
}

template<class ElemType>
bool LinkStack<ElemType>::Pop()
{
    if (IsEmpty()) {
        return false;
    } else {
        return true;
    }
    while(!this->next) {
        this = this->next;
    }
}


int main()
{


    return 0;
}

