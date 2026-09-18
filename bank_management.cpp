#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

class BankAccount
{
private:
    int accountNumber;
    string name;
    double balance;

public:

    void createAccount()
    {
        cout << "Enter Account Number: ";
        cin >> accountNumber;

        cout << "Enter Name: ";
        cin >> name;

        cout << "Enter Initial Balance: ";
        cin >> balance;

        cout << "\nAccount created successfully!\n";
    }

    void display()
    {
        cout << "\n-----------------------------\n";
        cout << "Account Number : " << accountNumber << endl;
        cout << "Name           : " << name << endl;
        cout << "Balance        : " << balance << endl;
        cout << "-----------------------------\n";
    }

    void deposit()
    {
        double amount;

        cout << "Enter amount to deposit: ";
        cin >> amount;

        if (amount > 0)
        {
            balance = balance + amount;
            cout << "Amount deposited successfully!\n";
            cout << "New Balance: " << balance << endl;
        }
        else
        {
            cout << "Invalid amount!\n";
        }
    }

    void withdraw()
    {
        double amount;

        cout << "Enter amount to withdraw: ";
        cin >> amount;

        if (amount <= 0)
        {
            cout << "Invalid amount!\n";
        }
        else if (amount > balance)
        {
            cout << "Insufficient balance!\n";
        }
        else
        {
            balance = balance - amount;
            cout << "Amount withdrawn successfully!\n";
            cout << "Remaining Balance: " << balance << endl;
        }
    }

    void checkBalance()
    {
        cout << "\nCurrent Balance: " << balance << endl;
    }

    void saveToFile()
    {
        ofstream file("bank.txt", ios::app);

        if (!file)
        {
            cout << "Error opening file!\n";
            return;
        }

        file << accountNumber << " "
             << name << " "
             << balance << endl;

        file.close();
    }

    bool loadFromFile(int accNo)
    {
        ifstream file("bank.txt");

        if (!file)
            return false;

        while (file >> accountNumber >> name >> balance)
        {
            if (accountNumber == accNo)
            {
                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    void updateFile()
    {
        ifstream file("bank.txt");
        ofstream temp("temp.txt");

        if (!file || !temp)
        {
            cout << "Error opening file!\n";
            return;
        }

        int id;
        string customerName;
        double customerBalance;

        while (file >> id >> customerName >> customerBalance)
        {
            if (id == accountNumber)
            {
                temp << accountNumber << " "
                     << name << " "
                     << balance << endl;
            }
            else
            {
                temp << id << " "
                     << customerName << " "
                     << customerBalance << endl;
            }
        }

        file.close();
        temp.close();

        remove("bank.txt");
        rename("temp.txt", "bank.txt");
    }
};


int main()
{
    BankAccount account;

    int choice;
    int accountNumber;

    do
    {
        cout << "\n================================\n";
        cout << "       BANK MANAGEMENT SYSTEM\n";
        cout << "================================\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Check Balance\n";
        cout << "5. Display Account\n";
        cout << "6. Exit\n";
        cout << "================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            account.createAccount();
            account.saveToFile();
            break;

        case 2:
            cout << "Enter Account Number: ";
            cin >> accountNumber;

            if (account.loadFromFile(accountNumber))
            {
                account.deposit();
                account.updateFile();
            }
            else
            {
                cout << "Account not found!\n";
            }
            break;

        case 3:
            cout << "Enter Account Number: ";
            cin >> accountNumber;

            if (account.loadFromFile(accountNumber))
            {
                account.withdraw();
                account.updateFile();
            }
            else
            {
                cout << "Account not found!\n";
            }
            break;

        case 4:
            cout << "Enter Account Number: ";
            cin >> accountNumber;

            if (account.loadFromFile(accountNumber))
            {
                account.checkBalance();
            }
            else
            {
                cout << "Account not found!\n";
            }
            break;

        case 5:
            cout << "Enter Account Number: ";
            cin >> accountNumber;

            if (account.loadFromFile(accountNumber))
            {
                account.display();
            }
            else
            {
                cout << "Account not found!\n";
            }
            break;

        case 6:
            cout << "\nThank you for using the Bank Management System!\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}