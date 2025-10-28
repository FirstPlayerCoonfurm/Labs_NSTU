#include "DateUtils.h"
#include <cstdio>

// Функция для вычитания двух дат
int subtractDates(const Date& lhs, const Date& rhs) {
    return ((lhs.getYear() - rhs.getYear())*365 +
            (lhs.getMonth() - rhs.getMonth())*30 +
            (lhs.getDay() - rhs.getDay()));
}

// Демонстрация полиморфизма
void demonstratePolymorphism(Date* dates[], int count) {
    printf("\n=== Демонстрация полиморфизма ===\n");
    for(int i = 0; i < count; i++) {
        printf("Объект %d: ", i+1);
        dates[i]->display();  // Виртуальный вызов!
        printf("String представление: %s\n\n", dates[i]->toString());
    }
}
