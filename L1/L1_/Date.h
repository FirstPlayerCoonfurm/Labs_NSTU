#ifndef DATE_H
#define DATE_H

class Date {
private:
    int day;          
    int month;        
    int year;         
    char* weekDay;    

public:
    Date();                                   // Конструктор по умолчанию
    Date(int d, int m, int y, const char* wd); // Конструктор с параметрами
    Date(const Date& other);                 // Копирующий конструктор
    ~Date();                                 // Деструктор

    void display() const;                    // Метод для вывода даты
};

#endif
