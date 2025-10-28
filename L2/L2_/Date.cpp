#include "Date.h"
#include <cstdio>
#include <cstring>

// Определение статического массива
const int Date::daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Конструктор по умолчанию
Date::Date() : day(1), month(1), year(2000) {
    printf("Конструктор по умолчанию\n");
    weekDay = new char[10];
    strcpy(weekDay, "Monday");
}

// Конструктор с параметрами
Date::Date(int d, int m, int y, const char* wd) : day(d), month(m), year(y) {
    printf("Конструктор с параметрами\n");
    weekDay = new char[strlen(wd) + 1];
    strcpy(weekDay, wd);
}

// Копирующий конструктор
Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {
    printf("Копирующий конструктор\n");
    weekDay = new char[strlen(other.weekDay) + 1];
    strcpy(weekDay, other.weekDay);
}

// Деструктор
Date::~Date() {
    delete[] weekDay;
    printf("Освобождение памяти\n");
}

// Операция сложения: добавляет указанное количество дней к текущей дате
void Date::addDays(int numDays) {
    while(numDays > 0) {
        if(day + numDays <= daysInMonth[month]) {
            day += numDays;
            break;
        } else {
            int remainingDays = daysInMonth[month] - day + 1;
            numDays -= remainingDays;
            day = 1;
            
            if(month == 11) {
                month = 0;
                ++year;
            } else {
                ++month;
            }
        }
    }
}

// Присваивание (копирование объекта)
Date& Date::operator=(const Date& other) {
    if(this != &other) {
        this->day = other.day;
        this->month = other.month;
        this->year = other.year;
        
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
Date Date::operator++(int dummy) {
    Date temp(*this);
    addDays(1);
    return temp;
}

// Приведение к строке
const char* Date::toString() const {
    static char buffer[11];
    snprintf(buffer, sizeof(buffer), "%02d-%02d-%04d", day, month+1, year);
    return buffer;
}

// Метод для демонстрации
void Date::display() const {
    printf("Дата: %d.%d.%d, День недели: %s\n", day, month+1, year, weekDay);
}

// Функция для вычитания двух дат
int subtractDates(const Date& lhs, const Date& rhs) {
    return ((lhs.getYear() - rhs.getYear())*365 +
            (lhs.getMonth() - rhs.getMonth())*30 +
            (lhs.getDay() - rhs.getDay()));
}
