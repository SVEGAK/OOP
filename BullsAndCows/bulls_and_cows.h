#pragma once
#include <stdbool.h>
#include <iostream>
//#define DEBUG
//Перемешивание массива
void shake_mass(int* mass, int len); 
//Перевод ввода пользователя в массив с которым удобно работать
void number_to_array(int user_input, int* user_num, int len);
//Проверка, что пользователь ввел число верной длины
bool check_user_input_length(int user_input, int N);
//Функция с основной логикой игры - проверкой ответа юзера
void check_user_answer(int* pc_num, int* user_num, bool* is_not_guessed, int len);


void printDebugModeBanner() {
    std::cout << "╔════════════════╗\n";
    std::cout << "║   DEBUG MODE   ║\n";
    std::cout << "╚════════════════╝\n";
}
void printCorrectBanner() {
    std::cout << "╔════════════════╗\n";
    std::cout << "║    CORRECT!    ║\n";
    std::cout << "╚════════════════╝\n";
}
void printMenu() {
    std::cout << "── Menu ──────────────────────────────\n";
    std::cout << "   1 - Easy   - 4 numbers             \n";
    std::cout << "   2 - Medium - 7 numbers             \n";
    std::cout << "   3 - Hard   - 9 numbers             \n";
    std::cout << "                                      \n";
    std::cout << "   Choose complication: ";
}

void printPcWishLabel(int* num, int N) {
    std::cout << "──[ PC ]────────\n";
    std::cout << " I wish a number:" ;
    for (size_t i = 0; i < N; i++) {
        std::cout << num[i];
    }
    std::cout << "\n\n";
}
void printUserLabel() {
    std::cout << "──[ YOU ]─────── \n";
    std::cout << "  User: ";
}
void printPcHint() {
    std::cout << "╭─[ PC ]────────────────────────────╮\n";
    std::cout << "│ I wish a number. Try to guess it. │\n";
    std::cout << "╰───────────────────────────────────╯\n";
    std::cout << "-─[ YOU ]───────-\n";
    std::cout << "  User: ";
}