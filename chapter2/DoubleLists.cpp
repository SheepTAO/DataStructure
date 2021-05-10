//双循环链表
#include <iostream>
using namespace std;
typedef int ElemType;

typedef struct DNode{
    ElemType data;
    struct DNode* prior,* next;
}DNode;

void InitDoubleLists(DNode*&, const int*, int);             //初始化双链表
void DisplayForward(DNode*);                                //前向打印
void DisplayBackwards(DNode*);                              //后向打印
bool HeadInsert(DNode*, int, ElemType);                     //头插法插入数据
bool TailInsert(DNode*, int, ElemType);                     //尾插法插入数据
bool DelElem(DNode*, ElemType);                             //删除某个元素
bool GetElem(DNode*, ElemType);                             //查找表中某个元素
void DestroyLists(DNode*);                                  //销毁数据链表(有待优化)


int main()
{
    DNode* list = nullptr;
    int choice = 0;
    int index;
    ElemType data;
    ElemType dataLists[] = {1, 2, 3, 4, 5, 6};
    int size = sizeof(dataLists)/sizeof(dataLists[0]);

    cout << "------DoubleLists MENU------" << endl;
    cout << "1-Init,2-HeadInsert,3-TailInsert,4-DelElem,5-GetElem,8-DisplayForward,9-DisplayBackwards:";
    cin >> choice;
    while(choice != 0) {
        switch(choice) {
            case 1:
                InitDoubleLists(list, dataLists, size);
                break;
            case 2:
                cout << "Input index and data:";
                cin >> index >> data;
                if (HeadInsert(list, index, data)) {
                    cout << "Done!" << endl;
                } else {
                    cout << "Error!" << endl;
                }
                break;
            case 3:
                cout << "Input index and data:";
                cin >> index >> data;
                if (TailInsert(list, index, data)) {
                    cout << "Done!" << endl;
                } else {
                    cout << "Error!" << endl;
                }
                break;
            case 4:
                cout << "Input delete data:";
                cin >> data;
                if (DelElem(list, data)) {
                    cout << "Done!" << endl;
                } else {
                    cout << "Error!" << endl;
                }
                break;
            case 5:
                cout << "Input check data:";
                cin >> data;
                if (GetElem(list, data)) {
                    cout << "Done!" << endl;
                } else {
                    cout << "Error!" << endl;
                }
                break;
            case 8:
                DisplayForward(list);
                break;
            case 9:
                DisplayBackwards(list);
                break;
            default:
                cout << "Error!" << endl;
                break;
        }
        cout << "Continue or exit(0-exit):";
        cin >> choice;
    }
//    DestroyLists(list);

    return 0;
}

void InitDoubleLists(DNode*& list, const int* data, int size)
{
    DNode* newNode,* listPtr;

    if(list == nullptr) {
        list = new DNode;
        list->prior = list;
        list->next = list;
        list->data = 0;
    }
    listPtr = list;
    for(int i = 0; i < size; ++i) {
        newNode = new DNode;
        newNode->data = data[i];
        newNode->prior = listPtr;
        newNode->next = nullptr;
        listPtr->next = newNode;
        listPtr = listPtr->next;
        ++(list->data);
    }
    list->prior = newNode;
    newNode->next = list;
    cout << "Finished!" << endl;
}

bool HeadInsert(DNode* list, int index, ElemType data)
{
    int i = 1;
    DNode* priPtr = list;
    DNode* newNode = nullptr;

    if (index < 1 || index >> list->data) {
        return false;
    } else {
        while(i++ < index) {
            list = list->next;
        }
        newNode = new DNode;
        newNode->data = data;
        newNode->next = list->next;
        newNode->prior = list;
        list->next = newNode;
        ++(priPtr->data);
        return true;
    }
}

bool TailInsert(DNode* list, int index, ElemType data)
{
    int i = 1;
    DNode* head = list;
    DNode* newNode = nullptr;

    if (index < 1 || index > list->data) {
        return false;
    } else {
        list = list->next;
        while(i++ < index) {
            list = list->next;
        }
        newNode = new DNode;
        newNode->data = data;
        newNode->next = list->next;
        newNode->prior = list;
        list->next = newNode;               //newNode的前驱结点的后驱指针指向newNode!!!
        newNode->next->prior = newNode;     //newNode的后驱结点的前驱指针指向newNode!!!
        ++(head->data);
        return true;
    }
}

bool DelElem(DNode* list, ElemType data)
{
    DNode* ptr = list;
    DNode* head = list;

    list = list->next;
    while (list != ptr) {
        if (list->data == data) {
            cout << list->data << " has been deleted." << endl;
            ptr = list->prior;
            ptr->next = list->next;
            list->next->prior = ptr;
            delete list;
            --(head->data);
            return true;
        }
        list = list->next;
    }
    return false;
}

bool GetElem(DNode* list, ElemType data)
{
    DNode* head = list;
    int index = 0;

    list = list->next;
    while (list != head) {
        ++index;
        if (list->data == data) {
            cout << data << " is in " << index << endl;
            return true;
        }
        list = list->next;
    }
    return false;
}

void DisplayForward(DNode* list)
{
    int index = 0;
    DNode* head = list;

    cout << "The list's length is " << list->data << endl;
    list = list->prior;
    while (list != head) {
        cout << "Data[" << index++ << "] = " << list->data << endl;
        list = list->prior;
    }
}

void DisplayBackwards(DNode* list)
{
    int index = 0;
    DNode* head = list;

    cout << "The list's length is " << list->data << endl;
    list = list->next;
    while(head != list) {
        cout << "Data[" << index++ << "] = " << list->data << endl;
        list = list->next;
    }
}

//void DestroyLists(DNode* list)
//{
//    DNode* priPtr = list;
//    DNode* delPtr;
//    while(list->next != priPtr) {
//        delPtr = list;
//        list = list->next;
//        delete delPtr;
//    }
//    delete list->next;
//}

