#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date {
private:
    int day;
    int month;  // 0-11
    int year;
    char* weekDay;

public:
    // Геттеры
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    const char* getWeekDay() const { return weekDay; }

    // Статический массив
    static const int daysInMonth[];

    // Конструкторы и деструктор
    Date();
    Date(int d, int m, int y, const char* wd);
    Date(const Date& other);
    ~Date();

    // Основные операции с датами
    void addDays(int numDays);

    // Операторы
    Date& operator=(const Date& other);
    Date& operator++();
    Date operator++(int);

    // Методы представления
    const char* toString() const;
    void display() const;

    // Вспомогательные методы
    bool isLeapYear() const;
    int getDaysInMonth() const;

    // Операторы ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);

    // Дружественные функции для бинарного ввода/вывода
    friend void writeDateToBinaryFile(const Date& date, const char* filename);
    friend Date readDateFromBinaryFile(const char* filename);
};

#endif
