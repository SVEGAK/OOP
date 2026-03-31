#include <iostream>
#include <iomanip>

#define BULLS_AND_COWS

#ifdef GEOMETRY
#include "geometry.h"
#include "geometry_main.cpp"
int main() {
    system("chcp 65001"); system("cls");
    geometry_main();
}
#endif

#ifdef BULLS_AND_COWS
#include "bulls_and_cows.cpp"
#include "bulls_and_cows.h"
int main() {
    system("chcp 65001"); system("cls");
    bulls_and_cows();
}
#endif