#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;
struct Student {
    int id, age;
    string name, course;
    float marks;
};

void add() {
    Student s;
    cout << "ID: "; cin >> s.id;
    cout << "Name: "; cin >> s.name;
    cout << "Age: "; cin >> s.age;
    cout << "Course: "; cin >> s.course;
    cout << "Marks: "; cin >> s.marks;

    ofstream f("students.txt", ios::app);
    f << s.id << " " << s.name << " "
      << s.age << " " << s.course << " "
      << s.marks << endl;
    f.close();

    cout << "Student added!\n";
}

void display() {
    Student s;
    ifstream f("students.txt");

    while (f >> s.id >> s.name >> s.age >> s.course >> s.marks)
        cout << s.id << " " << s.name << " "
             << s.age << " " << s.course << " "
             << s.marks << endl;

    f.close();
}

void update() {
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID: ";
    cin >> id;

    ifstream f("students.txt");
    ofstream t("temp.txt");

    while (f >> s.id >> s.name >> s.age >> s.course >> s.marks) {
        if (s.id == id) {
            cout << "Name: "; cin >> s.name;
            cout << "Age: "; cin >> s.age;
            cout << "Course: "; cin >> s.course;
            cout << "Marks: "; cin >> s.marks;
            found = true;
        }

        t << s.id << " " << s.name << " "
          << s.age << " " << s.course << " "
          << s.marks << endl;
    }

    f.close();
    t.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    cout << (found ? "Updated!\n" : "Not found!\n");
}

void removeStudent() {
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID: ";
    cin >> id;

    ifstream f("students.txt");
    ofstream t("temp.txt");

    while (f >> s.id >> s.name >> s.age >> s.course >> s.marks) {
        if (s.id == id)
            found = true;
        else
            t << s.id << " " << s.name << " "
              << s.age << " " << s.course << " "
              << s.marks << endl;
    }

    f.close();
    t.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    cout << (found ? "Deleted!\n" : "Not found!\n");
}

int main() {
    int choice;

    do {
        cout << "\n1. Add\n2. Display\n3. Update\n4. Delete\n5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) add();
        else if (choice == 2) display();
        else if (choice == 3) update();
        else if (choice == 4) removeStudent();
        else if (choice != 5) cout << "Invalid choice!\n";

    } while (choice != 5);

    return 0;
}