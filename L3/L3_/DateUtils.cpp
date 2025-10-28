#include "DateUtils.h"

// Функция для вычитания двух дат (упрощенная)
int subtractDates(const Date& lhs, const Date& rhs) {
    // Простая реализация - разница в днях без учета месяцев разной длины
    int days1 = lhs.getYear() * 365 + lhs.getMonth() * 30 + lhs.getDay();
    int days2 = rhs.getYear() * 365 + rhs.getMonth() * 30 + rhs.getDay();
    return days1 - days2;
}
