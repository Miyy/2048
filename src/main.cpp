#include <iostream>

#include "Field.h"
#include "draw.h"

int main() {
    Field f(4, 4);
    char input = 0;
    draw(f);
    while (f.isGameOn()) {
        std::cin >> input;
        switch (input) {
            case 'w':
                f.move(MovementType::UP);
                break;
            case 'a':
                f.move(MovementType::LEFT);
                break;
            case 's':
                f.move(MovementType::DOWN);
                break;
            case 'd':
                f.move(MovementType::RIGHT);
                break;
            case 'e':
                return 0;
        }
        draw(f);
    }
    return 0;
}
