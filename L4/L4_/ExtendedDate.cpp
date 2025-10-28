#include "ExtendedDate.h"
#include <cstdio>
#include <cstring>

// ========== DateWithTime реализации ==========

// Конструктор по умолчанию
DateWithTime::DateWithTime() : Date(), hour(0), minute(0), second(0) {
    printf("Конструктор DateWithTime по умолчанию\n");
}

// Конструктор с параметрами
DateWithTime::DateWithTime(int d, int m, int y, const char* wd, int h, int min, int s) 
    : Date(d, m, y, wd), hour(h), minute(min), second(s) {
    printf("Конструктор DateWithTime с параметрами\n");
}

// Копирующий конструктор
DateWithTime::DateWithTime(const DateWithTime& other) 
    : Date(other), hour(other.hour), minute(other.minute), second(other.second) {
    printf("Копирующий конструктор DateWithTime\n");
}

// Деструктор
DateWithTime::~DateWithTime() {
    printf("Освобождение памяти DateWithTime\n");
}

// Переопределенный метод display
void DateWithTime::display() const {
    printf("Дата и время: %d.%d.%d %02d:%02d:%02d, День недели: %s\n", 
           day, month+1, year, hour, minute, second, weekDay);
}

// Переопределенный метод toString
const char* DateWithTime::toString() const {
    static char buffer[20];
    snprintf(buffer, sizeof(buffer), "%02d-%02d-%04d %02d:%02d:%02d", 
             day, month+1, year, hour, minute, second);
    return buffer;
}

// Добавление секунд
void DateWithTime::addSeconds(int seconds) {
    second += seconds;
    while(second >= 60) {
        second -= 60;
        minute++;
        if(minute >= 60) {
            minute = 0;
            hour++;
            if(hour >= 24) {
                hour = 0;
                addDays(1);
            }
        }
    }
}

// Установка времени
void DateWithTime::setTime(int h, int m, int s) {
    hour = h;
    minute = m;
    second = s;
}

// ========== DateWithEvent реализации ==========

// Конструктор по умолчанию
DateWithEvent::DateWithEvent() : Date() {
    printf("Конструктор DateWithEvent по умолчанию\n");
    eventName = new char[10];
    strcpy(eventName, "Meeting");
    location = new char[10];
    strcpy(location, "Office");
}

// Конструктор с параметрами
DateWithEvent::DateWithEvent(int d, int m, int y, const char* wd, const char* event, const char* loc) 
    : Date(d, m, y, wd) {
    printf("Конструктор DateWithEvent с параметрами\n");
    eventName = new char[strlen(event) + 1];
    strcpy(eventName, event);
    location = new char[strlen(loc) + 1];
    strcpy(location, loc);
}

// Копирующий конструктор
DateWithEvent::DateWithEvent(const DateWithEvent& other) 
    : Date(other) {
    printf("Копирующий конструктор DateWithEvent\n");
    eventName = new char[strlen(other.eventName) + 1];
    strcpy(eventName, other.eventName);
    location = new char[strlen(other.location) + 1];
    strcpy(location, other.location);
}

// Деструктор
DateWithEvent::~DateWithEvent() {
    delete[] eventName;
    delete[] location;
    printf("Освобождение памяти DateWithEvent\n");
}

// Оператор присваивания
DateWithEvent& DateWithEvent::operator=(const DateWithEvent& other) {
    if(this != &other) {
        // Вызываем оператор присваивания базового класса
        Date::operator=(other);
        
        delete[] eventName;
        delete[] location;
        
        eventName = new char[strlen(other.eventName) + 1];
        strcpy(eventName, other.eventName);
        location = new char[strlen(other.location) + 1];
        strcpy(location, other.location);
    }
    return *this;
}

// Переопределенный метод display
void DateWithEvent::display() const {
    printf("Дата события: %d.%d.%d, День недели: %s\n", day, month+1, year, weekDay);
    printf("Событие: %s, Место: %s\n", eventName, location);
}

// Переопределенный метод toString
const char* DateWithEvent::toString() const {
    static char buffer[100];
    snprintf(buffer, sizeof(buffer), "%02d-%02d-%04d | Событие: %s | Место: %s", 
             day, month+1, year, eventName, location);
    return buffer;
}

// Переопределенный метод записи в текстовый файл
bool DateWithEvent::writeToTextFile(const char* filename) const {
    FILE* file = fopen(filename, "w");
    if(file == nullptr) {
        perror("Ошибка открытия файла для записи текста");
        return false;
    }
    fprintf(file, "%d %d %d %s %s %s\n", day, month+1, year, weekDay, eventName, location);
    fclose(file);
    return true;
}

// Установка события
void DateWithEvent::setEvent(const char* event, const char* loc) {
    delete[] eventName;
    delete[] location;
    
    eventName = new char[strlen(event) + 1];
    strcpy(eventName, event);
    location = new char[strlen(loc) + 1];
    strcpy(location, loc);
}
