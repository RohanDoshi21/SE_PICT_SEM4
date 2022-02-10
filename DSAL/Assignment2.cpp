//! Author: Rohan Doshi
//? Problem statement
/*
 */

#include <iostream>
#include <string>
using namespace std;
class Node
{
    Node *lchild;
    Node *rchild;
    string value;
    string meaning;

public:
    Node(string value = "", string meaning = "") : value(value), meaning(meaning)
    {
        lchild = nullptr;
        rchild = nullptr;
    };
    friend class BST;
};

class BST
{
public:
    Node *root;
    bool isFound;
    int comp = 0;
    BST()
    {
        root = nullptr;
        isFound = false;
    }
    Node *Insert(Node *p, string value, string meaning)
    {
        if (p == nullptr)
        {
            return new Node(value, meaning);
        }
        else if (p->value.compare(value) < 0)
        {
            p->rchild = Insert(p->rchild, value, meaning);
        }
        else if (p->value.compare(value) > 0)
        {
            p->lchild = Insert(p->lchild, value, meaning);
        }
        return p;
    }
    void Create()
    {
        string value;
        string meaning;
        while (true)
        {
            cout << "^C to exit else continue: " << endl;
            cin >> value;
            if (value.compare("^C") == 0)
            {
                cout << "Creation over\n";
                break;
            }
            else
            {
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                if (this->root == nullptr)
                {
                    this->root = Insert(root, value, meaning);
                }
                else
                {
                    Insert(root, value, meaning);
                }
            }
        }
    }
    void Display()
    {
        cout << "DISPLAYING TREE" << endl;
        inorder(root);
        cout << "\n";
    }
    void inorder(Node *p)
    {
        if (p)
        {
            inorder(p->lchild);
            cout << p->value << ": " << p->meaning << endl;
            inorder(p->rchild);
        }
    }
    void reverseInorder(Node *p)
    {
        if (p)
        {
            reverseInorder(p->rchild);
            cout << p->value << " ";
            reverseInorder(p->lchild);
        }
    }
    Node *Search(Node *p, string key)
    {
        if (p)
        {
            Search(p->lchild, key);
            Search(p->rchild, key);
            if (p->value == key)
            {
                cout << "KEY FOUND" << endl;
                cout << "Meaning: " << p->meaning << endl;
                isFound = true;
                return p;
            }
        }
        return nullptr;
    }
    void Search1(Node *p, string key)
    {
        if (p)
        {
            auto x = p->value.compare(key);
            comp++;
            if (x == 0)
            {
                cout << "KEY FOUND" << endl;
                cout << "Meaning: " << p->meaning << endl;
                cout << "No of comparisons: " << comp << endl;
                isFound = true;
                return;
            }
            else if (x < 0)
            {
                Search1(p->rchild, key);
            }
            else
            {
                Search1(p->lchild, key);
            }
        }
    }
    // Node* Replace(Node* p, string key){
    // }
    void Find()
    {
        cout << "Enter the key to search: ";
        string key;
        cin >> key;
        isFound = false;
        comp = 0;
        Search1(root, key);
        if (!isFound)
        {
            cout << "NO KEY FOUND" << endl;
            cout << "No of comparisons: " << comp << endl;
        }
    }
    void Update()
    {
        cout << "Enter the key to be updated: ";
        string key;
        cin >> key;
        isFound = false;
        Search(root, key);
        if (!isFound)
        {
            cout << "NO KEY FOUND" << endl;
        }
    }
};

int main()
{
    BST t1;
    t1.Create();
    t1.Display();
    t1.Find();
    return 0;
}