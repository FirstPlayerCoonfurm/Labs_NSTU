#include "menu.h"
#include <iostream>

using namespace std;

// Функция для демонстрации меню
void showMenu() {
    cout << "\n=== БАЗА ДАННЫХ МЕЖДУГОРОДНИХ ПЕРЕГОВОРОВ ===\n";
    cout << "1. Добавить запись\n";
    cout << "2. Удалить запись\n";
    cout << "3. Вставить запись\n";
    cout << "4. Показать все записи\n";
    cout << "5. Сортировать по дате\n";
    cout << "6. Найти неоплаченные переговоры\n";
    cout << "7. Сохранить в файл\n";
    cout << "8. Загрузить из файла\n";
    cout << "9. Очистить базу данных\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

// Функция для ввода данных записи
void inputCallData(char* city, char* city_code, double& tariff, char* date, 
                  char* time, int& duration, char* phone_number, char* payment_date) {
    cout << "Город: ";
    cin >> city;
    cout << "Код города: ";
    cin >> city_code;
    cout << "Тариф за минуту: ";
    cin >> tariff;
    cout << "Дата (ДД.ММ.ГГГГ): ";
    cin >> date;
    cout << "Время (ЧЧ:ММ): ";
    cin >> time;
    cout << "Продолжительность (мин): ";
    cin >> duration;
    cout << "Телефон: ";
    cin >> phone_number;
    cout << "Дата оплаты (Enter если не оплачено): ";
    cin.ignore();
    cin.getline(payment_date, 100);
}
