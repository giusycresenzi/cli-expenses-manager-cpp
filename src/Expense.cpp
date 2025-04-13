#include "../include/Expense.h"


// Print the details of the expense
void Expense::print() const {
    std::cout << ", Description: " << description
              << "Date: " << date.day << "/" << date.month << "/" << date.year
              << ", Amount: " << amount
              << ", Category: " << category << std::endl;
}

// Filter expenses by a keyword in the description
std::vector<Expense> Expense::filterByKeyword(const std::vector<Expense>& expenses, const std::string& keyword) {
    std::vector<Expense> filteredExpenses;
    for (const auto& expense : expenses) {
        if (expense.description.find(keyword) != std::string::npos) {
            filteredExpenses.push_back(expense);
        }
    }
    return filteredExpenses;
}

// Filter expenses by a specific month and year
std::vector<Expense> Expense::filterByMonth(const std::vector<Expense>& expenses, int year, int month) {
    std::vector<Expense> filteredExpenses;
    for (const auto& expense : expenses) {
        if (expense.date.year == year && expense.date.month == month) {
            filteredExpenses.push_back(expense);
        }
    }
    return filteredExpenses;
}

// Generate a monthly report for a specific year and month
void Expense::generateMonthlyReport(const std::vector<Expense>& expenses, int year, int month) {
    auto filteredExpenses = filterByMonth(expenses, year, month);
    double totalAmount = 0.0;

    std::cout << "Monthly Report for " << year << "-" << std::setw(2) << std::setfill('0') << month << ":\n";
    for (const auto& expense : filteredExpenses) {
        expense.print();
        totalAmount += expense.amount;
    }
    std::cout << "Total Expenses: " << totalAmount << std::endl;
}

// Generate recurring expenses based on a given expense
std::vector<Expense> Expense::generateRecurringExpenses(const Expense& expense, int recurrencePeriodInMonths, int numberOfOccurrences) {
    std::vector<Expense> recurringExpenses;
    Expense newExpense = expense;

    for (int i = 0; i < numberOfOccurrences; ++i) {
        newExpense.date.month += recurrencePeriodInMonths;
        while (newExpense.date.month > 12) {
            newExpense.date.month -= 12;
            newExpense.date.year += 1;
        }
        recurringExpenses.push_back(newExpense);
    }
    return recurringExpenses;
}