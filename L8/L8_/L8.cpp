#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <random>
#include "timer.h"

using namespace std;

// Генерация случайных чисел
vector<int> generate_data(size_t n) {
    vector<int> data(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 100000);
    
    for (size_t i = 0; i < n; ++i) {
        data[i] = dist(gen);
    }
    return data;
}

template<typename Container>
void test_vector_operations() {
    const size_t DATA_SIZE = 100000;
    auto data = generate_data(DATA_SIZE);
    Container vec;

    cout << "=== Тестирование vector ===" << endl;

    // Тест добавления
    Timer t;
    for (const auto& item : data) {
        vec.push_back(item);
    }
    cout << "Добавление " << DATA_SIZE << " элементов: " << t.elapsed() << " с" << endl;

    // Тест сортировки
    t.reset();
    sort(vec.begin(), vec.end());
    cout << "Сортировка: " << t.elapsed() << " с" << endl;

    // Тест поиска
    t.reset();
    int found_count = 0;
    for (size_t i = 0; i < 1000; ++i) {
        auto it = find(vec.begin(), vec.end(), data[i]);
        if (it != vec.end()) found_count++;
    }
    cout << "Поиск 1000 элементов (найдено: " << found_count << "): " << t.elapsed() << " с" << endl;

    // Тест удаления
    t.reset();
    while (!vec.empty()) {
        vec.pop_back();
    }
    cout << "Удаление всех элементов: " << t.elapsed() << " с" << endl;
    cout << endl;
}

template<typename Key, typename Value>
void test_map_operations() {
    const size_t DATA_SIZE = 100000;
    auto data = generate_data(DATA_SIZE);
    map<Key, Value> dict;

    cout << "=== Тестирование map ===" << endl;

    // Тест добавления
    Timer t;
    for (const auto& item : data) {
        dict[item] = item;
    }
    cout << "Добавление " << DATA_SIZE << " элементов: " << t.elapsed() << " с" << endl;

    // Тест поиска
    t.reset();
    int found_count = 0;
    for (size_t i = 0; i < 1000; ++i) {
        auto it = dict.find(data[i]);
        if (it != dict.end()) found_count++;
    }
    cout << "Поиск 1000 элементов (найдено: " << found_count << "): " << t.elapsed() << " с" << endl;

    // Тест удаления
    t.reset();
    for (size_t i = 0; i < 1000; ++i) {
        dict.erase(data[i]);
    }
    cout << "Удаление 1000 элементов: " << t.elapsed() << " с" << endl;
    cout << endl;
}

int main() {
    cout << "Лабораторная работа: Сравнение производительности STL контейнеров" << endl;
    cout << "===============================================================" << endl;
    
    // Тестирование vector
    test_vector_operations<vector<int>>();
    
    // Тестирование map
    test_map_operations<int, int>();

    cout << "Тестирование завершено!" << endl;
    return 0;
}
