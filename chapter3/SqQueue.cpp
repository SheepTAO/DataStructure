//顺序队列
#include <iostream>
using namespace std;

template<class ElemType>
class SqQueue {
private:
    const static int MaxSize = 5;
    ElemType data[MaxSize];         //存放队列元素
    int front, rear;                //队头指针和队尾指针
public:
    SqQueue();                      //初始化队列对象
    bool IsEmpty();                 //判断队列是否为空
    bool IsFull();                  //判断队列是否为满
    bool EnQueue(const ElemType&);  //入队
    bool DeQueue();                 //出队
    friend ostream& operator<<(ostream& os, const SqQueue<ElemType>& sq) {
        int sFront = sq.front;
        int sRear = sq.rear;
        while (sFront != sRear) {
            os << "Data[" << sFront << "] = " << sq.data[sFront] << endl;
            sFront = (sFront + 1) % MaxSize;
        }
        return os;
    }
};

template<class ElemType>
SqQueue<ElemType>::SqQueue()
{
    this->front = 0;
    this->rear = 0;
}

template<class ElemType>
bool SqQueue<ElemType>::IsEmpty()
{
    return front == rear;
}

template<class ElemType>
bool SqQueue<ElemType>::IsFull()
{
    return (rear + 1) % MaxSize == front;
}

template<class ELemType>
bool SqQueue<ELemType>::EnQueue(const ELemType& enData)
{
    if (IsFull()) {
        return false;
    } else {
        this->data[rear] = enData;
        rear = (rear + 1) % MaxSize;
        return true;
    }
}

template<class ElemType>
bool SqQueue<ElemType>::DeQueue()
{
    if (IsEmpty()) {
        return false;
    } else {
        cout << this->data[front] << " has been deleted." << endl;
        front = (front + 1) % MaxSize;
        return true;
    }
}

int main()
{
    SqQueue<int> sq;
    int data;
    char choice;

    cout << "------SqQueue Menu------" << endl
         << "1-Push,2-Pop,3-Display,0-exit:";
    cin >> choice;
    while (choice != '0') {
        switch (choice) {
            case '1':
                cout << "Input push data:";
                cin >> data;
                if (sq.EnQueue(data)) {
                    cout << "Done!" << endl;
                } else {
                    cout << "Full!" << endl;
                }
                break;
            case '2':
                if (sq.DeQueue()) {
                    cout << "Done!" << endl;
                } else {
                    cout << "Empty!" << endl;
                }
                break;
            case '3':
                cout << sq << endl;
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
