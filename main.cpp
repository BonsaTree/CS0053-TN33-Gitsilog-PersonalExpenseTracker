#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Expense {
  string e_date;
  double e_amount;
  string e_category;
  string e_description;
};

const int MAX_EXPENSES = 100;
const int IGNORE_LIMIT = 10000; // Limit for ignoring characters in input stream
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
void printExpense(const Expense &expense, int id);
// Helper function in printing expense data

void displaymainmenu() {
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
    displaymainmenu();
    cout << "Enter your choice: ";
    if (!(cin >> choice)) {
      cin.clear();
      cin.ignore(IGNORE_LIMIT, '\n');
      cout << "Invalid input. Please enter a number." << endl;
      continue;
    };
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

void addExpense() {
  if (expenseCount >= MAX_EXPENSES) {
    cout << "Expense limit reached. Cannot add more expenses." << endl;
    return;
  }

  cout << "Enter date (YYYY-MM-DD): ";
  cin >> expenses[expenseCount].e_date;

  cout << "Enter amount: ";
  if (!(cin >> expenses[expenseCount].e_amount) ||
      expenses[expenseCount].e_amount <=
          0) // Check for invalid input or negative amount
  {
    cin.clear();
    cin.ignore(IGNORE_LIMIT, '\n');
    cout << "Invalid amount. Please enter a positive number." << endl;
    return;
  }

  cout << "Enter category: ";
  cin >> expenses[expenseCount].e_category;
  if (expenses[expenseCount].e_category.find_first_not_of(" \t\r\n") == string::npos) {
    cout << "Category cannot be empty." << endl;
    return;
  }

  cout << "Enter description: ";
  cin.ignore();
  getline(cin, expenses[expenseCount].e_description);

  expenseCount++;
  cout << "Expense added successfully!" << endl;
  return;
}

void viewExpense() {
  if (expenseCount == 0) {
    cout << "No expenses to display." << endl;
    return;
  }

  cout << "Sort by:" << endl;
  cout << "1. Entry order" << endl;
  cout << "2. Date" << endl;
  cout << "3. Category" << endl;
  cout << "Enter your choice: ";
  int sortChoice;
  if (!(cin >> sortChoice)) {
    cin.clear();
    cin.ignore(IGNORE_LIMIT, '\n');
    cout << "Invalid choice." << endl;
    return;
  }
  cin.ignore(IGNORE_LIMIT, '\n');

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
          shouldSwap =
              expenses[order[j]].e_date > expenses[order[j + 1]].e_date;
        } else {
          shouldSwap =
              expenses[order[j]].e_category > expenses[order[j + 1]].e_category;
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
    printExpense(expenses[index], index + 1);
    overallTotal += expenses[index].e_amount;
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
  if (!(cin >> searchChoice)) {
    cin.clear();
    cin.ignore(IGNORE_LIMIT, '\n');
    cout << "Invalid choice." << endl;
    return;
  }

  bool found = false;

  switch (searchChoice) {
  case 1: {
    string searchDate = "";
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> searchDate;
    for (int i = 0; i < expenseCount; i++) {
      if (expenses[i].e_date == searchDate) {
        printExpense(expenses[i], i + 1);
        found = true;
      }
    }
    break;
  }
  case 2: {
    string searchCategory = "";
    cout << "Enter category: ";
    cin >> searchCategory;
    for (int i = 0; i < expenseCount; i++) {
      if (expenses[i].e_category == searchCategory) {
        printExpense(expenses[i], i + 1);
        found = true;
      }
    }
    break;
  }
  case 3: {
    double searchAmount = 0;
    cout << "Enter amount: ";
    if (!(cin >> searchAmount) || searchAmount <= 0) {
      cin.clear();
      cin.ignore(IGNORE_LIMIT, '\n');
      cout << "Invalid amount." << endl;
      return;
    }
    for (int i = 0; i < expenseCount; i++) {
      if (expenses[i].e_amount == searchAmount) {
        printExpense(expenses[i], i + 1);
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
    printExpense(expenses[i], i + 1);
  }

  cout << "Enter the ID of the expense to edit (1 to " << expenseCount << "): ";
  if (!(cin >> id)) {
    cin.clear();
    cin.ignore(IGNORE_LIMIT, '\n');
    cout << "Invalid ID." << endl;
    return;
  }

  if (id < 1 || id > expenseCount) {
    cout << "Invalid ID." << endl;
    return;
  }

  int index = id - 1;
  cin.ignore(IGNORE_LIMIT, '\n');
  cout << "Editing expense " << id
       << " (leave a field blank to keep it unchanged)." << endl;

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
      if (amount <= 0 || (lastNonSpace != string::npos &&
          parsedCharacters != lastNonSpace + 1)) {
        cout << "Invalid amount. Expense was not updated." << endl;
        return;
      }
      updatedExpense.e_amount = amount;
    } catch (...) {
      cout << "Invalid amount. Expense was not updated." << endl;
      return;
    }
  }

  cout << "Current category: " << updatedExpense.e_category
       << " - New category: ";
  getline(cin, input);
  if (!input.empty()) {
    updatedExpense.e_category = input;
  }

  cout << "Current description: " << updatedExpense.e_description
       << " - New description: ";
  getline(cin, input);
  if (!input.empty()) {
    updatedExpense.e_description = input;
  }

  expenses[index] = updatedExpense;
  cout << "Expense updated successfully!" << endl;
}

void saveData() {
  ofstream outFile("expenses.txt");

  if (!outFile) {
    cout << "Error: Unable to open file for saving." << endl;
    return;
  }

  for (int i = 0; i < expenseCount; i++) {
    outFile << expenses[i].e_date << "|" << expenses[i].e_amount << "|"
            << expenses[i].e_category << "|" << expenses[i].e_description
            << endl;
  }
  outFile.close();

  cout << "Expenses saved successfully!" << endl;
}

void loadData() {
  ifstream inFile("expenses.txt");

  if (!inFile) {
    cout << "Error: Unable to open file for loading." << endl;
    return;
  }

  Expense loadedExpenses[MAX_EXPENSES];
  int loadedCount = 0;
  string line;

  while (getline(inFile, line)) {
    if (line.empty()) {
      continue;
    }

    if (loadedCount >= MAX_EXPENSES) {
      cout << "Error: File contains too many expenses." << endl;
      inFile.close();
      return;
    }

    stringstream ss(line);
    string date, amountText, category, description;

    if (!getline(ss, date, '|') || !getline(ss, amountText, '|') ||
        !getline(ss, category, '|') || !getline(ss, description)) {

      cout << "Error: Invalid data found in file." << endl;
      inFile.close();
      return;
    }

    try {
      size_t parsedCharacters;
      double amount = stod(amountText, &parsedCharacters);

      if (parsedCharacters != amountText.length()) {
        cout << "Error: Invalid amount in file." << endl;
        inFile.close();
        return;
      }

      loadedExpenses[loadedCount].e_date = date;
      loadedExpenses[loadedCount].e_amount = amount;
      loadedExpenses[loadedCount].e_category = category;
      loadedExpenses[loadedCount].e_description = description;

      loadedCount++;
    } catch (...) {
      cout << "Error: Invalid amount in file." << endl;
      inFile.close();
      return;
    }
  }

  inFile.close();

  for (int i = 0; i < loadedCount; i++) {
    expenses[i] = loadedExpenses[i];
  }

  expenseCount = loadedCount;

  cout << "Expense loaded successfully!" << endl;
  cout << "Total records loaded: " << expenseCount << endl;
}

void printExpense(const Expense &expense, int id) {
  cout << "ID: " << id << ", Date: " << expense.e_date
       << ", Amount: " << expense.e_amount
       << ", Category: " << expense.e_category
       << ", Description: " << expense.e_description << endl;
}