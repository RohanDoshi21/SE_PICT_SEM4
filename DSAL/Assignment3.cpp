//! Author: Rohan Doshi
//? Problem statement
/*
 */

#include <iostream>
using namespace std;

class TBTNode
{
    string data;
    bool lbit;
    bool rbit;
    TBTNode *lchild;
    TBTNode *rchild;

public:
    TBTNode(string data = "") : data(data)
    {
        lbit = 0;
        rbit = 0;
        lchild = nullptr;
        rchild = nullptr;
    }
    friend class TBT;
};

class Queue
{
private:
    class QNode
    {
        TBTNode *data;
        QNode *next;

    public:
        QNode(TBTNode *data = nullptr, QNode *next = nullptr) : data(data), next(next){};
        friend class Queue;
    };
    QNode *front;
    QNode *rear;

public:
    Queue() : front(nullptr), rear(nullptr){};
    void enqueue(TBTNode *data)
    {
        QNode *temp = new QNode(data);
        if (front == nullptr)
        {
            front = rear = temp;
        }
        else
        {
            rear->next = temp;
            rear = temp;
        }
    }
    TBTNode *dequeue()
    {
        if (front == nullptr)
        {
            cout << "Queue is empty" << endl;
            return nullptr;
        }
        else
        {
            QNode *temp = front;
            front = front->next;
            TBTNode *x = temp->data;
            delete temp;
            return x;
        }
    }
    bool isEmpty()
    {
        return front == nullptr;
    }
};

class TBT
{
    TBTNode *header;

public:
    TBT()
    {
        header = new TBTNode();
        header->lchild = header;
        header->rchild = header;
        header->rbit = 1;
    }
    void insertLeft(TBTNode *parent, TBTNode *child)
    {
        child->lchild = parent->lchild;
        child->rchild = parent;
        parent->lchild = child;
        parent->lbit = 1;
    }
    void insertRight(TBTNode *parent, TBTNode *child)
    {
        child->rchild = parent->rchild;
        child->lchild = parent;
        parent->rchild = child;
        parent->rbit = 1;
    }
    void Create()
    {
        string data;
        cout << "Enter Data for root Node: ";
        cin >> data;
        auto root = new TBTNode();
        root->data = data;
        insertLeft(header, root);
        Queue q;
        q.enqueue(root);
        while (!q.isEmpty())
        {
            auto p = q.dequeue();

            cout << "Enter left child data of " << p->data << ": ";
            cin >> data;
            if (data.compare("-") != 0)
            {
                auto child = new TBTNode(data);
                insertLeft(p, child);
                q.enqueue(child);
            }

            cout << "Enter right child data of " << p->data << ": ";
            cin >> data;
            if (data.compare("-") != 0)
            {
                auto child = new TBTNode(data);
                insertRight(p, child);
                q.enqueue(child);
            }
        }
    }
    void inorder()
    {
        TBTNode *temp = header;
        while (true)
        {
            temp = inorderSuccessor(temp);
            if (temp == header)
                return;

            cout << temp->data << " ";
        }
    }
    TBTNode *inorderSuccessor(TBTNode *x)
    {
        auto successor = x->rchild;
        if (x->rbit == 1)
        {
            while (successor->lbit == 1)
            {
                successor = successor->lchild;
            }
        }
        return successor;
    }
};

int main()
{
    TBT t1;
    t1.Create();
    t1.inorder();
    return 0;
}
