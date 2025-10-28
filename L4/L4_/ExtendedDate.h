#ifndef EXTENDED_DATE_H
#define EXTENDED_DATE_H

#include "Date.h"

// Первый производный класс: Дата с временем
class DateWithTime : public Date {
private:
    int hour;
    int minute;
    int second;

public:
    // Конструкторы
    DateWithTime();
    DateWithTime(int d, int m, int y, const char* wd, int h, int min, int s);
    DateWithTime(const DateWithTime& other);
    ~DateWithTime();

    // Геттеры для времени
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }

    // Переопределенные виртуальные методы
    virtual void display() const override;
    virtual const char* toString() const override;

    // Собственные методы
    void addSeconds(int seconds);
    void setTime(int h, int m, int s);
};

// Второй производный класс: Дата с событием
class DateWithEvent : public Date {
private:
    char* eventName;
    char* location;

public:
    // Конструкторы
    DateWithEvent();
    DateWithEvent(int d, int m, int y, const char* wd, const char* event, const char* loc);
    DateWithEvent(const DateWithEvent& other);
    ~DateWithEvent();

    // Оператор присваивания
    DateWithEvent& operator=(const DateWithEvent& other);

    // Геттеры
    const char* getEventName() const { return eventName; }
    const char* getLocation() const { return location; }

    // Переопределенные виртуальные методы
    virtual void display() const override;
    virtual const char* toString() const override;
    virtual bool writeToTextFile(const char* filename) const override;

    // Собственные методы
    void setEvent(const char* event, const char* loc);
};

#endif
