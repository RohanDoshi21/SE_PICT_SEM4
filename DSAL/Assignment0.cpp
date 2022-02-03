#include <iostream>
#include <stack>

using namespace std;

class GLLNode {
    GLLNode *next;
    bool tag;
    union node {
        char data;
        GLLNode *down;
    } data;

public:
    GLLNode(bool tag = false, char data = '\0', GLLNode *next = nullptr) : next(next), tag(tag) {
        if (tag == false) {
            this->data.data = data;
        } else {
            this->data.down = nullptr;
        }
    };

    friend class GLL;
};

class GLL {
    GLLNode *head;

public:
    GLL() { head = nullptr; }

    void create() {
        int choice = 0;
        stack<GLLNode *> s1;
        while (choice != -1) {
            cout << "MENU" << endl;
            cout << "1. ADD Element" << endl;
            cout << "2. ADD Down Link" << endl;
            if (head != nullptr) {
                if (s1.top() != head) {
                    cout << "3. Drop Link" << endl;
                }
                if (s1.top() == head) {
                    cout << "-1 End" << endl;
                }
            } else {
                cout << "-1 End" << endl;
            }
            cout << "Enter your choice" << endl;
            cin >> choice;
            switch (choice) {
                case 1: {
                    if (head == nullptr) {
                        cout << "Enter Data" << endl;
                        char x;
                        cin >> x;
                        GLLNode *add = new GLLNode(false, x);
                        head = add;
                        s1.emplace(head);
                    } else {
                        auto temp = s1.top();
                        if (temp != nullptr) {
                            while (temp->next != nullptr) {
                                temp = temp->next;
                            }
                            cout << "Enter Data" << endl;
                            char x;
                            cin >> x;
                            if (temp->data.data == '`') {
                                temp->data.data = x;
                            } else {
                                GLLNode *add = new GLLNode(false, x);
                                temp->next = add;
                            }
                        }
//                        else {
//                            cout << "Enter Data" << endl;
//                            char x;
//                            cin >> x;
//                            *(s1.top()) = new GLLNode(false, x);
//                        }
                    }
                    break;
                }
                case 2: {
                    if (head == nullptr) {
                        cout << "Setting up a down link" << endl;
                        GLLNode *add = new GLLNode(true);
                        head = add;
                        s1.emplace(head);
                        s1.emplace(add->data.down);
                    } else {
                        auto temp = s1.top();
                        while (temp->next != nullptr) {
                            temp = temp->next;
                        }
                        cout << "Setting up a down link" << endl;
                        GLLNode *add = new GLLNode(true);
                        temp->next = add;
                        add->data.down = new GLLNode(false, '`');
                        s1.emplace(add->data.down);
                    }
                    break;
                }
                case 3: {
                    cout << "Dropping Link" << endl;
                    s1.pop();
                    break;
                }
                case -1:
                    return;
                    break;

                default:
                    break;
            }
        }
    }

    void DisplaySubList(GLLNode *pNode) {
        cout << "( ";
        while (pNode != nullptr) {
            if (!pNode->tag) {
                cout << pNode->data.data << ", ";
            } else {
                DisplaySubList(pNode->data.down);
            }
            pNode = pNode->next;
        }
        cout << ")";
    }

    void Display() {
        GLLNode *t;
        t = head;
        cout << "( ";
        while (t != nullptr) {
            if (t->tag) {
                DisplaySubList(t->data.down);
            } else {
                cout << t->data.data << ", ";
            }
            t = t->next;
        }
        cout << ")";
    }
};

int main() {
    GLL list1;
    list1.create();
    list1.Display();
    return 0;
}