#ifndef MODIFIER_H
#define MODIFIER_H

class Modifier
{
public:

    virtual int apply(int damage)=0;

    virtual ~Modifier(){}
};

class DoubleDamage : public Modifier
{
public:

    int apply(int damage) override
    {
        return damage*2;
    }
};

class BonusDamage : public Modifier
{
public:

    int apply(int damage) override
    {
        return damage+5;
    }
};

#endif