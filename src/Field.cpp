#include <cstdlib>
#include <vector>

#include "Field.h"
#include "Block.h"

Field::Field(unsigned sizeHorizontal, unsigned sizeVertical)
{
    this->sizeHorizontal = sizeHorizontal;
    this->sizeVertical   = sizeVertical;

    this->blocks = new Block*[sizeHorizontal];

    for (unsigned i = 0; i < sizeHorizontal; i++) {
        blocks[i] = new Block[sizeVertical];
    }

    gameOn       = true;
    score        = 0;
    biggestValue = 2;

    generateNewBlock();
}



unsigned Field::getSizeHorizontal() const
{
    return sizeHorizontal;
}



unsigned Field::getSizeVertical() const
{
    return sizeVertical;
}



Block Field::getBlock(unsigned x, unsigned y) const
{
    return blocks[x][y];
}



unsigned Field::getScore() const
{
    return score;
}



unsigned Field::getBiggestValue() const
{
    return biggestValue;
}



void Field::move(MovementType type)
{
    bool didAnyMove;

    for (unsigned x = 0; x < sizeHorizontal; x++) {
        for (unsigned y = 0; y < sizeVertical; y++) {
            blocks[x][y].setDidCollide(false);
        }
    }

    switch (type) {
        case MovementType::UP:
            didAnyMove = moveUp();
            break;
        case MovementType::LEFT:
            didAnyMove = moveLeft();
            break;
        case MovementType::DOWN:
            didAnyMove = moveDown();
            break;
        case MovementType::RIGHT:
            didAnyMove = moveRight();
            break;
    }
    if (didAnyMove) {
        generateNewBlock();
    } else {
        auto emptyBlocks = getEmptyBlocks();
        if (emptyBlocks.size() == 0) {
            gameOn = false;
        }
    }
}



bool Field::isGameOn() const
{
    return gameOn;
}



Field::~Field()
{
    for (unsigned i = 0; i < sizeHorizontal; i++) {
        delete blocks[i];
    }
    delete blocks;
}



unsigned Field::checkMovementUp(unsigned x, unsigned y) const
{
    unsigned res = 0;
    int i;
    for (unsigned k = y; k > 0;  k--) {
        i = k - 1;
        if (blocks[x][i].isEmpty()) {
            ++res;
        } else {
            break;
        }
    }
    return res;
}



unsigned Field::checkMovementLeft(unsigned x, unsigned y) const
{
    unsigned res = 0;
    int i;
    for (unsigned k = x; k > 0;  k--) {
        i = k - 1;
        if (blocks[i][y].isEmpty()) {
            ++res;
        } else {
            break;
        }
    }
    return res;
}



unsigned Field::checkMovementDown(unsigned x, unsigned y) const
{
    unsigned res = 0;
    for (unsigned i = y + 1; i < sizeVertical;  i++) {
        if (blocks[x][i].isEmpty()) {
            ++res;
        } else {
            break;
        }
    }
    return res;
}



unsigned Field::checkMovementRight(unsigned x, unsigned y) const
{
    unsigned res = 0;
    for (unsigned i = x + 1; i < sizeHorizontal; i++) {
        if (blocks[i][y].isEmpty()) {
            ++res;
        } else {
            break;
        }
    }
    return res;
}



bool Field::moveUp()
{
    bool didAnyMove = false;
    for (unsigned y = 1; y < sizeVertical; y++) {
        for (unsigned x = 0; x < sizeHorizontal; x++) {
            if (blocks[x][y].isEmpty()) {
                continue;
            }

            int m = checkMovementUp(x, y);
            if (m == y) {
                didAnyMove = moveBlock(x, y, x, 0);
            } else if (blocks[x][y - m - 1] == blocks[x][y] &&
                !blocks[x][y - m - 1].getDidCollide()) {
                didAnyMove = collideBlock(x, y, x, y - m - 1);
            } else if (m != 0) {
                didAnyMove = moveBlock(x, y, x, y - m);
            }
        }
    }
    return didAnyMove;
}



bool Field::moveLeft()
{
    bool didAnyMove = false;
    for (unsigned x = 1; x < sizeHorizontal; x++) {
        for (unsigned y = 0; y < sizeVertical; y++) {
            if (blocks[x][y].isEmpty()) {
                continue;
            }

            int m = checkMovementLeft(x, y);
            if (m == x) {
                didAnyMove = moveBlock(x, y, 0, y);
            } else if (blocks[x - m - 1][y] == blocks[x][y] &&
                !blocks[x - m - 1][y].getDidCollide()) {
                didAnyMove = collideBlock(x, y, x - m - 1, y);
            } else if (m != 0) {
                didAnyMove = moveBlock(x, y, x - m, y);
            }
        }
    }
    return didAnyMove;
}



bool Field::moveDown()
{
    bool didAnyMove = false;
    for (unsigned i = sizeVertical - 1; i > 0; i--) {
        unsigned y = i - 1;
        for (unsigned x = 0; x < sizeHorizontal; x++) {
            if (blocks[x][y].isEmpty()) {
                continue;
            }

            int m = checkMovementDown(x, y);
            if (m == sizeVertical - 1 - y) {
                didAnyMove = moveBlock(x, y, x, sizeVertical - 1);
            } else if (blocks[x][y + m + 1] == blocks[x][y] &&
                !blocks[x][y + m + 1].getDidCollide()) {
                didAnyMove = collideBlock(x, y, x, y + m + 1);
            } else if (m != 0) {
                didAnyMove = moveBlock(x, y, x, y + m);
            }
        }
    }
    return didAnyMove;
}



bool Field::moveRight()
{
    bool didAnyMove = false;
    for (unsigned i = sizeHorizontal - 1; i > 0; i--) {
        unsigned x = i - 1;
        for (unsigned y = 0; y < sizeVertical; y++) {
            if (blocks[x][y].isEmpty()) {
                continue;
            }

            int m = checkMovementRight(x, y);
            if (m == sizeHorizontal - 1 - x) {
                didAnyMove = moveBlock(x, y, sizeHorizontal - 1, y);
            } else if (blocks[x + m + 1][y] == blocks[x][y] &&
                !blocks[x + m + 1][y].getDidCollide()) {
                didAnyMove = collideBlock(x, y, x + m + 1, y);
            } else if (m != 0) {
                didAnyMove = moveBlock(x, y, x + m, y);
            }
        }
    }
    return didAnyMove;
}



bool Field::moveBlock(unsigned x1, unsigned y1, unsigned x2, unsigned y2)
{
    blocks[x2][y2] = blocks[x1][y1];
    blocks[x1][y1].empty();
    return true;
}



bool Field::collideBlock(unsigned x1, unsigned y1, unsigned x2, unsigned y2)
{
    blocks[x1][y1].empty();
    blocks[x2][y2].upgrade();
    if (blocks[x2][y2].getValue() > biggestValue) {
        biggestValue = blocks[x2][y2].getValue();
    }
    score += blocks[x2][y2].getValue();
    blocks[x2][y2].setDidCollide(true);
    return true;
}



std::vector<Block*> Field::getEmptyBlocks()
{
    std::vector<Block*> res;
    for (unsigned x = 0; x < sizeHorizontal; x++) {
        for (unsigned y = 0; y < sizeVertical; y++) {
            if (blocks[x][y].isEmpty()) {
                res.push_back(&blocks[x][y]);
            }
        }
    }
    return res;
}



void Field::generateNewBlock()
{
    auto emptyBlocks = getEmptyBlocks();
    unsigned x = rand() % emptyBlocks.size();
    *emptyBlocks.at(x) = Block(2);
}
