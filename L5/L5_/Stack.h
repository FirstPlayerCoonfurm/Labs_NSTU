#ifndef STACK_H
#define STACK_H

#include "Date.h"
#include "ExtendedDate.h"

class StackNode {
public:
    Date* data;
    StackNode* next;
    
    StackNode(Date* date) : data(date), next(nullptr) {}
    ~StackNode() { delete data; }
};

class Stack {
private:
    StackNode* top;
    int size;

    // Вспомогательная функция для копирования
    void copyFrom(const Stack& other);
    
public:
    // Конструкторы и деструктор
    Stack();
    Stack(const Stack& other);
    ~Stack();
    
    // Оператор присваивания
    Stack& operator=(const Stack& other);
    
    // Основные операции стека
    void push(Date* date);
    Date* pop();
    Date* peek() const;
    
    // Операции по заданию
    void insert(int position, Date* date);  // Вставка по номеру
    void removeAt(int position);            // Удаление по номеру
    int find(Date* date) const;             // Поиск элемента
    void display() const;                   // Просмотр всей структуры
    
    // Дополнительные методы
    bool isEmpty() const { return top == nullptr; }
    int getSize() const { return size; }
    void clear();
};

#endif
