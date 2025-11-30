#include <iostream>
#include <cstring>
#include "call_database.h"
#include "menu.h"

using namespace std;

int main() {
    CallDatabase database;
    int choice;
    
    // Добавим тестовые данные для демонстрации
    database.addRecord("Москва", "495", 2.5, "15.01.2024", "10:30", 15, "79161234567", "20.01.2024");
    database.addRecord("Санкт-Петербург", "812", 2.0, "10.01.2024", "14:15", 8, "79169876543");
    database.addRecord("Новосибирск", "383", 3.0, "20.01.2024", "16:45", 25, "79165554433", "25.01.2024");

    do {
        showMenu();
        cin >> choice;
        
        switch (choice) {
            case 1: {
                char city[100], city_code[10], date[20], time[10], phone[20], payment[100] = "";
                double tariff;
                int duration;
                
                inputCallData(city, city_code, tariff, date, time, duration, phone, payment);
                database.addRecord(city, city_code, tariff, date, time, duration, phone, 
                                 strlen(payment) > 0 ? payment : "");
                cout << "Запись добавлена!\n";
                break;
            }
            case 2: {
                int index;
                cout << "Введите индекс для удаления: ";
                cin >> index;
                if (database.removeRecord(index)) {
                    cout << "Запись удалена!\n";
                } else {
                    cout << "Неверный индекс!\n";
                }
                break;
            }
            case 3: {
                int index;
                char city[100], city_code[10], date[20], time[10], phone[20], payment[100] = "";
                double tariff;
                int duration;
                
                cout << "Введите индекс для вставки: ";
                cin >> index;
                inputCallData(city, city_code, tariff, date, time, duration, phone, payment);
                
                if (database.insertRecord(index, city, city_code, tariff, date, time, duration, phone, 
                                        strlen(payment) > 0 ? payment : "")) {
                    cout << "Запись вставлена!\n";
                } else {
                    cout << "Неверный индекс!\n";
                }
                break;
            }
            case 4:
                database.displayAll();
                break;
            case 5:
                database.sortByDate();
                cout << "Данные отсортированы по дате!\n";
                database.displayAll();
                break;
            case 6:
                database.findUnpaidCalls();
                break;
            case 7:
                if (database.saveToFile("calls.dat")) {
                    cout << "Данные сохранены в файл calls.dat\n";
                } else {
                    cout << "Ошибка сохранения!\n";
                }
                break;
            case 8:
                if (database.loadFromFile("calls.dat")) {
                    cout << "Данные загружены из файла calls.dat\n";
                } else {
                    cout << "Ошибка загрузки или файл не найден!\n";
                }
                break;
            case 9:
                database.clear();
                cout << "База данных очищена!\n";
                break;
            case 0:
                cout << "Выход...\n";
                break;
            default:
                cout << "Неверный выбор!\n";
        }
    } while (choice != 0);

    return 0;
}
