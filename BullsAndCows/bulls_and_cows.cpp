#include "bulls_and_cows.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
//#define DEBUG
void check_user_answer(int* pc_num, int* user_num, bool* is_not_guessed, int len) {
	int bulls_count = 0;
	int* possible_cows = new int[len];
	int* other_pc_nums = new int[len];
	int cows_count = 0;
	int p = 0;
	for (int i = 0; i < len; i++) {//подсчет быков - эл-в совпадающих по позиции и значению
		if (pc_num[i] == user_num[i]) {
			bulls_count++;
		}
		else {
			possible_cows[p] = user_num[i];
			other_pc_nums[p] = pc_num[i];
			p++;
		}
	}
#ifdef DEBUG
	printDebugModeBanner();
#endif
	//Проверка выиграл ли игрок - совпадает ли количество быков с длиной числа.
	if (len == bulls_count) { 
		printCorrectBanner();
		*is_not_guessed = false;
		delete[] other_pc_nums;
		delete[] possible_cows;
		return;
	}
	int cows_count_possible = len - bulls_count;
	possible_cows = (int*)realloc(possible_cows, cows_count_possible * sizeof(int));
	other_pc_nums = (int*)realloc(other_pc_nums, cows_count_possible * sizeof(int));
#ifdef DEBUG
	std::cout << "\n"  << "Количество возможных коров: " << cows_count_possible << "\nВозможные коровы: ";
	for (int i = 0; i < cows_count_possible; i++) {
		std::cout << possible_cows[i];
	}
	std::cout << "\n\nНеразгаданные числа: ";
	for (int i = 0; i < cows_count_possible; i++) {
		std::cout << other_pc_nums[i];
	}
	std::cout << "\n";
#endif
	for (int i = 0; i < cows_count_possible; i++) {
		for (int j = 0; j < cows_count_possible; j++) {
			if (possible_cows[i] == other_pc_nums[j]) {
				cows_count++;
			}
		}
	}
	std::cout << "\n Bulls count: " << bulls_count << " Cows count: " << cows_count << "\n";
	delete[] other_pc_nums;
	delete[] possible_cows;
	return;
}
void number_to_array(int user_input, int* user_num, int len) {
	for (int i = len - 1; i >= 0; i--) {
		user_num[i] = user_input % 10;
		user_input = user_input / 10;
	}
}
bool check_user_input_length(int user_input, int N) {
	int len = 0;
	while (user_input > 0) {
		user_input /= 10;
		len++;
	}
	if (len == N) {
		return true;
	}
	return false;
}
void shake_mass(int* mass, int len) {
	for (int i = 0; i < len; i++) {
		int new_i = rand() % len;
		int other = mass[new_i];
		mass[new_i] = mass[i];
		mass[i] = other;
	}
}
int bulls_and_cows() {
	srand(static_cast<unsigned int>(time(nullptr)));
	int complication = 1, N;
	bool is_not_guessed = true;

	printMenu();

	std::cin >> complication; 
	system("cls");

	switch (complication) {
		case 1:
			N = 4;
			break;
		case 2:
			N = 7;
			break;
		case 3:
			N = 9;
			break;
		default:
			throw std::invalid_argument("Invalid complication number.");
	}
	int user_input = 0;
	int *pc_num = new int[N];
	int *user_num = new int[N];
	for (int i = 0; i < N; i++) {
		pc_num[i] = i + 1;
	}

	shake_mass(pc_num, N);
	do {
		#ifdef DEBUG
		printPcWishLabel(pc_num, N);
		printUserLabel();
		
		#endif

		#ifndef DEBUG
		printPcHint();
		
		#endif
		std::cin >> user_input;
		if ((((pow(10, N - 1) <= user_input) && (user_input < pow(10, N))) == 0)) {
			continue;
		}
		if (check_user_input_length(user_input, N) == false) {
			throw std::invalid_argument("Incorrect number length.");
		}
		number_to_array(user_input, user_num,N);//число преобразую в массив 
		check_user_answer(pc_num, user_num, &is_not_guessed, N);
	} while (is_not_guessed);
	delete pc_num;
	delete user_num;
	return 0;
}