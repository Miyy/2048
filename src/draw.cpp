#include <iostream>
#include <iomanip>

#include "draw.h"
#include "Field.h"
#include "Block.h"

unsigned getDigitsNumber(unsigned n)
{
    unsigned res = 0;

    do {
        n /= 10;
        ++res;
    } while (n != 0);

    return res;
}

void draw(const Field& field)
{
    unsigned width = getDigitsNumber(field.getBiggestValue());

    std::cout << "#";

    for (unsigned i = 0; i < field.getSizeHorizontal(); i++) {
        std::cout << std::setfill('#') << std::setw(width) << "#";
        std::cout << "#";
    }

    std::cout << std::endl << std::setfill(' ');

    for (unsigned y = 0; y < field.getSizeVertical(); y++) {
        std::cout << "#";
        for (unsigned x = 0; x < field.getSizeHorizontal() - 1; x++) {
            if (field.getBlock(x, y).isEmpty()) {
                std::cout << std::setw(width) << " " << "|";
            } else {
                std::cout << std::setw(width) <<
                field.getBlock(x, y).getValue() << "|";
            }
        }
        if (field.getBlock(field.getSizeHorizontal() - 1, y).isEmpty()) {
            std::cout << std::setw(width) << " ";
        } else {
            std::cout << std::setw(width) <<
            field.getBlock(field.getSizeHorizontal() - 1, y).getValue();
        }
        std::cout << "#" << std::endl;
    }

    std::cout << "#";

    for (unsigned i = 0; i < field.getSizeHorizontal(); i++) {
        std::cout << std::setfill('#') << std::setw(width) << "#";
        std::cout << "#";
    }

    std::cout << std::endl;

    std::cout << "\n" << "Score: " << field.getScore() << std::endl;
}
