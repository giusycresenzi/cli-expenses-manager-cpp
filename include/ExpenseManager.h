#ifndef EXPENSE_MANAGER_H
#define EXPENSE_MANAGER_H

#include "Expense.h"

class ExpenseManager {
private:
    std::vector<Expense> expenses;

public:
    // Add a new expense
    void addExpense(const Expense& expense) {
        expenses.push_back(expense);
    }

    // Remove an expense by index
    void removeExpense(size_t index) {
        if (index < expenses.size()) {
            expenses.erase(expenses.begin() + index);
        }
    }

    // List all expenses
    void listExpenses() const {
        for (size_t i = 0; i < expenses.size(); ++i) {
            std::cout << "[" << i << "] ";
            expenses[i].print();
        }
    }

    // Filter expenses by category
    std::vector<Expense> filterByCategory(const std::string& category) const {
        std::vector<Expense> filtered;
        for (const auto& expense : expenses) {
            if (expense.getCategory() == category) {
                filtered.push_back(expense);
            }
        }
        return filtered;
    }

    // Filter expenses by date (year and month)
    std::vector<Expense> filterByDate(int year, int month) const {
        return Expense::filterByMonth(expenses, year, month);
    }

    // Generate a monthly report
    void generateMonthlyReport(int year, int month) const {
        Expense::generateMonthlyReport(expenses, year, month);
    }
};

#endif // EXPENSE_MANAGER_H