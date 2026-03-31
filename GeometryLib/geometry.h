#pragma once

struct Point {
    int x;
    int y;
};
struct Circle {
    Point center;
    int r;
};

enum Positions { NOT_RELATED, INTERSECTION, EQUAL, TOUCH, ONE_INSIDE_THE_ANOTHER, NONE };

Positions get_position(Circle C1, Circle C2);