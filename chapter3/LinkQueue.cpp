//队列的链式存储(带头结点)
#include <iostream>
#include <map>
using namespace std;
typedef int ElemType;

enum StringValue{
    stringValue0,
    stringValue1,
    stringValue2,
    stringValue3,
    stringValue4,
    stringValue5
};
static map<string, StringValue>mapSwitchCase;       //定义mapSwitchCase

typedef struct LinkNode {               //链式队列结点
    ElemType data;
    struct LinkNode* next;
}LinkNode;

typedef struct LinkQueue {              //链式队列
    LinkNode* front,* rear;             //队列的队头和队尾指针
}LinkQueue;

static void InitializeMap();                        //初始化mapSwitchCase容器
void InitQueue(LinkQueue*&);                        //初始化链表
bool IsEmpty(LinkQueue*);                           //判断队空
void EnQueue(LinkQueue*&, ElemType);                //入队
bool DeQueue(LinkQueue*&);                          //出队
ostream& operator<<(ostream&, LinkQueue*);          //打印
void DestroyQueue(LinkQueue*);                      //未实现

int main()
{
    LinkQueue* linkQueue = new LinkQueue;
    int data;
    const int MaxInput = 30;
    string choice;

    InitializeMap();
    InitQueue(linkQueue);
    cout << "------LinkQueue Menu------" << endl
         << "1-Push,2-Pop,3-Display,0-exit:";
    cin >> choice;
    while (mapSwitchCase[choice] != stringValue0) {
        switch (mapSwitchCase[choice]) {
            case stringValue1:
                cout << "Input push data:";
                cin >> data;
                EnQueue(linkQueue, data);
                break;
            case stringValue2:
                if (DeQueue(linkQueue)) {
                    cout << "Done!" << endl;
                } else {
                    cout << "Empty!" << endl;
                }
                break;
            case stringValue3:
                cout << linkQueue << endl;
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

void InitializeMap()
{
    mapSwitchCase["0"] = stringValue0;
    mapSwitchCase["1"] = stringValue1;
    mapSwitchCase["2"] = stringValue2;
    mapSwitchCase["3"] = stringValue3;
    mapSwitchCase["4"] = stringValue4;
    mapSwitchCase["5"] = stringValue5;
}

void InitQueue(LinkQueue*& lq)
{
    lq->front = lq->rear = new LinkNode;
    lq->front->data = 0;
    lq->front->next = nullptr;
}

bool IsEmpty(LinkQueue* lq)
{
    return lq->front == lq->rear;
}

void EnQueue(LinkQueue*& lq, ElemType data)
{
    LinkNode* newNode = new LinkNode;

    newNode->data = data;
    newNode->next = nullptr;
    lq->rear->next = newNode;           //构建链接表
    lq->rear = newNode;                 //尾指针重新指向队尾
    ++(lq->front->data);
}

bool DeQueue(LinkQueue*& lq)
{
    LinkNode* delNode = lq->front;
    if (IsEmpty(lq)) {
        return false;
    } else {
        cout << delNode->data << " has been deleted." << endl;
        lq->front = lq->front->next;            //头指针指向头指针的next
        delete delNode;
        return true;
    }
}

ostream& operator<<(ostream& os, LinkQueue* lq)
{
    if (IsEmpty(lq)) {
        os << "This is a empty queue." << endl;
        return os;
    }

    LinkNode* pFront = lq->front->next;
    LinkNode* pRear = lq->rear;
    os << "This queue's length is " << lq->front->data << endl;
    while (pFront) {            //不能写成pFront!=pRear，因为这样最后一个就无法访问
        os << "["  <<  pFront->data << "]->";
        pFront = pFront->next;
    }
    os << "nullptr";
    return os;
}
