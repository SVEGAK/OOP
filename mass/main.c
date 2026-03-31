#include <stdio.h>
#include "menu.h"
#include "dmassive.h"
#include <locale.h>

int main() {
	system("chcp 65001 >nul");
	srand(time(NULL));
	main_menu();
	return 7;
}