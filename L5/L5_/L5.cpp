#include "Date.h"
#include "ExtendedDate.h"
#include "Stack.h"
#include <cstdio>

// Функция для демонстрации полиморфизма
void demonstratePolymorphism(Stack& stack) {
    printf("\n=== Демонстрация полиморфизма ===\n");
    
    StackNode* current = reinterpret_cast<StackNode*>(&stack);
    
    // Создаем временный указатель для обхода стека
    // В реальной реализации нужно использовать методы стека
    // Для демонстрации создадим временный стек
    Stack tempStack = stack;
    
    int position = 0;
    while (!tempStack.isEmpty()) {
        Date* date = tempStack.pop();
        printf("Элемент %d (виртуальный вызов display): ", position);
        date->display();  // Полиморфный вызов!
        
        printf("Элемент %d (виртуальный вызов toString): %s\n", 
               position, date->toString());  // Полиморфный вызов!
        
        delete date;
        position++;
    }
}

int main() {
    printf("=== Демонстрация динамического стека на однонаправленном списке ===\n\n");
    
    Stack stack;
    
    // 1. Добавление объектов разных типов в стек
    printf("1. Добавление объектов в стек:\n");
    stack.push(new Date(15, 5, 2024, "Wednesday"));
    stack.push(new DateWithTime(16, 5, 2024, "Thursday", 14, 30, 45));
    stack.push(new DateWithEvent(17, 5, 2024, "Friday", "Экзамен", "Аудитория 101"));
    stack.push(new Date(18, 5, 2024, "Saturday"));
    
    stack.display();
    
    // 2. Демонстрация полиморфизма
    demonstratePolymorphism(stack);
    
    // 3. Вставка по номеру
    printf("\n3. Вставка по номеру 2:\n");
    stack.insert(2, new DateWithTime(19, 5, 2024, "Sunday", 10, 0, 0));
    stack.display();
    
    // 4. Удаление по номеру
    printf("\n4. Удаление по номеру 1:\n");
    stack.removeAt(1);
    stack.display();
    
    // 5. Поиск элемента
    printf("\n5. Поиск элемента:\n");
    Date* searchDate = new Date(15, 5, 2024, "Wednesday");
    int foundPosition = stack.find(searchDate);
    if (foundPosition != -1) {
        printf("Элемент найден на позиции: %d\n", foundPosition);
    } else {
        printf("Элемент не найден\n");
    }
    delete searchDate;
    
    // 6. Работа с верхним элементом
    printf("\n6. Работа с верхним элементом:\n");
    Date* topElement = stack.peek();
    if (topElement) {
        printf("Верхний элемент: ");
        topElement->display();
    }
    
    // 7. Удаление из стека
    printf("\n7. Удаление из стека (pop):\n");
    Date* popped = stack.pop();
    if (popped) {
        printf("Удаленный элемент: ");
        popped->display();
        delete popped;
    }
    stack.display();
    
    // 8. Копирование стека
    printf("\n8. Копирование стека:\n");
    Stack copiedStack = stack;
    printf("Оригинальный стек: ");
    stack.display();
    printf("Скопированный стек: ");
    copiedStack.display();
    
    // 9. Очистка стека
    printf("\n9. Очистка стека:\n");
    stack.clear();
    printf("После очистки: ");
    stack.display();
    
    printf("\n=== Демонстрация завершена ===\n");
    
    return 0;
}
