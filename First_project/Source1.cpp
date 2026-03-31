#include <iostream>
#include <iomanip>
#include <cmath>
struct Point {
    int x;
    int y;
};
struct Circle {
    Point center;
    int r;
};

enum Positions { NON_RELATED, INTERSECTION, EQUAL, TOUCH, ONE_INSIDE_THE_ANOTHER, NONE };
Positions get_position(Circle C1, Circle C2) {
    float d = sqrt(pow(C1.center.x - C2.center.x, 2) + pow(C1.center.y - C2.center.y, 2));
    char answer = NONE;
    if (C1.r + C2.r < d) {
        answer = NON_RELATED;
    }
    if (C1.r == C2.r) {
        if ((C1.center.x == C2.center.x) && (C1.center.y == C2.center.y)) {
            return EQUAL;
        }
    }

    if (C1.r + C2.r == d) {
        return TOUCH;
    }
    if (C1.r + C2.r < d) {
        return INTERSECTION;
    }
    if ((C1.r < d) || (C2.r < d)) {
        return ONE_INSIDE_THE_ANOTHER;
    }
}
int main() {
    Circle circle1;
    Circle circle2;
    std::cout << "chcp 65001";
    std::cout << "Input first circle: ";
    std::cin >> circle1.center.x;
    std::cin >> circle1.center.y;
    std::cin >> circle1.r;
    std::cout << "Your first circle: " << "( " << circle1.center.x << ", " << circle1.center.y << ") " << circle1.r;

    std::cout << "Input second circle: ";
    std::cin >> circle2.center.x;
    std::cin >> circle2.center.y;
    std::cin >> circle2.r;
    std::cout << "Your first circle: " << "( " << circle2.center.x << ", " << circle2.center.y << ") " << circle2.r;

    std::cout << get_position(circle1, circle2);

}