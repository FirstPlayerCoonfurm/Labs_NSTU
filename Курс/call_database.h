#ifndef CALL_DATABASE_H
#define CALL_DATABASE_H

#include "call_record.h"

class CallDatabase {
private:
    CallRecord* head;
    CallRecord* tail;
    int size;

    // Вспомогательные методы
    char* copyString(const char* source);
    void swapRecordsData(CallRecord* a, CallRecord* b);

public:
    // Конструктор и деструктор
    CallDatabase();
    ~CallDatabase();

    // Основные операции
    void addRecord(const char* city, const char* city_code, double tariff, 
                  const char* date, const char* time, int duration, 
                  const char* phone_number, const char* payment_date = "");
    
    bool removeRecord(int index);
    bool insertRecord(int index, const char* city, const char* city_code, double tariff, 
                     const char* date, const char* time, int duration, 
                     const char* phone_number, const char* payment_date = "");
    
    CallRecord* getRecord(int index);
    
    // Операции с данными
    void sortByDate();
    void findUnpaidCalls();
    void displayAll();
    
    // Работа с файлами
    bool saveToFile(const char* filename);
    bool loadFromFile(const char* filename);
    
    // Сервисные методы
    void clear();
    int getSize() const;
};

#endif
