#include <iostream>
#include <string>
using namespace std;

struct Expense {
    string e_date;
    double e_amount;
    string e_category;
    string e_description;
};

const int MAX_EXPENSES = 100;
Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

// Scroll down below main function for functions implementation



void addExpense();
    // Function to add an expense
    // Data stored: Date, Amount, Category, Description
    // Categorization of expenses done based on user input
void viewExpense();
    // Function to view expenses
    // Sort and display expenses based on categories or date
    // Display total expenses by category or overall
void searchExpense(); 
    // Function to search expenses
    // Allow user to search expenses based on date, category, or amount
    // Display matching records

void editExpense();
    // Function to edit an existing expense
    // Allow user to select an expense and modify its details

void saveData();
    // Function to save data
    // csv or txt file format can be used to store data

void loadData(); 
    // Function to load data
    // Read data from an existing txt file and populate the records 
    // and wipe previous data (if any) (tentative)

void mainmenu() {
    cout << "Personal Expense Tracker" << endl;
    cout << "------------------------" << endl;
    cout << "1. Add Expense" << endl;
    cout << "2. View Expenses" << endl;
    cout << "3. Search Expenses" << endl;
    cout << "4. Edit Expense" << endl;
    cout << "5. Save Data" << endl;
    cout << "6. Load Data" << endl;
    cout << "7. Exit" << endl;
    cout << "------------------------" << endl;
    
}

int main() {
    int choice;
    do {
        mainmenu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            addExpense();
            break;
        case 2:
            viewExpense();
            break;
        case 3:
            searchExpense();
            break;
        case 4:
            editExpense();
            break;
        case 5:
            saveData();
            break;
        case 6:
            loadData();
            break;
        case 7:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Select a valid option." << endl;
            } 
        } while (choice != 7);
    return 0;
}


void addExpense(){
    return mainmenu();
}
    // Function to add an expense
    // Data stored: Date, Amount, Category, Description
    // Categorization of expenses done based on user input
void viewExpense(){
    return mainmenu();
}
    // Function to view expenses
    // Sort and display expenses based on categories or date
    // Display total expenses by category or overall
void searchExpense(){
    return mainmenu();
}
    // Function to search expenses
    // Allow user to search expenses based on date, category, or amount
    // Display matching records

void editExpense(){
    return mainmenu();
}
    // Function to edit an existing expense
    // Allow user to select an expense and modify its details

void saveData(){
    return mainmenu();
}
    // Function to save data
    // csv or txt file format can be used to store data

void loadData(){
    return mainmenu();
} 
    // Function to load data
    // Read data from an existing txt file and populate the records 
    // and wipe previous data (if any) (tentative)
