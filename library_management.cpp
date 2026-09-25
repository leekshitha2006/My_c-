#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Book
{
public:
    int id;
    string title;
    string author;
    bool issued;

    void addBook()
    {
        cout << "Enter Book ID: ";
        cin >> id;

        cout << "Enter Book Title: ";
        cin >> title;

        cout << "Enter Author Name: ";
        cin >> author;

        issued = false;
    }

    void displayBook()
    {
        cout << "\n-----------------------------\n";
        cout << "Book ID     : " << id << endl;
        cout << "Title       : " << title << endl;
        cout << "Author      : " << author << endl;

        if (issued)
            cout << "Status      : Issued" << endl;
        else
            cout << "Status      : Available" << endl;

        cout << "-----------------------------\n";
    }
};


class Member
{
public:
    int memberId;
    string name;

    void addMember()
    {
        cout << "Enter Member ID: ";
        cin >> memberId;

        cout << "Enter Member Name: ";
        cin >> name;
    }
};


void saveBook(Book b)
{
    ofstream file("books.txt", ios::app);

    file << b.id << " "
         << b.title << " "
         << b.author << " "
         << b.issued << endl;

    file.close();
}


void displayBooks()
{
    ifstream file("books.txt");

    Book b;
    bool found = false;

    while (file >> b.id >> b.title >> b.author >> b.issued)
    {
        b.displayBook();
        found = true;
    }

    file.close();

    if (!found)
        cout << "\nNo books found.\n";
}


void issueBook()
{
    int bookId;
    bool found = false;

    cout << "Enter Book ID: ";
    cin >> bookId;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    Book b;

    while (file >> b.id >> b.title >> b.author >> b.issued)
    {
        if (b.id == bookId)
        {
            found = true;

            if (b.issued)
            {
                cout << "Book is already issued!\n";
            }
            else
            {
                b.issued = true;
                cout << "Book issued successfully!\n";
            }
        }

        temp << b.id << " "
             << b.title << " "
             << b.author << " "
             << b.issued << endl;
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        cout << "Book not found!\n";
}


void returnBook()
{
    int bookId;
    bool found = false;

    cout << "Enter Book ID: ";
    cin >> bookId;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    Book b;

    while (file >> b.id >> b.title >> b.author >> b.issued)
    {
        if (b.id == bookId)
        {
            found = true;

            if (!b.issued)
            {
                cout << "This book is already available!\n";
            }
            else
            {
                b.issued = false;
                cout << "Book returned successfully!\n";
            }
        }

        temp << b.id << " "
             << b.title << " "
             << b.author << " "
             << b.issued << endl;
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        cout << "Book not found!\n";
}


void searchBook()
{
    int choice;
    string searchText;

    cout << "\n1. Search by Title\n";
    cout << "2. Search by Author\n";
    cout << "Enter choice: ";
    cin >> choice;

    cout << "Enter search text: ";
    cin >> searchText;

    ifstream file("books.txt");

    Book b;
    bool found = false;

    while (file >> b.id >> b.title >> b.author >> b.issued)
    {
        if (choice == 1 && b.title == searchText)
        {
            b.displayBook();
            found = true;
        }
        else if (choice == 2 && b.author == searchText)
        {
            b.displayBook();
            found = true;
        }
    }

    file.close();

    if (!found)
        cout << "\nBook not found!\n";
}


int main()
{
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "       LIBRARY MANAGEMENT SYSTEM\n";
        cout << "====================================\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Search Book\n";
        cout << "6. Exit\n";
        cout << "====================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            Book b;

            b.addBook();
            saveBook(b);

            cout << "Book added successfully!\n";
            break;
        }

        case 2:
            displayBooks();
            break;

        case 3:
            issueBook();
            break;

        case 4:
            returnBook();
            break;

        case 5:
            searchBook();
            break;

        case 6:
            cout << "\nThank you for using the Library Management System!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}