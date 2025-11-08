#include "Stack.h"
#include <cstdio>

// Конструктор по умолчанию
Stack::Stack() : top(nullptr), size(0) {}

// Копирующий конструктор
Stack::Stack(const Stack& other) : top(nullptr), size(0) {
    copyFrom(other);
}

// Деструктор
Stack::~Stack() {
    clear();
}

// Оператор присваивания
Stack& Stack::operator=(const Stack& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

// Вспомогательная функция для копирования
void Stack::copyFrom(const Stack& other) {
    if (other.top == nullptr) return;

    // Создаем временный стек для сохранения порядка
    Stack temp;
    StackNode* current = other.top;

    while (current != nullptr) {
        Date* cloned = current->data->clone();
        if (!cloned) {
            throw MemoryException("Не удалось клонировать объект при копировании стека");
        }
        temp.push(cloned);
        current = current->next;
    }

    // Переносим из временного стека в текущий
    while (!temp.isEmpty()) {
        push(temp.pop());
    }
}

// Добавление элемента в стек
void Stack::push(Date* date) {
    if (!date) {
        throw InvalidDateException("Попытка добавить нулевой указатель в стек");
    }

    StackNode* newNode = new (std::nothrow) StackNode(date);
    if (!newNode) {
        throw MemoryException("Не удалось выделить память для нового узла стека");
    }

    newNode->next = top;
    top = newNode;
    size++;
}

// Удаление и возврат верхнего элемента
Date* Stack::pop() {
    if (isEmpty()) {
        throw EmptyStackException("Попытка извлечения из пустого стека");
    }

    StackNode* temp = top;
    Date* data = temp->data;
    top = top->next;
    temp->data = nullptr;
    delete temp;
    size--;

    return data;
}

// Просмотр верхнего элемента без удаления
Date* Stack::peek() const {
    if (isEmpty()) {
        throw EmptyStackException("Попытка просмотра пустого стека");
    }
    return top->data;
}

// Вставка по номеру
void Stack::insert(int position, Date* date) {
    if (!date) {
        throw InvalidDateException("Попытка вставки нулевого указателя");
    }

    if (position < 0 || position > size) {
        throw OutOfRangeException("Неверная позиция для вставки");
    }

    if (position == 0) {
        push(date);
        return;
    }

    // Находим элемент перед позицией вставки
    StackNode* current = top;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }

    StackNode* newNode = new (std::nothrow) StackNode(date);
    if (!newNode) {
        throw MemoryException("Не удалось выделить память для нового узла при вставке");
    }

    newNode->next = current->next;
    current->next = newNode;
    size++;
}

// Удаление по номеру
void Stack::removeAt(int position) {
    if (position < 0 || position >= size) {
        throw OutOfRangeException("Неверная позиция для удаления");
    }

    if (position == 0) {
        pop();
        return;
    }

    // Находим элемент перед удаляемым
    StackNode* current = top;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }

    StackNode* toDelete = current->next;
    current->next = toDelete->next;
    toDelete->data = nullptr;
    delete toDelete;
    size--;
}

// Поиск элемента
int Stack::find(Date* date) const {
    if (!date) {
        return -1;
    }

    StackNode* current = top;
    int position = 0;

    while (current != nullptr) {
        if (current->data->isEqual(date)) {
            return position;
        }
        current = current->next;
        position++;
    }

    return -1;
}

// Просмотр всей структуры
void Stack::display() const {
    if (isEmpty()) {
        printf("Стек пуст\n");
        return;
    }

    printf("Содержимое стека (размер: %d):\n", size);
    StackNode* current = top;
    int position = 0;

    while (current != nullptr) {
        printf("[%d] ", position);
        current->data->display();
        current = current->next;
        position++;
    }
}

// Очистка стека
void Stack::clear() {
    while (!isEmpty()) {
        Date* data = pop();
        delete data;
    }
}
