#include <stdio.h>
#include <stdlib.h>
#include "windows.h"
#include "utilits.h"
void setCursor(int line, int column){
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void getCursor(int* line, int* column) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        *column = csbi.dwCursorPosition.X;
        *line = csbi.dwCursorPosition.Y;
    } else {    
        *column = 0;
        *line = 0;
    }
}