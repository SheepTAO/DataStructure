//单链表(有头结点)
#include <iostream>
using namespace std;
typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode* next;
}LNode;

void InitList(LNode *&);                            //初始化list
void ListHeadInsert(LNode *&);                      //头插法
void ListTailInsert(LNode *&);                      //尾插法
void DisplayList(LNode *);                          //打印链表
bool GetElem(LNode *, int &, int &);                //按序号查找
bool LocateElem(LNode *, int &, ElemType &);        //按值查找
LNode *GetPtr(LNode *, int);                        //寻找前驱结点(有待优化)
bool TailInsert(LNode *, int, ElemType);            //尾插法插入数据
bool HeadInsert(LNode *, int, ElemType);            //头插法插入数据
bool DeleteElem(LNode*, int);                       //删除结点
int GetListLength(LNode*);                          //求表长

//主函数
int main() {
    LNode* list = nullptr;
    int choice;
    int index;
    ElemType data;

    cout << "SingleList test menu(1-ListHeadInsert,2-ListTailInsert,3-GetElem,4-LocateElem,\n"
            "5-TailInsert,6-HeadInsert,7-DeleteData,8-GetLength,9-Display,0-exit):";
    cin >> choice;
    while(choice != 0) {
        switch(choice){
            case 1:
                ListHeadInsert(list);
                break;
            case 2:
                ListTailInsert(list);
                break;
            case 3:
                cout << "Which index you want to know(max is " << list->data << "):";
                cin >> index;
                if(GetElem(list, index, data)) {
                    cout << "It is " << data << endl;
                } else {
                    cout << "Error!" << endl;
                }
                break;
            case 4:
                cout << "Input you want to know elem:";
                cin >> index;
                if(LocateElem(list, index, data)) {
                    cout << data << " is in " << index << endl;
                } else {
                    cout << "Error!" << endl;
                }
                break;
            case 5:
                cout << "Input you where you want to insert and data:";
                cin >> index >> data;
                if(TailInsert(list, index, data)) {
                    cout << "Done!" << endl;
                } else {
                    cout << "Error!" << endl;
                }
                break;
            case 6:
                cout << "Input you where you want to insert and data:";
                cin >> index >> data;
                if(HeadInsert(list, index, data)) {
                    cout << "Done!" << endl;
                } else {
                    cout << "Error!" << endl;
                }
                break;
            case 7:
                cout << "Input which you want to delete:";
                cin >> index;
                if(DeleteElem(list, index)) {
                    cout << "Done!" << endl;
                } else {
                    cout << "Error!" << endl;
                }
                break;
            case 8:
                cout << "This list's length is " << GetListLength(list) << endl;
                break;
            case 9:
                DisplayList(list);
                break;
            default:
                cout << "Error! Try again." << endl;
                break;
        }
        cout << "Continue or exit:";
        cin >> choice;
    }

    return 0;
}

void InitList(LNode *&l)
{
    if(l == nullptr) {
        l = new LNode;
        l->data = 0;
        l->next = nullptr;
    }
}

void ListHeadInsert(LNode *&l)
{
    ElemType data;
    LNode *s;

    InitList(l);
    cout << "HeadInsert input data(-1 to stop):";
    cin >> data;
    while(data != -1) {
        s = new LNode;
        s->data = data;
        s->next = l->next;
        l->next = s;
        ++(l->data);
        cout << "Input next data:";
        cin >> data;
    }
}

void ListTailInsert(LNode *&l)
{
    ElemType data;
    LNode *s, *p;

    InitList(l);
    p = l;
    while(p->next) {
        p = p->next;
    }
    cout << "TailInsert input data(-1 to stop):";
    cin >> data;
    while(data != -1) {
        s = new LNode;
        s->data = data;
        p->next = s;
        p = s;                  //保持p指针始终指向尾结点
        ++(l->data);
        cout << "Input next data:";
        cin >> data;
    }
    p->next = nullptr;          //尾结点的next指向空
}

bool GetElem(LNode *l, int& count, int &elem)
{
    int index = 0;

    if(count < 0 || count > l->data) {
        return false;
    } else {
        l = l->next;
        while(l->next && index++ < count) {
            l = l->next;
        }
        elem = l->data;
        return true;
    }
}

bool LocateElem(LNode *l, int& count, ElemType &elem)
{
    int index = 0;

    l = l->next;
    while(l->next) {
        ++index;
        if(l->data == elem) {
            count = index;
            return true;
        }
        l = l->next;
    }
    return false;
}

LNode *GetPtr(LNode *l, int i)
{
    int index = 1;

    l = l->next;
    while(index++ < i) {
        l = l->next;
    }
    return l;
}

bool TailInsert(LNode* l, int i, int data)
{
    LNode* s;
    LNode* p = l;

    if(i < 1 || i > l->data) {
        return false;
    } else {
        l = GetPtr(l, i);
        s = new LNode;
        s->data = data;
        s->next = l->next;
        l->next = s;
        ++(p->data);                  //头结点长度数据长度+1
        return true;
    }
}

bool HeadInsert(LNode* l, int i, int data)
{
    LNode* s;
    LNode* p = l;
    ElemType temp;

    if(i < 1 || i > l->data) {
        return false;
    } else {
        l = GetPtr(l, i);
        s = new LNode;
        s->data = data;
        s->next = l->next;
        l->next = s;
        temp = l->data;
        l->data = s->data;
        s->data = temp;
        ++(p->data);
        return true;
    }
}

bool DeleteElem(LNode* l, int i)
{
    LNode* s;
    LNode* p = l;

    if(i < 1 || i > l->data) {
        return false;
    } else if(i == 1) {
        s = l->next;
        l->next = s->next;
    } else {
        l = GetPtr(l, i-1);
        s = l->next;
        l->next = s->next;
    }
    cout << s->data << " has been deleted." << endl;
    --(p->data);
    delete s;
    return true;
}

int GetListLength(LNode* l)
{
    int length = 0;

    l = l->next;
    while(l) {
        l = l->next;
        ++length;
    }
    return length;
}

void DisplayList(LNode *l)
{
     int i = 0;

     cout << "Data Length is " << l->data << endl;
     l = l->next;
     while(l != nullptr) {
         cout << "Data[" << i++ << "] = " << l->data << endl;
         l = l->next;
     }
}
