#ifndef STACK_H
#define STACK_H

#include "Date.h"
#include "ExtendedDate.h"
#include "Exceptions.h"

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

    void copyFrom(const Stack& other);

public:
    Stack();
    Stack(const Stack& other);
    ~Stack();

    Stack& operator=(const Stack& other);

    // Основные операции стека
    void push(Date* date);
    Date* pop();
    Date* peek() const;

    // Операции по заданию
    void insert(int position, Date* date);
    void removeAt(int position);
    int find(Date* date) const;
    void display() const;

    // Дополнительные методы
    bool isEmpty() const { return top == nullptr; }
    int getSize() const { return size; }
    void clear();
};

#endif
