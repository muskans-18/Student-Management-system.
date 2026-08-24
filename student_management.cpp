#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstdio>
using namespace std;

struct Student {
    int rollNo;
    string name;
    int age;
    string course;
    string phone;
};

const string FILE_NAME = "students.dat";

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool rollExists(int rollNo) {
    ifstream file(FILE_NAME, ios::binary);
    Student s;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.rollNo == rollNo)
            return true;
    }
    return false;
}

void addStudent() {
    Student s;

    cout << "\n--- Add Student ---\n";
    cout << "Enter Roll Number: ";
    cin >> s.rollNo;

    if (cin.fail()) {
        clearInput();
        cout << "Invalid roll number.\n";
        return;
    }

    if (rollExists(s.rollNo)) {
        cout << "A student with this roll number already exists.\n";
        return;
    }

    clearInput();

    cout << "Enter Name: ";
    getline(cin, s.name);

    cout << "Enter Age: ";
    cin >> s.age;
    clearInput();

    cout << "Enter Course: ";
    getline(cin, s.course);

    cout << "Enter Phone Number: ";
    getline(cin, s.phone);

    ofstream file(FILE_NAME, ios::binary | ios::app);
    file.write(reinterpret_cast<char*>(&s), sizeof(Student));

    cout << "Student added successfully!\n";
}

void displayStudents() {
    ifstream file(FILE_NAME, ios::binary);
    Student s;
    bool found = false;

    cout << "\n---------------- Student Records ----------------\n";
    cout << left << setw(10) << "Roll"
         << setw(25) << "Name"
         << setw(8) << "Age"
         << setw(20) << "Course"
         << setw(18) << "Phone" << '\n';
    cout << string(81, '-') << '\n';

    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        found = true;
        cout << left << setw(10) << s.rollNo
             << setw(25) << s.name
             << setw(8) << s.age
             << setw(20) << s.course
             << setw(18) << s.phone << '\n';
    }

    if (!found)
        cout << "No student records found.\n";
}

void searchStudent() {
    int rollNo;
    cout << "\nEnter Roll Number to search: ";
    cin >> rollNo;

    if (cin.fail()) {
        clearInput();
        cout << "Invalid roll number.\n";
        return;
    }

    ifstream file(FILE_NAME, ios::binary);
    Student s;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.rollNo == rollNo) {
            found = true;
            cout << "\nStudent Found!\n";
            cout << "Roll Number : " << s.rollNo << '\n';
            cout << "Name        : " << s.name << '\n';
            cout << "Age         : " << s.age << '\n';
            cout << "Course      : " << s.course << '\n';
            cout << "Phone       : " << s.phone << '\n';
            break;
        }
    }

    if (!found)
        cout << "Student not found.\n";
}

void updateStudent() {
    int rollNo;
    cout << "\nEnter Roll Number to update: ";
    cin >> rollNo;

    if (cin.fail()) {
        clearInput();
        cout << "Invalid roll number.\n";
        return;
    }

    fstream file(FILE_NAME, ios::binary | ios::in | ios::out);
    Student s;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.rollNo == rollNo) {
            found = true;
            clearInput();

            cout << "Enter New Name: ";
            getline(cin, s.name);

            cout << "Enter New Age: ";
            cin >> s.age;
            clearInput();

            cout << "Enter New Course: ";
            getline(cin, s.course);

            cout << "Enter New Phone Number: ";
            getline(cin, s.phone);

            streampos position = file.tellg() - static_cast<streamoff>(sizeof(Student));
            file.seekp(position);
            file.write(reinterpret_cast<char*>(&s), sizeof(Student));

            cout << "Student updated successfully!\n";
            break;
        }
    }

    if (!found)
        cout << "Student not found.\n";
}

void deleteStudent() {
    int rollNo;
    cout << "\nEnter Roll Number to delete: ";
    cin >> rollNo;

    if (cin.fail()) {
        clearInput();
        cout << "Invalid roll number.\n";
        return;
    }

    ifstream input(FILE_NAME, ios::binary);
    ofstream temp("temp.dat", ios::binary);

    Student s;
    bool found = false;

    while (input.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.rollNo == rollNo) {
            found = true;
            continue;
        }
        temp.write(reinterpret_cast<char*>(&s), sizeof(Student));
    }

    input.close();
    temp.close();

    remove(FILE_NAME.c_str());
    rename("temp.dat", FILE_NAME.c_str());

    if (found)
        cout << "Student deleted successfully!\n";
    else
        cout << "Student not found.\n";
}

void showMenu() {
    cout << "\n============================================\n";
    cout << "       STUDENT MANAGEMENT SYSTEM\n";
    cout << "============================================\n";
    cout << "1. Add Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Please enter a valid choice.\n";
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                cout << "\nThank you for using Student Management System!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);

    return 0;
}
