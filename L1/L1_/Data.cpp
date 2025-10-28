#include "Date.h"
#include <cstdio>
#include <cstring>

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

// Метод для вывода даты
void Date::display() const {
    printf("Дата: %d.%d.%d, День недели: %s\n", day, month, year, weekDay);
}
