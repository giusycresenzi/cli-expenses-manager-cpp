#ifndef EXPENSE_H
#define EXPENSE_H

#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <algorithm>

struct Date {
    int day;
    int month;
    int year;

    Date(int d = 1, int m = 1, int y = 1970) : day(d), month(m), year(y) {}

    // Print in dd/mm/yyyy format
    void print() const {
        std::cout << std::setw(2) << std::setfill('0') << day << "/"
                  << std::setw(2) << std::setfill('0') << month << "/"
                  << year;
    }
};

class Expense {
private:
    std::string description;
    std::string category;
    Date date;
    double amount;
    bool isRecurring;
    int recurrencePeriod; // in months
    bool isPaid;

public:
    Expense();
    //overloaded c'tor for one-time expenses
    Expense(bool rec = false, int period = 0) : isRecurring(rec), recurrencePeriod(period) {}

    ~Expense();

    // Setters and Getters
    void setDescription(const std::string& desc) { description = desc; }
    std::string getDescription() const { return description; }

    void setCategory(const std::string& cat) { category = cat; }
    std::string getCategory() const { return category; }

    void setDate(const Date d) { date = d; }
    Date getDate() const { return date; }

    void setAmount(double amt) { amount = amt; }
    double getAmount() const { return amount; }

    void setIsRecurring(bool rec) { isRecurring = rec; }
    bool getIsRecurring() const { return isRecurring; }

    void setRecurrencePeriod(int period) { recurrencePeriod = period; }
    int getRecurrencePeriod() const { return recurrencePeriod; }

    void setIsPaid(bool paid) { isPaid = paid; }
    bool getIsPaid() const { return isPaid; }

    // Print expense
    void print() const;

    // Static methods for filtering and reporting
    static std::vector<Expense> filterByKeyword(const std::vector<Expense>& expenses, const std::string& keyword);
    static std::vector<Expense> filterByMonth(const std::vector<Expense>& expenses, int year, int month);
    static void generateMonthlyReport(const std::vector<Expense>& expenses, int year, int month);
    static std::vector<Expense> generateRecurringExpenses(const Expense& expense, int recurrencePeriodInMonths, int numberOfOccurrences);
};

#endif // EXPENSE_H
