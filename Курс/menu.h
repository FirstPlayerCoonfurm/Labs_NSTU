#ifndef MENU_H
#define MENU_H

#include "call_database.h"

// Функции меню
void showMenu();
void inputCallData(char* city, char* city_code, double& tariff, char* date, 
                  char* time, int& duration, char* phone_number, char* payment_date);

#endif
