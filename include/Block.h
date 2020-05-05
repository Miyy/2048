#ifndef MIY_2048_BLOCK
#define MIY_2048_BLOCK

class Block
{
public:
    Block();
    Block(unsigned value);

    unsigned getValue() const;

    void empty();
    void upgrade();

    void setDidCollide(bool b);

    bool isEmpty() const;
    bool getDidCollide() const;

    bool operator==(Block b) const;

private:
    unsigned value;
    bool didCollide;
};

#endif
