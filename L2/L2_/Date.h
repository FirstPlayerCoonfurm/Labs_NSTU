#ifndef DATE_H
#define DATE_H

class Date {
private:
    int day;          
    int month;        
    int year;         
    char* weekDay;    

public:
    // Геттеры для доступа к частным данным
    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    // Статический массив с количеством дней в каждом месяце
    static const int daysInMonth[];

    // Конструкторы и деструктор
    Date();
    Date(int d, int m, int y, const char* wd);
    Date(const Date& other);
    ~Date();

    // Методы класса
    void addDays(int numDays);
    Date& operator=(const Date& other);
    Date& operator++();           // Префиксный инкремент
    Date operator++(int dummy);   // Постфиксный инкремент
    const char* toString() const;
    void display() const;
};

// Функция для вычитания двух дат
int subtractDates(const Date& lhs, const Date& rhs);

#endif
