#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

class Colors {
public:
  string red;
  string blue;
  string def;
  string yellow;
  string orange;
  string magenta;
  string cyan;
  string green;
  string white;
  string black;
  string bold;
  Colors() {
    black = "\033[30m";
    def = "\033[0m";
    red = "\033[31m";
    green = "\033[32m";
    yellow = "\033[33m";
    blue = "\033[34m";
    magenta = "\033[35m";
    cyan = "\033[36m";
    white = "\033[37m";
    bold = "\033[1m";
  }
};
class Student {

public:
  int rollno;
  char name[50];
  int eng, maths, sci, comp;
  double average;
  char grade;

  Student() {
    eng = 0;
    maths = 0;
    sci = 0;
    comp = 0;
    calculate();
  }
  void getdata(int);
  void get_sp_data(int, char *, int, int, int, int);
  void showdata() const;
  void calculate();
  // int rollno() const;
}; // class ends here

// function declaration
void create_student();
void buffer();
void checker(Student);
void fileChecker(string);
void display_sp(int); // display specific record
int check_existence(int);
void display_all();                    // display all records
void delete_student(int);              // delete specific record
void change_student(int);              // edit particular record
void copy_studentFile(string, string); // copy student file
// MAIN

void Student::calculate() {
  average = (eng + maths + sci + comp) / 4.0;
  if (average >= 90)
    grade = 'A';
  else if (average >= 80)
    grade = 'B';
  else if (average >= 70)
    grade = 'C';
  else if (average >= 60)
    grade = 'D';
  else if (average >= 32)
    grade = 'E';
  else
    grade = 'F';
}
void Student::getdata(int rn) {
  Colors c;
  rollno = rn;
  cout << c.blue << "Enter Student Name: " << c.def;
  cin.ignore();
  cin.getline(name, 50);
  this->showdata();
  cout << c.yellow << "\nAll marks should be out of 100\n" << c.def;
  cout << c.blue << "Enter marks in English: " << c.def;
  cin >> eng;
  cout << c.blue << "Enter marks in Math:  " << c.def;
  cin >> maths;
  cout << c.blue << "Enter marks in Science:  " << c.def;
  cin >> sci;
  cout << c.blue << "Enter marks in Computer science:  " << c.def;
  cin >> comp;
  calculate();
}
void Student::showdata() const {
  Colors c;
  cout << c.bold << c.green << "\n\nName: " << c.def << name << endl;
  cout << c.bold << c.green << "RollNo: " << c.def << rollno << endl;
  cout << "┌──────────┬──────────┬──────────┐" << endl;
  cout << "│" << setiosflags(ios::left) << c.bold << c.cyan << setw(10)
       << "Subjects" << c.white << "│" << c.cyan << setw(10) << "Marks"
       << c.white << "│" << c.cyan << setw(10) << "Full Marks" << c.white << "│"
       << c.def << endl
       << "├──────────┼──────────┼──────────┤" << endl
       << c.white << "│" << c.blue << setw(10) << "English" << c.white << "│"
       << c.magenta << setw(10) << eng << c.white << "│" << c.blue << setw(10)
       << 100 << c.white << "│" << endl
       << "├──────────┼──────────┼──────────┤" << endl
       << c.white << "│" << c.blue << setw(10) << "Maths" << c.white << "│"
       << c.magenta << setw(10) << maths << c.white << "│" << c.blue << setw(10)
       << 100 << c.white << "│" << endl
       << "├──────────┼──────────┼──────────┤" << endl
       << c.white << "│" << c.blue << setw(10) << "Science" << c.white << "│"
       << c.magenta << setw(10) << sci << c.white << "│" << c.blue << setw(10)
       << 100 << c.white << "│" << endl
       << "├──────────┼──────────┼──────────┤" << endl
       << c.white << "│" << c.blue << setw(10) << "Computer" << c.white << "│"
       << c.magenta << setw(10) << comp << c.white << "│" << c.blue << setw(10)
       << 100 << c.white << "│" << endl
       << "├──────────┼──────────┼──────────┤" << endl
       << c.white << "│" << c.blue << setw(10) << "Percentage" << c.white << "│"
       << c.magenta << setw(9) << average << "%" << c.white << "│" << c.blue
       << setw(9) << 100 << "%" << c.white << "│" << endl;
  cout << "└──────────┴──────────┴──────────┘" << endl;
  if (grade != 'F') {
    cout << c.bold << c.green << "Grade: " << c.def << grade << endl;
  } else {
    cout << c.bold << c.green << "Grade: " << c.red << grade << c.def << endl;
  }
}

int main() {
  char ch;
  Colors c;
  cout << setprecision(3);
  // MENU
  do {
    int num;
    if (system("clear"))
      system("cls");
    cout << c.bold << c.blue << "\n\n\nMENU" << c.def;
    cout << c.bold << c.magenta << "\n\n\t1⇾ Create" << c.white
         << " Student Record" << c.def;
    cout << c.bold << c.magenta << "\n\n\t2⇾ Search" << c.white
         << " Student Record" << c.def;
    cout << c.bold << c.magenta << "\n\n\t3⇾ Display" << c.white
         << " All Student Records" << c.def;
    cout << c.bold << c.magenta << "\n\n\t4⇾ Delete" << c.white
         << " Student Records" << c.def;
    cout << c.bold << c.magenta << "\n\n\t5⇾ Modify" << c.white
         << " Student Records" << c.def;
    cout << c.bold << c.magenta << "\n\n\t6⇾ Exit" << c.white << " Program"
         << c.def;
    cout << c.bold << c.green << "\n\nWhat is your Choice? " << c.magenta
         << "(1/2/3/4/5/6) " << c.def;
    cin >> ch;

    if (system("clear"))
      system("cls");
    switch (ch) {
    // CREATE
    case '1':
      create_student();
      break;
    // SEARCH
    case '2':
      cout << c.bold << c.yellow << "SEARCH" << c.def << endl;
      cout << c.bold << c.blue << "\n\nEnter The roll number " << c.def;
      cin >> num;
      display_sp(num);
      buffer();
      break;
    // DISPLAY
    case '3':
      display_all();
      buffer();
      break;
    // DELETE
    case '4':
      num = 0;
      char confirm;
      cout << c.bold << c.yellow << "DELETE RECORD" << c.def << endl;
      cout << c.bold << c.blue << "\n\nEnter The roll number: " << c.def;
      cin >> num;
      display_sp(num);
      if (check_existence(num)) {
        cout << c.bold << c.red << "\n\nAre you sure to delete the entry (Y/N) "
             << c.def;
        cin >> confirm;
        if (tolower(confirm) == 'y') {
          delete_student(num);
          cout << c.green << "Record Deleted!" << c.def;
        } else {
          cout << c.green << "Record Not Deleted .." << c.def;
        }
      }
      buffer();
      break;
    // MODIFY
    case '5':
      cout << c.bold << c.yellow << "MODIFY" << c.def << endl;
      cout << c.blue << "\n\nEnter The roll number " << c.def;
      cin >> num;
      change_student(num);
      buffer();
      break;
    case '6':
      cout << c.black << "Exiting, Thank you!" << c.def;
      exit(0);
    }
  } while (ch != '6');

  return 0;
}
// write student details to file
void create_student() {
  Student st;
  char override;
  Colors c;
  int rollno;
  cout << c.bold << c.yellow << "CREATE STUDENT\n\n" << c.def << endl;
  cout << c.bold << c.blue << "Enter student's roll number: " << c.def;
  cin >> rollno;

  int exists = check_existence(rollno);
  if (exists) {
    cout << c.bold << c.red << "Student Data with that RollNo already exists! "
         << c.def << endl;
    cout << c.bold << c.green << "Do you wish to override the data ? (Y/N)"
         << c.def;
    cin >> override;
    // Safety first
    if (tolower(override) != 'y' && tolower(override) != 'n') {
      cout << c.red
           << "Please input a valid character. Defaulting to NOT override."
           << c.def << endl;
      override = 'n';
    }
    if (tolower(override) == 'y') {
      delete_student(rollno);
    }
  }
  st.getdata(rollno);
  // checker(st);
  // fileChecker("student.dat");
  ofstream oFile;
  oFile.open("student.dat", ios::binary | ios::app);
  if (!oFile) {
    cout << c.red << "\n\nError! Student record could not be created!" << endl;
  } else {
    oFile.write((char *)&st, sizeof(st));
    fileChecker("student.dat");
    cout << c.green << "\n\nStudent record has Been created!" << endl;
  }
  oFile.close();
  st.showdata();
  checker(st);
  buffer();
}
// read file records
void display_all() {
  Colors c;
  Student stud;
  ifstream inFile;
  inFile.open("student.dat", ios::binary);
  if (!inFile) {
    cout << c.red << "File could not be opened." << c.def;
    return;
  }
  cout << c.yellow << "REPORT CARDS\n\n" << c.def;
  while (inFile.read((char *)&stud, sizeof(stud))) {
    stud.showdata();
  }
  inFile.close();
}
// read specific record based on roll number
void display_sp(int n) {
  Colors c;
  Student stud;
  ifstream iFile;
  iFile.open("student.dat", ios::binary);
  if (!iFile) {
    cout << "File could not be opened";
    return;
  }
  bool flag = false;
  while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(Student))) {
    if (stud.rollno == n) {
      stud.showdata();
      flag = true;
    }
  }
  iFile.close();
  if (flag == false)
    cout << c.red << "\n\nRecord does not exist" << c.def;
}
// modify record for specified roll number
void change_student(int n) {
  bool found = false;
  Student stud;
  int data_to_modify;
  Colors c;
  fstream fl;
  fl.open("student.dat", ios::binary | ios::out | ios::in | ios::app);
  if (!fl) {
    cout << c.red << "File could not be opened." << c.def;
    return;
  }
  int exists = check_existence(n);
  if (exists) {
    do {
      while (!fl.eof()) {
        fl.read(reinterpret_cast<char *>(&stud), sizeof(Student));
        if (stud.rollno == n) {
          if (system("clear"))
            system("cls");
          stud.showdata();
          cout << c.bold << c.yellow << "MODIFY:" << c.def;
          cout << c.bold << c.magenta << "\n\n\t1⇾ Name" << c.white
               << " of the Student Record" << c.def;
          cout << c.bold << c.magenta << "\n\n\t2⇾ Roll No" << c.white
               << " of the Student Record" << c.def;
          cout << c.bold << c.magenta << "\n\n\t3⇾ Marks" << c.white
               << " of the Student Record" << c.def;
          cout << c.bold << c.magenta << "\n\n\t4⇾ Save and Exit" << c.white
               << " from this menu" << c.def;
          cout << c.bold << c.green << "\n\nWhat is your Choice? " << c.magenta
               << "(1/2/3/4) " << c.def;
          cin >> data_to_modify;
          switch (data_to_modify) {
          case 1:
            cout << c.magenta << "Name: " << c.def;
            cin >> stud.name;
            break;
          case 2:
            cout << c.magenta << "RollNo: " << c.def;
            cin >> stud.rollno;
            break;
          case 3:
            int sub;
            do {
              if (system("clear"))
                system("cls");
              stud.showdata();
              cout << c.bold << c.magenta << "\n\n\t1⇾  English" << c.white
                   << " Marks" << c.def;
              cout << c.bold << c.magenta << "\n\n\t2⇾  Maths" << c.white
                   << " Marks" << c.def;
              cout << c.bold << c.magenta << "\n\n\t3⇾  Science" << c.white
                   << " Marks" << c.def;
              cout << c.bold << c.magenta << "\n\n\t4⇾  Computer" << c.white
                   << " Marks" << c.def;
              cout << c.bold << c.magenta << "\n\n\t5⇾  Exit" << c.white
                   << " from this menu" << c.def;
              cout << c.bold << c.green << "\n\nWhat is your Choice? "
                   << c.magenta << "(1/2/3/4/5) " << c.def;
              cin >> sub;
              switch (sub) {
              case 1:
                cout << c.magenta << "English: " << c.def;
                cin >> stud.eng;
                break;
              case 2:
                cout << c.magenta << "Maths: " << c.def;
                cin >> stud.maths;
                break;
              case 3:
                cout << c.magenta << "Science: " << c.def;
                cin >> stud.sci;
                break;
              case 4:
                cout << c.magenta << "Computer: " << c.def;
                cin >> stud.comp;
                break;
              }
            } while (sub != 5);
            break;
          case 4:
            break;
          }
        }
        fl.write(reinterpret_cast<char *>(&stud), sizeof(Student));
      }
    } while (data_to_modify != 4);

  } else {
    cout << c.red << "Record doesn't exist.";
  }
  fl.close();
  delete_student(n);
  ofstream oFile;
  oFile.open("student.dat", ios::binary | ios::app);
  oFile.write(reinterpret_cast<char *>(&stud), sizeof(Student));
}
// delete record with particular roll number
void delete_student(int n) {
  Student stud;
  Colors c;
  ifstream iFile;
  iFile.open("student.dat", ios::binary);
  if (!iFile) {
    cout << c.red << "File could not be opened!" << c.def;
    buffer();
    return;
  }
  ofstream oFile;
  oFile.open("Temp.dat");
  iFile.seekg(0, ios::beg);
  while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(Student))) {
    if (stud.rollno != n) {
      oFile.write(reinterpret_cast<char *>(&stud), sizeof(Student));
    }
  }
  oFile.close();
  iFile.close();
  remove("student.dat");
  rename("Temp.dat", "student.dat");
}

void copy_studentFile(string source, string destination) {
  Student stud;
  ifstream iFile;
  iFile.open(source, ios::binary);
  ofstream oFile;
  oFile.open(destination, ios::out);
  iFile.seekg(0, ios::beg);
  while (iFile.read(reinterpret_cast<char *>(&stud), sizeof(Student))) {
    oFile.write(reinterpret_cast<char *>(&stud), sizeof(Student));
  }
  oFile.close();
  iFile.close();
}

int check_existence(int rollno) {
  int retVal = 0;
  copy_studentFile("student.dat", "copied.dat");
  Student stud;
  ifstream inFile;
  inFile.open("copied.dat", ios::binary | ios::app);

  while (inFile.read(reinterpret_cast<char *>(&stud), sizeof(Student))) {
    if (rollno == stud.rollno) {
      retVal = 1;
    }
  }
  inFile.close();
  remove("copied.dat");
  return retVal;
}

void buffer() {
  Colors c;
  cout << c.black << "\nPress ANY key." << endl;
  cin.ignore();
  cin.get();
}

void checker(Student st) { st.showdata(); }

void fileChecker(string fileName) {
  Student stud;
  // copy_studentFile(fileName, "checkBuffer.dat");
  ifstream inFile;
  inFile.open(fileName, ios::binary);
  while (inFile.read((char *)&stud, sizeof(stud))) {
    stud.showdata();
  }
  inFile.close();
}
