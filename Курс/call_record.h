#ifndef CALL_RECORD_H
#define CALL_RECORD_H

// Структура для хранения данных о междугороднем переговоре
struct CallRecord {
    char* city;          // Город
    char* city_code;     // Код города
    double tariff;       // Тариф за минуту
    char* date;          // Дата переговоров
    char* time;          // Время переговоров
    int duration;        // Продолжительность в минутах
    char* phone_number;  // Телефон абонента
    char* payment_date;  // Дата оплаты (пусто если не оплачено)
    
    CallRecord* next;    // Указатель на следующий элемент
    CallRecord* prev;    // Указатель на предыдущий элемент
};

#endif
