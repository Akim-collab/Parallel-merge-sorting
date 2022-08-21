//
//  header.h
//  SecondTask
//
//  Created by Аким Каленюк on 22.05.2021.
//

#include <iostream>
#include <pthread.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>

// количество элементов в массиве

// количество потоков
#define THREAD_MAX 4

using namespace std;

vector<int> a;
int part = 0;

unsigned long MAX;

// функция слияния для объединения двух частей

void merge(int low, int mid, int high) {
    
    int* left = new int[mid - low + 1];

    int* right = new int[high - mid];

    // n1 это размер левой части, а n2 это размер правой части

    int n1 = mid - low + 1, n2 = high - mid, i, j;

    // сохраняем значения в левой части

    for (i = 0; i < n1; i++)
        left[i] = a[i + low];
    
    // сохраняем значения в правой части

    for (i = 0; i < n2; i++)
        right[i] = a[i + mid + 1];

    int k = low;
    
    i = j = 0;

    // объединяем влево и вправо в порядке возрастания

    while (i < n1 && j < n2) {
            if (left[i] <= right[j])
                a[k++] = left[i++];
            else
                a[k++] = right[j++];
        
    }

    // вставляем оставшиеся значения слева

    while (i < n1) {
        a[k++] = left[i++];
    }

    // вставляем оставшиеся значения справа

    while (j < n2) {
        a[k++] = right[j++];
    }

}

// объединить функцию сортировки

void merge_sort(int low, int high) {

    // вычисление средней точки массива
    int mid = low + (high - low) / 2;

    if (low < high) {
        // вызов первой половины

        merge_sort(low, mid);
        // вызов второй половины
        merge_sort(mid + 1, high);
        // объединяем две половины
        merge(low, mid, high);
    }

}

// функция потока для многопоточности

void* merge_sort(void* arg) {

    // какая часть из 4-х частей
    int thread_part = part++;

    // вычисление низкого и высокого

    int low = thread_part * (MAX / 4);

    int high = (thread_part + 1) * (MAX / 4) - 1;

    // оцениваем середину

    int mid = low + (high - low) / 2;

    if (low < high) {
        merge_sort(low, mid);

        merge_sort(mid + 1, high);

        merge(low, mid, high);

    }
    
    return 0;
}

