#include "Stack.h"
#include <cstdio>

// Функция для демонстрации работы с int
void demonstrateIntStack() {
    printf("=== Демонстрация стека для int ===\n");
    
    // Создаем стек для int с начальной емкостью 3
    Stack<int, 3> intStack;
    
    // Добавляем элементы (будет происходить увеличение размера)
    printf("\n1. Добавление элементов в стек:\n");
    for (int i = 1; i <= 7; ++i) {
        intStack.push(i * 11);
    }
    intStack.display();
    
    // Просмотр верхнего элемента
    printf("\n2. Верхний элемент: %d\n", intStack.peek());
    
    // Извлечение элементов
    printf("\n3. Извлечение элементов из стека:\n");
    while (!intStack.isEmpty()) {
        int value = intStack.pop();
        printf("Извлечено: %d\n", value);
    }
    
    printf("Состояние после извлечения всех элементов: ");
    intStack.display();
}

// Функция для демонстрации работы с char
void demonstrateCharStack() {
    printf("\n=== Демонстрация стека для char ===\n");
    
    // Создаем стек для char с начальной емкостью 2
    Stack<char, 2> charStack;
    
    // Добавляем элементы
    printf("\n1. Добавление символов в стек:\n");
    char chars[] = {'A', 'B', 'C', 'D', 'E'};
    for (int i = 0; i < 5; ++i) {
        charStack.push(chars[i]);
    }
    charStack.display();
    
    // Просмотр верхнего элемента
    printf("\n2. Верхний элемент: '%c'\n", charStack.peek());
    
    // Извлечение некоторых элементов
    printf("\n3. Извлечение 2 элементов:\n");
    for (int i = 0; i < 2; ++i) {
        char value = charStack.pop();
        printf("Извлечено: '%c'\n", value);
    }
    
    printf("Состояние после извлечения 2 элементов:\n");
    charStack.display();
    
    // Добавление еще элементов
    printf("\n4. Добавление новых символов:\n");
    charStack.push('X');
    charStack.push('Y');
    charStack.push('Z');
    charStack.display();
}

// Функция для демонстрации обработки ошибок
void demonstrateErrorHandling() {
    printf("\n=== Демонстрация обработки ошибок ===\n");
    
    Stack<int, 2> errorStack;
    
    // Попытка извлечения из пустого стека
    printf("1. Попытка извлечения из пустого стека:\n");
    try {
        errorStack.pop();
        printf("Ошибка: исключение не было брошено!\n");
    } catch (const StackException& e) {
        printf("Поймано исключение: %s\n", e.what());
    }
    
    // Попытка просмотра пустого стека
    printf("\n2. Попытка просмотра пустого стека:\n");
    try {
        errorStack.peek();
        printf("Ошибка: исключение не было брошено!\n");
    } catch (const StackException& e) {
        printf("Поймано исключение: %s\n", e.what());
    }
    
    // Корректные операции
    printf("\n3. Корректные операции:\n");
    errorStack.push(100);
    errorStack.push(200);
    errorStack.display();
    
    printf("Верхний элемент: %d\n", errorStack.peek());
    printf("Извлечено: %d\n", errorStack.pop());
    printf("Извлечено: %d\n", errorStack.pop());
    
    // Снова попытка извлечения из пустого стека
    printf("\n4. Снова попытка извлечения из пустого стека:\n");
    try {
        errorStack.pop();
        printf("Ошибка: исключение не было брошено!\n");
    } catch (const StackException& e) {
        printf("Поймано исключение: %s\n", e.what());
    }
}

// Функция для демонстрации копирования
void demonstrateCopying() {
    printf("\n=== Демонстрация копирования ===\n");
    
    Stack<int, 4> original;
    original.push(10);
    original.push(20);
    original.push(30);
    
    printf("Оригинальный стек:\n");
    original.display();
    
    // Копирующий конструктор
    Stack<int, 4> copy1 = original;
    printf("\nСкопированный стек (конструктор копирования):\n");
    copy1.display();
    
    // Оператор присваивания
    Stack<int, 4> copy2;
    copy2 = original;
    printf("\nСкопированный стек (оператор присваивания):\n");
    copy2.display();
    
    // Изменение копии не влияет на оригинал
    copy1.push(40);
    printf("\nПосле изменения копии:\n");
    printf("Оригинал:\n");
    original.display();
    printf("Копия:\n");
    copy1.display();
}

// Функция для демонстрации разных размеров
void demonstrateDifferentSizes() {
    printf("\n=== Демонстрация разных начальных размеров ===\n");
    
    // Стек с маленькой начальной емкостью
    Stack<int, 2> smallStack;
    printf("Маленький стек (емкость 2):\n");
    for (int i = 1; i <= 5; ++i) {
        smallStack.push(i);
    }
    smallStack.display();
    
    // Стек с большой начальной емкостью
    Stack<char, 10> bigStack;
    printf("\nБольшой стек (емкость 10):\n");
    for (char c = 'A'; c <= 'D'; ++c) {
        bigStack.push(c);
    }
    bigStack.display();
}

int main() {
    printf("=== Демонстрация шаблонного стека на динамическом массиве ===\n");
    
    // Демонстрация для int
    demonstrateIntStack();
    
    // Демонстрация для char  
    demonstrateCharStack();
    
    // Демонстрация обработки ошибок
    demonstrateErrorHandling();
    
    // Демонстрация копирования
    demonstrateCopying();
    
    // Демонстрация разных размеров
    demonstrateDifferentSizes();
    
    printf("\n=== Все тесты завершены успешно ===\n");
    return 0;
}
