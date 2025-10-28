#ifndef DATE_UTILS_H
#define DATE_UTILS_H

#include "Date.h"
#include "ExtendedDate.h"

// Утилиты для работы с датами
int subtractDates(const Date& lhs, const Date& rhs);

// Функция для демонстрации полиморфизма
void demonstratePolymorphism(Date* dates[], int count);

#endif
