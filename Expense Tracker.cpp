#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

using namespace std;

class Expense 
{
public:
    string time;
    string description;
    string date;
    int amount;

    void inputExpense() {
        cout << "Enter date: ";
        cin >> date;
        cout << "Enter time: ";
        cin >> time;
        cout << "Enter amount: ";
        cin >> amount;
        cout << "Enter description: ";
        cin >> description;
    }

    void displayExpense() {
        cout << "Date: " << date << ", Time: " << time << ", Amount: " << amount << ", Description: " << description << endl;
    }
};

void writeToFile(const multimap<string, Expense>& expenseMap, const string& filename) {
    ofstream file(filename);
    file << left << setw(12) << "Date" << setw(8) << "Time" << setw(10) << "Amount" << "Description\n";
    int totalAmount = 0;
    if (file.is_open()) {
        for (const auto& pair : expenseMap) {
            Expense exp = pair.second;
            file << left << setw(12) << exp.date << setw(8) << exp.time << setw(10) << exp.amount << exp.description << endl;
            totalAmount += exp.amount;
        }
        file << "\n\nTotal Amount: " << totalAmount << endl;
        file.close();
        cout << "Data written to " << filename << " successfully.\n";
    } else {
        cout << "Error opening the file.\n";
    }
}

int calculateTotalAmount(const multimap<string, Expense>& expenseMap) {
    int totalAmount = 0;
    for (const auto& pair : expenseMap) {
        totalAmount += pair.second.amount;
    }
    return totalAmount;
}

int main() {
    multimap<string, Expense> expenseMap;

    int choice, total=0;
    string filename;

    do {
        cout << "\nMenu:\n1. Add Expense\n2. Display Expenses\n3. Save Expenses to File\n4. Exit\nEnter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: {
                Expense newExpense;
                newExpense.inputExpense();
                expenseMap.insert({newExpense.date, newExpense});
                break;
            }
            case 2: {
                for (const auto& pair : expenseMap) {
                    Expense exp = pair.second;
                    exp.displayExpense();
                }
                break;
            }
            case 3:
                cout << "Enter the name of the file: ";
                cin >> filename;
                writeToFile(expenseMap, filename);
                total = calculateTotalAmount(expenseMap);
                cout << "Total Amount: " << total << endl;
                break;
            case 4:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while(choice != 4);

    return 0;
}