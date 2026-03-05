#ifndef PERK_H
#define PERK_H

#include <string>

class Perk
{
public:
    virtual int modifyDamage(int baseDamage) = 0;
    virtual std::string getName() = 0;
    virtual ~Perk() {}
};


// +21% damage
class Bonus21Damage : public Perk
{
public:
    int modifyDamage(int baseDamage) override;
    std::string getName() override;
};


// damage +5 flat
class FlatDamagePlus5 : public Perk
{
public:
    int modifyDamage(int baseDamage) override;
    std::string getName() override;
};


// jika blackjack (21) damage double
class BlackjackDouble : public Perk
{
public:
    int modifyDamage(int baseDamage) override;
    std::string getName() override;
};

#endif