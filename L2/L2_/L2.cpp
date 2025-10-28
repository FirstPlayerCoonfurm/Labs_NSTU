#include "Date.h"
#include <cstdio>

int main() {
    // Тестовая дата
    Date myDate(1, 1, 2023, "Monday");
    myDate.display();

    // Сложение (добавление дней)
    myDate.addDays(365);
    myDate.display();

    // Присваивание (создание копии)
    Date anotherDate(myDate);
    anotherDate.display();

    // Префиксный инкремент
    ++anotherDate;
    anotherDate.display();

    // Постфиксный инкремент
    Date prevState = anotherDate++;
    prevState.display();
    anotherDate.display();

    // Приведение к строке
    printf("Строковое представление: %s\n", anotherDate.toString());

    // Разность дат
    Date earlierDate(1, 1, 2022, "Sunday");
    int diff = subtractDates(anotherDate, earlierDate);
    printf("Разница в днях: %d\n", diff);

    return 0;
}
