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
    void Inorder()
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
    void Preorder()
    {
        TBTNode *temp = header;
        temp = temp->lchild; //go to root node
        do
        {
            cout << temp->data << " ";
            if (temp->lbit == 1)
            {
                temp = temp->lchild;
            }
            else if (temp->rbit == 1)
            {
                temp = temp->rchild;
            }
            else
            {
                while (temp->rbit != 1)
                {
                    temp = temp->rchild;
                }
                temp = temp->rchild;
            }
        } while (temp != header);
    }
    TBTNode *Search(string data)
    {
        TBTNode *temp = header;
        while (true)
        {
            temp = inorderSuccessor(temp);
            if (temp == header)
            {
                cout << "NOT FOUND" << endl;
                return nullptr;
            }
            else if (temp->data == data)
            {
                cout << "FOUND " << data << endl;
                return temp;
            }
        }
    }
    void Delete()
    {
        bool flag = 0;
        auto parent = header;
        auto T = header->lchild;
        while (flag != 1)
        {
            // Case Delete Leaf Node T->rbit == 0 && T->lbit == 0
            // Leaf node is rchild
            if (T == parent->rchild)
            {
                parent->rchild = T->rchild;
                parent->rbit = 0;
                delete T;
                flag = 1;
            }
            // Leaf Node is lchild
            else if (T == parent->lchild)
            {
                parent->lchild = T->lchild;
                parent->lbit = 0;
                delete T;
                flag = 1;
            }
            // Case with Left Child only
            if (T->lbit == 1 && T->rbit == 0)
            {
                parent->rchild = T->lchild;
                // T's (predecessor)->rchild = T->child 
            }
        }
    }
};

int main()
{
    TBT t1;
    cout << "BST DICTIONARY CREATION" << endl;
    t1.Create();
    cout << endl;
    cout << endl;

    bool continueProgram = true;
    while (continueProgram)
    {
        cout << "Menu" << endl;
        cout << "1. Inorder traversal" << endl;
        cout << "2. Preorder traversal" << endl;
        cout << "3. Search Element" << endl;
        cout << "4. Delete Element" << endl;
        cout << "-1 End" << endl;
        cout << "Choose operations u want to perform? ";
        int choice = 0;
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
        {
            cout << "Inorder Traversal: ";
            t1.Inorder();
            cout << endl;
            cout << endl;
            break;
        }
        case 2:
        {
            cout << "Preorder Traversal: ";
            t1.Preorder();
            cout << endl;
            cout << endl;
            break;
        }
        case 3:
        {
            string key;
            cout << "Enter Element to be Searched: ";
            cin >> key;
            t1.Search(key);
            break;
        }
        case 4:
        {
            string key;
            cout << "Enter the element you want to Delete: ";
            cin >> key;
            auto result = t1.Search(key);
            if (result != nullptr)
            {
                t1.Delete();
            }
            else
            {
                cout << "Cannot Delete element which does not exist";
            }
            break;
        }
        case -1:
        {
            continueProgram = false;
            break;
        }
        default:
        {
            cout << "INVALID CHOICE" << endl;
            break;
        }
            cout << endl;
        }
    }
    return 0;
}
