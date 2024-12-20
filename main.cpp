#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

struct Expense {
    string date;
    string category;
    string description;
    double amount;
};

void addExpense(vector<Expense>& expenses) {
    Expense newExpense;
    cout << "Enter Valid date (YYYY-MM-DD): ";
    cin >> newExpense.date;
    cout << "Enter category (Food, Transport, Shopping, Other): ";
    cin >> newExpense.category;
    cout << "Enter description for product: ";
    cin.ignore();
    getline(cin, newExpense.description);
    cout << "Enter amount that you've Spent : ";
    cin >> newExpense.amount;
    expenses.push_back(newExpense);
    cout << "Expense added successfully.\n";
}

void viewExpenses(const vector<Expense>& expenses) {
    string category;
    cout << "Enter category to view (Food, Transport, Shopping, Other): ";
    cin >> category;
    double total = 0.0;
    cout << "\nExpenses in category: " << category << "\n";
    cout << "*************************************************************\n";
    cout << "Date       | Description       | Amount\n";
    cout << "*************************************************************\n";
    for (const auto& exp : expenses) {
        if (exp.category == category) {
            cout << exp.date << " | " << exp.description << " | $" << fixed << setprecision(2) << exp.amount << "\n";
            total += exp.amount;
        }
    }
    cout << "*************************************************************\n";
    cout << "Total " << category << " expenses: $" << fixed << setprecision(2) << total << "\n";
}

void loadExpensesFromFile(vector<Expense>& expenses, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        Expense exp;
        while (file >> exp.date >> exp.category >> ws) {
            getline(file, exp.description, ' ');
            file >> exp.amount;
            expenses.push_back(exp);
        }
        file.close();
        cout << "Expenses loaded from file successfully.\n";
    } else {
        cout << "No previous data found.\n";
    }
}

int main() {
    vector<Expense> expenses;
    string filename = "expenses.txt";

    loadExpensesFromFile(expenses, filename);

    int choice;
    do {
        cout << "\nExpense Tracker Menu\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses by Category\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addExpense(expenses);
                break;
            case 2:
                viewExpenses(expenses);
                break;
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
