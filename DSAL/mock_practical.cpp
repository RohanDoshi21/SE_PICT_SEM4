//============================================================================
// Name        : Mock.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#define size 500
using namespace std;

class Node {
	string key;
	string value;
	Node* next;

public:
	Node(string key = "", string value = "", Node* next = nullptr) : key(key), value(value), next(next){};
	friend class LinkedList;
};

class LinkedList {
	Node* head;
public:
	friend class HashTable;
	LinkedList():head(nullptr){};
	void insert(string key, string value){
		auto p = head;
		if (p!= nullptr){
			if (p->key == key){
				cout << "Key Already present" << endl;
				return;
			}
			while(p->next != nullptr){
				p = p->next;
			}
				p->next = new Node(key, value);
		}
		else {
			head = new Node(key, value);
		}
	}

	void deletion(string key){
		Node* p = head;
		Node* follow = nullptr;
		while(p != nullptr && p->key != key){
			cout << p->value << " ";
			follow = p;
			p = p->next;
		}
		if (p == head){
			head = head->next;
			delete p;
			return;
		}
		if (p != nullptr){
			follow->next = p->next;
			delete p;
		}
	}
	bool search(string key){
			int comparisons = 1;
			auto p = head;
				if (p!= nullptr){
				while(p != nullptr){
					if (p->key == key){
						cout << "Found " << p->key << " " << p->value << endl;
						cout << "No of comparisons: " << comparisons << endl;
						return true;
					}
					p = p->next;
					comparisons++;
				}
					cout << "Not Found" << endl;
					cout << "No of comparisons: " << comparisons << endl;
					return false;
				}
				else {
					cout << "Not Found" << endl;
					cout << "No of comparisons: " << comparisons << endl;
					return false;
				}
	}
	void print(){
		auto p = head;
		while(p != nullptr){
			cout << p->key << " " << p->value << endl;
			p = p->next;
		}
	}
};

class HashTable {
	LinkedList hashEntry[size];

	int hashFunction(string key){
			int x = 0;
			for(char i : key){
				x += (int)i;
			}
		return x;
	}
public:
	void insert(string key, string value){
		int hashValue = hashFunction(key);
		hashEntry[hashValue%size].insert(key, value);
	}
	void print(){
		for(int i = 0; i < size; i++){
			if (hashEntry[i].head != nullptr){
				cout << "For hash value " << i << endl;
				hashEntry[i].print();
				cout << endl;
			}
		}
	}

	void search(string key){
		int hashValue = hashFunction(key);
		hashEntry[hashValue%size].search(key);
	};

	void deletion(string key){
		int hashValue = hashFunction(key);
		if(hashEntry[hashValue%size].search(key)){
			hashEntry[hashValue%size].deletion(key);
			cout << "Delete Successful" << endl;
		}
		else {
			cout << "No deletion occurred" << endl;
		}
	}
};



int main() {
//	LinkedList l1;
//	l1.insert(12, "abc");
//	l1.insert(13, "def");
//	l1.insert(1, "adef");
//	l1.del(1);
//	l1.print();
//	l1.search(1);
//	l1.search(12);
//	l1.print();

	cout << "Welcome" << endl;

//	HashTable t1;

//	int choice = 0;
//	while (ch)
//	cout << "Menu "
//	t1.insert("Rohan", "My Name");
//	t1.insert("Rohbm", "Rohbm");
//	t1.insert("XYZ", "Rohit");
//
//	cout << endl;
//	t1.search("Rohan");
//	t1.search("Rohit");
//
//	cout << endl;
//	t1.print();
//
//	cout << endl;
//	t1.insert("Rohan", "My Name");
//
//	cout << endl;
//	t1.deletion("Rohan");
//
//	cout << endl;
//	t1.print();

	HashTable t1;
	int choice = 0;
	while (choice != -1){
		cout << "****Menu****" << endl;
		cout << "1. Insert" << endl;
		cout << "2. Search" << endl;
		cout << "3. Delete" << endl;
		cout << "4. Print" << endl;
		cout << "-1. Exit" << endl;

		cout << "Enter your choice ";
		cin >> choice;
		cin.clear();
		cin.ignore();
		cout << endl;

		switch(choice){
		case 1: {
			string key;
			string value;
			cout << "Enter Key ";
			cin >> key;
			cout << "Enter Value ";
			cin >> value;
			t1.insert(key, value);
			break;
		}
		case 2: {
					string key;
					cout << "Enter Key ";
					cin >> key;
					t1.search(key);
					break;
			}
		case 3: {
					string key;
					cout << "Enter Key ";
					cin >> key;
					t1.deletion(key);
					break;
				}
		case 4: {
					t1.print();
					break;
				}
		case -1: {
			cout << "Exiting" << endl;
			break;
		}
		}
		cout << endl;
	}

	return 0;
}
