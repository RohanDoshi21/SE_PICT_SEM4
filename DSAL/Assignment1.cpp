//! Author: Rohan Doshi
//? Problem statement
/*
Beginning with an empty binary tree, Construct binary tree by inserting the values in the order given. After constructing a binary tree perform
 following operations on it- 
 1. Perform inorder /
 2. preorder and post order traversal
 3. Change a tree so that the roles of the left and right pointers are swapped at every node
 4. Find the height of treeCopy this tree to another [operator=]
 5. Count number of leaves, number of internal nodes.
 6. Erase all nodes in a binary tree.
(implement both recursive and non-recursive methods)
*/

#include <iostream>
using namespace std;

class Node
{
    char data;
    Node *lchild;
    Node *rchild;

public:
    Node(char data = '0', Node *lchild = nullptr, Node *rchild = nullptr) : data(data), lchild(lchild), rchild(rchild){};
    friend class Tree;
};

// Queue of Node class -> required for creation of binary tree
class Queue
{
private:
    class QNode
    {
        Node *data;
        QNode *next;

    public:
        QNode(Node *data = nullptr, QNode *next = nullptr) : data(data), next(next){};
        friend class Queue;
    };
    QNode *front;
    QNode *rear;

public:
    Queue() : front(nullptr), rear(nullptr){};
    void enqueue(Node *data)
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
    Node *dequeue()
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
            Node *x = temp->data;
            delete temp;
            return x;
        }
    }
    bool isEmpty()
    {
        return front == nullptr;
    }
};

class Node1
{
private:
    char data;
    Node1 *next;

public:
    explicit Node1(char data = ' ', Node1 *next = nullptr) : data(data), next(next){};

    friend class Stack1;
};

class Stack1
{
private:
    Node1 *top;

public:
    Stack1() : top(nullptr){};

    void push(char data)
    {
        Node1 *temp = new Node1(data);
        temp->next = top;
        top = temp;
    }

    char pop()
    {
        if (top == nullptr)
        {
            return '1';
        }
        else
        {
            Node1 *temp = top;
            top = top->next;
            temp->next = nullptr;
            char x = temp->data;
            delete temp;
            return x;
        }
    }

    bool isEmpty()
    {
        return top == nullptr ? true : false;
    }

    char getTop()
    {
        return top->data;
    }
};

class Stack
{
private:
    class QNode
    {
        Node *data;
        QNode *next;

    public:
        QNode(Node *data = nullptr, QNode *next = nullptr) : data(data), next(next){};
        friend class Stack;
    };
    QNode *top;

public:
    Stack() : top(nullptr){};
    void push(Node *data)
    {
        QNode *temp = new QNode(data);
        temp->next = top;
        top = temp;
    }
    Node *pop()
    {
        if (top == nullptr)
        {
            cout << "Stack underflow" << endl;
            return nullptr;
        }
        else
        {
            QNode *temp = top;
            top = top->next;
            temp->next = nullptr;
            auto x = temp->data;
            delete temp;
            return x;
        }
    }
    bool isEmpty()
    {
        return top == nullptr;
    }
    QNode *getTop()
    {
        return top;
    }
};

class Tree
{
public:
    Node *root; // Keeping public to use to pass as parameter to functions
    Tree() : root(nullptr){};
    void CreateTree() //exit condition is '-'
    {
        Node *p;
        Node *t;
        char x;
        Queue q;

        root = new Node();
        cout << "Enter root data: ";
        cin >> x;
        root->data = x;
        // default setting lchild and rchild to nullptrs
        q.enqueue(root);

        while (!q.isEmpty())
        {
            p = q.dequeue();

            cout << "Enter left child data of " << p->data << ": ";
            cin >> x;
            if (x != '-')
            {
                t = new Node(x);
                p->lchild = t;
                q.enqueue(t);
            }

            cout << "Enter right child data of " << p->data << ": ";
            cin >> x;
            if (x != '-')
            {
                t = new Node(x);
                p->rchild = t;
                q.enqueue(t);
            }
        }
    }
    // Preorder = Root Left Right
    void Preorder(Node *p)
    {
        if (p == nullptr)
            return;
        cout << p->data << ", ";
        Preorder(p->lchild);
        Preorder(p->rchild);
    }
    // Inorder = Left Root Right
    void Inorder(Node *p)
    {
        if (p == nullptr)
            return;
        Inorder(p->lchild);
        cout << p->data << ", ";
        Inorder(p->rchild);
    }
    // Postorder = Left Right Root
    void Postorder(Node *p)
    {
        if (p == nullptr)
            return;
        Postorder(p->lchild);
        Postorder(p->rchild);
        cout << p->data << ", ";
    }
    // Depth/height logic = lDepth > rDepth ? lDepth+1 : rDepth + 1
    // No of nodes logic = return leftCount + rightCount + 1
    // Nodes with D = 2 Logic = lchild && rchild  ? x + y +1 : x + y
    int height(Node *p)
    {
        if (p == nullptr)
            return 0;
        else
        {
            int lDepth = height(p->lchild);
            int rDepth = height(p->rchild);
            return lDepth > rDepth ? lDepth + 1 : rDepth + 1;
        }
    }
    int leafNodes(Node *p)
    {
        if (p == nullptr)
            return 0;
        if (p->lchild == nullptr && p->rchild == nullptr)
        {
            cout << p->data << ", ";
            return 1;
        }
        else
            return leafNodes(p->lchild) + leafNodes(p->rchild);
    }
    int InternalNodes(Node *p)
    {
        if (p == nullptr)
            return 0;
        else
        {
            int lcount = InternalNodes(p->lchild);
            int rcount = InternalNodes(p->rchild);
            if (p->lchild == nullptr && p->rchild == nullptr)
                return lcount + rcount;
            else
            {
                cout << p->data << ", ";
                return lcount + rcount + 1;
            }
        }
    }
    void PreorderNonRecursive(Node *p)
    {
        if (p == nullptr)
            return;
        Stack s1;
        auto current = root;
        while (current != nullptr || !s1.isEmpty())
        {
            if (current != nullptr)
            {
                cout << current->data << ", ";
                s1.push(current);
                current = current->lchild;
            }
            else
            {
                current = s1.pop();
                current = current->rchild;
            }
        }
    }
    void InorderNonRecursive(Node *p)
    {
        if (p == nullptr)
            return;
        Stack s1;
        auto current = root;
        while (current != nullptr || !s1.isEmpty())
        {
            if (current != nullptr)
            {
                s1.push(current);
                current = current->lchild;
            }
            else
            {
                current = s1.pop();
                cout << current->data << ", ";
                current = current->rchild;
            }
        }
    }
    void PostorderNonRecursive(Node *p)
    {
        if (p == nullptr)
            return;
        Stack s1;
        s1.push(root);
        Stack1 out;
        while (!s1.isEmpty())
        {
            auto current = s1.pop();
            out.push(current->data);
            if (current->lchild)
            {
                s1.push(current->lchild);
            }
            if (current->rchild)
            {
                s1.push(current->rchild);
            }
        }
        while (!out.isEmpty())
        {
            cout << out.pop() << ", ";
        }
    }
    void deleteTree(Node *p)
    {
        if (p == nullptr)
            return;
        deleteTree(p->lchild);
        deleteTree(p->rchild);
        cout << "Deleting node " << p->data << endl;
        delete p;
    }
    void swapNodes(Node *p)
    {
        if (p == nullptr)
            return;

        swapNodes(p->lchild);
        swapNodes(p->rchild);

        auto temp = p->lchild;
        p->lchild = p->rchild;
        p->rchild = temp;
    }
    Node *copy(Node *p)
    {
        Node *new_root;
        if (p != nullptr)
        {
            new_root = new Node;
            new_root->data = p->data;
            new_root->lchild = copy(p->lchild);
            new_root->rchild = copy(p->rchild);
        }
        else
            return nullptr;
        return new_root;
    }
    Tree operator=(Tree t1)
    {
        this->root = copy(t1.root);
        return *this;
    }
};

int main()
{
    Tree bt;
    cout << "TREE CREATION" << endl;
    bt.CreateTree();
    cout << endl;
    cout << endl;

    char continueProgram = true;
    while (continueProgram)
    {
        cout << "Menu" << endl;
        cout << "1. Inorder traversal" << endl;
        cout << "2. Preorder traversal" << endl;
        cout << "3. Postorder traversal" << endl;
        cout << "4. swap" << endl;
        cout << "5. No of leaf Nodes and height of tree" << endl;
        cout << "6. Delete Tree" << endl;
        cout << "7. Copy Tree" << endl;
        cout << "8 End" << endl;
        cout << "Choose operations u want to perform? ";
        int choice = 0;
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
        {
            if (bt.root != nullptr)
            {
                cout << "Inorder: ";
                bt.Inorder(bt.root);
                cout << endl;
                cout << endl;

                cout << "Inorder Non-Recursive: ";
                bt.InorderNonRecursive(bt.root);
                cout << endl;
                cout << endl;
            }
            else
            {
                cout << "Tree is empty" << endl;
            }
            break;
        }
        case 2:
        {
            if (bt.root != nullptr)
            {
                cout << "Preorder: ";
                bt.Preorder(bt.root);
                cout << endl;
                cout << endl;

                cout << "Preorder Non-Recursive: ";
                bt.PreorderNonRecursive(bt.root);
                cout << endl;
                cout << endl;
            }
            else
            {
                cout << "Tree is empty" << endl;
            }
            break;
        }
        case 3:
        {
            if (bt.root != nullptr)
            {
                cout << "Postorder: ";
                bt.Postorder(bt.root);
                cout << endl;
                cout << endl;

                cout << "Postorder Non-Recursive: ";
                bt.PostorderNonRecursive(bt.root);
                cout << endl;
                cout << endl;
            }
            else
            {
                cout << "Tree is empty" << endl;
            }
            break;
        }
        case 4:
        {
            if (bt.root != nullptr)
            {
                cout << "Swapping left and Right Nodes" << endl;
                bt.swapNodes(bt.root);
                cout << endl;
                cout << endl;
            }
            else
            {
                cout << "Tree is empty" << endl;
            }
            break;
        }
        case 5:
        {
            if (bt.root != nullptr)
            {
                cout << "Height: " << bt.height(bt.root) << endl;
                cout << endl;

                cout << "Leaf Nodes are ";
                int x = bt.leafNodes(bt.root);
                cout << endl;
                cout << "No of Leaf Nodes: " << x;
                cout << endl;
                cout << endl;

                cout << "Internal Nodes are ";
                x = bt.InternalNodes(bt.root);
                cout << endl;
                cout << "No of Internal Nodes: " << x << endl;
                cout << endl;
            }
            else
            {
                cout << "Tree is empty" << endl;
            }
            break;
        }
        case 6:
        {
            if (bt.root != nullptr)
            {
                cout << "Delete Tree" << endl;
                bt.deleteTree(bt.root);
                bt.root = nullptr;
                cout << endl;
                cout << endl;
            }
            else
            {
                cout << "Tree is empty" << endl;
            }
            break;
        }
        case 7:
        {
            if (bt.root != nullptr)
            {
                cout << "Copying Tree" << endl;
                Tree copy = bt;

                cout << "Inorder on copied tree: ";
                copy.Inorder(copy.root);

                cout << endl;
                cout << endl;
            }
            else
            {
                cout << "Tree is empty" << endl;
            }
            break;
        }
        case 8:
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