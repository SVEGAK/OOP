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
    std::cout << "Your first circle: " << "(" << circle1.center.x << ", " << circle1.center.y << ") " << circle1.r << "\n";

    std::cout << "Input second circle: ";
    std::cin >> circle2.center.x;
    std::cin >> circle2.center.y;
    std::cin >> circle2.r;
    std::cout << "Your second circle: " << "(" << circle2.center.x << ", " << circle2.center.y << ") " << circle2.r << "\n";
    system("cls");
    std::cout << "\n" << "Your first circle: " << "(" << circle1.center.x << ", " << circle1.center.y << ") " << circle1.r << "\n";
    std::cout << "Your second circle: " << "(" << circle2.center.x << ", " << circle2.center.y << ") " << circle2.r << "\n";
    switch (get_position(circle1, circle2)) {
    case 0:
        std::cout << "╔══════════════════════════════════╗\n";
        std::cout << "║  Not-related - не пересекаются.  ║\n";
        std::cout << "╚══════════════════════════════════╝\n";
        break;

    case 1:
        std::cout << "╔════════════════════════════════╗\n";
        std::cout << "║  Intersection - пересекаются.  ║\n";
        std::cout << "╚════════════════════════════════╝\n";
        break;

    case 2:
        std::cout << "╔══════════════════════╗\n";
        std::cout << "║  Equal - совпадают.  ║\n";
        std::cout << "╚══════════════════════╝\n";
        break;

    case 3:
        std::cout << "╔═════════════════════╗\n";
        std::cout << "║  Touch - касаются.  ║\n";
        std::cout << "╚═════════════════════╝\n";
        break;

    case 4:
        std::cout << "╔════════════════════════════════════════════════╗\n";
        std::cout << "║  One inside the another - одна внутри другой.  ║\n";
        std::cout << "╚════════════════════════════════════════════════╝\n";
        break;

    case 5:
        std::cout << "╔═════════════════╗\n";
        std::cout << "║  NONE - error.  ║\n";
        std::cout << "╚═════════════════╝\n";
        break;

    default:
        std::cout << "╔════════════════════════╗\n";
        std::cout << "║  No response - error.  ║\n";
        std::cout << "╚════════════════════════╝\n";
        break;
    }
    return 0;
}