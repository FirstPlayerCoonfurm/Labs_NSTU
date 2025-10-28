#ifndef DATE_H
#define DATE_H

#include <cstdio>
#include <cstring>
#include <fstream>

class Date {
protected:  // Изменено с private на protected для доступа в производных классах
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
    virtual ~Date();  // Виртуальный деструктор для корректного удаления производных классов

    // Основные операции с датами
    void addDays(int numDays);
    
    // Операторы
    Date& operator=(const Date& other);
    Date& operator++();
    Date operator++(int dummy);

    // Виртуальные методы (для позднего связывания)
    virtual const char* toString() const;
    virtual void display() const;  // Виртуальный метод

    // Файловые операции
    virtual bool writeToTextFile(const char* filename) const;
    virtual bool writeToBinaryFile(const char* filename) const;
    virtual bool readFromBinaryFile(const char* filename);
};

#endif
