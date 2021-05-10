//二叉树(无意义的   甚至都没有完成)
#include <iostream>
using namespace std;

template<class ElemType>
class BinaryTree {
private:
    typedef struct Node {
        ElemType data;
        struct Node* lChild,* rChild;
    }Node;
    Node* headNode;
public:
    void CreateNode(ElemType&);                 //创建结点
    void InsertNode(ElemType&);                 //插入结点
    void BTInit(ElemType[], int);                    //初始化二叉树
    void PreOrder() const;                      //先序遍历(NLR)
    void InOrder() const;                       //中序遍历(LNR)
    void PostOrder()const;                      //后序遍历(LRN)
    friend ostream& operator<<(ostream& os, BinaryTree<ElemType> bt) {
        os << bt.headNode->data;
        return os;
    }
};

/*template<class ElemType>
bool BinaryTree<ElemType>::LInsert(Node* pNode, const ElemType& data)
{
    if (pNode->lChild) {
        return false;
    } else {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->lChild = nullptr;
        newNode->rChild = nullptr;
        pNode->lChild = newNode;                 //将新的节点挂在二叉树左孩子上
        return true;
    }
}

template<class ElemType>
bool BinaryTree<ElemType>::RInsert(Node* pNode,const ElemType& data)
{
    if (pNode->rChild) {
        return false;
    } else {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->lChild = nullptr;
        newNode->rChild = nullptr;
        pNode->rChild = newNode;                 //将新的节点挂在二叉树右孩子上
        return true;
    }
}*/

/*template<class ElemType>
void BinaryTree<ElemType>::InsertNode()
{
    int choice;
    ElemType data;
    Node* pNode = headNode;
    bool lEmpty;
    bool rEmpty;

    do {
        lEmpty = (pNode->lChild == nullptr);             //刷新左空判断
        rEmpty = (pNode->rChild == nullptr);             //刷新右空判断
        if (!lEmpty && !rEmpty) {
            do {
                cout << "----Go to next node----" << endl << "Input[1-l,2-r]:";
                cin >> choice;
                switch (choice) {
                    case 1:
                        pNode = pNode->lChild;
                        break;
                    case 2:
                        pNode = pNode->rChild;
                        break;
                    default:
                        cout << "Error!" << endl;
                        break;
                }
                lEmpty = (pNode->lChild == nullptr);             //刷新左空判断
                rEmpty = (pNode->rChild == nullptr);             //刷新右空判断
            } while(choice != 1 && choice != 2);
        }
        cout << "Input lChild(" << lEmpty << ") and rChild(" << rEmpty << ")[1-l,2-r,0-exit]:";
        cin >> choice;
        cout << "Input data:";
        cin >> data;
        switch (choice) {
            case 0:
                break;
            case 1:
                if (LInsert(pNode, data)) {
                    cout << "Insert finished." << endl;
                } else {
                    cout << "Insert interrupt." << endl;
                }
                break;
            case 2:
                if (RInsert(pNode, data)) {
                    cout << "Insert finished." << endl;
                } else {
                    cout << "Insert interrupt." << endl;
                }
                break;
            default:
                cout << "Error!" << endl;
                break;
        }
    } while (choice != 0);
}*/

template<class ElemType>
void BinaryTree<ElemType>::CreateNode(ElemType &data)
{
    this = new Node ;
    this->headNode->data = data;
    this->headNode->lChild = nullptr;
    this->headNode->lChild = nullptr;
}

template<class ElemType>
void BinaryTree<ElemType>::InsertNode(ElemType &data)
{
    Node* pNode = headNode;

}

template<class ElemType>
void BinaryTree<ElemType>::BTInit(ElemType arr[], int i)
{
    if (!this) {
        CreateNode(arr[i]);
    }
}

template<class ElemType>
void BinaryTree<ElemType>::PreOrder() const
{
    if (this) {
        cout << this->headNode->data << "\t";
        PreOrder(this->headNode->lChild);
        PreOrder(this->headNode->rChild);
    }
}

template<class ElemType>
void BinaryTree<ElemType>::InOrder() const
{
    if (this) {
        InOrder(this->headNode->lChild);
        cout << this->headNode->data << "\t";
        InOrder(this->headNode->rChild);
    }
}

template<class ElemType>
void BinaryTree<ElemType>::PostOrder() const
{
    if (this) {
        PostOrder(this->headNode->lChild);
        PostOrder(this->headNode->rChild);
        cout << this->headNode->data << "\t";
    }
}

int main()
{
    BinaryTree<int> bt;

    bt.InsertNode();
    cout << bt << endl;

    return 0;
}

