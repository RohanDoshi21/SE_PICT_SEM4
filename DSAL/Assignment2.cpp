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
            cout << "Enter Word to add in dictionary else enter ^C to stop creation" << endl;
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
            cout << p->value << ": " << p->meaning << endl;
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
    void Replace(Node *p, string key)
    {
        if (p)
        {
            auto x = p->value.compare(key);
            if (x == 0)
            {
                cout << "KEY FOUND" << endl;
                cout << "Current Meaning: " << p->meaning << endl;
                cout << "Enter New Meaning: ";
                string meaning;
                cin.ignore();
                getline(cin, meaning);
                p->meaning = meaning;
                isFound = true;
                return;
            }
            else if (x < 0)
            {
                Replace(p->rchild, key);
            }
            else
            {
                Replace(p->lchild, key);
            }
        }
    }
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
        Replace(root, key);
        if (!isFound)
        {
            cout << "NO KEY FOUND" << endl;
        }
    }

    Node *Delete(Node *p, string key)
    {
        if (p == nullptr)
            return p;

        else if (key.compare(p->value) < 0)
            p->lchild = Delete(p->lchild, key);

        else if (key.compare(p->value) > 0)
            p->rchild = Delete(p->rchild, key);

        // else if (key.compare(root->value) == 0)
        else
        {
            // Case 2: Root has 1 child where left is null
            if (p->lchild == nullptr)
            {
                auto temp = p->rchild;
                delete p;
                return temp;
            }
            // Case 2: Root has 1 child where right is null
            else if (p->rchild == nullptr)
            {
                auto temp = p->lchild;
                delete p;
                return temp;
            }
            // Case 3: Root has 2 children
            else if (p->lchild != nullptr && p->rchild != nullptr)
            {
                auto temp = minLeftChildNotNull(p->rchild);
                p->value = temp->value;
                p->meaning = temp->meaning;
                p->rchild = Delete(p->rchild, p->value);
            }
        }
        return p;
    }

    Node *minLeftChildNotNull(Node *p)
    {
        Node *curr = p;
        while (curr->lchild != nullptr)
        {
            curr = curr->lchild;
        }
        return curr;
    }

    void DeleteNode()
    {
        cout << "Enter the key to Deleted: ";
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
        else
        {
            Delete(root, key);
            cout << "Deleting Word Successful" << endl;
        }
    }
};

int main()
{
    BST t1;
    cout << "BST DICTIONARY CREATION" << endl;
    t1.Create();
    cout << endl;
    cout << endl;

    bool continueProgram = true;
    while (continueProgram)
    {
        cout << "Menu" << endl;
        cout << "1. Inorder traversal" << endl;
        cout << "2. Search Word" << endl;
        cout << "3. Update Meaning" << endl;
        cout << "4. Delete Word" << endl;
        cout << "5. Reverse Sort" << endl;
        cout << "-1 End" << endl;
        cout << "Choose operations u want to perform? ";
        int choice = 0;
        cin >> choice;
        cout << endl;

        switch (choice)
        {
        case 1:
        {
            if (t1.root != nullptr)
            {
                t1.Display();
                cout << endl;
                cout << endl;
            }
            break;
        }
        case 2:
        {
            if (t1.root != nullptr)
            {
                cout << "Searching Word" << endl;
                t1.Find();
                cout << endl;
                cout << endl;
            }
            break;
        }
        case 3:
        {
            if (t1.root != nullptr)
            {
                cout << "Updatating Meaning" << endl;
                t1.Update();
                cout << endl;
                cout << endl;
            }
            break;
        }
        case 4:
        {
            if (t1.root != nullptr)
            {
                cout << "Deleting Word" << endl;
                t1.DeleteNode();
                cout << endl;
                cout << endl;
            }
            break;
        }
        case 5:
        {
            if (t1.root != nullptr)
            {
                cout << "DECENDING ORDER" << endl;
                t1.reverseInorder(t1.root);
                cout << endl;
                cout << endl;
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