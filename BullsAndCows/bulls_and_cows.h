#pragma once
#include <stdbool.h>
#include <iostream>
#define DEBUG
void shake_mass(int* mass, int len) {
	for (int i = 0; i < len; i++) {
		int new_i = rand() % len;
		int other = mass[new_i];
		mass[new_i] = mass[i];
		mass[i] = other;
	}
}
void number_to_array(int user_input,int* user_num, int len){
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
void check_user_answer(int *pc_num,int *user_num, bool *is_not_guessed, int len) {
	int bulls_count = 0;
	int* possible_cows = new int[len];
	int* other_pc_nums = new int[len];
	int cows_count = 0;
	int p = 0;
	for (int i = 0; i < len; i++) {//подсчет быков
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
	std::cout <<"\nbulls_count-debug : " << bulls_count;
	#endif
	if (len == bulls_count) {
		std::cout << "\nCorrect!";
		*is_not_guessed = false;
		delete other_pc_nums;
		delete possible_cows;
		return;
	}
	int cows_count_possible = len-bulls_count; 
	possible_cows = (int*)realloc(possible_cows, cows_count_possible *sizeof(int));
	other_pc_nums = (int*)realloc(other_pc_nums, cows_count_possible * sizeof(int));

	for (int i = 0; i < cows_count_possible; i++) { //убираем повторяющиеся цифры
		for (int j = i+1; j < cows_count_possible; j++) {
			if (possible_cows[i] == possible_cows[j]) {
				for (int k = j; j < cows_count_possible - 1; j++) {
					possible_cows[k] = possible_cows[k + 1];
				}
				cows_count_possible--;//тк убрали 1 повторяющееся значение
				
			}
		}
	}
	possible_cows = (int*)realloc(possible_cows, cows_count_possible * sizeof(int));//убираем лишние ячейки в конце массива
	#ifdef DEBUG
	std::cout <<"\n" << cows_count_possible << "<- cows_count_possible\n"<< "possible cows array :";
	for (int i = 0; i <cows_count_possible; i++) {
		std::cout << possible_cows[i];
	}
	std::cout << "\n other_pc_nums array -> ";
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
	std::cout << "\n Bulls count: " << bulls_count << " Cows count: " << cows_count;
	delete other_pc_nums;
	delete possible_cows;
	return;
}