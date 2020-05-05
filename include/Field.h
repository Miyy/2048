#ifndef MIY_2048_FIELD
#define MIY_2048_FIELD

#include <vector>

#include "Block.h"

enum class MovementType
{
    UP, LEFT, DOWN, RIGHT
};

class Field
{
public:
    Field(unsigned sizeHorizontal, unsigned sizeVertical);

    unsigned getSizeHorizontal() const;
    unsigned getSizeVertical()   const;

    Block getBlock(unsigned x, unsigned y) const;
    
    unsigned getScore() const;
    unsigned getBiggestValue() const;

    void move(MovementType type);

    bool isGameOn() const;

    ~Field();

private:
    unsigned sizeHorizontal;
    unsigned sizeVertical;
    Block    **blocks;
    bool     gameOn;
    unsigned score;
    unsigned biggestValue;

    unsigned checkMovementUp(unsigned x, unsigned y) const;
    unsigned checkMovementLeft(unsigned x, unsigned y) const;
    unsigned checkMovementDown(unsigned x, unsigned y) const;
    unsigned checkMovementRight(unsigned x, unsigned y) const;

    bool moveUp();
    bool moveLeft();
    bool moveDown();
    bool moveRight();

    bool moveBlock(unsigned x1, unsigned y1, unsigned x2, unsigned y2);
    bool collideBlock(unsigned x1, unsigned y1, unsigned x2, unsigned y2);

    std::vector<Block*> getEmptyBlocks();
    void generateNewBlock();
};

#endif
