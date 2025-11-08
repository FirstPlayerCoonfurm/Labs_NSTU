#include "Date.h"
#include "ExtendedDate.h"
#include "Stack.h"
#include "Exceptions.h"
#include <cstdio>

// Функция для демонстрации различных исключений
void demonstrateExceptions() {
    printf("\n=== Демонстрация обработки исключений ===\n");

    // 1. Исключение при создании неверной даты
    printf("1. Попытка создания неверной даты:\n");
    try {
        Date invalidDate(32, 13, 2024, "InvalidDay");
        printf("Ошибка: исключение не было брошено!\n");
    } catch (const InvalidDateException& e) {
        printf("Поймано исключение: %s\n", e.what());
    } catch (const Exception& e) {
        printf("Поймано общее исключение: %s\n", e.what());
    }

    // 2. Исключение при работе с пустым стеком
    printf("\n2. Попытка извлечения из пустого стека:\n");
    try {
        Stack emptyStack;
        emptyStack.pop();
        printf("Ошибка: исключение не было брошено!\n");
    } catch (const EmptyStackException& e) {
        printf("Поймано исключение: %s\n", e.what());
    } catch (const Exception& e) {
        printf("Поймано общее исключение: %s\n", e.what());
    }

    // 3. Исключение при неверной позиции
    printf("\n3. Попытка вставки по неверной позиции:\n");
    try {
        Stack stack;
        stack.insert(5, new Date());  // Неверная позиция
        printf("Ошибка: исключение не было брошено!\n");
    } catch (const OutOfRangeException& e) {
        printf("Поймано исключение: %s\n", e.what());
    } catch (const Exception& e) {
        printf("Поймано общее исключение: %s\n", e.what());
    }

    // 4. Исключение при работе с файлом
    printf("\n4. Попытка записи в неверный файл:\n");
    try {
        Date date;
        date.writeToTextFile("/invalid/path/file.txt");
        printf("Ошибка: исключение не было брошено!\n");
    } catch (const FileException& e) {
        printf("Поймано исключение: %s\n", e.what());
    } catch (const Exception& e) {
        printf("Поймано общее исключение: %s\n", e.what());
    }

    // 5. Исключение при установке неверного дня
    printf("\n5. Попытка установки неверного дня:\n");
    try {
        Date date;
        date.setDay(32);  // Неверный день
        printf("Ошибка: исключение не было брошено!\n");
    } catch (const InvalidDateException& e) {
        printf("Поймано исключение: %s\n", e.what());
    } catch (const Exception& e) {
        printf("Поймано общее исключение: %s\n", e.what());
    }
}

// Функция для демонстрации нормальной работы с обработкой исключений
void demonstrateNormalWork() {
    printf("\n=== Демонстрация нормальной работы с обработкой ошибок ===\n");

    Stack stack;

    try {
        // Добавляем корректные данные
        stack.push(new Date(15, 5, 2024, "Wednesday"));
        stack.push(new DateWithTime(16, 5, 2024, "Thursday", 14, 30, 45));
        stack.push(new DateWithEvent(17, 5, 2024, "Friday", "Собрание", "Офис"));

        printf("Стек успешно создан:\n");
        stack.display();

        // Корректные операции
        printf("\nКорректное извлечение:\n");
        Date* popped = stack.pop();
        if (popped) {
            printf("Извлеченный элемент: ");
            popped->display();
            delete popped;
        }

        printf("\nСтек после извлечения:\n");
        stack.display();

        // Корректная вставка
        printf("\nКорректная вставка по позиции 1:\n");
        stack.insert(1, new Date(18, 5, 2024, "Saturday"));
        stack.display();

    } catch (const Exception& e) {
        printf("Произошла ошибка: %s\n", e.what());
    }
}

// Функция для демонстрации полиморфизма исключений
void demonstrateExceptionPolymorphism() {
    printf("\n=== Демонстрация полиморфизма исключений ===\n");

    Exception* exceptions[4];

    exceptions[0] = new MemoryException("Особая ошибка памяти");
    exceptions[1] = new OutOfRangeException("Особая ошибка диапазона");
    exceptions[2] = new InvalidDateException("Особая ошибка даты");
    exceptions[3] = new FileException("Особая ошибка файла");

    for (int i = 0; i < 4; i++) {
        try {
            printf("Бросаем исключение %d: ", i + 1);
            throw exceptions[i];
        } catch (const MemoryException& e) {
            printf("Обработана MemoryException: %s\n", e.what());
        } catch (const OutOfRangeException& e) {
            printf("Обработана OutOfRangeException: %s\n", e.what());
        } catch (const InvalidDateException& e) {
            printf("Обработана InvalidDateException: %s\n", e.what());
        } catch (const FileException& e) {
            printf("Обработана FileException: %s\n", e.what());
        } catch (const Exception& e) {
            printf("Обработана общая Exception: %s\n", e.what());
        }
    }

    // Освобождаем память
    for (int i = 0; i < 4; i++) {
        delete exceptions[i];
    }
}

int main() {
    printf("=== Демонстрация обработки исключительных ситуаций ===\n");

    try {
        // Демонстрация различных типов исключений
        demonstrateExceptions();

        // Демонстрация нормальной работы
        demonstrateNormalWork();

        // Демонстрация полиморфизма исключений
        demonstrateExceptionPolymorphism();

        // Дополнительная демонстрация: обработка в цепочке
        printf("\n=== Демонстрация вложенной обработки ===\n");
        try {
            Stack stack;
            // Создаем ситуацию, которая может вызвать несколько исключений
            stack.push(new Date(31, 2, 2024, "Wednesday"));  // Неверная дата
        } catch (const InvalidDateException& e) {
            printf("Внутреннее исключение: %s\n", e.what());
            // Бросаем новое исключение
            throw FileException("Не удалось добавить элемент в стек из-за неверной даты");
        } catch (const Exception& e) {
            printf("Внешнее исключение: %s\n", e.what());
        }

    } catch (const Exception& e) {
        printf("Исключение перехвачено в main: %s\n", e.what());
    }

    printf("\n=== Программа завершена успешно ===\n");
    return 0;
}
