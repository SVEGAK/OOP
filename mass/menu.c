#include <stdio.h>
#include "menu.h"
#include <stdbool.h>
#include <stdlib.h>
#include "dmassive.h"
#include <string.h>
#include "windows.h"
// ================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ
// ================================

void clear_screen() {
    system("cls");
}

void print_menu_header(const char* header) {
    clear_screen();
    printf("\n%s\n\n", header);
}

void print_current_array(DMassive* mass) {
    if (mass == NULL || mass->data == NULL || mass->size == 0) {
        printf("Массив пуст.\n");
    } else {
        printf("Текущий массив [%d элементов]:\n", mass->size);
        print(mass, "", ' ', '\n');
        printf("\n");
    }
}

// ================================
// ФУНКЦИИ ВВОДА ДАННЫХ
// ================================

int get_user_choice(int min, int max) {
    int choice = -1;
    
    while (1) {
        printf(USER_CHOOSE_TEXT);
        
        if (scanf_s("%d", &choice) != 1) {
            printf("Ошибка ввода! Пожалуйста, введите число.\n");
            while (getchar() != '\n');  // Очистка буфера
            continue;
        }
        
        while (getchar() != '\n');  // Очистка буфера
        
        if (choice < min || choice > max) {
            printf("Ошибка! Введите число от %d до %d.\n", min, max);
            continue;
        }
        
        break;
    }
    
    return choice;
}

int get_array_size() {
    int size = 0;
    
    printf("Введите размер массива: ");
    
    while (1) {
        if (scanf_s("%d", &size) != 1) {
            printf("Ошибка ввода! Пожалуйста, введите число: ");
            while (getchar() != '\n');
            continue;
        }
        
        while (getchar() != '\n');
        
        if (size <= 0) {
            printf("Размер должен быть положительным. Введите размер массива: ");
            continue;
        }
        
        break;
    }
    
    return size;
}

double get_double_value(const char* prompt) {
    double value = 0.0;
    printf("%s", prompt);
    
    while (scanf_s("%lf", &value) != 1) {
        printf("Ошибка ввода! Пожалуйста, введите число: ");
        while (getchar() != '\n');
    }
    
    while (getchar() != '\n');
    return value;
}

// ================================
// МЕНЮ РЕЖИМА РАБОТЫ
// ================================

int mod_menu(bool* exit_flag) {
    int user_choice = -1;
    
    while (!*exit_flag) {
        print_menu_header(HEADER_MODE);
        printf(MODE_MENU_TEXT);

        user_choice = get_user_choice(0, MODE_MENU_ITEMS_COUNT);

        switch (user_choice) {
            case 0:
                *exit_flag = true;
                return 0;
            case 1:
                printf("Выбран режим работы с одним элементом.\n");
                system("pause");
                return MOD_ONE;
            case 2:
                printf("Выбран режим работы с несколькими элементами.\n");
                system("pause");
                return MOD_SEVERAL;
            case 3:
                return 0;
        }
    }
    
    return 0;
}

// ================================
// МЕНЮ СОРТИРОВКИ
// ================================

void sort_menu(bool* exit_flag, DMassive* mass) {
    int user_choice = -1;
    
    while (!*exit_flag) {
        print_menu_header(HEADER_SORT);
        printf(SORT_MENU_TEXT);

        user_choice = get_user_choice(0, SORT_MENU_ITEMS_COUNT);

        switch (user_choice) {
            case 0:
                *exit_flag = true;
                return;
            case 1:
                printf("Выбрана пузырьковая сортировка.\n");
                bubble_sort(mass);
                return;
            case 2:
                printf("Выбрана оптимизированная пузырьковая сортировка.\n");
                bubble_sort_pro(mass);
                return;
            case 3:
                printf("Выбрана быстрая сортировка(TBD).\n");
                system("pause");
                return;
            case 4:
                printf("Выбрана Шейкерная сортировка.\n");
                shaker_sort(mass);
                return;
            case 5:
                return;
        }
    }
}

void sort_mode_menu(bool* exit_flag, DMassive* mass) {
    int user_choice = -1;
    
    while (!*exit_flag) {
        print_menu_header(HEADER_SORT_MOD);
        printf(SORT_MODE_MENU_TEXT);

        user_choice = get_user_choice(0, SORT_MODE_MENU_ITEMS_COUNT);

        switch (user_choice) {
            case 0:
                *exit_flag = true;
                return;
            case 1:
                printf("Выбрана сортировка по возрастанию.\n");
                sort_menu(exit_flag, mass);
                break;
            case 2:
                printf("Выбрана сортировка по убыванию.\n");
                sort_menu(exit_flag, mass);
                revers_mass(mass);
                break;
            case 3:
                return;
        }
        
        system("pause");
    }
}

// ================================
// МЕНЮ СОЗДАНИЯ МАССИВА
// ================================

void create_arr_menu(bool* exit_flag, DMassive* mass) {
    int user_choice = -1;
    double min = 0.0, max = 0.0;
    int size = 0;

    while (!*exit_flag) {
        print_menu_header(HEADER_CREATE);
        printf(CREATE_MENU_TEXT);

        user_choice = get_user_choice(0, CREATE_MENU_ITEMS_COUNT);

        switch (user_choice) {
            case 0:
                *exit_flag = true;
                return;
            case 1:
                printf("Выбрано создание базового массива.\n");
                size = get_array_size();
                set_memory(mass, size);
                fill_elementary(mass);
                printf("Массив создан с %d элементами.\n", size);
                system("pause");
                break;
            case 2:
                printf("Выбрано создание случайного массива.\n");
                size = get_array_size();
                printf("Введите границы генерации чисел (минимум максимум): ");
                scanf_s("%lf %lf", &min, &max);
                while (getchar() != '\n');
                set_memory(mass, size);
                fill_randomly(mass, min, max);
                printf("Массив создан с %d случайными элементами в диапазоне [%.2lf, %.2lf].\n", size, min, max);
                system("pause");
                break;
            case 3:
                printf("Выбран ручной ввод элементов.\n");
                size = get_array_size();
                set_memory(mass, size);
                fill_manual_input(mass);
                printf("Массив создан с %d элементами, введенными вручную.\n", size);
                system("pause");
                break;
            case 4:
                return;
        }
    }
}

// ================================
// МЕНЮ ВСТАВКИ ЭЛЕМЕНТОВ
// ================================

void insert_menu(bool* exit_flag, DMassive* mass, int mod) {
    int user_choice = -1;
    double value = 0.0;
    int position = 0;
    Status status;

    if (mass->data == NULL) {
        printf("Массив еще не создан! Пожалуйста, создайте массив сначала.\n");
        system("pause");
        return;
    }

    while (!*exit_flag) {
        print_menu_header(HEADER_INSERT);
        print_current_array(mass);
        printf(INSERT_MENU_TEXT);

        user_choice = get_user_choice(0, INSERT_MENU_ITEMS_COUNT);

        switch (user_choice) {
            case 0:
                *exit_flag = true;
                return;
            case 1:
                printf("Выбрана вставка в начало массива.\n");
                value = get_double_value("Введите значение для вставки: ");
                push_front(mass, value);
                printf("Значение %.2lf вставлено в начало массива.\n", value);
                system("pause");
                break;
            case 2:
                printf("Выбрана вставка в конец массива.\n");
                value = get_double_value("Введите значение для вставки: ");
                push_back(mass, value);
                printf("Значение %.2lf вставлено в конец массива.\n", value);
                system("pause");
                break;
            case 3:
                printf("Выбрана вставка на указанную позицию.\n");
                printf("Введите позицию для вставки (от 0 до %d): ", mass->size);
                scanf_s("%d", &position);
                value = get_double_value("Введите значение для вставки: ");
                
                status = insert(mass, position, value);
                if (status == SUCCESS) {
                    printf("Значение %.2lf вставлено на позицию %d.\n", value, position);
                } else {
                    printf("Не удалось вставить значение.\n");
                }
                
                system("pause");
                break;
            case 4:
                return;
        }
    }
}

// ================================
// МЕНЮ УДАЛЕНИЯ ЭЛЕМЕНТОВ
// ================================

void erase_menu(bool* exit_flag, DMassive* mass, int mod) {
    int user_choice = -1;
    int position = 0;
    Status status;

    if (mass->data == NULL || mass->size == 0) {
        printf("Массив пуст или не был создан!\n");
        system("pause");
        return;
    }

    while (!*exit_flag) {
        print_menu_header(HEADER_ERASE);
        print_current_array(mass);
        printf(ERASE_MENU_TEXT);

        user_choice = get_user_choice(0, ERASE_MENU_ITEMS_COUNT);

        switch (user_choice) {
            case 0:
                *exit_flag = true;
                return;
            case 1:
                printf("Выбрано удаление из начала массива.\n");
                status = pop_front(mass);
                if (status == SUCCESS) {
                    printf("Первый элемент удален.\n");
                } else {
                    printf("Не удалось удалить элемент.\n");
                }
                system("pause");
                break;
            case 2:
                printf("Выбрано удаление из конца массива.\n");
                status = pop_back(mass);
                if (status == SUCCESS) {
                    printf("Последний элемент удален.\n");
                } else {
                    printf("Не удалось удалить элемент.\n");
                }
                system("pause");
                break;
            case 3:
                printf("Выбрано удаление с указанной позиции.\n");
                printf("Введите позицию для удаления (от 0 до %d): ", mass->size - 1);
                scanf_s("%d", &position);
                while (getchar() != '\n');
                
                status = erase(mass, position);
                if (status == SUCCESS) {
                    printf("Элемент на позиции %d удален.\n", position);
                } else {
                    printf("Не удалось удалить элемент.\n");
                }
                
                system("pause");
                break;
            case 4:
                return;
        }
    }
}

// ================================
// МЕНЮ ПОИСКА
// ================================

void search_menu(bool* exit_flag, DMassive* mass) {
    int user_choose = -1;
    double target;
    if (mass->data == NULL || mass->size == 0) {
        printf("Массив пуст или не создан!\n");
        system("pause");
        return;
    }

    while (!*exit_flag) {
        printf("Введите значение которое хотите найти: ");
        scanf_s("%lf", &target);
        while (getchar() != '\n');
        clear_screen();

        print_menu_header(HEADER_SEARCH);
        printf(SEARCH_MENU_TEXT);

        user_choose = get_user_choice(0, SEARCH_MENU_ITEMS_COUNT);

        switch (user_choose) {
        case 0:
            *exit_flag = true;
            return;
        case 1:
            printf("Количество: %d\n", count_occurrences(mass, target));
            system("pause");
            return;
        case 2:
            printf("Первое вхождение: %d\n", binary_search_left(mass, target));
            system("pause");
            return;
        case 3:
            printf("Второе вхождение: %d\n", binary_search_right(mass, target));
            system("pause");
            return;
        case 4:
            printf("Все вхождения найдены поиском.\n");
            int occurrence_count;
            int* indices = find_all_occurrences(mass, target, &occurrence_count);
            if (indices != NULL) {
                printf("Найденные индексы элементов:\n");
                for (int i = 0; i < occurrence_count; i++) {
                    printf("%d ", indices[i]);
                }
                printf("\n");
            }
            else{
                printf("Элемент %.2f не найден\n", target);
            }
            system("pause >null");
            free(indices);
            return;
        case 5:
            return;
        }
    }
}

// ================================
// Меню работы с файлами
// ================================
int choose_file_properties_menu(bool* exit_flag,char*dir,char*file_name, char type){
    char temp_file_name[100];
    printf(CHOOSE_FILE_NAME_TEXT);
    fgets(temp_file_name, sizeof(temp_file_name), stdin);
    temp_file_name[strcspn(temp_file_name, "\n")] = '\0';
    if (strlen(temp_file_name) ==0){ // если пользователь ничего не ввел
        return 0;
    }
    char* dot = strrchr(temp_file_name, '.');
    
    if (dot == NULL) {
        strcat(temp_file_name, ".txt");
    }
    strcpy(file_name, temp_file_name);
    // if (type == 'w'){
    //     strcat(file_name,".txt");
    // }
    int user_choice = -1;
    while (!*exit_flag) {
        clear_screen();
        printf(PATH_MENU_TEXT);
        user_choice = get_user_choice(0, FILE_PROPERTIES_MENU);

        switch (user_choice) {
            case 0:
                *exit_flag = true;
                return 0;
            case 1:
                //Текущая директория
                strcpy(dir,".\\");
                Sleep(500);
                printf("Текущая директория %s для сохранения/записи.",dir);
                // system("pause");
                return 1;
            case 2:{
                clear_screen();
                printf(DIR_FILE_NAME_TEXT);
                char temp_dir[100];
                fgets(temp_dir, sizeof(temp_dir), stdin);
                temp_dir[strcspn(temp_dir, "\n")] = '\0';
                strcpy(dir, temp_dir);
                size_t len = strlen(dir);
                if (len > 0 && dir[len-1] != '\\' && dir[len-1] != '/') {
                    strcat(dir, "\\");
                }
                printf("Директория %s пользователя установлена для сохранения/записи.",dir);
                // system("pause");
                Sleep(500);
                return 1;
            }

            case 5:
                return 0;
        }
    }
    return 0;
}
// ================================
// ГЛАВНОЕ МЕНЮ
// ================================

void main_menu() {
    int user_choice = -1;
    int mode = 0;
    bool exit_flag = false;
    DMassive mass = { 0 };

    while (!exit_flag) {
        print_menu_header(HEADER_MAIN);
        print_current_array(&mass);
        printf(MAIN_MENU_BASE_TEXT);

        user_choice = get_user_choice(0, MAIN_MENU_ITEMS_COUNT);

        switch (user_choice) {
            case 0:
                exit_flag = true;
                printf("Завершение работы программы...\n");
                break;
            case 1:
                create_arr_menu(&exit_flag, &mass);
                break;
            case 2:
                mode = mod_menu(&exit_flag);
                if (!exit_flag && mode != 0) {
                    insert_menu(&exit_flag, &mass, mode);
                }
                break;
            case 3:
                mode = mod_menu(&exit_flag);
                if (!exit_flag && mode != 0) {
                    erase_menu(&exit_flag, &mass, mode);
                }
                break;
            case 4:
                search_menu(&exit_flag, &mass);
                break;
            case 5:
                shake_mass(&mass);
                system("pause");
                break;
            case 6:
                sort_mode_menu(&exit_flag, &mass);
                break;
            case 7:
                clear_memory(&mass);
                printf("Массив очищен.\n");
                system("pause");
                break;
            case 8:{
                char dir[100] = ".";
                char file_name[100];
                mode = choose_file_properties_menu(&exit_flag,dir,file_name,'w');
                if (!exit_flag && mode != 0) {
                    write_mass_in_file(dir,file_name,&mass);
                    Sleep(5);
                }
                
                break;
            }
                
            case 9:{
                char dir[100] = ".";
                char file_name[100];
                mode = choose_file_properties_menu(&exit_flag,dir,file_name,'r');
                if (!exit_flag && mode != 0) {
                    read_mass_from_file(dir,file_name,&mass); 
                    Sleep(5);
                    system("pause");
                }
                break;
            }
               
                
        }
    }

    // Освобождение памяти при выходе
    if (mass.data != NULL) {
        clear_memory(&mass);
    }
}