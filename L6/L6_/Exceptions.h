#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <cstdio>
#include <cstring>

// Базовый класс для исключений
class Exception {
protected:
    char* message;
public:
    Exception(const char* msg) {
        message = new char[strlen(msg) + 1];
        strcpy(message, msg);
    }
    
    virtual const char* what() const {
        return message;
    }
    
    virtual ~Exception() {
        delete[] message;
    }
};

// Исключение для ошибок памяти
class MemoryException : public Exception {
public:
    MemoryException(const char* msg = "Ошибка выделения памяти") : Exception(msg) {}
};

// Исключение для выхода за границы
class OutOfRangeException : public Exception {
public:
    OutOfRangeException(const char* msg = "Выход за границы диапазона") : Exception(msg) {}
};

// Исключение для неверных дат
class InvalidDateException : public Exception {
public:
    InvalidDateException(const char* msg = "Неверная дата") : Exception(msg) {}
};

// Исключение для ошибок файлов
class FileException : public Exception {
public:
    FileException(const char* msg = "Ошибка работы с файлом") : Exception(msg) {}
};

// Исключение для пустого стека
class EmptyStackException : public Exception {
public:
    EmptyStackException(const char* msg = "Стек пуст") : Exception(msg) {}
};

#endif
