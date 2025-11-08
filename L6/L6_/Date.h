#ifndef DATE_H
#define DATE_H

#include <cstdio>
#include <cstring>
#include <fstream>
#include "Exceptions.h"

class Date {
protected:
    int day;
    int month;
    int year;
    char* weekDay;

    // Вспомогательные методы для проверки
    bool isValidDate(int d, int m, int y) const;
    bool isValidWeekDay(const char* wd) const;

public:
    // Статический массив
    static const int daysInMonth[];

    // Конструкторы и деструктор
    Date();
    Date(int d, int m, int y, const char* wd);
    Date(const Date& other);
    virtual ~Date();

    // Геттеры
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }
    const char* getWeekDay() const { return weekDay; }

    // Сеттеры с проверкой
    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);
    void setWeekDay(const char* wd);

    // Основные операции с датами
    void addDays(int numDays);

    // Операторы
    Date& operator=(const Date& other);
    Date& operator++();
    Date operator++(int dummy);

    // Виртуальные методы
    virtual const char* toString() const;
    virtual void display() const;
    virtual Date* clone() const;

    // Файловые операции
    virtual bool writeToTextFile(const char* filename) const;
    virtual bool writeToBinaryFile(const char* filename) const;
    virtual bool readFromBinaryFile(const char* filename);

    // Виртуальный метод для сравнения
    virtual bool isEqual(const Date* other) const;
};

#endif
