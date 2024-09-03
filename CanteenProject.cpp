#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <vector>
using namespace std;

// Function Declarations
void write_account();
void display_all();
void all_items();
void intro();
void add_item();
void edit_item();
void delete_item();
void manager_mode();

// Structure for Items
struct Items
{
    string itemname;
    int price;
};
vector<Items> item;

// Class for Customer Account
class account
{
    int age;
    char name[50];
    char type;
    int total = 0;

public:
    void create_account();
    void show_account() const;
    void report() const;
};

void account::create_account()
{
    int i = 1, x = 1;
    cout << "\n\nEnter The Name of customer: ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nEnter The Age: ";
    cin >> age;
    cout << "\nEnter Gender of Customer (m/f): ";
    cin >> type;
    type = toupper(type);
    cout << "\n\n\nCustomer Created.." << endl
         << endl;
    all_items();
    cout << endl;
    while (1)
    {
        cout << "Press 0 to submit" << endl
             << endl;
        cout << "Enter the item id you want to purchase: ";
        if (i <= item.size())
        {
            cin >> i;
            if (i == 0)
                break;
            cout << "Enter the number of quantity you want of that item: ";
            cin >> x;
            total = total + (item[i - 1].price * x);
        }
        else
            cout << "Invalid entry" << endl;
    }
    cout << "Your bill is " << total << endl;
}

void account::show_account() const
{
    cout << "\nAge: " << age;
    cout << "\nCustomer Name: " << name;
    cout << "\nGender of Customer: " << type;
}

void account::report() const
{
    cout << age << setw(10) << " " << name << setw(10) << " " << type << setw(6) << total << endl
         << endl;
}

void write_account()
{
    account ac;
    ofstream outFile;
    outFile.open("account.dat", ios::binary | ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char *>(&ac), sizeof(account));
    outFile.close();
}

void all_items()
{
    int i = 0;
    cout << "Item ID"
         << "\t"
         << "Item Name"
         << "\t"
         << "Price" << endl
         << endl;
    for (i = 0; i < item.size(); i++)
    {
        cout << i + 1 << "\t" << item[i].itemname << "\t\t" << item[i].price << endl;
    }
}

void add_item()
{
    string a;
    int b;
    cout << "Enter the item name: ";
    cin >> a;
    cout << "Enter the item price: ";
    cin >> b;
    item.push_back({a, b});
    cout << "Item added successfully" << endl
         << endl;
    all_items();
}

void edit_item()
{
    int j;
    cout << "Enter the ID of item: ";
    cin >> j;
    if (j <= item.size())
    {
        cout << "Enter the item name: ";
        cin >> item[j - 1].itemname;
        cout << "Enter the item price: ";
        cin >> item[j - 1].price;
        cout << endl
             << "Item edited successfully" << endl;
    }
    else
    {
        cout << "Invalid entry";
    }
}

void delete_item()
{
    int j;
    cout << "Enter the ID of item: ";
    cin >> j;
    if (j <= item.size())
    {
        item.erase(item.begin() + j - 1);
        cout << endl
             << "Item deleted successfully" << endl;
    }
    else
    {
        cout << "Invalid entry";
    }
}

void display_all()
{
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open! Press any Key...";
        return;
    }
    cout << "\n\n\t\tCUSTOMER LIST\n\n";
    cout << "====================================================\n";
    cout << "Age      NAME           Type      Bill\n";
    cout << "====================================================\n";
    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}

void manager_mode()
{
    string password;
    cout << "Enter the manager password: ";
    cin >> password;

    if (password == "avishar")
    {
        char ch;
        do
        {
            system("cls");
            cout << "\n\n\n\tMANAGER MENU";
            cout << "\n\n\t1. All Items";
            cout << "\n\n\t2. Add New Items";
            cout << "\n\n\t3. Edit Item";
            cout << "\n\n\t4. Delete Item";
            cout << "\n\n\t5. View Customer List";
            cout << "\n\n\t6. Exit";
            cout << "\n\n\tSelect Your Option (1-6): ";
            cin >> ch;
            system("cls");
            switch (ch)
            {
            case '1':
                all_items();
                break;
            case '2':
                add_item();
                break;
            case '3':
                edit_item();
                break;
            case '4':
                delete_item();
                break;
            case '5':
                display_all();
                break;
            case '6':
                cout << "\n\n\tExiting Manager Mode";
                break;
            default:
                cout << "\a";
            }
            cin.ignore();
            cin.get();
        } while (ch != '6');
    }
    else
    {
        cout << "Incorrect manager password. Access denied.";
    }
}

int main()
{
    char ch;
    item.push_back({"Chips", 20});
    item.push_back({"Kurkure", 20});
    item.push_back({"Maggie", 30});
    item.push_back({"Toffee", 10});
    item.push_back({"Biscuit", 45});
    item.push_back({"Dosa", 90});

    do
    {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t1. New Customer";
        cout << "\n\n\t2. Manager Mode";
        cout << "\n\n\t3. Exit";
        cout << "\n\n\tSelect Your Option (1-3): ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            manager_mode();
            break;
        case '3':
            cout << "\n\n\tThanks for using Canteen Management System";
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch != '3');
    return 0;
}

