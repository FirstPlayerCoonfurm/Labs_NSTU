#include "call_database.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

// Конструктор
CallDatabase::CallDatabase() : head(nullptr), tail(nullptr), size(0) {}

// Деструктор
CallDatabase::~CallDatabase() {
    clear();
}

// Копирование строки с выделением памяти
char* CallDatabase::copyString(const char* source) {
    if (!source) return nullptr;
    char* dest = new char[strlen(source) + 1];
    strcpy(dest, source);
    return dest;
}

// Добавление записи в конец списка
void CallDatabase::addRecord(const char* city, const char* city_code, double tariff, 
                            const char* date, const char* time, int duration, 
                            const char* phone_number, const char* payment_date) {
    CallRecord* newRecord = new CallRecord;
    
    newRecord->city = copyString(city);
    newRecord->city_code = copyString(city_code);
    newRecord->tariff = tariff;
    newRecord->date = copyString(date);
    newRecord->time = copyString(time);
    newRecord->duration = duration;
    newRecord->phone_number = copyString(phone_number);
    newRecord->payment_date = copyString(payment_date);
    
    newRecord->next = nullptr;
    newRecord->prev = tail;

    if (tail) {
        tail->next = newRecord;
    } else {
        head = newRecord;
    }
    tail = newRecord;
    size++;
}

// Удаление записи по индексу
bool CallDatabase::removeRecord(int index) {
    if (index < 0 || index >= size) return false;
    
    CallRecord* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    if (current->prev) {
        current->prev->next = current->next;
    } else {
        head = current->next;
    }

    if (current->next) {
        current->next->prev = current->prev;
    } else {
        tail = current->prev;
    }

    // Освобождение памяти
    delete[] current->city;
    delete[] current->city_code;
    delete[] current->date;
    delete[] current->time;
    delete[] current->phone_number;
    delete[] current->payment_date;
    delete current;
    
    size--;
    return true;
}

// Вставка записи по индексу
bool CallDatabase::insertRecord(int index, const char* city, const char* city_code, double tariff, 
                               const char* date, const char* time, int duration, 
                               const char* phone_number, const char* payment_date) {
    if (index < 0 || index > size) return false;
    
    if (index == size) {
        addRecord(city, city_code, tariff, date, time, duration, phone_number, payment_date);
        return true;
    }

    CallRecord* newRecord = new CallRecord;
    newRecord->city = copyString(city);
    newRecord->city_code = copyString(city_code);
    newRecord->tariff = tariff;
    newRecord->date = copyString(date);
    newRecord->time = copyString(time);
    newRecord->duration = duration;
    newRecord->phone_number = copyString(phone_number);
    newRecord->payment_date = copyString(payment_date);

    CallRecord* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    newRecord->prev = current->prev;
    newRecord->next = current;

    if (current->prev) {
        current->prev->next = newRecord;
    } else {
        head = newRecord;
    }
    current->prev = newRecord;
    
    size++;
    return true;
}

// Получение записи по индексу
CallRecord* CallDatabase::getRecord(int index) {
    if (index < 0 || index >= size) return nullptr;
    
    CallRecord* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

// Обмен данными между двумя узлами
void CallDatabase::swapRecordsData(CallRecord* a, CallRecord* b) {
    swap(a->city, b->city);
    swap(a->city_code, b->city_code);
    swap(a->tariff, b->tariff);
    swap(a->date, b->date);
    swap(a->time, b->time);
    swap(a->duration, b->duration);
    swap(a->phone_number, b->phone_number);
    swap(a->payment_date, b->payment_date);
}

// Сортировка по дате переговоров (пузырьковая сортировка)
void CallDatabase::sortByDate() {
    if (size < 2) return;
    
    bool swapped;
    do {
        swapped = false;
        CallRecord* current = head;
        
        while (current->next != nullptr) {
            if (strcmp(current->date, current->next->date) > 0) {
                swapRecordsData(current, current->next);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

// Поиск неоплаченных переговоров
void CallDatabase::findUnpaidCalls() {
    CallRecord* current = head;
    double totalAmount = 0;
    int unpaidCount = 0;
    
    cout << "\n=== НЕОПЛАЧЕННЫЕ ПЕРЕГОВОРЫ ===\n";
    while (current != nullptr) {
        if (current->payment_date == nullptr || strlen(current->payment_date) == 0) {
            double callCost = current->tariff * current->duration;
            totalAmount += callCost;
            unpaidCount++;
            
            cout << "Город: " << current->city 
                 << ", Код: " << current->city_code
                 << ", Дата: " << current->date
                 << ", Продолжительность: " << current->duration << " мин."
                 << ", Стоимость: " << callCost << " руб.\n";
        }
        current = current->next;
    }
    
    cout << "Всего неоплаченных: " << unpaidCount 
         << ", Общая сумма: " << totalAmount << " руб.\n";
}

// Вывод всех записей
void CallDatabase::displayAll() {
    CallRecord* current = head;
    int index = 0;
    
    cout << "\n=== ВСЕ ЗАПИСИ (" << size << ") ===\n";
    while (current != nullptr) {
        cout << index++ << ". Город: " << current->city 
             << ", Код: " << current->city_code
             << ", Дата: " << current->date
             << ", Время: " << current->time
             << ", Длительность: " << current->duration << " мин."
             << ", Телефон: " << current->phone_number
             << ", Оплата: " << (current->payment_date && strlen(current->payment_date) > 0 ? current->payment_date : "НЕ ОПЛАЧЕНО")
             << "\n";
        current = current->next;
    }
}

// Сохранение в бинарный файл
bool CallDatabase::saveToFile(const char* filename) {
    ofstream file(filename, ios::binary);
    if (!file.is_open()) return false;

    CallRecord* current = head;
    while (current != nullptr) {
        // Сохранение строк с указанием длины
        int len = strlen(current->city);
        file.write(reinterpret_cast<char*>(&len), sizeof(len));
        file.write(current->city, len);

        len = strlen(current->city_code);
        file.write(reinterpret_cast<char*>(&len), sizeof(len));
        file.write(current->city_code, len);

        file.write(reinterpret_cast<char*>(&current->tariff), sizeof(current->tariff));

        len = strlen(current->date);
        file.write(reinterpret_cast<char*>(&len), sizeof(len));
        file.write(current->date, len);

        len = strlen(current->time);
        file.write(reinterpret_cast<char*>(&len), sizeof(len));
        file.write(current->time, len);

        file.write(reinterpret_cast<char*>(&current->duration), sizeof(current->duration));

        len = strlen(current->phone_number);
        file.write(reinterpret_cast<char*>(&len), sizeof(len));
        file.write(current->phone_number, len);

        len = current->payment_date ? strlen(current->payment_date) : 0;
        file.write(reinterpret_cast<char*>(&len), sizeof(len));
        if (len > 0) file.write(current->payment_date, len);

        current = current->next;
    }
    
    file.close();
    return true;
}

// Загрузка из бинарного файла
bool CallDatabase::loadFromFile(const char* filename) {
    ifstream file(filename, ios::binary);
    if (!file.is_open()) return false;

    clear(); // Очищаем текущие данные

    while (file.peek() != EOF) {
        CallRecord record;
        int len;

        // Чтение города
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        record.city = new char[len + 1];
        file.read(record.city, len);
        record.city[len] = '\0';

        // Чтение кода города
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        record.city_code = new char[len + 1];
        file.read(record.city_code, len);
        record.city_code[len] = '\0';

        file.read(reinterpret_cast<char*>(&record.tariff), sizeof(record.tariff));

        // Чтение даты
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        record.date = new char[len + 1];
        file.read(record.date, len);
        record.date[len] = '\0';

        // Чтение времени
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        record.time = new char[len + 1];
        file.read(record.time, len);
        record.time[len] = '\0';

        file.read(reinterpret_cast<char*>(&record.duration), sizeof(record.duration));

        // Чтение телефона
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        record.phone_number = new char[len + 1];
        file.read(record.phone_number, len);
        record.phone_number[len] = '\0';

        // Чтение даты оплаты
        file.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (len > 0) {
            record.payment_date = new char[len + 1];
            file.read(record.payment_date, len);
            record.payment_date[len] = '\0';
        } else {
            record.payment_date = nullptr;
        }

        // Добавляем запись в список
        addRecord(record.city, record.city_code, record.tariff, record.date, 
                 record.time, record.duration, record.phone_number, 
                 record.payment_date ? record.payment_date : "");

        // Освобождаем временную память
        delete[] record.city;
        delete[] record.city_code;
        delete[] record.date;
        delete[] record.time;
        delete[] record.phone_number;
        if (record.payment_date) delete[] record.payment_date;
    }
    
    file.close();
    return true;
}

// Очистка всего списка
void CallDatabase::clear() {
    CallRecord* current = head;
    while (current != nullptr) {
        CallRecord* next = current->next;
        delete[] current->city;
        delete[] current->city_code;
        delete[] current->date;
        delete[] current->time;
        delete[] current->phone_number;
        delete[] current->payment_date;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}

// Получение размера списка
int CallDatabase::getSize() const {
    return size;
}
