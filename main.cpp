//
//  main.cpp
//  SecondTask
//
//  Created by Аким Каленюк on 22.05.2021.
//

// Программа CPP для реализации сортировки слиянием с использованием
// многопоточность

#include "header.h"

int main() {
    
    ifstream File;
    File.open("test.txt");
    
    int number;
    while(File >> number)
        a.push_back(number);
    
    cout << "Первоначальный массив: ";
    
    for (auto now : a) {
        cout << now << " ";
    }
    cout << endl;
    
    MAX = a.size();
    
    if (MAX % 2 == 1) {
        MAX = MAX + 1;
        a.push_back(0);
    }
    
    File.close();

    // t1 и t2 для расчета времени для

    // Сортировка слиянием

    clock_t t1, t2;

    t1 = clock();

    pthread_t threads[THREAD_MAX];

    // создаем 4 темы

    for (int i = 0; i < THREAD_MAX; i++)
        pthread_create(&threads[i], NULL, merge_sort, (void*)NULL);

    // объединяем все 4 темы

    for (int i = 0; i < 4; i++)
        pthread_join(threads[i], NULL);

    // объединяем последние 4 части

    merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1);

    merge(MAX / 2, MAX / 2 + ( MAX - 1 - MAX / 2) / 2, MAX - 1);

    merge(0, (MAX - 1)/2, MAX - 1);

    t2 = clock();

    // отображение отсортированного массива

    cout << "Отсортированный массив: ";
    
    int count_zero = 0;

    for (auto now : a) {
        if (count_zero == 0 && now == 0) {
            count_zero = 1;
            continue;
        }
        cout << now << " ";
    }

    cout << endl;

    // время, затраченное на сортировку слиянием в секундах

    cout << "Time taken: " << (t2 - t1) / (double)CLOCKS_PER_SEC << endl;
    
    return 0;
}
