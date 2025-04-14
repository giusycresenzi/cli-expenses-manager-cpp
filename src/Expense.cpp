#include "../include/Expense.h"


// Print the details of the expense
void Expense::print() const {
    std::cout << ", Description: " << description
              << "Date: " << std::put_time(&date, "%d/%m/%Y") // put_time(&var) formats the date
              << ", Amount: " << amount
              << ", Category: " << category << std::endl;
}

bool Expense::IsDue() {
    if (!isRecurring) return; // Only process recurring expenses

    // Get the current date
    std::time_t now_time = std::time(nullptr); // Get the current time as time_t
    std::tm* currentDate = std::localtime(&now_time); // Convert to tm structure

    // Calculate the months since the expense was last paid
    int monthsSincePaid = (currentDate->tm_year + 1900 - date.tm_year) * 12 + (currentDate->tm_mon - date.tm_mon);

    // If the recurrence period has passed, mark as unpaid
    if (monthsSincePaid >= recurrencePeriod) {
        isPaid = false;

        // Remove "[paid]" from the description if it exists
        size_t pos = description.find("[paid]");
        if (pos != std::string::npos) {
            description.erase(pos, 6); // Remove "[paid]"
        }
    }
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
        if ((expense.date.tm_year + 1900) == year && (expense.date.tm_mon + 1) == month) {
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
        newExpense.date.tm_mon += recurrencePeriodInMonths;
        while (newExpense.date.tm_mon > 11) {
            newExpense.date.tm_mon -= 12;
            newExpense.date.tm_year += 1;
        }
        recurringExpenses.push_back(newExpense);
    }
    return recurringExpenses;
}