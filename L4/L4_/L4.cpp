#include "Date.h"
#include "ExtendedDate.h"
#include "DateUtils.h"

int main() {
    printf("=== Демонстрация наследования и полиморфизма ===\n\n");

    // 1. Создание объектов разных типов
    printf("1. Создание объектов:\n");
    Date basicDate(15, 5, 2024, "Wednesday");
    DateWithTime dateTime(15, 5, 2024, "Wednesday", 14, 30, 45);
    DateWithEvent dateEvent(15, 5, 2024, "Wednesday", "День рождения", "Кафе");

    // 2. Демонстрация виртуальных функций через массив указателей на базовый класс
    printf("\n2. Демонстрация полиморфизма:\n");
    Date* dates[3];
    dates[0] = &basicDate;
    dates[1] = &dateTime;
    dates[2] = &dateEvent;

    demonstratePolymorphism(dates, 3);

    // 3. Копирование объектов родственных типов
    printf("3. Копирование объектов:\n");
    DateWithTime copiedDateTime = dateTime;  // Копирующий конструктор
    printf("Скопированный объект DateWithTime: ");
    copiedDateTime.display();

    DateWithEvent copiedDateEvent;
    copiedDateEvent = dateEvent;  // Оператор присваивания
    printf("Присвоенный объект DateWithEvent: ");
    copiedDateEvent.display();

    // 4. Работа с виртуальными функциями файловых операций
    printf("\n4. Файловые операции:\n");
    basicDate.writeToTextFile("basic_date.txt");
    dateTime.writeToTextFile("datetime_date.txt");
    dateEvent.writeToTextFile("event_date.txt");
    printf("Объекты записаны в текстовые файлы\n");

    // 5. Демонстрация специфических методов производных классов
    printf("\n5. Специфические методы производных классов:\n");
    
    // DateWithTime методы
    dateTime.addSeconds(125);  // Добавляем 2 минуты 5 секунд
    printf("После добавления 125 секунд: ");
    dateTime.display();

    // DateWithEvent методы
    dateEvent.setEvent("Собеседование", "Офис компании");
    printf("После изменения события: ");
    dateEvent.display();

    // 6. Демонстрация работы с базовыми методами через производные классы
    printf("\n6. Наследование базовых методов:\n");
    dateTime.addDays(7);  // Метод базового класса
    printf("DateWithTime после добавления 7 дней: ");
    dateTime.display();

    ++dateEvent;  // Оператор инкремента базового класса
    printf("DateWithEvent после инкремента: ");
    dateEvent.display();

    return 0;
}
