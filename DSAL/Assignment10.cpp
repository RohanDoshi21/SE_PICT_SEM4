#include <iostream>
#include <fstream>
#define file_name "Assignment10.bin"
#define temp_name "temp10.bin"
using namespace std;

class Student
{
private:
    int rollNum;
    string name;
    string address;
    string division;

public:
    friend class FileHandling;
    Student()
    {
        name = "";
        rollNum = -1;
        division = "";
        address = "";
    }
    Student(string name, int roll, string div, string addr)
    {
        this->name = name;
        this->rollNum = roll;
        this->division = div;
        this->address = addr;
    }
    friend class FileHandling;
};

class FileHandling
{
public:
    Student std;
    void insert()
    {
        ofstream outf;
        cout << "\nEnter name: ";
        cin.ignore();
        getline(cin, std.name);
        cout << "Enter roll number: ";
        cin >> std.rollNum;
        cout << "Enter division: ";
        cin >> std.division;
        cout << "Enter address: ";
        cin.ignore();
        getline(cin, std.address);
        outf.open(file_name, ios::binary | ios::app);
        outf.write((char *)&std, sizeof(std)) << flush;
        outf.close();
        cout << "\nSuccessfully added";
    }

    void Deletion()
    {
        bool flag = 0;
        int x;
        string name;
        string s;
        cout << "\nEnter name: ";
        cin >> name;
        ifstream fin;
        ofstream fout;
        fout.open(temp_name, ios::app | ios::binary);
        fin.open(file_name, ios::in | ios::binary);
        while (fin.read((char *)&std, sizeof(std)))
        {
            if (std.name == name)
                flag = 1;
            if (std.name != name)
                fout.write((char *)&std, sizeof(std)) << flush;
        }
        fin.close();
        fout.close();
        remove(file_name);
        rename(temp_name, file_name);
        cout << (flag ? "\nDeletion Success" : "\nCould not Record");
    }

    void Search()
    {
        bool flag = 0;
        string name;
        cout << "\nEnter name: ";
        cin >> name;
        ifstream inf;
        inf.open(file_name, ios::in | ios::binary);
        inf.seekg(0);
        inf.clear();
        int x;
        if (inf.is_open())
        {
            while (inf.read((char *)&std, sizeof(std)))
            {
                if (std.name == name)
                {
                    flag = 1;
                    cout << "\nEntry present";
                    cout << "\nName: " << std.name;
                    cout << "\nRoll number: " << std.rollNum;
                    cout << "\nDivision: " << std.division;
                    cout << "\nAddress: " << std.address;
                }
            }
            if (!flag)
                cout << "\nCould not find record";
            inf.close();
        }
        else
            cout << "\nUnable to open";
    }

    void Display()
    {
        ifstream fin;
        fin.open(file_name, ios::in | ios::binary);
        fin.seekg(ios::beg);
        if (fin.is_open())
        {
            int i = 1;
            cout << "Name\tRollNo\tDivision\tAddress\n";
            while (fin.read((char *)&std, sizeof(std)))
            {
                i++;
                cout << std.name << "\t" << std.rollNum << "\t" << std.division << "\t" << std.address << endl;
                cout << endl;
            }
            fin.close();
        }
        else
            cout << "\nCould not open";
    }
} * file;

int main()
{
    bool menu = 1;
    file = new FileHandling();
    while (menu)
    {
        int ch;
        cout << "\n\n**********MENU**********";
        cout << "\n1. Insert Record\n2. Search Record\n3. Delete Record\n4. Display Entire File Contents\n-1. Exit\n What do you want to perform: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            file->insert();
            break;

        case 2:
            file->Search();
            break;

        case 3:
            file->Deletion();
            break;

        case 4:
            file->Display();
            break;

        case -1:
            menu = 0;
            break;
        default:
            break;
        }
    }
    return 0;
}

// #include <iostream>
// #include <fstream>
// #define file_name "Assignment10.txt"
// #define temp_name "Assignment_temp.txt"
// using namespace std;

// class Student
// {
// private:
//     string roll;
//     string name, address, cl;

// public:
//     Student()
//     {
//         roll = "0";
//         name = "";
//         address = "";
//     }

//     Student(string roll, string name, string address, string cl)
//     {
//         this->address = address;
//         this->cl = cl;
//         this->name = name;
//         this->roll = roll;
//     }

//     void display()
//     {
//         cout << name << "  " << address << "  " << cl << "  " << roll << endl;
//     }

//     string getRoll()
//     {
//         return roll;
//     }

//     string getName()
//     {
//         return name;
//     }

//     string getAddress()
//     {
//         return address;
//     }

//     string getclass()
//     {
//         return cl;
//     }
// };

// class fileOp
// {
//     fstream file;

// public:
//     void write(string filename, Student st)
//     {
//         ofstream fout(filename, ios::app);
//         if (!fout)
//         {
//             cout << "Cannot open file for writing" << endl;
//             return;
//         }
//         fout << st.getName() << " " << st.getRoll() << " " << st.getAddress()
//              << " " << st.getclass() << endl;
//         fout.close();
//     }

//     void read(string filename)
//     {
//         ifstream fin(filename, ios::in);

//         if (!fin)
//         {
//             cerr << "Cannot open file for writing" << endl;
//             return;
//         }
//         int roll = 0;
//         string name = "";
//         string cl = "";
//         string address = "";
//         while (fin >> name >> roll >> address >> cl)
//         {
//             cout << name << "  " << roll << "  " << address << "  " << cl
//                  << endl;
//         }
//     }

//     void deleteStudent(string filename, string name)
//     {
//         ifstream fin;
//         fin.open(file_name);

//         ofstream temp;
//         temp.open(temp_name);

//         string line;
//         while (getline(fin, line))
//         {
//             if (line.find(name))
//             {
//                 temp << line << endl;
//             }
//         }
//         temp.close();
//         fin.close();
//         remove(file_name);
//         rename(temp_name, file_name);
//     }

//     void searchStudent(string filename, string name)
//     {
//         ifstream fin;
//         fin.open(file_name);
//         int flag = 0;
//         string line;

//         while (getline(fin, line))
//         {

//             if (!line.find(name))
//             {
//                 cout << line << endl;
//                 flag = 1;
//             }
//         }

//         if (flag == 0)
//         {
//             cout << "Record not present\n";
//         }

//         fin.close();
//     }
// };

// int main()
// {
//     fileOp obj;
//     string filename = file_name;

//     int choice = 0;

//     while (choice != 5)
//     {
//         cout << "**********\n";
//         cout << "1. Add a student\n2. Display all students\n3. Delete a student profile\n4. Search a student profile\n5. Exit\n";
//         cout << "**********\n";

//         cout << "Enter your choice: ";
//         cin >> choice;

//         switch (choice)
//         {
//         case 1:
//         {
//             string name, address, cl;
//             string roll;

//             cout << "Enter the name of the student: ";
//             cin >> name;
//             cout << "\nEnter the address: ";
//             cin >> address;
//             cout << "\nEnter the division: ";
//             cin >> cl;
//             cout << "\nEnter the roll number: ";
//             cin >> roll;

//             Student st = Student(roll, name, address, cl);
//             obj.write(filename, st);
//         }
//         break;
//         case 2:
//         {
//             obj.read(filename);
//         }
//         break;
//         case 3:
//         {
//             string roll;
//             cout << "Enter the name you want to delete: ";
//             cin >> roll;
//             obj.deleteStudent(filename, roll);
//         }
//         break;
//         case 4:
//         {
//             string roll;
//             cout << "Enter the name you want to search: ";
//             cin >> roll;
//             obj.searchStudent(filename, roll);
//         }
//         break;
//         case 5:
//         {
//             cout << "Exit" << endl;
//         }
//         break;
//         default:
//             cout << "Enter a valid choice";
//             break;
//         }
//     }
//     return 0;
// }
