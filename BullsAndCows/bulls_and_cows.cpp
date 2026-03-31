#include "bulls_and_cows.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#define DEBUG
int bulls_and_cows() {
	srand(static_cast<unsigned int>(time(nullptr)));
	int complication = 1, N;
	bool is_not_guessed = true;
	std::cout <<"  1 - Easy - 4 numbers\n  2 - Medium - 7 numbers\n  3 - Hard - 9 numbers\n" << "Choose complication: ";
	std::cin >> complication; 
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
		std::cout << "\nPC: I wish a number: ";
		for (int i = 0; i < N; i++) { 
			std::cout << pc_num[i]; 
		}
		std::cout << "\nUser: ";
		
		#endif

		#ifndef DEBUG
		std::cout << "\nPC: I wish a number. Try to guess it.\n" << "User: ";
		
		#endif
		std::cin >> user_input;
		if ((((pow(10, N - 1) <= user_input) && (user_input < pow(10, N))) == 0)) {
			continue;
		}
		if (check_user_input_length(user_input, N) == false) {
			throw std::invalid_argument("Incorrect number length.");
		}
		number_to_array(user_input, user_num,N);//число преобразую в массив 
		#ifdef DEBUG
		std::cout << "\n User input-array-debug : ";
		for (int i = 0; i < N; i++) {
			std::cout << user_num[i];
		}
		std::cout << "\n";
		#endif
		check_user_answer(pc_num, user_num, &is_not_guessed, N);
	} while (is_not_guessed);
	delete pc_num;
	delete user_num;
	return 0;
}