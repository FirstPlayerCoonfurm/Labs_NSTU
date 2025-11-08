#ifndef STACK_H
#define STACK_H

#include <cstdio>
#include <cstring>

// Класс исключения без STL
class StackException {
private:
    char message[100];
public:
    StackException(const char* msg) {
        strncpy(message, msg, sizeof(message) - 1);
        message[sizeof(message) - 1] = '\0';
    }
    
    const char* what() const {
        return message;
    }
};

template<typename T, size_t Capacity = 10>
class Stack {
private:
    T* data;           // Динамический массив
    size_t topIndex;   // Индекс верхнего элемента
    size_t capacity;   // Текущая емкость

    // Увеличение емкости
    void resize() {
        size_t newCapacity = capacity * 2;
        T* newData = new T[newCapacity];
        
        // Копируем элементы
        for (size_t i = 0; i < topIndex; ++i) {
            newData[i] = data[i];
        }
        
        delete[] data;
        data = newData;
        capacity = newCapacity;
        
        printf("Стек увеличен. Новая емкость: %zu\n", capacity);
    }

public:
    // Конструктор
    Stack() : capacity(Capacity), topIndex(0) {
        data = new T[capacity];
        printf("Стек создан с емкостью: %zu\n", capacity);
    }

    // Деструктор
    ~Stack() {
        delete[] data;
        printf("Стек уничтожен\n");
    }

    // Копирующий конструктор
    Stack(const Stack& other) : capacity(other.capacity), topIndex(other.topIndex) {
        data = new T[capacity];
        for (size_t i = 0; i < topIndex; ++i) {
            data[i] = other.data[i];
        }
        printf("Стек скопирован\n");
    }

    // Оператор присваивания
    Stack& operator=(const Stack& other) {
        if (this != &other) {
            delete[] data;
            
            capacity = other.capacity;
            topIndex = other.topIndex;
            data = new T[capacity];
            
            for (size_t i = 0; i < topIndex; ++i) {
                data[i] = other.data[i];
            }
        }
        printf("Стек присвоен\n");
        return *this;
    }

    // Добавление элемента в стек (загрузка)
    void push(const T& value) {
        if (topIndex >= capacity) {
            resize();
        }
        
        data[topIndex] = value;
        topIndex++;
        printf("Элемент добавлен в стек. Текущий размер: %zu\n", topIndex);
    }

    // Извлечение элемента из стека
    T pop() {
        if (isEmpty()) {
            throw StackException("Попытка извлечения из пустого стека");
        }
        
        topIndex--;
        T value = data[topIndex];
        printf("Элемент извлечен из стека. Текущий размер: %zu\n", topIndex);
        
        return value;
    }

    // Просмотр верхнего элемента без извлечения
    T peek() const {
        if (isEmpty()) {
            throw StackException("Стек пуст");
        }
        return data[topIndex - 1];
    }

    // Проверка на пустоту
    bool isEmpty() const {
        return topIndex == 0;
    }

    // Получение текущего размера
    size_t size() const {
        return topIndex;
    }

    // Получение емкости
    size_t getCapacity() const {
        return capacity;
    }

    // Вывод содержимого стека
    void display() const {
        if (isEmpty()) {
            printf("Стек пуст\n");
            return;
        }
        
        printf("Содержимое стека (размер: %zu, емкость: %zu):\n", topIndex, capacity);
        for (int i = topIndex - 1; i >= 0; --i) {
            printf("[%d] ", i);
            
            // Специальный вывод для char
            if constexpr (sizeof(T) == sizeof(char)) {
                printf("'%c'\n", data[i]);
            } else {
                printf("%d\n", data[i]);
            }
        }
    }
};

#endif
