#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#define STEP_OF_CAPACITY 15

struct DMassive
{
	double* data;
	int size;
	int capacity;
	int front;
	int back;
};
enum Status { SUCCESS, WARNING, ERROR };


typedef struct DMassive DMassive;
typedef enum Status Status;


// Вспомогательные функции
int calculate_capacity(int size);
int get_pos(DMassive* mass, int pos);
int get_next_pos(DMassive* mass, int pos);
int get_prev_pos(DMassive* mass, int pos);
int is_empty(DMassive* mass);
int is_full(DMassive* mass);
void right_shift(DMassive* mass, int pos);
void left_shift(DMassive* mass, int pos);
bool sorted_left_to_right(DMassive* mass);
bool sorted_right_to_left(DMassive* mass);
void swap(double* first, double* second);

// Основные операции с памятью
void set_memory(DMassive* mass, int size);
void clear_memory(DMassive* mass);
void resize(DMassive* mass, int new_size);

// Заполнение массива
void fill_elementary(DMassive* mass);
void fill_randomly(DMassive* mass, double min_val, double max_val);
void fill_manual_input(DMassive* mass);

// Реверс массива
void revers_mass(DMassive* mass);

// Операции вставки
void push_front(DMassive* mass, double value);
void push_back(DMassive* mass, double value);
Status insert(DMassive* mass, int pos, double value);

// Операции удаления
Status pop_front(DMassive* mass);
Status pop_back(DMassive* mass);
Status erase(DMassive* mass, int pos);

// Вывод массива
void print(DMassive* mass, const char* text, char sep, char end);

// Алгоритмы сортировки
void bubble_sort(DMassive* mass);
void bubble_sort_pro(DMassive* mass);
void shaker_sort(DMassive*mass);
// Функция перемешивания
void shake_mass(DMassive* mass);
// Запись и чтение из файла
void write_mass_in_file(char* dir, char* file_name, DMassive* mass);
void read_mass_from_file(char* dir, char* file_name, DMassive* mass);
// функции поиска
void quick_sort(DMassive* mass);
int binary_search_left(DMassive* mass, double target);
int binary_search_right(DMassive* mass, double target);
int count_occurrences(DMassive* mass, double target);
int* find_all_occurrences(DMassive* mass, double target, int* count);
double get_element(DMassive* mass, int logical_index);
int search_cmp(double a, double b);

/**
* Функция вывода массива на экран
*
* @param mass указатель на массив типа структуры DMassive
* @param text текст перед выводом массива
* @param sep разделитель элементов
* @param end символ в конце вывода
* @param dir текущая директория для сохранения файлов
*/

