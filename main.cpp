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
    cout << "---------------------------------------" << endl;
    cout << "Personal Expense Tracker (by gitSilog)" << endl;
    cout << "---------------------------------------" << endl;
    cout << "1. Add Expense" << endl;
    cout << "2. View Expenses" << endl;
    cout << "3. Search Expenses" << endl;
    cout << "4. Edit Expense" << endl;
    cout << "5. Save Data" << endl;
    cout << "6. Load Data" << endl;
    cout << "7. Exit" << endl;
    cout << "---------------------------------------" << endl;

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
        //case 5:
            saveData();
            break;
        //case 6:
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


void addExpense() {
    if (expenseCount >= MAX_EXPENSES) {
        cout << "Expense limit reached. Cannot add more expenses." << endl;
        return;
    }

    cout << "Enter date (YYYY-MM-DD): ";
    cin >> expenses[expenseCount].e_date;

    cout << "Enter amount: ";
    cin >> expenses[expenseCount].e_amount;

    cout << "Enter category: ";
    cin >> expenses[expenseCount].e_category;

    cout << "Enter description: ";
    cin.ignore();
    getline(cin, expenses[expenseCount].e_description);

    expenseCount++;
    cout << "Expense added successfully!" << endl;
}

void viewExpense() {
    if (expenseCount == 0) {
        cout << "No expenses to display." << endl;
        return;
    }

    cout << "Sort by: 1. Entry order 2. Date 3. Category" << endl;
    cout << "Enter your choice: ";
    int sortChoice;
    if (!(cin >> sortChoice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid choice." << endl;
        return;
    }
    cin.ignore(10000, '\n');

    if (sortChoice < 1 || sortChoice > 3) {
        cout << "Invalid choice." << endl;
        return;
    }

    int order[MAX_EXPENSES];
    for (int i = 0; i < expenseCount; i++) {
        order[i] = i;
    }

    if (sortChoice == 2 || sortChoice == 3) {
        for (int i = 0; i < expenseCount - 1; i++) {
            for (int j = 0; j < expenseCount - i - 1; j++) {
                bool shouldSwap = false;
                if (sortChoice == 2) {
                    shouldSwap = expenses[order[j]].e_date > expenses[order[j + 1]].e_date;
                } else {
                    shouldSwap = expenses[order[j]].e_category > expenses[order[j + 1]].e_category;
                }

                if (shouldSwap) {
                    int temp = order[j];
                    order[j] = order[j + 1];
                    order[j + 1] = temp;
                }
            }
        }
    }

    cout << "Expenses List:" << endl;
    double overallTotal = 0;
    for (int i = 0; i < expenseCount; i++) {
        int index = order[i];
        const Expense& expense = expenses[index];
        cout << "ID: " << index + 1 << ", Date: " << expense.e_date
             << ", Amount: " << expense.e_amount
             << ", Category: " << expense.e_category
             << ", Description: " << expense.e_description << endl;
        overallTotal += expense.e_amount;
    }

    cout << "Total expenses: " << overallTotal << endl;
    cout << "Totals by category:" << endl;
    for (int i = 0; i < expenseCount; i++) {
        bool categoryAlreadyShown = false;
        for (int previous = 0; previous < i; previous++) {
            if (expenses[previous].e_category == expenses[i].e_category) {
                categoryAlreadyShown = true;
                break;
            }
        }

        if (!categoryAlreadyShown) {
            double categoryTotal = 0;
            for (int j = 0; j < expenseCount; j++) {
                if (expenses[j].e_category == expenses[i].e_category) {
                    categoryTotal += expenses[j].e_amount;
                }
            }
            cout << expenses[i].e_category << ": " << categoryTotal << endl;
        }
    }
}

void searchExpense() {
    if (expenseCount == 0) {
        cout << "No expenses to search." << endl;
        return;
    }

    int searchChoice;
    cout << "Search by: 1. Date 2. Category 3. Amount" << endl;
    cin >> searchChoice;

    bool found = false;

    switch (searchChoice) {
    case 1: {
        string searchDate;
        cout << "Enter date (YYYY-MM-DD): ";
        cin >> searchDate;
        for (int i = 0; i < expenseCount; i++) {
            if (expenses[i].e_date == searchDate) {
                cout << "Date: " << expenses[i].e_date << ", Amount: " << expenses[i].e_amount
                     << ", Category: " << expenses[i].e_category << ", Description: "
                     << expenses[i].e_description << endl;
                found = true;
            }
        }
        break;
    }
    case 2: {
        string searchCategory;
        cout << "Enter category: ";
        cin >> searchCategory;
        for (int i = 0; i < expenseCount; i++) {
            if (expenses[i].e_category == searchCategory) {
                cout << "Date: " << expenses[i].e_date << ", Amount: " << expenses[i].e_amount
                     << ", Category: " << expenses[i].e_category << ", Description: "
                     << expenses[i].e_description << endl;
                found = true;
            }
        }
        break;
    }
    case 3: {
        double searchAmount;
        cout << "Enter amount: ";
        cin >> searchAmount;
        for (int i = 0; i < expenseCount; i++) {
            if (expenses[i].e_amount == searchAmount) {
                cout << "Date: " << expenses[i].e_date << ", Amount: " << expenses[i].e_amount
                     << ", Category: " << expenses[i].e_category << ", Description: "
                     << expenses[i].e_description << endl;
                found = true;
            }
        }
        break;
    }
    default:
        cout << "Invalid choice." << endl;
        return;
    }

    if (!found) {
        cout << "No matching expenses found." << endl;
    }
}

void editExpense() {
    if (expenseCount == 0) {
        cout << "No expenses to edit." << endl;
        return;
    }

    int id;
    cout << "Expenses:" << endl;
    for (int i = 0; i < expenseCount; i++) {
        cout << "ID: " << i + 1 << ", Date: " << expenses[i].e_date
             << ", Amount: " << expenses[i].e_amount
             << ", Category: " << expenses[i].e_category
             << ", Description: " << expenses[i].e_description << endl;
    }

    cout << "Enter the ID of the expense to edit (1 to " << expenseCount << "): ";
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid ID." << endl;
        return;
    }

    if (id < 1 || id > expenseCount) {
        cout << "Invalid ID." << endl;
        return;
    }

    int index = id - 1;
    cin.ignore(10000, '\n');
    cout << "Editing expense " << id << " (leave a field blank to keep it unchanged)." << endl;

    Expense updatedExpense = expenses[index];
    string input;
    cout << "Current date: " << updatedExpense.e_date << " - New date: ";
    getline(cin, input);
    if (!input.empty()) {
        updatedExpense.e_date = input;
    }

    cout << "Current amount: " << updatedExpense.e_amount << " - New amount: ";
    getline(cin, input);
    if (!input.empty()) {
        try {
            size_t parsedCharacters = 0;
            double amount = stod(input, &parsedCharacters);
            size_t lastNonSpace = input.find_last_not_of(" \t\r\n");
            if (lastNonSpace == string::npos || parsedCharacters != lastNonSpace + 1) {
                cout << "Invalid amount. Expense was not updated." << endl;
                return;
            }
            updatedExpense.e_amount = amount;
        } catch (...) {
            cout << "Invalid amount. Expense was not updated." << endl;
            return;
        }
    }

    cout << "Current category: " << updatedExpense.e_category << " - New category: ";
    getline(cin, input);
    if (!input.empty()) {
        updatedExpense.e_category = input;
    }

    cout << "Current description: " << updatedExpense.e_description << " - New description: ";
    getline(cin, input);
    if (!input.empty()) {
        updatedExpense.e_description = input;
    }

    expenses[index] = updatedExpense;
    cout << "Expense updated successfully!" << endl;
}

//void saveData(){
    //return mainmenu();
//}
    // Function to save data
    // csv or txt file format can be used to store data

//void loadData(){
    //return mainmenu();
//} 
    // Function to load data
    // Read data from an existing txt file and populate the records 
    // and wipe previous data (if any) (tentative)