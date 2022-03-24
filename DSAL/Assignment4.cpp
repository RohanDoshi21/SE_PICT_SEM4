#include <iostream>
using namespace std;
#define size 501

class HashEntry {
	long int telephoneNo;
	string name;
public:
	explicit HashEntry(long int telephoneNo = 0, string name = "") :
			telephoneNo(telephoneNo), name(name) {
	}
	friend class HashTable;
};

class HashTable {
	HashEntry hashArray[size];
	int hashFunction(long int key) {
		return key % size;
	}
public:
	void Insert(long int key, string value) {
		int hashIndex = hashFunction(key);
		int hashIndexCopy = hashIndex;
		do {
			if (hashArray[hashIndex].telephoneNo == 0) {
				hashArray[hashIndex].telephoneNo = key;
				hashArray[hashIndex].name = value;
				break;
			}

			hashIndex = (hashIndex + 1) % size;

		} while (hashIndex != hashIndexCopy);
	}

	void InsertWithReplacement(long int key, string value) {
		int hashIndex = hashFunction(key);
		int hashIndexCopy = hashIndex;

		do {
			if (hashArray[hashIndex].telephoneNo == 0) {
				hashArray[hashIndex].telephoneNo = key;
				hashArray[hashIndex].name = value;
				break;
			} else {
				int hashIndexOfCollision = hashFunction(
						hashArray[hashIndex].telephoneNo);
				if (hashIndex != hashIndexOfCollision
						&& hashIndex == hashIndexCopy) {
					long int keyCollision = hashArray[hashIndex].telephoneNo;
					string valueCollsion = hashArray[hashIndex].name;

					hashArray[hashIndex].telephoneNo = key;
					hashArray[hashIndex].name = value;

					InsertWithReplacement(keyCollision, valueCollsion);

					break;
				} else {
					hashIndex = (hashIndex + 1) % size;
				}
			}
		} while (hashIndex != hashIndexCopy);

	}

	void Display() {
		for (int i = 0; i < size; i++) {
			if (hashArray[i].telephoneNo != 0) {
				cout << i << " " << hashArray[i].name << " "
						<< hashArray[i].telephoneNo << endl;
			}
		}
	}
	void Search(long int key) {
		int count = 0;
		int hashIndex = hashFunction(key);
		int hashIndexCopy = hashIndex;
		do {
			if (hashArray[hashIndex].telephoneNo == key) {
				cout << "Found" << endl;
				cout << hashIndex << " " << hashArray[hashIndex].name << " "
						<< hashArray[hashIndex].telephoneNo << " Collisions: "
						<< count << endl;
			}
			hashIndex = (hashIndex + 1) % size;
			count++;

		} while (hashIndex != hashIndexCopy);
	}
	void Update(long int key) {
		int hashIndex = hashFunction(key);
		int hashIndexCopy = hashIndex;
		do {
			if (hashArray[hashIndex].telephoneNo == key) {
				cout << "Found" << endl;
				cout << hashIndex << " " << hashArray[hashIndex].name << " "
						<< hashArray[hashIndex].telephoneNo << endl;
				cout << "Enter Name to be Updated: ";
				string nameUpdate;
				cin >> nameUpdate;
				hashArray[hashIndex].name = nameUpdate;
				cout << "Entry Updated" << endl;
				cout << hashIndex << " " << hashArray[hashIndex].name << " "
						<< hashArray[hashIndex].telephoneNo << endl;
			}
			hashIndex = (hashIndex + 1) % size;

		} while (hashIndex != hashIndexCopy);
	}
};

int main() {
	HashTable t1;
	t1.Insert(9049987412, "Mukund");
	t1.Insert(9325712554, "Rohan");
	t1.Insert(9325612554, "Rohan No2");
	t1.Insert(9125612554, "Rohan No3");
	t1.InsertWithReplacement(9125612555, "Rohan No4");
	t1.Display();
	t1.Search(9125612554);
	t1.Search(9325712554);
	return 0;
}
