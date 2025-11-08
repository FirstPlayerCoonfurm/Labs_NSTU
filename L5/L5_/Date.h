#ifndef DATE_H
#define DATE_H

#include <cstdio>
#include <cstring>
#include <fstream>

class Date {
protected:
    int day;
    int month;
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
    virtual ~Date();

    // Основные операции с датами
    void addDays(int numDays);
    
    // Операторы
    Date& operator=(const Date& other);
    Date& operator++();
    Date operator++(int dummy);

    // Виртуальные методы
    virtual const char* toString() const;
    virtual void display() const;
    virtual Date* clone() const;  // Виртуальный метод для клонирования

    // Файловые операции
    virtual bool writeToTextFile(const char* filename) const;
    virtual bool writeToBinaryFile(const char* filename) const;
    virtual bool readFromBinaryFile(const char* filename);

    // Виртуальный метод для сравнения (для поиска)
    virtual bool isEqual(const Date* other) const;
};

#endif
