#include "Date.h"
#include "DateUtils.h"
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>

// Функция для записи Date в бинарный файл (ИСПРАВЛЕННАЯ)
void writeDateToBinaryFile(const Date& date, const char* filename) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        // Прямой доступ к приватным полям через дружественную функцию
        file.write(reinterpret_cast<const char*>(&date.day), sizeof(int));
        file.write(reinterpret_cast<const char*>(&date.month), sizeof(int));
        file.write(reinterpret_cast<const char*>(&date.year), sizeof(int));

        // Записываем строку БЕЗ нулевого терминатора
        int length = strlen(date.weekDay);
        file.write(reinterpret_cast<const char*>(&length), sizeof(int));
        file.write(date.weekDay, length);  // Только символы, без '\0'

        file.close();
        printf("Объект записан в бинарный файл '%s'\n", filename);

        // Отладочная информация
        printf("Записано: day=%d, month=%d, year=%d, weekDay='%s' (length=%d)\n",
               date.day, date.month, date.year, date.weekDay, length);
    } else {
        printf("Ошибка записи в файл '%s'\n", filename);
    }
}

// Функция для чтения Date из бинарного файла (ИСПРАВЛЕННАЯ)
Date readDateFromBinaryFile(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    Date date;

    if (file.is_open()) {
        // Прямой доступ к приватным полям через дружественную функцию
        file.read(reinterpret_cast<char*>(&date.day), sizeof(int));
        file.read(reinterpret_cast<char*>(&date.month), sizeof(int));
        file.read(reinterpret_cast<char*>(&date.year), sizeof(int));

        int length;
        file.read(reinterpret_cast<char*>(&length), sizeof(int));

        // Проверяем корректность длины
        if (length > 0 && length < 100) {
            delete[] date.weekDay;
            date.weekDay = new char[length + 1];
            file.read(date.weekDay, length);
            date.weekDay[length] = '\0';  // Добавляем терминатор
        } else {
            // Значение по умолчанию при ошибке
            delete[] date.weekDay;
            date.weekDay = new char[10];
            strcpy(date.weekDay, "Unknown");
        }

        file.close();
        printf("Объект загружен из бинарного файла '%s'\n", filename);
        printf("Прочитано: day=%d, month=%d, year=%d, weekDay='%s'\n",
               date.day, date.month, date.year, date.weekDay);
    } else {
        printf("Ошибка чтения файла '%s'\n", filename);
    }

    return date;
}

// Функция для вывода hex-дампа файла
void printHexDump(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        printf("Hex-дамп файла '%s':\n", filename);
        char buffer[256];
        std::streamsize totalBytes = 0;

        while (file.read(buffer, 16)) {
            std::streamsize bytesRead = file.gcount();

            // Вывод адреса
            printf("%08lx: ", totalBytes);

            // Hex значения
            for (int i = 0; i < bytesRead; i++) {
                printf("%02x ", (unsigned char)buffer[i]);
                if (i == 7) printf(" ");
            }

            // Заполнение пробелами
            for (int i = bytesRead; i < 16; i++) {
                printf("   ");
                if (i == 7) printf(" ");
            }

            printf(" ");

            // ASCII значения
            for (int i = 0; i < bytesRead; i++) {
                if (buffer[i] >= 32 && buffer[i] <= 126) {
                    printf("%c", buffer[i]);
                } else {
                    printf(".");
                }
            }

            printf("\n");
            totalBytes += bytesRead;
        }

        // Обработка последней неполной строки
        std::streamsize bytesRead = file.gcount();
        if (bytesRead > 0) {
            printf("%08lx: ", totalBytes);
            for (int i = 0; i < bytesRead; i++) {
                printf("%02x ", (unsigned char)buffer[i]);
                if (i == 7) printf(" ");
            }
            for (int i = bytesRead; i < 16; i++) {
                printf("   ");
                if (i == 7) printf(" ");
            }
            printf(" ");
            for (int i = 0; i < bytesRead; i++) {
                if (buffer[i] >= 32 && buffer[i] <= 126) {
                    printf("%c", buffer[i]);
                } else {
                    printf(".");
                }
            }
            printf("\n");
            totalBytes += bytesRead;
        }

        file.close();
        printf("Всего байт: %ld\n", totalBytes);
    } else {
        printf("Не удалось открыть файл '%s' для чтения\n", filename);
    }
}

int main() {
    // Тестовая дата
    Date myDate(1, 1, 2023, "Monday");
    printf("Исходная дата: ");
    myDate.display();

    // Запись в текстовый файл
    std::ofstream outFile("date.txt");
    if (outFile.is_open()) {
        outFile << myDate;
        outFile.close();
        printf("Объект записан в текстовый файл 'date.txt'\n");
    }

    // Чтение из текстового файла
    Date loadedDate;
    std::ifstream inFile("date.txt");
    if (inFile.is_open()) {
        inFile >> loadedDate;
        inFile.close();
        printf("Объект загружен из текстового файла 'date.txt'\n");
        loadedDate.display();
    }

    // Работа с бинарными файлами
    printf("\n--- Работа с бинарными файлами ---\n");
    writeDateToBinaryFile(myDate, "date.bin");

    // Выводим hex-дамп
    printHexDump("date.bin");

    // Чтение из бинарного файла
    Date binaryDate = readDateFromBinaryFile("date.bin");
    printf("Дата из бинарного файла: ");
    binaryDate.display();

    // Демонстрация работы утилит
    Date earlierDate(1, 1, 2022, "Sunday");
    int diff = subtractDates(myDate, earlierDate);
    printf("Разница в днях: %d\n", diff);

    return 0;
}
