#include "pch.h"
#include "main_test_func.h"
//#include "geometry.h"
Positions get_position(Circle C1, Circle C2) {
    float d = sqrt(pow(C1.center.x - C2.center.x, 2) + pow(C1.center.y - C2.center.y, 2));
    Positions answer = NONE;
    if (d > C1.r + C2.r) { //не пересекаются
        answer = NOT_RELATED;
    }
    else  if (C1.r + C2.r == d) { //касаются
        answer = TOUCH;
    }
    else if (C1.r > C2.r) {
        if (C1.r - C2.r < d) {// пересекаются 
            answer =  INTERSECTION;
        }
    }
    else {
        if (C2.r - C1.r < d) {// пересекаются 
            answer = INTERSECTION;
        }
    }
    if (C1.r == C2.r) { // совпадают
        if ((C1.center.x == C2.center.x) && (C1.center.y == C2.center.y)) {
            answer = EQUAL;
        }
    }
    else if (d <= abs(C1.r - C2.r)) { //одна вписана в другую
        answer = ONE_INSIDE_THE_ANOTHER;
    }
    return answer;
}