#include <iostream>
#include <fstream>
#define file_name "Assignment10.txt"
#define temp_name "Assignment_temp.txt"
using namespace std;

class Student
{
private:
    string roll;
    string name, address, cl;

public:
    Student()
    {
        roll = "0";
        name = "";
        address = "";
    }

    Student(string roll, string name, string address, string cl)
    {
        this->address = address;
        this->cl = cl;
        this->name = name;
        this->roll = roll;
    }

    void display()
    {
        cout << name << "  " << address << "  " << cl << "  " << roll << endl;
    }

    string getRoll()
    {
        return roll;
    }

    string getName()
    {
        return name;
    }

    string getAddress()
    {
        return address;
    }

    string getclass()
    {
        return cl;
    }
};

class fileOp
{
    fstream file;

public:
    void write(string filename, Student st)
    {
        ofstream fout(filename, ios::app);
        if (!fout)
        {
            cout << "Cannot open file for writing" << endl;
            return;
        }
        fout << st.getName() << " " << st.getRoll() << " " << st.getAddress()
             << " " << st.getclass() << endl;
        fout.close();
    }

    void read(string filename)
    {
        ifstream fin(filename, ios::in);

        if (!fin)
        {
            cerr << "Cannot open file for writing" << endl;
            return;
        }
        int roll = 0;
        string name = "";
        string cl = "";
        string address = "";
        while (fin >> name >> roll >> address >> cl)
        {
            cout << name << "  " << roll << "  " << address << "  " << cl
                 << endl;
        }
    }

    void deleteStudent(string filename, string name)
    {
        ifstream fin;
        fin.open(file_name);

        ofstream temp;
        temp.open(temp_name);

        string line;
        while (getline(fin, line))
        {
            if (line.find(name))
            {
                temp << line << endl;
            }
        }
        temp.close();
        fin.close();
        remove(file_name);
        rename(temp_name, file_name);
    }

    void searchStudent(string filename, string name)
    {
        ifstream fin;
        fin.open(file_name);
        int flag = 0;
        string line;

        while (getline(fin, line))
        {

            if (!line.find(name))
            {
                cout << line << endl;
                flag = 1;
            }
        }

        if (flag == 0)
        {
            cout << "Record not present\n";
        }

        fin.close();
    }
};

int main()
{
    fileOp obj;
    string filename = file_name;

    int choice = 0;

    while (choice != 5)
    {
        cout << "**********\n";
        cout << "1. Add a student\n2. Display all students\n3. Delete a student profile\n4. Search a student profile\n5. Exit\n";
        cout << "**********\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string name, address, cl;
            string roll;

            cout << "Enter the name of the student: ";
            cin >> name;
            cout << "\nEnter the address: ";
            cin >> address;
            cout << "\nEnter the division: ";
            cin >> cl;
            cout << "\nEnter the roll number: ";
            cin >> roll;

            Student st = Student(roll, name, address, cl);
            obj.write(filename, st);
        }
        break;
        case 2:
        {
            obj.read(filename);
        }
        break;
        case 3:
        {
            string roll;
            cout << "Enter the name you want to delete: ";
            cin >> roll;
            obj.deleteStudent(filename, roll);
        }
        break;
        case 4:
        {
            string roll;
            cout << "Enter the name you want to search: ";
            cin >> roll;
            obj.searchStudent(filename, roll);
        }
        break;
        case 5:
        {
            cout << "Exit" << endl;
        }
        break;
        default:
            cout << "Enter a valid choice";
            break;
        }
    }
    return 0;
}