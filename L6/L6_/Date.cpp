#include "Date.h"

// Определение статического массива
const int Date::daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// Проверка корректности даты
bool Date::isValidDate(int d, int m, int y) const {
    if (y < 1900 || y > 2100) return false;
    if (m < 0 || m > 11) return false;
    if (d < 1 || d > daysInMonth[m]) return false;
    return true;
}

// Проверка корректности дня недели
bool Date::isValidWeekDay(const char* wd) const {
    if (!wd || strlen(wd) == 0 || strlen(wd) > 20) return false;
    return true;
}

// Конструктор по умолчанию
Date::Date() : day(1), month(1), year(2000) {
    weekDay = new (std::nothrow) char[10];
    if (!weekDay) {
        throw MemoryException("Не удалось выделить память для weekDay в конструкторе по умолчанию");
    }
    strcpy(weekDay, "Monday");
}

// Конструктор с параметрами
Date::Date(int d, int m, int y, const char* wd) : day(d), month(m), year(y) {
    if (!isValidDate(d, m, y)) {
        throw InvalidDateException("Некорректная дата в конструкторе с параметрами");
    }

    if (!isValidWeekDay(wd)) {
        throw InvalidDateException("Некорректный день недели в конструкторе с параметрами");
    }

    weekDay = new (std::nothrow) char[strlen(wd) + 1];
    if (!weekDay) {
        throw MemoryException("Не удалось выделить память для weekDay в конструкторе с параметрами");
    }
    strcpy(weekDay, wd);
}

// Копирующий конструктор
Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {
    weekDay = new (std::nothrow) char[strlen(other.weekDay) + 1];
    if (!weekDay) {
        throw MemoryException("Не удалось выделить память для weekDay в копирующем конструкторе");
    }
    strcpy(weekDay, other.weekDay);
}

// Деструктор
Date::~Date() {
    delete[] weekDay;
}

// Сеттеры с проверкой
void Date::setDay(int d) {
    if (!isValidDate(d, month, year)) {
        throw InvalidDateException("Некорректный день");
    }
    day = d;
}

void Date::setMonth(int m) {
    if (!isValidDate(day, m, year)) {
        throw InvalidDateException("Некорректный месяц");
    }
    month = m;
}

void Date::setYear(int y) {
    if (!isValidDate(day, month, y)) {
        throw InvalidDateException("Некорректный год");
    }
    year = y;
}

void Date::setWeekDay(const char* wd) {
    if (!isValidWeekDay(wd)) {
        throw InvalidDateException("Некорректный день недели");
    }

    delete[] weekDay;
    weekDay = new (std::nothrow) char[strlen(wd) + 1];
    if (!weekDay) {
        throw MemoryException("Не удалось выделить память для weekDay в setWeekDay");
    }
    strcpy(weekDay, wd);
}

// Операция сложения дней
void Date::addDays(int numDays) {
    if (numDays < 0) {
        throw InvalidDateException("Количество дней не может быть отрицательным");
    }

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

        char* newWeekDay = new (std::nothrow) char[strlen(other.weekDay) + 1];
        if (!newWeekDay) {
            throw MemoryException("Не удалось выделить память в операторе присваивания");
        }

        delete[] weekDay;
        weekDay = newWeekDay;
        strcpy(weekDay, other.weekDay);
    }
    return *this;
}

// Остальные методы остаются без изменений, но добавляем проверки...
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

// Виртуальный метод для клонирования
Date* Date::clone() const {
    return new Date(*this);
}

// Запись в текстовый файл
bool Date::writeToTextFile(const char* filename) const {
    FILE* file = fopen(filename, "w");
    if(file == nullptr) {
        throw FileException("Не удалось открыть файл для записи");
    }
    fprintf(file, "%d %d %d %s\n", day, month+1, year, weekDay);
    fclose(file);
    return true;
}

// Запись в бинарный файл
bool Date::writeToBinaryFile(const char* filename) const {
    std::ofstream out(filename, std::ios::binary|std::ios::out);
    if(!out.is_open()) {
        throw FileException("Не удалось открыть файл для бинарной записи");
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
        throw FileException("Не удалось открыть файл для чтения");
    }

    in.read((char*)&day, sizeof(day));
    in.read((char*)&month, sizeof(month));
    in.read((char*)&year, sizeof(year));

    size_t len;
    in.read((char*)&len, sizeof(len));

    char* newWeekDay = new (std::nothrow) char[len + 1];
    if (!newWeekDay) {
        in.close();
        throw MemoryException("Не удалось выделить память при чтении из файла");
    }

    delete[] weekDay;
    weekDay = newWeekDay;
    in.read(weekDay, len);
    weekDay[len] = '\0';

    in.close();
    return true;
}

// Сравнение объектов
bool Date::isEqual(const Date* other) const {
    if (!other) return false;
    return day == other->day && month == other->month && year == other->year &&
    strcmp(weekDay, other->weekDay) == 0;
}
