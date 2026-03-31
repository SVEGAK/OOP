#include "functions.cpp"
#include "geometry.h"
#include <iostream>
#include <iomanip>
int geometry_main() {
    Circle circle1;
    Circle circle2;
    std::cout << "Input first circle: ";
    std::cin >> circle1.center.x;
    std::cin >> circle1.center.y;
    std::cin >> circle1.r;
    std::cout << "Your first circle: " << "( " << circle1.center.x << ", " << circle1.center.y << ") " << circle1.r << "\n";

    std::cout << "Input second circle: ";
    std::cin >> circle2.center.x;
    std::cin >> circle2.center.y;
    std::cin >> circle2.r;
    std::cout << "Your second circle: " << "( " << circle2.center.x << ", " << circle2.center.y << ") " << circle2.r << "\n";
    system("cls");

    switch (get_position(circle1, circle2)) {
    case 0:
        std::cout << "Not-related - не пересекаются.";
        break;
    case 1:
        std::cout << "Intersection - пересекаются. ";
        break;
    case 2:
        std::cout << "Equal - совпадают. ";
        break;
    case 3:
        std::cout << "Touch - касаются. ";
        break;
    case 4:
        std::cout << "One inside the another - одна внутри другой. ";
        break;
    case 5:
        std::cout << "NONE - error. ";
        break;
    default:
        std::cout << "No response - error. ";
        break;
    }
    std::cout << "\n" << "Your first circle: " << "( " << circle1.center.x << ", " << circle1.center.y << ") " << circle1.r << "\n";
    std::cout << "Your second circle: " << "( " << circle2.center.x << ", " << circle2.center.y << ") " << circle2.r << "\n";
    return 0;
}