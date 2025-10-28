#include "Date.h"
#include <cstdio>
#include <cstring>
#include <fstream>

// Определение статического массива
const int Date::daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Конструктор по умолчанию
Date::Date() : day(1), month(0), year(2000) {
    weekDay = new char[10];
    strcpy(weekDay, "Monday");
}

// Конструктор с параметрами
Date::Date(int d, int m, int y, const char* wd) : day(d), month(m - 1), year(y) {
    weekDay = new char[strlen(wd) + 1];
    strcpy(weekDay, wd);
}

// Копирующий конструктор
Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {
    weekDay = new char[strlen(other.weekDay) + 1];
    strcpy(weekDay, other.weekDay);
}

// Деструктор
Date::~Date() {
    delete[] weekDay;
}

// Проверка на високосный год
bool Date::isLeapYear() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Получение количества дней в текущем месяце
int Date::getDaysInMonth() const {
    if (month == 1) {  // Февраль
        return isLeapYear() ? 29 : 28;
    }
    return daysInMonth[month];
}

// Операция сложения дней (ИСПРАВЛЕННАЯ)
void Date::addDays(int numDays) {
    day += numDays;

    while (day > getDaysInMonth()) {
        day -= getDaysInMonth();
        month++;

        if (month >= 12) {
            month = 0;
            year++;
        }
    }
}

// Оператор присваивания
Date& Date::operator=(const Date& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;

        delete[] weekDay;
        weekDay = new char[strlen(other.weekDay) + 1];
        strcpy(weekDay, other.weekDay);
    }
    return *this;
}

// Префиксный инкремент
Date& Date::operator++() {
    addDays(1);
    return *this;
}

// Постфиксный инкремент
Date Date::operator++(int) {
    Date temp(*this);
    addDays(1);
    return temp;
}

// Приведение к строке
const char* Date::toString() const {
    static char buffer[20];
    snprintf(buffer, sizeof(buffer), "%02d.%02d.%04d", day, month + 1, year);
    return buffer;
}

// Метод для демонстрации
void Date::display() const {
    printf("Дата: %02d.%02d.%04d, День недели: %s\n", day, month + 1, year, weekDay);
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.day << " " << (date.month + 1) << " " << date.year << " " << date.weekDay;
    return os;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, Date& date) {
    int tempDay, tempMonth, tempYear;
    char tempWeekDay[100];

    is >> tempDay >> tempMonth >> tempYear >> tempWeekDay;

    // Проверка корректности ввода
    if (tempMonth < 1 || tempMonth > 12) {
        is.setstate(std::ios::failbit);
        return is;
    }

    date.day = tempDay;
    date.month = tempMonth - 1;
    date.year = tempYear;

    delete[] date.weekDay;
    date.weekDay = new char[strlen(tempWeekDay) + 1];
    strcpy(date.weekDay, tempWeekDay);

    return is;
}
