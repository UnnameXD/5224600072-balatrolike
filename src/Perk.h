#ifndef PERK_H
#define PERK_H

class Perk
{
public:
    virtual int apply(int damage) = 0;
    virtual ~Perk() {}
};

class Bonus21Damage : public Perk
{
public:
    int apply(int damage) override;
};

#endif