#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Student
{
    int rollno;
    char name[50];
    int eng_marks, math_marks, sci_marks, cs_marks;
    double average;
    char grade;

public:
    int getdata(int);
    void showdata() const;
    void calculate();
    int retrollno() const;
}; // class ends here

// function declaration
void create_student();
void display_sp(int);     // display specific record
void display_all();       // display all records
void delete_student(int); // delete specific record
void delete_student_all(); // delete all records
void change_student(int); // edit particular record
void copy_student(); // copy
void sort_records_by_rollno();
// MAIN

void Student::calculate()
{
    average = (eng_marks + math_marks + sci_marks + cs_marks) / 4.0;
    if (average >= 90.0)
        grade = 'A';
    else if (average >= 75.0)
        grade = 'B';
    else if (average >= 50.0)
        grade = 'C';
    else
        grade = 'F';
}

int Student::getdata(int over)
{
    cout << "Enter student's roll number: ";
    cin >> rollno;
    int continuable = 1;
    char override;

    copy_student();

    ifstream inFile;
    Student stud;
    inFile.open("copied.dat", ios::binary | ios::app);

    if (over != 1)
    {
    while (inFile.read(reinterpret_cast<char *>(&stud), sizeof(Student)))
    {
        if (rollno == stud.rollno)
        {
            

            cout << "Student record with that roll no already exists" << endl;

            cout << "Do you wish to overrive the data ? (Y/N)" << endl;
            cin >> override ;
            if (tolower(override) == 'y')
            {   
                delete_student(rollno);
                continuable = 1 ;
            }
            else 
            {   
                continuable = 0;
            }
        }
        else
        {

        }
    }
    }
    if (continuable) 
    {
        cout << "Enter student name: ";
        cin.ignore();
        cin.getline(name, 50);

        cout << "All marks should be out of 100\n";
        cout << "Enter marks in English: ";
        cin >> eng_marks;
        cout << "Enter marks in Math:  ";
        cin >> math_marks;
        cout << "Enter marks in Science:  ";
        cin >> sci_marks;
        cout << "Enter marks in Computer science:  ";
        cin >> cs_marks;
        calculate();
    }

    inFile.close();
    remove("copied.dat");

    return continuable;
}
void Student::showdata() const
{
    cout << "\nRoll number of student : " << rollno;
    cout << "\nName of student : " << name;
    cout << "\nEnglish : " << eng_marks;
    cout << "\nMaths : " << math_marks;
    cout << "\nScience : " << sci_marks;
    cout << "\nComputer Science : " << cs_marks;
    cout << "\nAverage Marks : " << average;
    cout << "\nGrade of student is : " << grade;
}

int Student::retrollno() const
{
    return rollno;
}


int main()
{
    char ch;
    cout << setprecision(3);
    do
    {
        int num;
        if (system("clear"))
            system("cls");
        cout << "\n\n\n\t\t   MENU";
        cout << "\n\n\t1. Create student record";
        cout << "\n\n\t2. Search student record";
        cout << "\n\n\t3. Display all students records ";
        cout << "\n\n\t4. Delete student record";
        cout << "\n\n\t5. Delete ALL student records";
        cout << "\n\n\t6. Modify student record";
        cout << "\n\n\t7. Exit";
        cout << "\n\nWhat is your Choice (1/2/3/4/5/6/7) ";
        cin >> ch;
        if (system("clear"))
            system("cls");
        switch (ch)
        {
        case '1':
            create_student();
            sort_records_by_rollno();
            break;
        case '2':
            cout << "\n\n\tEnter The roll number ";
            cin >> num;
            display_sp(num);
            cin.ignore();
            cin.get();
            break;
        case '3':
            display_all();
            break;
        case '4':
            cout << "\n\n\tEnter The roll number: ";
            cin >> num;
            display_sp(num);
            char confirm;
            cout << "\n\n\tAre you sure to delete the entry (Y/N)" << endl << "\t" ;
            cin >> confirm;
            if (tolower(confirm) == 'y')
            {   
                delete_student(num);
                cout << "\n\n\tRecord Deleted ..";
                cin.ignore();
                cin.get();
            }
            else
            {
                cout << "\n\n\tRecord Not Deleted ..";
                cin.ignore();
                cin.get();
            }
            break;
        case '5':
            char deleteall;
            cout << "\n\n\tAre you sure you want to delete all the data (Y/N)" << endl << "\t" ;
            cin >> deleteall;

            if (tolower(deleteall) == 'y')
            {   
                delete_student_all();
                cout << "\n\n\tALL Records Deleted ..";
                cin.ignore();
                cin.get();
            }
            else
            {
                cout << "\n\n\tRecords were Not Deleted ..";
                cin.ignore();
                cin.get();
            }
            break;
        case '6':
            cout << "\n\n\tEnter The roll number ";
            cin >> num;
            change_student(num);
            sort_records_by_rollno();
            break;
        case '7':
            cout << "Exiting, Thank you!";
            exit(0);
        }
    } while (ch != '7');
    return 0;
}
// write student details to file

void create_student()
{
    Student st;
    ofstream oFile;

    int override = 0;
    int temp = st.getdata(override);

    if (temp == 0) // oFile.write(reinterpret_cast<char *>(&st), sizeof(Student));
    {   
        cout << "Student record was not created" << endl;
        cin.ignore();
        cin.get();
    }
    else
    {
        oFile.open("student.dat", ios::binary | ios::app);
        oFile.write((char *)(&st), sizeof(Student));
        oFile.close();
        cout << "\n\nStudent record Has Been Created ";
        cin.ignore();
        cin.get();
    }
}

// read file records
void display_all()
{
    Student stud;
    ifstream inFile;
    inFile.open("student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be opened !! Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n\t\tDISPLAYING ALL RECORDS\n\n";
    while (inFile.read(reinterpret_cast<char *>(&stud), sizeof(Student)))
    {
        stud.showdata();
        cout << "\n\n====================================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}
// read specific record based on roll number
void display_sp(int n)
{
    Student stud;
    ifstream iFile;
    iFile.open("student.dat", ios::binary);
    if (!iFile)
    {
        cout << "File could not be opened... Press any Key to exit";
        return;
    }
    bool flag = false;
    while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(Student)))
    {
        if (stud.retrollno() == n)
        {
            stud.showdata();
            flag = true;
        }
    }
    iFile.close();
    if (flag == false)
        cout << "\n\nrecord does not exist";
}
// modify record for specified roll number
void change_student(int n)
{
    bool found = false;
    Student stud;
    fstream fl;
    fl.open("student.dat", ios::binary | ios::in | ios::out);
    if (!fl)
    {
        cout << "File could not be opened. Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    while (!fl.eof() && found == false)
    {
        fl.read(reinterpret_cast<char *>(&stud), sizeof(Student));
        if (stud.retrollno() == n)
        {
            stud.showdata();
            cout << "\n\nEnter new student details:" << endl;
            int overide = 1;
            stud.getdata(overide);
            int pos = (-1) * static_cast<int>(sizeof(stud));
            fl.seekp(pos, ios::cur);
            fl.write(reinterpret_cast<char *>(&stud), sizeof(Student));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    fl.close();
    if (found == false)
        {
            cout << "\n\n Record Not Found ";
        }
    cin.ignore();
    cin.get();
}
// delete record with particular roll number
void delete_student(int n)
{
    Student stud;
    ifstream iFile;
    iFile.open("student.dat", ios::binary);
    if (!iFile)
    {
        cout << "File could not be opened... Press any Key to exit...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream oFile;
    oFile.open("Temp.dat", ios::out);
    iFile.seekg(0, ios::beg);
    while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(Student)))
    {
        if (stud.retrollno() != n)
        {
            oFile.write(reinterpret_cast<char *>(&stud), sizeof(Student));
        }
    }
    oFile.close();
    iFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
    // cout << "\n\n\tRecord Deleted ..";
    // cin.ignore();
    // cin.get();
}

void delete_student_all() 
{
    ofstream oFile("Temp.dat");
    oFile.close();
    remove("student.dat");
    rename("Temp.dat", "student.dat");
}

void copy_student()
{
    Student stud;
    ifstream iFile;
    iFile.open("student.dat", ios::binary);
    ofstream oFile;
    oFile.open("copied.dat", ios::out);
    iFile.seekg(0, ios::beg);
    while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(Student)))
    {
        oFile.write(reinterpret_cast<char *>(&stud), sizeof(Student));
    }
    oFile.close();
    iFile.close();
}

void sort_records_by_rollno() 
{
    ifstream inFile("student.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened... Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }

    vector<Student> students;

    Student stud;
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        students.push_back(stud);
    }

    inFile.close();

    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.retrollno() < b.retrollno();
    });

    ofstream outFile("sorted_student.dat", ios::binary);
    if (!outFile) {
        cout << "Error creating sorted file. Press any Key to exit";
        cin.ignore();
        cin.get();
        return;
    }

    for (const auto& student : students) {
        outFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    }

    outFile.close();

    remove("student.dat");
    rename("sorted_student.dat", "student.dat");

}
