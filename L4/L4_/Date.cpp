#include "Date.h"

// Определение статического массива
const int Date::daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Конструктор по умолчанию
Date::Date() : day(1), month(1), year(2000) {
    printf("Конструктор Date по умолчанию\n");
    weekDay = new char[10];
    strcpy(weekDay, "Monday");
}

// Конструктор с параметрами
Date::Date(int d, int m, int y, const char* wd) : day(d), month(m), year(y) {
    printf("Конструктор Date с параметрами\n");
    weekDay = new char[strlen(wd) + 1];
    strcpy(weekDay, wd);
}

// Копирующий конструктор
Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {
    printf("Копирующий конструктор Date\n");
    weekDay = new char[strlen(other.weekDay) + 1];
    strcpy(weekDay, other.weekDay);
}

// Деструктор
Date::~Date() {
    delete[] weekDay;
    printf("Освобождение памяти Date\n");
}

// Операция сложения дней
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

// Оператор присваивания
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

// Запись в текстовый файл
bool Date::writeToTextFile(const char* filename) const {
    FILE* file = fopen(filename, "w");
    if(file == nullptr) {
        perror("Ошибка открытия файла для записи текста");
        return false;
    }
    fprintf(file, "%d %d %d %s\n", day, month+1, year, weekDay);
    fclose(file);
    return true;
}

// Запись в бинарный файл
bool Date::writeToBinaryFile(const char* filename) const {
    std::ofstream out(filename, std::ios::binary|std::ios::out);
    if(!out.is_open()) {
        perror("Ошибка открытия файла для бинарной записи");
        return false;
    }

    out.write((char*)&day, sizeof(day));
    out.write((char*)&month, sizeof(month));
    out.write((char*)&year, sizeof(year));
    size_t len = strlen(weekDay);
    out.write((char*)&len, sizeof(len));
    out.write(weekDay, len);

    out.close();
    return true;
}

// Чтение из бинарного файла
bool Date::readFromBinaryFile(const char* filename) {
    std::ifstream in(filename, std::ios::binary|std::ios::in);
    if(!in.is_open()) {
        perror("Ошибка открытия файла для чтения");
        return false;
    }

    in.read((char*)&day, sizeof(day));
    in.read((char*)&month, sizeof(month));
    in.read((char*)&year, sizeof(year));

    size_t len;
    in.read((char*)&len, sizeof(len));

    delete[] weekDay;
    weekDay = new char[len + 1];
    in.read(weekDay, len);
    weekDay[len] = '\0';

    in.close();
    return true;
}
