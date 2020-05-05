#include "Block.h"

Block::Block()
{
    value = 0;
}



Block::Block(unsigned value)
{
    this->value = value;
}



unsigned Block::getValue() const
{
    return value;
}



void Block::empty()
{
    value = 0;
}



void Block::upgrade()
{
    value *= 2;
    didCollide = true;
}



void Block::setDidCollide(bool b)
{
    didCollide = b;
}



bool Block::isEmpty() const
{
    return (value == 0);
}



bool Block::getDidCollide() const
{
    return didCollide;
}



bool Block::operator==(Block b) const
{
    return (this->value == b.value);
}
